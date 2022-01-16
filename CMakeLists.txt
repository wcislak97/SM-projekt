cmake_minimum_required(VERSION 3.19)
project(SmProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(SDL2)
include_directories(SDL2/include)
include_directories(SDL2/include/SDL2)

#find_library(SDL2_LIBRARY NAME SDL2)

add_executable(SmProject
        SDL2/include/SDL_config.h
        SDL2/include/SDL2/begin_code.h
        SDL2/include/SDL2/close_code.h
        SDL2/include/SDL2/SDL.h
        SDL2/include/SDL2/SDL_assert.h
        SDL2/include/SDL2/SDL_atomic.h
        SDL2/include/SDL2/SDL_audio.h
        SDL2/include/SDL2/SDL_bits.h
        SDL2/include/SDL2/SDL_blendmode.h
        SDL2/include/SDL2/SDL_clipboard.h
        SDL2/include/SDL2/SDL_config.h
        SDL2/include/SDL2/SDL_cpuinfo.h
        SDL2/include/SDL2/SDL_egl.h
        SDL2/include/SDL2/SDL_endian.h
        SDL2/include/SDL2/SDL_error.h
        SDL2/include/SDL2/SDL_events.h
        SDL2/include/SDL2/SDL_filesystem.h
        SDL2/include/SDL2/SDL_gamecontroller.h
        SDL2/include/SDL2/SDL_gesture.h
        SDL2/include/SDL2/SDL_haptic.h
        SDL2/include/SDL2/SDL_hints.h
        SDL2/include/SDL2/SDL_joystick.h
        SDL2/include/SDL2/SDL_keyboard.h
        SDL2/include/SDL2/SDL_keycode.h
        SDL2/include/SDL2/SDL_loadso.h
        SDL2/include/SDL2/SDL_log.h
        SDL2/include/SDL2/SDL_main.h
        SDL2/include/SDL2/SDL_messagebox.h
        SDL2/include/SDL2/SDL_metal.h
        SDL2/include/SDL2/SDL_mouse.h
        SDL2/include/SDL2/SDL_mutex.h
        SDL2/include/SDL2/SDL_name.h
        SDL2/include/SDL2/SDL_opengl.h
        SDL2/include/SDL2/SDL_opengl_glext.h
        SDL2/include/SDL2/SDL_opengles.h
        SDL2/include/SDL2/SDL_opengles2.h
        SDL2/include/SDL2/SDL_opengles2_gl2.h
        SDL2/include/SDL2/SDL_opengles2_gl2ext.h
        SDL2/include/SDL2/SDL_opengles2_gl2platform.h
        SDL2/include/SDL2/SDL_opengles2_khrplatform.h
        SDL2/include/SDL2/SDL_pixels.h
        SDL2/include/SDL2/SDL_platform.h
        SDL2/include/SDL2/SDL_power.h
        SDL2/include/SDL2/SDL_quit.h
        SDL2/include/SDL2/SDL_rect.h
        SDL2/include/SDL2/SDL_render.h
        SDL2/include/SDL2/SDL_revision.h
        SDL2/include/SDL2/SDL_rwops.h
        SDL2/include/SDL2/SDL_scancode.h
        SDL2/include/SDL2/SDL_sensor.h
        SDL2/include/SDL2/SDL_shape.h
        SDL2/include/SDL2/SDL_stdinc.h
        SDL2/include/SDL2/SDL_surface.h
        SDL2/include/SDL2/SDL_system.h
        SDL2/include/SDL2/SDL_syswm.h
        SDL2/include/SDL2/SDL_test.h
        SDL2/include/SDL2/SDL_test_assert.h
        SDL2/include/SDL2/SDL_test_common.h
        SDL2/include/SDL2/SDL_test_compare.h
        SDL2/include/SDL2/SDL_test_crc32.h
        SDL2/include/SDL2/SDL_test_font.h
        SDL2/include/SDL2/SDL_test_fuzzer.h
        SDL2/include/SDL2/SDL_test_harness.h
        SDL2/include/SDL2/SDL_test_images.h
        SDL2/include/SDL2/SDL_test_log.h
        SDL2/include/SDL2/SDL_test_md5.h
        SDL2/include/SDL2/SDL_test_memory.h
        SDL2/include/SDL2/SDL_test_random.h
        SDL2/include/SDL2/SDL_thread.h
        SDL2/include/SDL2/SDL_timer.h
        SDL2/include/SDL2/SDL_touch.h
        SDL2/include/SDL2/SDL_types.h
        SDL2/include/SDL2/SDL_version.h
        SDL2/include/SDL2/SDL_video.h
        SDL2/include/SDL2/SDL_vulkan.h
        SM2021-Projekt1.cpp)

target_link_libraries(SmProject /usr/local/lib/libSDL2-2.0.0.dylib)

