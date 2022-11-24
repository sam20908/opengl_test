# Copyright (c) 2021 - present, Avatar Cam. All rights reserved.
# SPDX-License-Identifier: CC-BY-NC-ND-3.0

# have to specify before project() call to take effect
set(X_VCPKG_APPLOCAL_DEPS_INSTALL TRUE) # copy library DLLs to installed exe location
set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake")

cmake_minimum_required(VERSION 3.20)
project(AvatarCam LANGUAGES CXX VERSION 4.0.0)

set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE SRC_FILES "src/main.cpp")
add_executable(AvatarCam "${SRC_FILES}")

target_compile_definitions(AvatarCam PRIVATE 
    AVATAR_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    AVATAR_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    AVATAR_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    AVATAR_DEBUG_BUILD=$<NOT:$<CONFIG:Release>>)

target_compile_options(AvatarCam PRIVATE /permissive-)

target_compile_definitions(AvatarCam PRIVATE WIN32_LEAN_AND_MEAN=1)
target_compile_definitions(AvatarCam PRIVATE NOMINMAX=1)
target_compile_definitions(AvatarCam PRIVATE PSAPI_VERSION=2)

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
# find_package(glad CONFIG REQUIRED)
# find_package(glm CONFIG REQUIRED)
# find_package(imgui CONFIG REQUIRED)
target_link_libraries(AvatarCam PRIVATE SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(AvatarCam PRIVATE OpenGL::GL)
target_link_libraries(AvatarCam PRIVATE dwmapi)
# target_link_libraries(AvatarCam PRIVATE glad::glad)
# target_link_libraries(AvatarCam PRIVATE glm::glm)
# target_link_libraries(AvatarCam PRIVATE imgui::imgui)

#target_precompile_headers(AvatarCam PRIVATE "src/header.pch")

target_compile_features(AvatarCam PRIVATE cxx_std_20)

# features like voice detection might not work without admin
# best to play safe and always require admin
set_target_properties(AvatarCam PROPERTIES LINK_FLAGS "/MANIFESTUAC:\"level='requireAdministrator'\"")

install(TARGETS AvatarCam CONFIGURATIONS Release RUNTIME DESTINATION "build-release")
install(FILES "$<TARGET_FILE_DIR:AvatarCam>/config.json" CONFIGURATIONS Release DESTINATION "build-release" OPTIONAL)
install(DIRECTORY "$<TARGET_FILE_DIR:AvatarCam>/img/" CONFIGURATIONS Release DESTINATION "build-release/img" OPTIONAL)
