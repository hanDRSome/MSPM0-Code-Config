set(CMAKE_SYSTEM_NAME Generic) # 无操作系统
set(CMAKE_SYSTEM_PROCESSOR arm)  # ARM 架构
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

cmake_minimum_required(VERSION 3.15)
project(demo C) # 项目名+编写语言

set(CMAKE_C_COMPILER arm-none-eabi-gcc) #编译器

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m0plus -mthumb -Wall -O0 -g -ffunction-sections -fdata-sections --specs=nano.specs --specs=nosys.specs")
#编译选项
set(CMAKE_EXECUTABLE_SUFFIX ".elf") #编译后缀

add_compile_definitions(
    __MSPM0G3507__
    DeviceFamily_MSPM0G3507
    __MSPM0__
    PART_MSPM0G3507
    DEBUG
)#宏定义

set(MSPM0_SOURCE_PATH "D:/ti/mspm0_sdk/source")#芯片资源路径
set(USER_PATH "src") #用户代码路径
set(DRIVER_PATH "dvr") # 驱动路径

file(GLOB_RECURSE STARTUP_SOURCES 
    "${MSPM0_SOURCE_PATH}/ti/devices/msp/m0p/startup_system_files/gcc/startup_mspm0g350x_gcc.c"
) #源文件
# add area---

# -------------
add_executable(${PROJECT_NAME}
    main.c
    ti_msp_dl_config.c
    ${STARTUP_SOURCES}
# add area---

# -------------
)#输出

target_include_directories(${PROJECT_NAME} PRIVATE
    ${MSPM0_SOURCE_PATH}
    ${MSPM0_SOURCE_PATH}/ti/devices/msp/m0p
    ${MSPM0_SOURCE_PATH}/ti/devices/msp/m0p/driverlib
    ${MSPM0_SOURCE_PATH}/ti/driverlib/m0p   
    ${MSPM0_SOURCE_PATH}/third_party/CMSIS/Core/Include
    ${CMAKE_SOURCE_DIR}
# add area---

# -------------
)#头文件

target_link_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m0plus
    -mthumb
    -T ${MSPM0_SOURCE_PATH}/ti/devices/msp/m0p/linker_files/gcc/mspm0g3507.lds
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--gc-sections
    -Wl,--print-memory-usage
    -Wl,--cref
)#链接设置

target_link_libraries(${PROJECT_NAME}
    ${MSPM0_SOURCE_PATH}/ti/driverlib/lib/ticlang/m0p/mspm0g1x0x_g3x0x/driverlib.a
    -lm
)#预编译

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) #编译数据库