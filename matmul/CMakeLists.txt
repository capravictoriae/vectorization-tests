cmake_minimum_required( VERSION 2.8 )
                       
## Specify a project name
project( ordering )

## Set the build type
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE "Release" 
       CACHE STRING "Build configuration 'Release' or 'Debug'."
       FORCE )
endif()

# add_definitions( "-g -msse4.1 -O3" )
# add_definitions( "-g -march=native -msse4.1 -O0" )
add_definitions( "-g -march=native -O0" )

add_executable(${PROJECT_NAME} src/check_if_sorted.cpp)

