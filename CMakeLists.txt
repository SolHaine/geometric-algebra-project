######################################################################################
################################# Presets CMakeList ##################################
######################################################################################

cmake_minimum_required(VERSION 3.5)
add_definitions(-std=c++14)

######################################################################################
############################### Configuration project  ###############################
######################################################################################

project(geometricAlgebraProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -std=c++14")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set the module path for "findLib.cmake"
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/modules)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/modules/")

######################################################################################
################################## Project files  ####################################
######################################################################################

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.hpp)
file(GLOB_RECURSE SHADER_FILES shaders/*.glsl)

######################################################################################
################################## Dependencies  #####################################
######################################################################################

find_package(OpenGL REQUIRED)
#find_package(SDL REQUIRED)
find_package(SDL2 REQUIRED)
find_package(GLEW REQUIRED)

# require Eigen
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
endif()

# require lib c3ga
find_package(C3GA)
if(${C3GA_FOUND})
    message(STATUS "lib C3GA found")
    message(STATUS "  include " ${C3GA_INCLUDE_DIRS})
    message(STATUS "  lib     " ${C3GA_LIBRARIES})
else()
    message(STATUS "lib C3GA should be set manually, please uncomment the commented lines in the CMakeLists.txt file")

    # linux users
    #set(C3GA_INCLUDE_DIRS "/home/[full path to]/garamon_c3ga/src/")
    #set(C3GA_LIBRARIES "[full path to]/garamon_c3ga/build/libc3ga.so")

    # mac users
    #set(C3GA_INCLUDE_DIRS "/home/[full path to]/garamon_c3ga/src/")
    #set(C3GA_LIBRARIES "[full path to]/garamon_c3ga/build/libc3ga.dylib")

    # windows users
    #set(C3GA_INCLUDE_DIRS "C:\[full path to]/garamon_c3ga/src/")
    #set(C3GA_LIBRARIES "[full path to]/garamon_c3ga/build/libc3ga.dll")

    # for manual setting, check if valid
    if(EXISTS "${C3GA_INCLUDE_DIRS}")
        message(STATUS "include for lib c3ga found: ${C3GA_INCLUDE_DIRS}" )
    else()
        message(FATAL_ERROR "include for lib c3ga invalid or not found: ${C3GA_INCLUDE_DIRS}" )
    endif()

    # for manual setting, check if valid
    if(EXISTS "${C3GA_LIBRARIES}")
        message(STATUS "library c3ga found: ${C3GA_LIBRARIES}" )
    else()
        message(FATAL_ERROR "library c3ga not found: ${C3GA_LIBRARIES}" )
    endif()
endif()

######################################################################################
###################################### Includes ######################################
######################################################################################

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
        lib/glimac/include 
        lib/imgui/include 
        lib/glm/include
        )
include_directories(${C3GA_INCLUDE_DIRS})
add_subdirectory(lib/glimac)
add_subdirectory(lib/imgui)
set(ALL_LIBRARIES glimac imgui ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} Eigen3::Eigen -lstdc++fs)

######################################################################################
########################### Declaration of .exe  #####################################
######################################################################################

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBRARIES})

######################################################################################
####################################### Copies  #####################################
######################################################################################

file(COPY src/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})