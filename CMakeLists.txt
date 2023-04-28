cmake_minimum_required(VERSION 3.0.0)
project(optimizer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

find_package(Eigen3 REQUIRED)
find_package(osqp REQUIRED)
find_package(OsqpEigen REQUIRED)
find_package(Python3 COMPONENTS Development NumPy)

include_directories(${EIGEN3_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} src/main.cpp 
                               src/reference_path_impl.cpp 
                               src/reference_path.cpp 
                               src/tension_smoother_2.cpp
                               tools/tools.cpp
                               tools/spline.cpp
                               tinyspline_ros/src/tinyspline_ros/tinysplinecpp.cpp
                               tinyspline_ros/src/tinyspline_ros/tinyspline.c
                               )

target_link_libraries(${PROJECT_NAME} osqp::osqp
                                      OsqpEigen::OsqpEigen
                                      Python3::Python 
                                      Python3::NumPy)

target_include_directories(${PROJECT_NAME} PUBLIC include
                                           ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${Python3_INCLUDE_DIRS} 
                                                   ${Python3_NumPy_INCLUDE_DIRS})

