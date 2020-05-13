cmake_minimum_required(VERSION 3.13)
if (DEFINED MCU)
	# Setting up the toolchain
	set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/cortex.cmake")
endif()
# Project information
project(AMS5812
	VERSION 1.0
	DESCRIPTION "AMS5812 sensor driver"
	LANGUAGES C CXX
)
if (DEFINED MCU)
	# Grab the processor and set up definitions and compile options
	include(${CMAKE_SOURCE_DIR}/cmake/config_mcu.cmake)
	configMcu(${MCU})
	# Fetch types
	include(FetchContent)
	FetchContent_Declare(
		types
		GIT_REPOSITORY 	git@gitlab.com:bolderflight/software/types.git
		GIT_TAG					v1.0.0
	)
	FetchContent_MakeAvailable(types)
	# Fetch core
	FetchContent_Declare(
		core
		GIT_REPOSITORY 	git@gitlab.com:bolderflight/software/core.git
	)
	FetchContent_MakeAvailable(core)
	# Add the library target
	add_library(ams5812
		src/ams5812/ams5812.cc
		include/ams5812/ams5812.h
	)
	# Link libraries
	target_link_libraries(ams5812
		PUBLIC
			core
			types
	)
	# Setup include directories 
	target_include_directories(ams5812 PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
endif()
# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	if (DEFINED MCU)
		# Add the spi example target
		add_executable(ams5812_example examples/ams5812_example.cc)
		# Add the includes
		target_include_directories(ams5812_example PUBLIC 
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>
		)
		# Link libraries to the example target
		target_link_libraries(ams5812_example
			PRIVATE 
			ams5812
		)
		# Add hex and upload targets
		include(${CMAKE_SOURCE_DIR}/cmake/flash_mcu.cmake)
		FlashMcu(ams5812_example ${MCU})
	endif()
endif()
