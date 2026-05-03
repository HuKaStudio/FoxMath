cmake_minimum_required(VERSION 3.10)

# 自动获取当前目标架构
if(DEFINED CMAKE_ANDROID_ARCH_ABI)
    set(LOCAL_ARCH ${CMAKE_ANDROID_ARCH_ABI})
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(LOCAL_ARCH "arm64-v8a")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "armv7")
    set(LOCAL_ARCH "armeabi-v7a")
else()
    set(LOCAL_ARCH "unknown")
endif()

# 收集核心源文件（建议加上 CONFIGURE_DEPENDS，需要 CMake 3.12+）
file(GLOB_RECURSE CORE_SRCS CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/core/*.cpp
)

add_library(foxmath-android SHARED
    foxmath_jni.cpp
    ${CORE_SRCS}
)

target_include_directories(foxmath-android PRIVATE ${CMAKE_SOURCE_DIR}/src/core)
target_link_libraries(foxmath-android log)

# 输出名带架构后缀，方便区分
set_target_properties(foxmath-android PROPERTIES
    OUTPUT_NAME "foxmath-android"
)
