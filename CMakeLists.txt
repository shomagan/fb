cmake_minimum_required(VERSION 3.6)
set(PRJ_NAME fb_emulator)
include(gccToolchain.cmake)
project(${PRJ_NAME} C CXX ASM)

file(GLOB MAIN main.c fb_parse.c frozen.c kernel.c node_editor.c serial.c)
file(GLOB FB FB/*.c)
set(SOURCE_FILES  ${MAIN} ${FB})

set(SDL2_INCLUDE_DIR C:/_work/fb)
set(SDL2_LIBRARY C:/_work/fb/lib)

include_directories(${SDL2_INCLUDE_DIR})
include_directories(FB/)
include_directories()

ADD_LIBRARY(mingw_lib STATIC IMPORTED)
SET_TARGET_PROPERTIES(mingw_lib PROPERTIES
    IMPORTED_LOCATION C:/mingw-w64/i686-7\.3\.0-posix-dwarf-rt_v5-rev0/mingw32/i686-w64-mingw32/lib/libmingw32.a)

ADD_LIBRARY(sdl2_main_lib STATIC IMPORTED)
SET_TARGET_PROPERTIES(sdl2_main_lib PROPERTIES
    IMPORTED_LOCATION C:/_work/fb/lib/libSDL2main.a)

ADD_LIBRARY(sdl2_lib STATIC IMPORTED)
SET_TARGET_PROPERTIES(sdl2_lib PROPERTIES
    IMPORTED_LOCATION C:/_work/fb/lib/libSDL2.dll.a)

ADD_LIBRARY(opengl_lib STATIC IMPORTED)
SET_TARGET_PROPERTIES(opengl_lib PROPERTIES
    IMPORTED_LOCATION C:/mingw-w64/i686-7\.3\.0-posix-dwarf-rt_v5-rev0/mingw32/i686-w64-mingw32/lib/libopengl32.a)

ADD_LIBRARY(glu32_lib STATIC IMPORTED)
SET_TARGET_PROPERTIES(glu32_lib PROPERTIES
    IMPORTED_LOCATION C:/mingw-w64/i686-7\.3\.0-posix-dwarf-rt_v5-rev0/mingw32/i686-w64-mingw32/lib/libglu32.a)

ADD_LIBRARY(m_lib STATIC IMPORTED)
SET_TARGET_PROPERTIES(m_lib PROPERTIES
    IMPORTED_LOCATION C:/mingw-w64/i686-7\.3\.0-posix-dwarf-rt_v5-rev0/mingw32/i686-w64-mingw32/lib/libm.a)

add_executable (${PRJ_NAME}.exe ${SOURCE_FILES})
target_link_libraries(${PRJ_NAME}.exe  mingw_lib )    
target_link_libraries(${PRJ_NAME}.exe  sdl2_main_lib )    
target_link_libraries(${PRJ_NAME}.exe  sdl2_lib )    
target_link_libraries(${PRJ_NAME}.exe  opengl_lib )    
target_link_libraries(${PRJ_NAME}.exe  m_lib )    
target_link_libraries(${PRJ_NAME}.exe  glu32_lib )    



