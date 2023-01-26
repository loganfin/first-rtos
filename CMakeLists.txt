cmake_minimum_required(VERSION 3.13)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# If PICO_SDK_PATH is defined on the user's system, use that. Else, use the git submodule included in this repo
#if(NOT EXISTS ${CMAKE_SOURCE_DIR}/lib/FreeRTOS-Kernel/CMakeLists.txt)
#    set(FREERTOS_URL https://github.com/FreeRTOS/FreeRTOS-Kernel.git)
#    message(STATUS "Downloading the FreeRTOS-Kernel from ${FREERTOS_URL}")
#    file(DOWNLOAD ${FREERTOS_URL} ${CMAKE_SOURCE_DIR}/lib/FreeRTOS-Kernel)
#endif()

if(DEFINED ENV{PICO_SDK_PATH})
    if(NOT EXISTS ${CMAKE_SOURCE_DIR}/pico_sdk_import.cmake)
        message("Copying $ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake to ${CMAKE_SOURCE_DIR}")
        file(COPY $ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake
            DESTINATION ${CMAKE_SOURCE_DIR})
    endif()
    include(pico_sdk_import.cmake)
else()
    if(EXISTS ${CMAKE_SOURCE_DIR}/lib/pico-sdk/pico_sdk_init.cmake)
        include(lib/pico-sdk/pico_sdk_init.cmake)
    else()
        message(FATAL_ERROR "lib/pico-sdk/pico_sdk_init.cmake was not found. Make sure to run
        git submodule update --init
        git -C lib/pico-sdk/ submodule update --init")
    endif()
endif()

if(NOT DEFINED PICO_SDK_FREERTOS_SOURCE)
    if (EXISTS ${CMAKE_SOURCE_DIR}/lib/FreeRTOS-Kernel/CMakeLists.txt)
        set(PICO_SDK_FREERTOS_SOURCE ${CMAKE_SOURCE_DIR}/lib/FreeRTOS-Kernel)
    else()
        message(FATAL_ERROR "FreeRTOS source not found. Either provide one with the -D option or run
        git submodule update lib/FreeRTOS-Kernel")
    endif()
endif()

project(rtos LANGUAGES C CXX ASM)

set(PICO_BOARD adafruit_feather_rp2040)
pico_sdk_init()

add_executable(${CMAKE_PROJECT_NAME} src/main.c)
target_link_libraries(${CMAKE_PROJECT_NAME} pico_stdlib)

pico_add_extra_outputs(${CMAKE_PROJECT_NAME})

