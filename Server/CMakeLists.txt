CMake_minimum_required(VERSION 3.5)

project(Audio)

set(Audio_VERSION_MAJOR 0)
set(Audio_VERSION_MINOR 9)
set(Audio_VERSION_PATCH 0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(source_dir "${PROJECT_SOURCE_DIR}/src/")

file(GLOB source_files "${source_dir}/*.cpp")

find_package(PortAudio REQUIRED)
find_package(Boost 1.68 REQUIRED COMPONENTS thread system)

add_executable(Audio ${source_files})	

target_include_directories(Audio
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/depenecies/sndfile/include
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${PORTAUDIO_INCLUDE_DIRS}
		${Boost_INCLUDE_DIRS}
)

target_link_libraries(Audio
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/dependencies/sndfile/lib/libsndfile.so.1.0.28
		${PORTAUDIO_LIBRARIES}
		Boost::boost
        Boost::thread
        Boost::system
)

target_compile_options(Audio PUBLIC -Werror)
