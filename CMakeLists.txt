cmake_minimum_required(VERSION 3.20)
project( cutil
    LANGUAGES C CXX
    VERSION 6               # 版本号只设一段 MAJOR
    HOMEPAGE_URL "https://github.com/BH2WFR/cutil"
)



#* 查找头文件
file(GLOB_RECURSE PROJ_HEADER_FILES "*.h" "*.hpp")
message("HEADERS:${PROJ_HEADER_FILES}")

#* 就在本文件夹下安装 (其实只是在 cmake 目录中生成 ...Config.cmake 文件)
set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}")

#* 创建一个 header-only Target, 无需编译为库
add_library(${PROJECT_NAME} INTERFACE
	${PROJ_HEADER_FILES}
)
add_library("${PROJECT_NAME}::${PROJECT_NAME}" ALIAS ${PROJECT_NAME})


#* 添加宏定义，对外暴露
target_compile_definitions(${PROJECT_NAME}
    INTERFACE "CUTIL_VERSION=${PROJECT_VERSION_MAJOR}"
)

#* include 目录
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

#* 设置安装信息
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    # INCLUDES DESTINATION ${PROJECT_NAME}/include
)

#* 输出 ...Config.cmake 文件, 直接输出到 cmake 目录下
install(EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Config.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION "cmake"
)


add_subdirectory(test)
