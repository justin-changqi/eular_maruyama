cmake_minimum_required (VERSION 2.6)

project (eular_maruyama)

# generate proper GUI program on specified platform
# if(WIN32) # Check if we are on Windows
# 	if(MSVC) # Check if we are using the Visual Studio compiler
# 		set_target_properties(${PROJECT_NAME} PROPERTIES
# 			WIN32_EXECUTABLE YES
# 			LINK_FLAGS "/ENTRY:mainCRTStartup"
# 		)
# 	elseif(CMAKE_COMPILER_IS_GNUCXX)
# 			# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
# 	else()
# 		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
# 	endif(MSVC)
# elseif(APPLE)
# 	set_target_properties(${PROJECT_NAME} PROPERTIES
# 			MACOSX_BUNDLE YES
# 	)
# elseif(UNIX)
# 	# Nothing special required
# else()
# 	message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
# endif(WIN32)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 14)

# Find the QtWidgets library
# find_package(Qt5Widgets)


set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories( include
                     lib/qcustomplot/include)


# add_executable(eular_maruyama src/eular_maruyama.cpp src/plot_data.cpp)
add_executable(eular_maruyama src/eular_maruyama.cpp )
target_link_libraries(eular_maruyama)
# target_link_libraries(eular_maruyama Qt5::Widgets)
