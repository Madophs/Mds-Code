cmake_minimum_required(VERSION 3.10)

project(mdscode VERSION 2.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(MdsCodeConfig.h.in MdsCodeConfig.h)

include_directories(include)

add_subdirectory(src)

add_executable(mdscode mdscode.cpp)

target_link_libraries(mdscode PUBLIC libmdscode)

target_include_directories(mdscode PUBLIC
                            "${PROJECT_SOURCE_DIR}"
                            "${PROJECT_SOURCE_DIR}/src"
                            "${PROJECT_SOURCE_DIR}/include"
                            )

