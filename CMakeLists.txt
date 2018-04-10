cmake_minimum_required (VERSION 2.6)

project (eular_maruyama)

# message($ENV{QT5_DIR})
# if($ENV{QT5_DIR})
#   set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "$ENV{QT5_DIR}/lib/cmake")
# endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
# find_package(Qt5Widgets)


set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories( include )

add_executable(eular_maruyama src/eular_maruyama.cpp)
target_link_libraries(eular_maruyama )
