cmake_minimum_required(VERSION 3.5)

project(keystone-tests)
enable_language(C)
enable_language(CXX)

# Folders configuration
get_filename_component(root_dir             ${CMAKE_SOURCE_DIR}           REALPATH)
get_filename_component(keystone_dir         ${root_dir}/deps/keystone     REALPATH)
get_filename_component(capstone_dir         ${root_dir}/deps/capstone     REALPATH)

# By default build in Release mode
if( NOT CMAKE_BUILD_TYPE )
	set(CMAKE_BUILD_TYPE "Release")
endif()

# Add Keystone targets
add_subdirectory(${keystone_dir})

# Add Capstone targets
add_subdirectory(${capstone_dir})

# Add common CMake functions and macros
include(common.cmake)

# Dependencies check
directory_is_empty(is_empty "${keystone_dir}")
if(is_empty)
  message(FATAL_ERROR "keystone dependency is missing, maybe you didn't pull the git submodules")
endif()
directory_is_empty(is_empty "${capstone_dir}")
if(is_empty)
	message(FATAL_ERROR "capstone dependency is missing, maybe you didn't pull the git submodules")
endif()

# Configure keystone target
if(MSVC)
	target_add_flag(keystone "/MDd" DEBUG)
	target_add_flag(keystone "/MD" RELWITHDEBINFO RELEASE)
endif()

# Configure keystone folder in IDE
foreach(keystone_target IN ITEMS keystone kstool uninstall)
	if(TARGET ${keystone_target})
		set_target_properties(${keystone_target} PROPERTIES FOLDER deps/keystone)
	endif()
endforeach()

# Configure capstone folder in IDE
foreach(capstone_target IN ITEMS capstone-shared capstone-static cstool test_arm test_arm_regression test_arm64 test_basic test_detail test_iter test_mips test_ppc test_skipdata test_sparc test_systemz test_x86 test_xcore)
	if(TARGET ${capstone_target})
		set_target_properties(${capstone_target} PROPERTIES FOLDER deps/capstone)
	endif()
endforeach()

# Add _d suffix in debug mode
set(CMAKE_DEBUG_POSTFIX _d)

get_files(
  test_includes
  "${root_dir}/include"
)
get_files(
  test_src_files
  "${root_dir}/src"
)
filter_in(test_src_files ".*/test_.+[.]c")

foreach(test_file ${test_src_files})
	get_filename_component(test_name ${test_file} NAME_WE)
	make_target(
	  ${test_name} "KeystoneTests" ${test_file} "${root_dir}/src/testKeystone.c" ${test_includes}
	  INCLUDES "include/" "${keystone_dir}/include/" "${capstone_dir}/include/"
	  OPTIONS c test
	)
	target_link_libraries(${test_name} PRIVATE "keystone" "capstone-static")
	set_property(TARGET ${test_name} PROPERTY C_STANDARD 11)
	set_property(TARGET ${test_name} PROPERTY C_STANDARD_REQUIRED ON)
endforeach()
