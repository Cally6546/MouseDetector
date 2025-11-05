cmake_minimum_required(VERSION 3.10)
project(MouseDetector VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add library
add_library(MouseDetector STATIC
    src/MouseDetector.cpp
)

# Include headers
target_include_directories(MouseDetector
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# Linux-specific linking for udev
if(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBUDEV REQUIRED libudev)
    target_include_directories(MouseDetector PRIVATE ${LIBUDEV_INCLUDE_DIRS})
    target_link_libraries(MouseDetector PRIVATE ${LIBUDEV_LIBRARIES})
endif()
