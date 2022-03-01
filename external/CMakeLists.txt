# copied some code snippets from Pesc0 (https://github.com/Pesc0/imgui-cmake)

cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

include(../cmake/CPM.cmake)

#----------------------- SDL2 -----------------------#

CPMAddPackage(
  NAME libsdl
  GIT_TAG release-2.0.20
  GITHUB_REPOSITORY libsdl-org/SDL
)

if(RASPBIAN)
    set(VIDEO_RPI ON)
endif()

set(SDL2_DIR ${libsdl_SOURCE_DIR})
link_directories(${SDL2_DIR} [EXCLUDE_FROM_ALL])


#----------------------- IMGUI -----------------------#


CPMAddPackage(
  NAME imguilib
  GIT_TAG origin/docking
  GITHUB_REPOSITORY ocornut/imgui
)

add_library(imgui STATIC)

target_sources(imgui 
    PRIVATE
        ${imguilib_SOURCE_DIR}/imgui.h
        ${imguilib_SOURCE_DIR}/imgui.cpp
        ${imguilib_SOURCE_DIR}/imconfig.h
        ${imguilib_SOURCE_DIR}/imgui_demo.cpp
        ${imguilib_SOURCE_DIR}/imgui_draw.cpp
        ${imguilib_SOURCE_DIR}/imgui_internal.h
        ${imguilib_SOURCE_DIR}/imgui_tables.cpp
        ${imguilib_SOURCE_DIR}/imgui_widgets.cpp
        ${imguilib_SOURCE_DIR}/imstb_rectpack.h
        ${imguilib_SOURCE_DIR}/imstb_textedit.h
        ${imguilib_SOURCE_DIR}/imstb_truetype.h
        ${imguilib_SOURCE_DIR}/backends/imgui_impl_sdl.cpp
        ${imguilib_SOURCE_DIR}/backends/imgui_impl_sdl.h
        ${imguilib_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
        ${imguilib_SOURCE_DIR}/backends/imgui_impl_opengl3.h
        ${imguilib_SOURCE_DIR}/backends/imgui_impl_opengl3_loader.h
)

target_include_directories( imgui
                            PUBLIC ${imguilib_SOURCE_DIR}/
                            PUBLIC ${imguilib_SOURCE_DIR}/backends
                            )

if(RASPBIAN)
    target_compile_definitions(imgui PUBLIC -D__RASPBIAN__)

    # Do not search for OpenGL on raspbian. Use GLES instead.
    set(USE_GLES ON) 
endif()


if(USE_GLES)
    target_compile_definitions(imgui PUBLIC -DIMGUI_IMPL_OPENGL_ES2)

    if(RASPBIAN AND USE_BROADCOM_DRIVER)
        target_link_directories(IMGUI PUBLIC /opt/vc/lib)
        target_link_libraries(imgui PUBLIC brcmGLESv2 brcmEGL)
    else()
        target_link_libraries(imgui PUBLIC GLESv2)
    endif()
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(imgui PUBLIC ${OPENGL_LIBRARIES})
endif()


target_link_libraries(imgui PUBLIC SDL2::SDL2 ${CMAKE_DL_LIBS})