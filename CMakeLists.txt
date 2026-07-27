cmake_minimum_required(VERSION 3.10)

# Cross-compiler selection, in priority order:
#   1. -DCMAKE_TOOLCHAIN_FILE=<file>   (CMake native, needs nothing here)
#   2. -DCMAKE_C_COMPILER=<gcc> -DCMAKE_CXX_COMPILER=<g++>
#   3. -DPLC_TOOLCHAIN_PREFIX=<prefix> where <prefix> ends with the trailing '-',
#      e.g. /opt/toolchain/bin/arm-none-linux-gnueabihf-
# No local path is hard-coded, so the checkout carries no machine-specific setup.
set(PLC_TOOLCHAIN_PREFIX "" CACHE STRING "Cross toolchain prefix; <prefix>gcc and <prefix>g++ are used")

if(NOT CMAKE_C_COMPILER AND PLC_TOOLCHAIN_PREFIX)
    set(CMAKE_C_COMPILER "${PLC_TOOLCHAIN_PREFIX}gcc")
endif()
if(NOT CMAKE_CXX_COMPILER AND PLC_TOOLCHAIN_PREFIX)
    set(CMAKE_CXX_COMPILER "${PLC_TOOLCHAIN_PREFIX}g++")
endif()

if(NOT CMAKE_TOOLCHAIN_FILE AND NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "No cross compiler configured. Pass one of:\n"
                        "  -DPLC_TOOLCHAIN_PREFIX=<prefix>   (e.g. /opt/toolchain/bin/arm-linux-gnueabihf-)\n"
                        "  -DCMAKE_C_COMPILER=<path> -DCMAKE_CXX_COMPILER=<path>\n"
                        "  -DCMAKE_TOOLCHAIN_FILE=<file>")
endif()

if(CMAKE_C_COMPILER AND NOT EXISTS "${CMAKE_C_COMPILER}")
    message(FATAL_ERROR "C compiler not found: ${CMAKE_C_COMPILER}")
endif()

project(plc_display)

# Version stamped into `plc_display --version`. Override at configure time:
#   cmake -DPLC_DISPLAY_VERSION=x.y.z ..
# Defaults to 0.0.3 when not specified.
set(PLC_DISPLAY_VERSION "0.0.3" CACHE STRING "Version reported by plc_display --version")

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/lib/lvgl
    ${CMAKE_SOURCE_DIR}/lib/lv_drivers
    ${CMAKE_SOURCE_DIR}/custom
    ${CMAKE_SOURCE_DIR}/generated
    ${CMAKE_SOURCE_DIR}/generated/guider_customer_fonts
    ${CMAKE_SOURCE_DIR}/generated/guider_fonts
    ${CMAKE_SOURCE_DIR}/generated/images
)

SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH "/usr/lib")


# lvgl
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/lvgl)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/lv_drivers)



file(GLOB SRC ${CMAKE_SOURCE_DIR}/src/*.c
            ${CMAKE_SOURCE_DIR}/custom/*.c
            ${CMAKE_SOURCE_DIR}/generated/*.c
            ${CMAKE_SOURCE_DIR}/generated/images/*.c
            ${CMAKE_SOURCE_DIR}/generated/guider_fonts/*.c
)

add_executable(${PROJECT_NAME}
            ${SRC}
    )

target_compile_definitions(${PROJECT_NAME} PRIVATE
    PLC_DISPLAY_VERSION="${PLC_DISPLAY_VERSION}"
)
# debug
add_compile_options(-fPIC -Wall -O3 -g0)
# warnning
add_compile_options(
    -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith
    -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess
    -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic
    -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048
    -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter
    -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes
    -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare -std=c99
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/src
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/lvgl/font
)

target_link_libraries(${PROJECT_NAME}
    #PRIVATE lvgl_examples
    PRIVATE lvgl::drivers
    pthread
)


