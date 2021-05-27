cmake_minimum_required(VERSION 3.19)
project(render)

set(CMAKE_CXX_STANDARD 17)
set(OpenCV_DIR "E:/environment/opencv-4.5.2/build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
find_package(Eigen3)
include_directories("E:/environment/eigen-3.4-rc1/eigen-3.4-rc1")
include_directories("./Header")

add_executable(render main.cpp Source/Triangle.cpp Header/Triangle.h Source/Scene.cpp Header/Scene.h Source/Rasterizer.cpp Header/Rasterizer.h Source/Camera.cpp Header/Camera.h Header/global.h)

# add libs you need
set(OpenCV_LIBS
        ${OpenCV_DIR}/lib/libopencv_calib3d452.dll.a
        ${OpenCV_DIR}/lib/libopencv_core452.dll.a
        ${OpenCV_DIR}/lib/libopencv_dnn452.dll.a
        ${OpenCV_DIR}/lib/libopencv_features2d452.dll.a
        ${OpenCV_DIR}/lib/libopencv_flann452.dll.a
        ${OpenCV_DIR}/lib/libopencv_highgui452.dll.a
        ${OpenCV_DIR}/lib/libopencv_imgcodecs452.dll.a
        ${OpenCV_DIR}/lib/libopencv_imgproc452.dll.a
        ${OpenCV_DIR}/lib/libopencv_ml452.dll.a
        ${OpenCV_DIR}/lib/libopencv_objdetect452.dll.a
        ${OpenCV_DIR}/lib/libopencv_photo452.dll.a
        ${OpenCV_DIR}/lib/libopencv_stitching452.dll.a
        ${OpenCV_DIR}/lib/libopencv_ts452.a
        ${OpenCV_DIR}/lib/libopencv_video452.dll.a
        ${OpenCV_DIR}/lib/libopencv_videoio452.dll.a
        )
# linking
target_link_libraries(render ${OpenCV_LIBS})