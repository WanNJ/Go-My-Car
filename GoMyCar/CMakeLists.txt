cmake_minimum_required(VERSION 3.7)
project(GoMyCar)

find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp ImgProcessing/preProcessing.cpp ImgProcessing/preProcessing.h Utils/coordinateSystem.cpp Utils/coordinateSystem.h CarController/CarController.cpp CarController/CarController.h CarController/GPIOlib.h PIDController/PIDController.cpp PIDController/PIDController.h)

SET(PROJECT_NAME
        GoMyCar)

LINK_DIRECTORIES("../lib/")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}  ${OpenCV_LIBS} GPIO wiringPi pthread)