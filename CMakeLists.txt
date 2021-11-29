cmake_minimum_required(VERSION 2.8)

project(MHT)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
add_definitions("-Wall")

MESSAGE(STATUS "This is BINARY dir " ${mot_BINARY_DIR})
MESSAGE(STATUS "This is SOURCE dir " ${mot_SOURCE_DIR})

#FIND_PACKAGE(OpenGL REQUIRED)
#INCLUDE_DIRECTORIES(${OpenGL_INCLUDE_DIRS})
#LINK_DIRECTORIES(${OpenGL_LIBRARY_DIRS})

#FIND_PACKAGE(PCL 1.7 REQUIRED)
#INCLUDE_DIRECTORIES(${PCL_INCLUDE_DIRS})
#LINK_DIRECTORIES(${PCL_LIBRARY_DIRS})

#FIND_PACKAGE(OpenGL REQUIRED)
#INCLUDE_DIRECTORIES(${OpenGL_INCLUDE_DIRS})
#LINK_DIRECTORIES(${OpenGL_LIBRARY_DIRS})

#FIND_PACKAGE(GLUT REQUIRED)
#INCLUDE_DIRECTORIES(${GLUT_INCLUDE_DIRS})
#LINK_DIRECTORIES(${GLUT_LIBRARY_DIRS})
FIND_PACKAGE(PkgConfig)
if(PKGCONFIG_FOUND)
    message(STATUS "PKGCONFIG FOUND")
endif()
# pkg_check_modules(PROTOBUF REQUIRED protobuf)
# LINK_DIRECTORIES(${PROTOBUF_LIBRARY_DIRS})
# message(STATUS ${PROTOBUF_INCLUDE_DIRS})
# message(STATUS ${PROTOBUF_LIBRARY_DIRS})

pkg_check_modules(OpenCV REQUIRED opencv4)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
LINK_DIRECTORIES(${OpenCV_LIBRARY_DIRS})
message(STATUS ${OpenCV_INCLUDE_DIRS})
message(STATUS ${OpenCV_LIBRARY_DIRS})
#message(STATUS ${OpenCV_LIBRARIES})

set(Eigen3_DIR "/usr/local/share/eigen3/cmake")
FIND_PACKAGE(Eigen3 REQUIRED)
if(EIGEN3_FOUND)
    message(STATUS "EIGEN3 FOUND")
    message(STATUS ${EIGEN3_INCLUDE_DIR})
endif()
INCLUDE_DIRECTORIES(${EIGEN3_INCLUDE_DIR})

#set(OpenCV_DIR "/usr/local/lib/cmake/opencv4")
#FIND_PACKAGE(OpenCV REQUIRED)
#if(OPENCV_FOUND)
#    message(STATUS "OPENCV FOUND")
#    message(STATUS "OPENCV VISION " ${OpenCV_VERSION})
#endif()
#INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

FIND_PACKAGE(FMT REQUIRED)
if(FMT_FOUND)
    message(STATUS "FMT FOUND")
endif()
INCLUDE_DIRECTORIES(${FMT_INCLUDE_DIRS})

FIND_PACKAGE(Boost REQUIRED COMPONENTS
                                chrono
                                filesystem
                                thread
                                system
                                serialization)

#FIND_PACKAGE(Boost REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

FIND_PACKAGE(OpenMP REQUIRED)
if(OPENMP_FOUND)
    message(STATUS "OPENMP FOUND")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS"${CMAKE_EXE_LINKER_FLAGS}${OpenMP_EXE_LINKER_FLAGS}")
endif()


#FIND_PACKAGE(Protobuf REQUIRED)
#if(PROTOBUF_FOUND)
#    message(STATUS "PROTOBUF FOUND")
#endif()

OPTION(USE_DEBUG off)
if(USE_DEBUG)
    message(STATUS "USE DEBUG")
    add_definitions("-DUSE_DEBUG")
else()
    message(STATUS "NO DEBUG")
endif(USE_DEBUG)

set(INC_PATH inc)
INCLUDE_DIRECTORIES(${INC_PATH})

# AUX_SOURCE_DIRECTORY(src/detection/ graph_src)
# add_library(graph_share SHARED ${graph_src})

AUX_SOURCE_DIRECTORY(src/common/ common_SRC)
add_library(common_share SHARED ${common_SRC})

AUX_SOURCE_DIRECTORY(src/meas/ meas_SRC)
add_library(meas_share SHARED ${meas_SRC})
# target_link_libraries(meas_share common_share)

#SET(track_SRC src/track/run_track.cc
#              src/track/track.cc
#              src/track/get_target.cc)
AUX_SOURCE_DIRECTORY(src/track/ track_SRC)
add_library(track_share SHARED ${track_SRC})


SET(track_LIBS ${Boost_LIBRARIES}
                # ${PCL_LIBRARIES}
                # ${OpenCV_LIBS}
                # ${OpenGL_LIBRARIES}
                # ${GLUT_LIBRARY}
                # ${PROTOBUF_LIBRARIES}
                # ${OpenCV_LIBRARIES}
                glog
                fmt::fmt
                meas_share
                common_share
                track_share
                )

#LINK_LIBRARIES(#${OpenCV_LIBS}
#               ${Boost_LIBRARIES}
#               ${PCL_LIBRARIES}
#               glog
#               fmt::fmt)

add_executable(run_track src/script/run_track.cc)
target_link_libraries(run_track ${track_LIBS})


