/* nuklear - 1.32.0 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_SDL_GL2_IMPLEMENTATION
#include "node_editor.h"
#include "nuklear_sdl_gl2.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600

#define UNUSED(a) (void)a
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) < (b) ? (b) : (a))
#define LEN(a) (sizeof(a)/sizeof(a)[0])

#define DEBUG 1

/* ===============================================================
 *
 *                          EXAMPLE
 *
 * ===============================================================*/
/* This are some code examples to provide a small overview of what can be
 * done with this library. To try out an example uncomment the include
 * and the corresponding function. */
#include "style.c"
#include "vars.h"
#include "kernel.h"
#include "jsonsl.h"
#include "json-datatypes.h"

extern u8* pStartCfg;
extern u8* pCFG;
extern u8* pCFG_temp;
extern vu16 FB_N_In, FB_N_Out, FB_N_Vars;
extern vu32 CfgStartTime;
extern vu8 CntCfg1SecExec;
extern u16 queue_status_for_modbus;

KernelInfo_t KernelInfo;
FB32_type FB32blok;
u32 cntSecFromStart;

/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/
int
main(int argc, char* argv[]){
    printf(" start  \n");
    u64 second_timer,clock_time,clock_timer;
    cntSecFromStart = 0;
    /* Platform */
    SDL_Window *win;
    SDL_GLContext glContext;
    struct nk_color background;
    int win_width, win_height;
    int running = 1;
    /* GUI */
    struct nk_context *ctx;
    char* pFB;
    FILE *file = fopen(argv[1], "r");
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
        fread(pFB,1, sz,file);
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
        json_parser(argv[2]);
    }

    /* SDL setup */
    SDL_SetHint(SDL_HINT_VIDEO_HIGHDPI_DISABLED, "0");
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    win = SDL_CreateWindow("Demo",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN|SDL_WINDOW_ALLOW_HIGHDPI);
    glContext = SDL_GL_CreateContext(win);
    SDL_GetWindowSize(win, &win_width, &win_height);

    /* GUI */
    ctx = nk_sdl_init(win);
    /* Load Fonts: if none of these are loaded a default font will be used  */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    {struct nk_font_atlas *atlas;
    nk_sdl_font_stash_begin(&atlas);
    /*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
    /*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16, 0);*/
    /*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
    /*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
    /*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
    /*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
    nk_sdl_font_stash_end();
    /*nk_style_load_all_cursors(ctx, atlas->cursors);*/
    /*nk_style_set_font(ctx, &roboto->handle)*/;}

    /* style.c */
    /*set_style(ctx, THEME_WHITE);*/
    /*set_style(ctx, THEME_RED);*/
    /*set_style(ctx, THEME_BLUE);*/

    set_style(ctx, 4);
    second_timer = clock();
    clock_time = clock();
    clock_timer = clock_time;
    background = nk_rgb(28,48,62);
    while (running)
    {
        /* Input */
        SDL_Event evt;
        nk_input_begin(ctx);
        clock_timer = clock();

        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) goto cleanup;
            nk_sdl_handle_event(&evt);
        }
        nk_input_end(ctx);

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 210, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            enum {EASY, HARD};
            static int op = EASY;
            static int property = 20;

            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "button"))
                fprintf(stdout, "button pressed\n");
            nk_layout_row_dynamic(ctx, 30, 2);
            if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
            if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "background:", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            if (nk_combo_begin_color(ctx, background, nk_vec2(nk_widget_width(ctx),400))) {
                nk_layout_row_dynamic(ctx, 120, 1);
                background = nk_color_picker(ctx, background, NK_RGBA);
                nk_layout_row_dynamic(ctx, 25, 1);
                background.r = (nk_byte)nk_propertyi(ctx, "#R:", 0, background.r, 255, 1,1);
                background.g = (nk_byte)nk_propertyi(ctx, "#G:", 0, background.g, 255, 1,1);
                background.b = (nk_byte)nk_propertyi(ctx, "#B:", 0, background.b, 255, 1,1);
                background.a = (nk_byte)nk_propertyi(ctx, "#A:", 0, background.a, 255, 1,1);
                nk_combo_end(ctx);
            }
        }
        nk_end(ctx);

        /* -------------- EXAMPLES ---------------- */
        /*calculator(ctx);*/
        /*overview(ctx);*/
        node_editor(ctx);
        /* ----------------------------------------- */

        if(clock_timer > clock_time + CLOCKS_PER_SEC*(1.0/KernelInfo.FBkernelRate)){
            clock_time = clock();
            if (KernelInfo.CfgSize){
#if DEBUG
                printf("while %lu",clock_timer);
#endif
                KernelCycle();
            }
        }
        if(clock_timer > second_timer +CLOCKS_PER_SEC){
            second_timer = clock();
            cntSecFromStart++;
        }
        /* Draw */
        {float bg[4];
        nk_color_fv(bg, background);
        SDL_GetWindowSize(win, &win_width, &win_height);
        glViewport(0, 0, win_width, win_height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg[0], bg[1], bg[2], bg[3]);
        /* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_sdl_render(NK_ANTI_ALIASING_ON);
        SDL_GL_SwapWindow(win);}
    }
    if (KernelInfo.CfgSize){
        free(pFB);
    }
cleanup:
    nk_sdl_shutdown();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

