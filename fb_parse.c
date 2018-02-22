#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>
#include "frozen.h"
#include "vars.h"
#include "kernel.h"
#include "regs.h"
#include "fb_parse.h"
#include "fb_config.h"
struct fb_branch* branch_array;
struct fb_visual* fb_array;
int branch_number_in_array;
int fb_number_in_array;
static uint8_t parse_branch(char* addr_ptr,char addr_len,u16 address);
void print_branch(void);
#define FAIL(str, line)                           \
  do {                                            \
    printf("Fail on line %d: [%s]\n", line, str); \
    return str;                                   \
  } while (0)

#define ASSERT(expr)                    \
  do {                                  \
    static_num_tests++;                 \
    if (!(expr)) FAIL(#expr, __LINE__); \
  } while (0)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define RUN_TEST(test)        \
  do {                        \
    const char *msg = test(); \
    if (msg) return msg;      \
  } while (0)


char parse_json_fb_array_file(const char *path){
    /*
    parse array config array file for branch on scheme

                *-----------.
                            |
                            |
                            '------------>

    */
    char *buf;
    char *buf_t;
    struct json_token key, val;
    u32 address_number;
    u32 branch_number;
    branch_number = 0;
    char buf_s[200];
    printf("==== %s ====\n", path);
    FILE *file = fopen(path, "r");
//    fd = open(path, O_RDONLY);
    if (file==NULL) {
        printf("==== did't open file %s ====\n", path);
        return 0;
    }else{
        u32 sz;
        fseek(file, 0L, SEEK_END);
        sz = ftell(file);
        buf = malloc(sizeof(char)*sz);
        fseek(file, 0L, SEEK_SET);
        printf("json file size - %u",sz);
        fread(buf,1,sz,file);
        void *h = NULL;
        while ((h = json_next_key(buf, sz, h, "", &key, &val)) != NULL) {
        	//find address number
            address_number = atoi(val.ptr);
        }
        buf_t = val.ptr + val.len + 1;
        printf("address number %i",address_number);
        sz -= (buf_t - buf);
        while ((h = json_next_key(buf_t, sz, h, "", &key, &val)) != NULL) {
        	u8 ti;
        	//find branch number
            ti = atoi(val.ptr+1);
            if(ti>1){
            	branch_number+=(ti-1);
            }
        }
        printf("branch number %i",branch_number);
        branch_array = malloc(branch_number*sizeof(struct fb_branch));
        branch_number_in_array = 0;
        while ((h = json_next_key(buf_t, sz, h, "", &key, &val)) != NULL){
        	u16 address;
        	address = atoi(key.ptr);
            parse_branch(val.ptr,val.len,address);
        }
        print_branch();
    }
}
uint8_t parse_branch(char* addr_ptr,char addr_len,u16 branch_address){
	int id_i=0;
    u32 current_branch_number ;
    void *h = NULL;
    char buf_s[200];
    current_branch_number = atoi(addr_ptr+1);
    if(current_branch_number >1){
    	struct json_token  val_b;
    	int input_num_for_addr = 0;
    	int id = 0;
        for (u16 tb=0;tb<=current_branch_number ;tb++){
            if((h = json_next_elem(addr_ptr, addr_len, h, "", &id, &val_b))!=NULL){
            	struct json_token val_i;
                if(tb>0){
                	uint16_t fb_type,gate_number;
                	uint32_t order_number;
                	char *direction;
                	for (u16 j=0;j<4;j++){
                	/*
                	 * fb type
                	 * order number
                	 * direction
                	 * gate number
                	 */
                	   if((h = json_next_elem(val_b.ptr, val_b.len, h, "", &id_i, &val_i))!=NULL){
                		   switch(j){
                		   case(0):
								   fb_type = atoi(val_i.ptr);
                				   break;
                		   case(1):
								   order_number = atoi(val_i.ptr);
                				   break;
                		   case(2):
								   direction = val_i.ptr;
                				   break;
                		   case(3):
								   gate_number = atoi(val_i.ptr);
                				   break;
                		   }
                	   }else{
                		   printf("element of branch lower then wrote",  buf_s);
                		   break;
                	   }
                	}
                	if (strncmp((char*)(direction), "input",5)==0){
                		branch_array[branch_number_in_array+input_num_for_addr].input_gate_number = gate_number;
                		branch_array[branch_number_in_array+input_num_for_addr].input_fb_number = order_number;
                		branch_array[branch_number_in_array+input_num_for_addr].address = branch_address;
                		input_num_for_addr++;
                	}else if (strncmp((char*)(direction), "output",6)==0){
                		for (int k=0;k<(current_branch_number-1);k++){
							branch_array[branch_number_in_array+k].output_gate_number = gate_number;
							branch_array[branch_number_in_array+k].output_fb_number = order_number;
                		}
                	}
                }
            }else{
            	printf("element of branch lower then wrote",  buf_s);
                break;
            }
        }
        branch_number_in_array +=input_num_for_addr;
    }
	return 0;
}
void print_branch(void){
	for (int i = 0;i<branch_number_in_array ;i++){
		printf("Branch - %i\n",i);
		printf("Output fb order-%i gate number-%i\n",branch_array[i].output_fb_number,branch_array[i].output_gate_number);
		printf("Input fb order-%i gate number-%i\n",branch_array[i].input_fb_number,branch_array[i].input_gate_number);
	}
}
char parse_json_fb_file(const char *path){
    uint32_t fd, status;
    char *buf;
    uint64_t nread;
    struct json_token key, val;
    char buf_s[200];
    printf("==== %s ====\n", path);
    uint32_t idx;
    FILE *file = fopen(path, "r");
//    fd = open(path, O_RDONLY);
    if (file==NULL) {
        printf("==== did't open file %s ====\n", path);
        return 0;
    }else{
        u32 sz;
        fseek(file, 0L, SEEK_END);
        sz = ftell(file);
        buf = malloc(sizeof(char)*sz);
        fseek(file, 0L, SEEK_SET);
        printf("json file size - %u",sz);
        fread(buf,1,sz,file);
        void *h = NULL;
        fb_number_in_array = 0;
        while ((h = json_next_key(buf, sz, h, "", &key, &val)) != NULL){
        	fb_number_in_array++;
        }
        h = NULL;
        fb_array = malloc(fb_number_in_array*sizeof(struct fb_visual));
        while ((h = json_next_key(buf, sz, h, "", &key, &val)) != NULL){
        	u32 order;
        	order = atoi(key.ptr);
        	parse_fb(val.ptr,val.len,order);
        }
        printf("fb numm %i ",fb_number_in_array);
    }
}
uint8_t parse_fb(char* fb_ptr,char fb_len){
	int id_i=0;
    u32 current_branch_number ;
    struct fb_branch temp_branch;
    void *h = NULL;
    char buf_s[200];
    current_branch_number = atoi(addr_ptr+1);
    if(current_branch_number >1){
    	struct json_token  val_b;
    	int input_num_for_addr = 0;
    	int id = 0;
        for (u16 tb=0;tb<=current_branch_number ;tb++){
            if((h = json_next_elem(addr_ptr, addr_len, h, "", &id, &val_b))!=NULL){
            	struct json_token val_i;
                if(tb>0){
                	uint16_t fb_type,gate_number;
                	uint32_t order_number;
                	char *direction;
                	for (u16 j=0;j<4;j++){
                	/*
                	 * fb type
                	 * order number
                	 * direction
                	 * gate number
                	 */
                	   if((h = json_next_elem(val_b.ptr, val_b.len, h, "", &id_i, &val_i))!=NULL){
                		   switch(j){
                		   case(0):
								   fb_type = atoi(val_i.ptr);
                				   break;
                		   case(1):
								   order_number = atoi(val_i.ptr);
                				   break;
                		   case(2):
								   direction = val_i.ptr;
                				   break;
                		   case(3):
								   gate_number = atoi(val_i.ptr);
                				   break;
                		   }
                	   }else{
                		   printf("element of branch lower then wrote",  buf_s);
                		   break;
                	   }
                	}
                	if (strncmp((char*)(direction), "input",5)==0){
                		branch_array[branch_number_in_array+input_num_for_addr].input_gate_number = gate_number;
                		branch_array[branch_number_in_array+input_num_for_addr].input_fb_number = order_number;
                		input_num_for_addr++;
                	}else if (strncmp((char*)(direction), "output",6)==0){
                		for (int k=0;k<(current_branch_number-1);k++){
							branch_array[branch_number_in_array+k].output_gate_number = gate_number;
							branch_array[branch_number_in_array+k].output_fb_number = order_number;
                		}
                	}
                }
            }else{
            	printf("element of branch lower then wrote",  buf_s);
                break;
            }
        }
        branch_number_in_array +=input_num_for_addr;
    }
	return 0;
}

uint32_t parse_fb32_file(const char *path,char* pFB){
    FILE *file = fopen(path, "r");
    if (file==NULL){
        printf(" error open config file\n");
        KernelInfo.CfgSize=0;
    }else{
        u32 sz;
        fseek(file, 0L, SEEK_END);
        sz = ftell(file);
        pFB = malloc(sizeof(char)*sz);
        fseek(file, 0L, SEEK_SET);
        printf("config file size - %u",sz);
        fread(pFB,1,sz,file);
        ConfigHead_t ConfigHead;
        SectionHead_t SectionHead;
        memcpy(&ConfigHead,pFB,sizeof(ConfigHead));
        for(u16 i=0;i<sz;i++){
            printf("%X ",(u8)pFB[i]);
        }
        if((ConfigHead.Size>8)&&(ConfigHead.Size<=sz)){
            u16 temp_crc;
            u16 crc;
            printf(" find config with size %i \n",ConfigHead.Size);
            printf("crc %i %i %i %i \n",pFB[ConfigHead.Size-4],pFB[ConfigHead.Size-3],pFB[ConfigHead.Size-2],pFB[ConfigHead.Size-1]);
            memcpy(&temp_crc,&pFB[ConfigHead.Size-2],sizeof(u16));
            crc = check_file_crc(pFB,ConfigHead.Size-2);
            if (temp_crc == crc){
                printf(" crc correct - %i \n",temp_crc);
                printf(" ConfigHead.SectionNumber - %u \n",ConfigHead.SectionNumber);
                for (u16 k=0;k<ConfigHead.SectionNumber;k++){
                    memcpy(&SectionHead,(pFB+sizeof(ConfigHead_t)+sizeof(SectionHead_t)*k),sizeof(SectionHead));
                    if (SectionHead.Type != BINAR_CONFIG_TYPE){
                        continue;
                    }
                    KernelInfo.CfgSize = SectionHead.LengthSection-2;
                    printf("SectionHead.LengthSection %u\n",(u16)SectionHead.LengthSection);
                    KernelInfo.pStartCFG = (char*)(pFB+SectionHead.Pozition);
                    printf("kernel start position %u\n",(u16)SectionHead.Pozition);
                    pCFG = (u8*)(KernelInfo.pStartCFG);
                    KernelInfo.CfgSize=ReadInt16Cfg()-2;
                    printf("KernelInfo.CfgSize %u\n",(u16)KernelInfo.CfgSize);
                    KernelInfo.CfgTWICommSize=ReadInt16Cfg();
                    printf("KernelInfo.CfgTWICommSize %u\n",(u16)KernelInfo.CfgTWICommSize);
                    pCFG +=KernelInfo.CfgTWICommSize;
                    KernelInfo.FBCfgSize=ReadInt16Cfg();
                    printf("KernelInfo.FBCfgSize %u\n",(u16)KernelInfo.FBCfgSize);
                    KernelInfo.FBkernelRate = *pCFG;
                    printf("KernelInfo.FBkernelRate %u\n",(u16)KernelInfo.FBkernelRate);
                }
            }else{
                printf(" crc not correct ,from file %i, decided %i \n",temp_crc,crc);
            }
        }else{
            printf("file size not correct - %i",ConfigHead.Size);
        }
    }
    return 0;
}
uint32_t first_cycle(void){
    vu16 CodeFB;
    u16 k;
    u32 fb_number;
    fb_number = 0;
    pCFG = (u8*)((u32)(KernelInfo.pStartCFG) + KernelInfo.CfgTWICommSize+7);
    do{
        if(pCFG < (u8*)((u32)(KernelInfo.pStartCFG) + KernelInfo.CfgSize)){
            fb_number++;
            CodeFB=ReadInt16Cfg();
#if DEBUG_LOAD
            printf("fb number %u",(u16)CodeFB);
#endif
            FB_N_In=FB_N_Out=FB_N_Vars=0;
            pCFG_temp=0;
            LoadFBRegister();
            if(CodeFB<124){
                fb_exec[CodeFB]();
            }else{
                FB32blok.vars.ErrCodFB |= 1<<FB_ERROR;
            }
            if(pCFG_temp){pCFG=pCFG_temp;}
            FB_N_Out=FB_N_Vars=0;
            SaveFBRegister();
            pCFG++;
            KernelInfo.pCFG = pCFG;
        }
    }while (pCFG < (u8*)((u32)(KernelInfo.pStartCFG) + KernelInfo.CfgSize));
}
