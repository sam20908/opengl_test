# have to specify before project() call to take effect
set(X_VCPKG_APPLOCAL_DEPS_INSTALL TRUE) # copy library DLLs to installed exe location
set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")

cmake_minimum_required(VERSION 3.20)
project(OpenGLTest LANGUAGES CXX VERSION 4.0.0)

set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(OpenGLTest "src/main.cpp")

target_compile_definitions(OpenGLTest PRIVATE WIN32_LEAN_AND_MEAN=1)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGLTest PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(OpenGLTest PRIVATE OpenGL::GL)
target_link_libraries(OpenGLTest PRIVATE dwmapi)

target_compile_features(OpenGLTest PRIVATE cxx_std_20)

set_target_properties(OpenGLTest PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator'\"")
