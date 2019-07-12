cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# LIBS
find_package( OpenCV REQUIRED )

set(LIBS ${OpenCV_LIBS} stdc++fs)

# Inlcude header files
#include_directories()

# Add subdir with sources
#add_subdirectory()

# Set sources
set(SOURCES
        # MAIN
        main.cpp

        )

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC ${LIBS})