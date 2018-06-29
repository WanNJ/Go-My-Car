cmake_minimum_required(VERSION 3.8)
project(GoMyCar)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp ImgProcessing/preProcessing.cpp ImgProcessing/preProcessing.h utils/coordinateSystem.cpp utils/coordinateSystem.h)

SET(PROJECT_NAME
        GoMyCar)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}  ${OpenCV_LIBS})