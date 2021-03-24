cmake_minimum_required(VERSION 3.5)

project(p2ga_sample)

# set the module path for "findLib.cmake"
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

# require Eigen
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
endif()

# require lib p2ga
find_package(P2GA)
if(${P2GA_FOUND})
    message(STATUS "lib P2GA found")
    message(STATUS "  include " ${P2GA_INCLUDE_DIRS})
    message(STATUS "  lib     " ${P2GA_LIBRARIES})
else()
    message(STATUS "lib P2GA should be set manually, please uncomment the commented lines in the CMakeLists.txt file")
    #set(P2GA_INCLUDE_DIRS "[path to]/garamon_p2ga/src/")
    #set(P2GA_LIBRARIES "[path to]/garamon_p2ga/build/libp2ga.dylib")

    # for manual setting, check if valid
    if(EXISTS "${P2GA_INCLUDE_DIRS}")
        message(STATUS "include for lib p2ga found: ${P2GA_INCLUDE_DIRS}" )
    else()
        message(FATAL_ERROR "include for lib p2ga invalid or not found: ${P2GA_INCLUDE_DIRS}" )
    endif()

    # for manual setting, check if valid
    if(EXISTS "${P2GA_LIBRARIES}")
        message(STATUS "library p2ga found: ${P2GA_LIBRARIES}" )
    else()
        message(FATAL_ERROR "library p2ga not found: ${P2GA_LIBRARIES}" )
    endif()
endif()


# compile
add_executable(p2ga_sample src/main.cpp)

# compilation flags
target_compile_features(p2ga_sample PRIVATE cxx_std_14) 
target_compile_options(p2ga_sample PRIVATE -Wall -O2) 

# includes
include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${P2GA_INCLUDE_DIRS})

# link
target_link_libraries(p2ga_sample ${P2GA_LIBRARIES})




