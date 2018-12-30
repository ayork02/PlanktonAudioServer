CMake_minimum_required(VERSION 3.5)

project(AudioClient)

set(AudioClient_VERSION_MAJOR 0)
set(AudioClient_VERSION_MINOR 9)
set(AudioClient_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*.cpp")

find_package(Boost 1.68 REQUIRED COMPONENTS system thread)

add_executable(AudioClient ${source_files})	

target_include_directories(AudioClient
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${Boost_INCLUDE_DIRS}
)

target_link_libraries(AudioClient
	PUBLIC
		Boost::boost
        Boost::system
		Boost::thread
)

target_compile_options(AudioClient PUBLIC -Werror)
