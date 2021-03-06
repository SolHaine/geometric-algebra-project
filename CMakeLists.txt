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


# require lib c2ga
find_package(C2GA)
if(${C2GA_FOUND})
    message(STATUS "lib C2GA found")
    message(STATUS "  include " ${C2GA_INCLUDE_DIRS})
    message(STATUS "  lib     " ${C2GA_LIBRARIES})
else()
    message(STATUS "lib C2GA should be set manually, please uncomment the commented lines in the CMakeLists.txt file")

    # linux users
    #set(C2GA_INCLUDE_DIRS "/home/[full path to]/garamon_c2ga/src/")
    #set(C2GA_LIBRARIES "[full path to]/garamon_c2ga/build/libc2ga.so")

    # mac users
    #set(C2GA_INCLUDE_DIRS "/home/[full path to]/garamon_c2ga/src/")
    #set(C2GA_LIBRARIES "[full path to]/garamon_c2ga/build/libc2ga.dylib")

    # windows users
    #set(C2GA_INCLUDE_DIRS "C:\[full path to]/garamon_c2ga/src/")
    #set(C2GA_LIBRARIES "[full path to]/garamon_c2ga/build/libc2ga.dll")

    # for manual setting, check if valid
    if(EXISTS "${C2GA_INCLUDE_DIRS}")
        message(STATUS "include for lib c2ga found: ${C2GA_INCLUDE_DIRS}" )
    else()
        message(FATAL_ERROR "include for lib c2ga invalid or not found: ${C2GA_INCLUDE_DIRS}" )
    endif()

    # for manual setting, check if valid
    if(EXISTS "${C2GA_LIBRARIES}")
        message(STATUS "library c2ga found: ${C2GA_LIBRARIES}" )
    else()
        message(FATAL_ERROR "library c2ga not found: ${C2GA_LIBRARIES}" )
    endif()
endif()

# require lib p2ga
find_package(P2GA)
if(${P2GA_FOUND})
    message(STATUS "lib P2GA found")
    message(STATUS "  include " ${P2GA_INCLUDE_DIRS})
    message(STATUS "  lib     " ${P2GA_LIBRARIES})
else()
    message(STATUS "lib P2GA should be set manually, please uncomment the commented lines in the CMakeLists.txt file")

    # linux users
    #set(P2GA_INCLUDE_DIRS "/home/[full path to]/garamon_p2ga/src/")
    #set(P2GA_LIBRARIES "[full path to]/garamon_p2ga/build/libp2ga.so")

    # mac users
    #set(P2GA_INCLUDE_DIRS "/home/[full path to]/garamon_p2ga/src/")
    #set(P2GA_LIBRARIES "[full path to]/garamon_p2ga/build/libp2ga.dylib")

    # windows users
    #set(P2GA_INCLUDE_DIRS "C:\[full path to]/garamon_p2ga/src/")
    #set(P2GA_LIBRARIES "[full path to]/garamon_p2ga/build/libp2ga.dll")

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

######################################################################################
###################################### Includes ######################################
######################################################################################

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${OPENGL_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
        lib/glimac/include 
        lib/glm/include
        )
include_directories(${C2GA_INCLUDE_DIRS})
include_directories(${P2GA_INCLUDE_DIRS})
add_subdirectory(lib/glimac)
set(ALL_LIBRARIES glimac ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY} Eigen3::Eigen -lstdc++fs)

######################################################################################
########################### Declaration of .exe  #####################################
######################################################################################

add_executable(${PROJECT_NAME} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES})
target_link_libraries(${PROJECT_NAME} ${ALL_LIBRARIES})

######################################################################################
####################################### Copies  #####################################
######################################################################################

file(COPY src/shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})