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
        while ((h = json_next_key(buf, sz, h, "", &key, &val)) != NULL) {
            snprintf(buf_s, sizeof(buf_s), "[%.*s] -> [%.*s]",key.len,key.ptr,val.len,val.ptr);
      //      ASSERT(strcmp(results[i], buf) == 0);

            printf("Key [%s]\n",  buf_s);
            void *k = NULL;
            struct json_token key_in, val_in;
            val.ptr = val.ptr+1;
            val.len = val.len-1;
            while ((k = json_next_key(val.ptr, val.len, k, "", &key_in, &val_in)) != NULL) {
                snprintf(buf_s, sizeof(buf_s), "[%.*s] -> [%.*s]", key_in.len, key_in.ptr, val_in.len,
                         val_in.ptr);
                printf("Key [%s]\n",  buf_s);
                k = val_in.ptr + val_in.len + 2;
                val.ptr = k;
                k = NULL;
                val.len = val.len - key_in.len - val_in.len;
            }
        }
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
        while ((h = json_next_key(buf, sz, h, "", &key, &val)) != NULL) {
            snprintf(buf_s, sizeof(buf_s), "[%.*s] -> [%.*s]",key.len,key.ptr,val.len,val.ptr);
      //      ASSERT(strcmp(results[i], buf) == 0);

            printf("Key [%s]\n",  buf_s);
            void *k = NULL;
            struct json_token key_in, val_in;
            val.ptr = val.ptr+1;
            val.len = val.len-1;
            while ((k = json_next_key(val.ptr, val.len, k, "", &key_in, &val_in)) != NULL) {
                snprintf(buf_s, sizeof(buf_s), "[%.*s] -> [%.*s]", key_in.len, key_in.ptr, val_in.len,
                         val_in.ptr);
                printf("Key [%s]\n",  buf_s);
                k = val_in.ptr + val_in.len + 2;
                val.ptr = k;
                k = NULL;
                val.len = val.len - key_in.len - val_in.len;
            }
        }
    }
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
