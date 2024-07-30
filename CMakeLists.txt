cmake_minimum_required(VERSION 3.10)

# 设置项目名称和语言
project(ChiledReader VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message("Current source dir: ${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source)


# 收集源文件
file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp" "${SOURCE_DIR}/*.h")
# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})
# 添加可执行文件
#add_executable(${PROJECT_NAME} main.cpp)
include_directories(${EMSCRIPTEN_ROOT_PATH}/system/include)
# 包含 pdfium-wasm 头文件
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pdfwasm/pdfium-wasm/include)

# 链接 pdfium-wasm 库
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pdfwasm/pdfium-wasm/lib/pdfium.wasm)