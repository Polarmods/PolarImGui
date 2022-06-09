cmake_minimum_required(VERSION 3.4.1)

add_library(
             native-lib
             SHARED
             native-lib.cpp
             ImGui/imgui.cpp
             ImGui/imgui_impl_android.cpp
             ImGui/imgui_impl_opengl3.cpp
             ImGui/imgui_tables.cpp
             ImGui/imgui_widgets.cpp
             ImGui/imgui_demo.cpp
             ImGui/imgui_draw.cpp
             ByNameModding/bnm.cpp
        http/cpr/async.cpp
        http/cpr/auth.cpp
        http/cpr/bearer.cpp
        http/cpr/cookies.cpp
        http/cpr/cprtypes.cpp
        http/cpr/curl_container.cpp
        http/cpr/curlholder.cpp
        http/cpr/error.cpp
        http/cpr/multipart.cpp
        http/cpr/parameters.cpp
        http/cpr/payload.cpp
        http/cpr/proxies.cpp
        http/cpr/proxyauth.cpp
        http/cpr/session.cpp
        http/cpr/threadpool.cpp
        http/cpr/timeout.cpp
        http/cpr/unix_socket.cpp
        http/cpr/util.cpp
        http/cpr/response.cpp
        http/cpr/redirect.cpp
        http/cpr/interceptor.cpp
        Obfuscation/instr.cpp
        Memory/KittyArm64.cpp
        Memory/KittyMemory.cpp
        Memory/KittyScanner.cpp
        Memory/KittyUtils.cpp
        Memory/MemoryBackup.cpp
        Memory/MemoryPatch.cpp)


find_library(log-lib log)
find_library(egl EGL)
find_library(android android)
find_library(GLESV2_LIB GLESv2)
find_library(LZ_LIB z)
find_package(curl REQUIRED CONFIG)
if (${ANDROID_PLATFORM_LEVEL} LESS 12)
    message(FATAL_ERROR "OpenGL 2 is not supported before API level 11 /
                      (currently using ${ANDROID_PLATFORM_LEVEL}).")
    return()
elseif (${ANDROID_PLATFORM_LEVEL} LESS 18)
    add_definitions("-DDYNAMIC_ES3")
    set(GL3STUB_SRC gl3stub.c)
    set(OPENGL_LIB GLESv2)
else ()
    set(OPENGL_LIB GLESv3)
endif (${ANDROID_PLATFORM_LEVEL} LESS 12)

    set(DOBBY_LIB ${CMAKE_CURRENT_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a)


target_link_libraries(
        native-lib
        ${LZ_LIB}
        ${DOBBY_LIB}
        ${OPENGL_LIB}
        ${GLESV2_LIB}
        ${android}
        ${egl}
        ${log-lib}
        curl::curl_static)