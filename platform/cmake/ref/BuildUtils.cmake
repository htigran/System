cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(CMAKE_VERBOSE_MAKEFILE true)
set(LOCAL_DEBUG false)
set(BUILD_DEBUG false)

#
# Include the toolchain script only once
#
include(compilerDefOpt.cmake)

#-----------------------------------------------------------------------------------------
# FUNC	myLog
#		Debug prints a message if the variable LOCAL_DEBUG is set to true
#
# INPUT
#		funName	: this variable should contain the name of the caller function
#				: variable number of strings to be printed
#
# OUTPUT
#		message all input elements
#-----------------------------------------------------------------------------------------
function(myLog funName)
	if (${LOCAL_DEBUG})
		set(logStr "<${funName}>")
		foreach(arg ${ARGN})
			set(${logStr} "${logStr} ${arg}")
		endforeach()
		message(${logStr})
	endif()
endfunction()

#-----------------------------------------------------------------------------------------
# FUNC	buildLog
#		Debug prints a message is the variable BUILD_DEBUG is set to true
#
# INPUT
#		ARGN	: variable number of strings to be printed
#
# OUTPUT
#		message all input elements
#-----------------------------------------------------------------------------------------
function(buildLog)
	if (${BUILD_DEBUG})
		foreach(str ${ARGN})
			message(${str})
		endforeach()
	endif()
endfunction()

#-----------------------------------------------------------------------------------------
# MACRO	dump_list
#	Debug prints a list
#
# INPUT
#		title	: first line to show
#		lst		: the actual list
#
# OUTPUT
#		message all elements in the lst
#-----------------------------------------------------------------------------------------
function(dump_list title_ lst_)
	message(${title_})
	message("[")
	foreach(w ${lst_})
		message("  ${w}")
	endforeach()
	message("]")
endfunction()

#-----------------------------------------------------------------------------------------
# FUNC	getLibName
#		returns the library name based on the target build options
#
# INPUT
#		libName	: variable name to store the library name
#		modName	: module name
#
# OUTPUT
#		libName : library name
#-----------------------------------------------------------------------------------------
function(getLibName libName modName)
	# Debug versus release naming
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		set(BUILD_TYPE "d")
	else()
		set(BUILD_TYPE "r")
	endif()
	set(${libName} ${modName}_${BFW_PLATFORM}_${BFW_OS}_${BFW_TARGET}_${BUILD_TYPE} PARENT_SCOPE)
endfunction()

#-----------------------------------------------------------------------------------------
# FUNC	getLibDirName
#		returns the library build folder name based on the target build options
#
# INPUT
#		libDirName	: variable name to store the library folder name
#
# OUTPUT
#		libDirName	: library folder name
#-----------------------------------------------------------------------------------------
function(getLibDirName libDirName)
	# Debug versus release naming
	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		set(BUILD_TYPE "d")
	else()
		set(BUILD_TYPE "r")
	endif()
	if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
		set(BUILD_IDE "_ide")
	else()
		set(BUILD_IDE "")
	endif()
	if(${CMAKE_BINARY_DIR} MATCHES "_lint")
		set(BUILD_LINT "_lint")
	else()
		set(BUILD_LINT "")
	endif()
	set(${libDirName} ${BFW_PLATFORM}_${BFW_OS}_${BFW_TARGET}${BUILD_IDE}_${BUILD_TYPE}${BUILD_LINT} PARENT_SCOPE)
endfunction()

#-----------------------------------------------------------------------------------------
# MACRO	set_project_name
#		Sets the project name and adds it to the build make, including a clean project
#
# INPUT
#		name	: Project name
#
# OUTPUT
#		none	:
#
#		NOTE: If the project name is empty then the folder name will be used as the name
#-----------------------------------------------------------------------------------------
macro(set_project_name name)
	myLog("set_project_name - ${CMAKE_CURRENT_SOURCE_DIR}" ${name})
	if(${name} STREQUAL "")
		message(FATAL_ERROR "<set_project_name> ERROR: project name not defined")
	elseif (${name} STREQUAL "_NAME_AUTO_")
		# Use the folder name as the projcet name
		get_filename_component(_project_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
		string(REPLACE " " "_" _project_name ${_project_name})
	else()
		# Use the input variable
		set(_project_name ${name})
	endif()
	#
	# Set the project name
	#
	project(${_project_name})
	if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
		# Add the project name as a target
		add_custom_target(${PROJECT_NAME})
		set_property(TARGET ${PROJECT_NAME} PROPERTY LABELS ${PROJECT_NAME})
	else()
		# Turn on the ability to create folders to organize projects (.vcproj)
		# It creates "CMakePredefinedTargets" folder by default and adds CMake
		# defined projects like INSTALL.vcproj and ZERO_CHECK.vcproj
		set_property(GLOBAL PROPERTY USE_FOLDERS ON)
	endif()
	#
	# Modules Library name
	#
	getLibName(LIBNAME ${PROJECT_NAME})
	#
	# Specific configuration for the root project
	#
	if (${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
		#
		# Find all the modules in the project
		#	(only needed in the root folder of the project)
		#
		set(MODULES_LIST)
		set(BIN_LAYER_LIST)
		set(SRC_LAYER_LIST)
		#file(WRITE "${CMAKE_BINARY_DIR}/versions.txt" "Module versions included in this build\n")
	endif()

	#
	# Configure the module if it has a "source" folder
	#
	if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/source)
		message("Module: ${PROJECT_NAME}")
		_config_module()
	else()
		message("Folder: ${PROJECT_NAME}")
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	_config_module
#		This macro does the basic module configuration
#
# INPUT
#		none	: 
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(_config_module)
	myLog("config_module - ${CMAKE_CURRENT_SOURCE_DIR}")
	#
	# Initialize some module variables that will be used to collect different kind of files
	#
	set(${PROJECT_NAME}_PUBLIC_HEADER)			# Module public header files list
	set(${PROJECT_NAME}_SRC)					# Module source code files list
	set(${PROJECT_NAME}_LIBS)					# Module libs list
	set(${PROJECT_NAME}_EXE_DEPENDS)			# Application exe dependencies
	set(${PROJECT_NAME}_DEPENDS)				# Module dependency list
	set(${PROJECT_NAME}_PROTO_FILES)			# Module source Goggle Protocol Buffers files list
	set(${PROJECT_NAME}_PUBLIC_PROTO_HEADER)	# Module public Goggle Protocol Buffers header files list
	
	set(${PROJECT_NAME}_TI_HEADER_INCLUDES "${TI_COMPILER_PATH}/include" CACHE STRING "TI Paths" FORCE)

	#Include FindTiTools script
#	include(FindTiTools)
	
	# Include needed directories
	include_directories(
		"${CMAKE_CURRENT_SOURCE_DIR}/source"							# Module's common source and header files
	)

#	foreach(_arch ${archList})
		# Include the source arch.cmake if exists
#		if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/source/arch/${_arch}/arch.cmake")
#			include_directories("${CMAKE_CURRENT_SOURCE_DIR}/source/arch/${_arch}")			# Module's specific platform arch files
#			include("${CMAKE_CURRENT_SOURCE_DIR}/source/arch/${_arch}/arch.cmake")
#		endif()
		# Include the config arch.cmake if exists
#		if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/config/arch/${_arch}/arch.cmake")
#			include_directories("${CMAKE_CURRENT_SOURCE_DIR}/config/arch/${_arch}")			# Module's specific config platform arch files
#			include("${CMAKE_CURRENT_SOURCE_DIR}/config/arch/${_arch}/arch.cmake")
#		endif()
#	endforeach()

	#
	# Build path: In CMake 2.x LIBRARY_OUTPUT_PATH is the lib location
	#
	getLibDirName(LIB_DIR_NAME)
	get_filename_component(LIBRARY_OUTPUT_PATH ${BFW_INSTALL_DIR}/${LIB_DIR_NAME}/${LIBNAME} ABSOLUTE)
	#
	# Install path
	#
	file(MAKE_DIRECTORY ${LIBRARY_OUTPUT_PATH})

	#
	# Auto-generated files
	#
	#if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt")
	#	include("${CMAKE_CURRENT_SOURCE_DIR}/version.txt")
	#	# Generate version.cpp file
	#	configure_file("${BFW_COMMON_TOOLS_PATH}/CMakeModules/Templates/version.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")
	#	# Generate version.txt file
	#	configure_file("${BFW_COMMON_TOOLS_PATH}/CMakeModules/Templates/version.txt.in" "${LIBRARY_OUTPUT_PATH}/version.txt")
	#	file(APPEND "${CMAKE_BINARY_DIR}/versions.txt" "${PROJECT_NAME}VersionStr = VVS_${LIBNAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH};\n")
	#endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_source_layers
#		This macro adds external source layers, in binary or source mode
#
# INPUT
#		${ARGN}	: list of pairs: name type
#					- name is the source layer name
#					- type is "b" for binary or "s" for source
#
# OUTPUT
#		none	: 
#
#		NOTE	: 
#-----------------------------------------------------------------------------------------
macro(add_source_layers)
	if (${ARGC})
		myLog("add_source_layer - ${CMAKE_CURRENT_SOURCE_DIR}")
		set(src_type FALSE)
		set(bin_layer_list)
		set(src_layer_list)
		foreach(el ${ARGN})
			if (NOT src_type)
				set(src_type ${el})
			else()
				if((${src_type} STREQUAL "s") OR ${BFW_JENKINS})
					list(APPEND src_layer_list ${el})
				elseif(${src_type} STREQUAL "b")
					list(APPEND bin_layer_list ${el})
				else()
					message(FATAL_ERROR "Invalid source layer type: ${src_type} ${el}")
				endif()
				set(src_type FALSE)
			endif()
		endforeach()
		if (bin_layer_list)
			_add_binary_layers(${bin_layer_list})
		endif()
		if (src_layer_list)
			_add_source_layers(${src_layer_list})
		endif()
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	_add_binary_layers
#		This macro adds external binary layer folders to import module dependencies
#
# INPUT
#		${ARGN}	: binary layer names list
#
# OUTPUT
#		none	: 
#
#		NOTE	: 
#-----------------------------------------------------------------------------------------
macro(_add_binary_layers)
	if (${ARGC})
		myLog("_add_binary_layers - ${CMAKE_CURRENT_SOURCE_DIR}")
		foreach(layer_name ${ARGN})
			# The binary distributions are always in the project install folder
			set(dist_root ${BFW_INSTALL_DIR}/../${layer_name})
			get_filename_component(layer_root_absolute ${dist_root} ABSOLUTE)
			get_filename_component(layer_root_name ${dist_root} NAME)
			# If the binary distribution is already added as source do nothing
			list(FIND SRC_LAYER_LIST "${layer_root_name}" HasMyDist)
			if(HasMyDist EQUAL -1)
				getLibDirName(LIB_DIR_NAME)
				set(_layer_dir ${layer_root_absolute}/${LIB_DIR_NAME})
				if(NOT IS_DIRECTORY ${_layer_dir})
				    set(PYTHON ${BFW_COMMON_TOOLS_PATH}/Python27/python)
					if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
						set(build_type "-d")
					else()
						set(build_type "-r")
					endif()
					if(${BFW_JENKINS})
						set(jenkins_build "-j")
					else()
						set(jenkins_build "")
					endif()
					get_filename_component(go_build_root_absolute ${BFW_PROJECT_PATH} ABSOLUTE)
					message("\n====================================================================================\n")
					message("Building binary layer:\n\t${layer_name}")
					message("\n====================================================================================\n")
					execute_process(
						COMMAND cmd
						/c
						${PYTHON} ${BFW_COMMON_TOOLS_PATH}/build/build.py 
						-s ${layer_name}
						-t ${BFW_CONFIG_NAME}
						${build_type}
						${jenkins_build}
						WORKING_DIRECTORY ${go_build_root_absolute}
						RESULT_VARIABLE retvalue
					)
					if(NOT ${retvalue} STREQUAL "0")
						message(FATAL_ERROR "Error: binary layer not built: ${layer_name}")
					endif()
					message("\n====================================================================================\n")
					message("${layer_name} binary layer built OK")
					message("\n====================================================================================\n")
				endif()
				if(IS_DIRECTORY ${_layer_dir})
					# Add the binary distribution to the binary distribution list
					list(APPEND BIN_LAYER_LIST ${layer_root_absolute})
					list(REMOVE_DUPLICATES BIN_LAYER_LIST)
				else()
					message(STATUS "Could not find the binary distribution folder: ${layer_root_absolute}")
				endif()
			endif()
		endforeach()
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	_add_source_layers
#		This macro adds external source layer folders to import module dependencies
#
# INPUT
#		${ARGN}	: source layer names list
#
# OUTPUT
#		none	: 
#
#-----------------------------------------------------------------------------------------
macro(_add_source_layers)
	if (${ARGC})
		myLog("_add_source_layers - ${CMAKE_CURRENT_SOURCE_DIR}")
		foreach(layer_name ${ARGN})
			# The source distributions are always in the parent project folder
			set(dist_root ${BFW_PROJECT_PATH}/../${layer_name})
			get_filename_component(layer_root_absolute ${dist_root} ABSOLUTE)
			get_filename_component(layer_root_name ${dist_root} NAME)
			if(IS_DIRECTORY ${layer_root_absolute})
				list(APPEND SRC_LAYER_LIST ${layer_root_name})
				list(REMOVE_DUPLICATES SRC_LAYER_LIST)

				# Add the source distribution to the project
				add_subdirectory(${layer_root_absolute} ${CMAKE_CURRENT_BINARY_DIR}/${layer_root_name})
			else()
				message(STATUS "Could not find the source distribution folder: ${layer_root_absolute}")
			endif()
		endforeach()
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_child_modules
#		Adds local child projects in the current project folder
#
# INPUT
#		none	:
#
# OUTPUT
#		none	:
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(add_child_modules)
	myLog("add_child_modules - ${CMAKE_CURRENT_SOURCE_DIR}")
	#
	# Add the local child modules
	#
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/modules_${BFW_OS}_${BFW_TARGET}.cmake")
		#
		# For selected modules add subdirectory
		#
		include("${CMAKE_CURRENT_SOURCE_DIR}/modules_${BFW_OS}_${BFW_TARGET}.cmake")
		set(MOD_LIST ${${PROJECT_NAME}_LOCAL_MODULES})
	else()
		#
		# For every module add subdirectory
		#
		find_child_modules("${CMAKE_CURRENT_SOURCE_DIR}" MOD_LIST)
	endif()

	foreach(module ${MOD_LIST})
		if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${module}/CMakeLists.txt")
			add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/${module})
			if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
				add_dependencies(${PROJECT_NAME} ${module})
			endif()
		else()
			message("Ignoring module '${module}' as no CMakeLists.txt was found")
		endif()
	endforeach()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_local_modules
#		Creates a list with local modules to be added for the current project.
#		This macro should be used in a file modules_ARCH.cmake to indicate
#		the specific modules in a folder for a specific architecture.
#
# INPUT
#		ARGN	: list of modules (sub-folders)
#
# OUTPUT
#		none	:
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(add_local_modules)
	myLog("add_local_modules - ${CMAKE_CURRENT_SOURCE_DIR}")
	set(${PROJECT_NAME}_LOCAL_MODULES)
	if (${ARGC})
		foreach(module ${ARGN})
			list(APPEND ${PROJECT_NAME}_LOCAL_MODULES ${module})
		endforeach()
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	find_child_modules
#		Finds project directories, given a top level directory.
#
# INPUT
#		topdir	: Top level directory
#
# OUTPUT
#		dirlist	: list of project directories
#
#		NOTE: A project directory shall contain a CMakeLists.txt file
#-----------------------------------------------------------------------------------------
macro(find_child_modules topdir dirlist)
	myLog("find_child_modules - ${CMAKE_CURRENT_SOURCE_DIR}" ${topdir})
	file(GLOB children RELATIVE ${topdir} ${topdir}/*)
	set(auxlist)
	foreach(child ${children})
		if(IS_DIRECTORY "${topdir}/${child}")
			if(EXISTS "${topdir}/${child}/CMakeLists.txt")
				list(APPEND auxlist "${child}")
			endif()
		endif()
	endforeach()
	if(auxlist)
		list(REMOVE_DUPLICATES auxlist)
		list(SORT auxlist)
	endif()
	set(${dirlist} ${auxlist})
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_module_dependencies
#		This macro adds the module dependencies to the current module
#
# INPUT
#		${ARGN}	: list with the dependencies list
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(add_module_dependencies)
	if (${ARGC})
		myLog("add_module_dependencies - ${CMAKE_CURRENT_SOURCE_DIR}")
		buildLog("Project dependencies:")
		foreach(mod_name ${ARGN})
			getLibName(IMPORT_LIBNAME ${mod_name})
			set(COMPONENT_PATH "NOT_FOUND")
			
			# Try to find an external component in a binary distribution
			foreach(layer ${BIN_LAYER_LIST})
				getLibDirName(LIB_DIR_NAME)
				set(_layer_dir ${layer}/${LIB_DIR_NAME})
				if (IS_DIRECTORY ${_layer_dir}/${IMPORT_LIBNAME})
					set(COMPONENT_PATH ${_layer_dir}/${IMPORT_LIBNAME})
					buildLog("-- External package: ${COMPONENT_PATH}")
					break()
				endif()
			endforeach()

			if(${COMPONENT_PATH} STREQUAL "NOT_FOUND")
				getLibDirName(LIB_DIR_NAME)
				set(_layer_dir ${BFW_INSTALL_DIR}/${LIB_DIR_NAME})
				# Try to find an external component in the install directory
				if (IS_DIRECTORY ${_layer_dir})
					get_filename_component(COMPONENT_PATH ${_layer_dir}/${IMPORT_LIBNAME} ABSOLUTE)
				endif()
			endif()

			if(NOT ${COMPONENT_PATH} STREQUAL "NOT_FOUND")
				# For Visual Studio Generators the libraries are into a sub-folder: Debug or Release
				if(${CMAKE_GENERATOR} MATCHES "Visual Studio")
					set(COMPONENT_LIB_PATH ${COMPONENT_PATH}/${CMAKE_BUILD_TYPE})
				else()
					set(COMPONENT_LIB_PATH ${COMPONENT_PATH})
				endif()
				
				# We've found the dependency, so include its public headers folder
				buildLog("-- Found: ${mod_name} - ${COMPONENT_LIB_PATH}/${CMAKE_STATIC_LIBRARY_PREFIX}${IMPORT_LIBNAME}${CMAKE_STATIC_LIBRARY_SUFFIX}")
				include_directories(${COMPONENT_PATH})
				
				# And add the library to the libraries list
				list(APPEND ${PROJECT_NAME}_LIBS ${COMPONENT_LIB_PATH}/${CMAKE_STATIC_LIBRARY_PREFIX}${IMPORT_LIBNAME}${CMAKE_STATIC_LIBRARY_SUFFIX})
				list(APPEND ${PROJECT_NAME}_DEPENDS ${IMPORT_LIBNAME})
			else()
				buildLog("\n<add_module_dependencies> Probable error, component ${mod_name} was not found. << ${${mod_name}_SOURCE_DIR} >>\n")
			endif()
		endforeach()
		list(REMOVE_DUPLICATES ${PROJECT_NAME}_LIBS)
		list(REMOVE_DUPLICATES ${PROJECT_NAME}_DEPENDS)
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_exe_dependencies
#		This macro adds the exe dependencies to the current module
#
# INPUT
#		${ARGN}	: list with the dependencies list
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(add_exe_dependencies)
	if (${ARGC})
		myLog("add_exe_dependencies - ${CMAKE_CURRENT_SOURCE_DIR}")
		buildLog("Project exe dependencies:")
		foreach(exe_name ${ARGN})
			getLibName(IMPORT_EXENAME ${exe_name})
			list(APPEND ${PROJECT_NAME}_EXE_DEPENDS ${IMPORT_EXENAME})
		endforeach()
		list(REMOVE_DUPLICATES ${PROJECT_NAME}_EXE_DEPENDS)
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	include_module_directories
#		This macro adds extra include directories to the module, relative to the module
#		source folder
#
# INPUT
#		${ARGN}	: list with the directories to the included
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(include_module_directories)
	if (${ARGC})
		myLog("include_module_directories - ${CMAKE_CURRENT_SOURCE_DIR}")
		foreach(folder ${ARGN})
			get_filename_component(folder_absolute ${CMAKE_CURRENT_SOURCE_DIR}/source/${folder} ABSOLUTE)
			if(NOT EXISTS ${folder_absolute})
				message(FATAL_ERROR "\n<include_module_directories> Module ${PROJECT_NAME}: folder ${folder_absolute} does not exist")
			endif()
			include_directories(${folder_absolute})
		endforeach()
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	_add_source_file
#		This macro adds a source file to the current project
#
# INPUT
#		${src_file}	: source file name with full path
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(_add_source_file src_file)
	myLog("_add_source_file - ${CMAKE_CURRENT_SOURCE_DIR}")
	get_filename_component(src_file_absolute ${src_file} ABSOLUTE)
	
	if( ${src_file_absolute} MATCHES \\.proto$ )
		# This file will be generated by the proto compiler, it doesn't exist at this moment
		list(APPEND ${PROJECT_NAME}_PROTO_FILES ${src_file_absolute})
	elseif( ${src_file_absolute} MATCHES \\.c$|\\.cxx$|\\.cpp$|\\.s$|\\.asm$|\\.s62$|\\.s64$ )
		if(NOT EXISTS ${src_file_absolute})
			message(FATAL_ERROR "\n<_add_source_file> Module ${PROJECT_NAME}: source file ${src_file_absolute} does not exist")
		endif()
		list(APPEND ${PROJECT_NAME}_SRC ${src_file_absolute})
	else()
		message(FATAL_ERROR "<_add_source_file> Invalide source file type ${src_file_absolute}")
	endif()
	buildLog("adding source file: ${src_file_absolute}")
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	_add_header_file
#		This macro adds a header file to the current project
#
# INPUT
#		${hdr_file}	: header file name with full path
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(_add_header_file hdr_file)
	myLog("_add_header_file - ${CMAKE_CURRENT_SOURCE_DIR}")
	get_filename_component(hdr_file_absolute ${hdr_file} ABSOLUTE)
	
	if( ${hdr_file_absolute} MATCHES \\.npb.h$|\\.npb.hpp$ )
		# This file will be generated by the proto compiler, it doesn't exist at this moment
		list(APPEND ${PROJECT_NAME}_PUBLIC_PROTO_HEADER ${hdr_file_absolute})
	elseif( ${hdr_file_absolute} MATCHES \\.h$|\\.hpp$ )
		if(NOT EXISTS ${hdr_file_absolute})
			message(FATAL_ERROR "\n<_add_header_file> Module ${PROJECT_NAME}: header file ${hdr_file_absolute} does not exist")
		endif()
		list(APPEND ${PROJECT_NAME}_PUBLIC_HEADER ${hdr_file_absolute})
	else()
		message(FATAL_ERROR "<_add_header_file> Invalide header file type ${hdr_file_absolute}")
	endif()
	buildLog("adding header file: ${hdr_file_absolute}")
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_sources
#		This macro adds the module sources to the source list
#
# INPUT
#		${ARGN}	: list with the source code files to add
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(add_sources)
	if (${ARGC})
		myLog("add_sources - ${CMAKE_CURRENT_SOURCE_DIR}")
		foreach(src ${ARGN})
			_add_source_file(${CMAKE_CURRENT_SOURCE_DIR}/source/${src})
		endforeach()
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_arch_sources
#		This macro adds the module sources to the source list
#
# INPUT
#		${ARGN}	: list with the source code files to add
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
#macro(add_arch_sources)
#	if (${ARGC})
#		myLog("add_arch_sources - ${CMAKE_CURRENT_SOURCE_DIR}")
#		foreach(src ${ARGN})
#			set(src_found FALSE)
#			foreach(_arch ${archList})
#				if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/source/arch/${_arch}/${src})
#					_add_source_file(${CMAKE_CURRENT_SOURCE_DIR}/source/arch/${_arch}/${src})
#					set(src_found TRUE)
#				endif()
#			endforeach()
#			if(NOT src_found)
#				message(FATAL_ERROR "Source File not found: ${src}")
#			endif()
#		endforeach()
#	endif()
#endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_config_arch_sources
#		This macro adds the module sources to the source list
#
# INPUT
#		${ARGN}	: list with the source code files to add
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
#macro(add_config_arch_sources)
#	if (${ARGC})
#		myLog("add_arch_sources - ${CMAKE_CURRENT_SOURCE_DIR}")
#		foreach(src ${ARGN})
#			set(src_found FALSE)
#			foreach(_arch ${archList})
#				if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config/arch/${_arch}/${src})
#					_add_source_file(${CMAKE_CURRENT_SOURCE_DIR}/config/arch/${_arch}/${src})
#					set(src_found TRUE)
#				endif()
#			endforeach()
#			if(NOT src_found)
#				message(FATAL_ERROR "Source File not found: ${src}")
#			endif()
#		endforeach()
#	endif()
#endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_sources_sim
#		This macro adds the module simulator sources to the source list
#
# INPUT
#		${ARGN}	: list with the simulator source code files to add
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(add_sources_simgui)
	if (${ARGC})
		myLog("add_sources - ${CMAKE_CURRENT_SOURCE_DIR}")
		foreach(src ${ARGN})
			list(APPEND ${PROJECT_NAME}_SRC ${src})
		endforeach()
	endif()
	# We need to add the binary directory because of the generated files
	include_directories(${CMAKE_CURRENT_BINARY_DIR})
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	_add_public_proto_headers
#		This macro adds the module public Goggle Protocol Buffer headers to the headers list
#
# INPUT
#		${ARGN}	: list with the header files to add
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(_add_public_proto_headers)
	if (${ARGC})
		myLog("_add_public_proto_headers - ${CMAKE_CURRENT_SOURCE_DIR}")
		foreach(hdr ${ARGN})
			_add_header_file(${CMAKE_CURRENT_BINARY_DIR}/proto/${hdr})
		endforeach()
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_public_headers
#		This macro adds the module public headers to the headers list
#
# INPUT
#		${ARGN}	: list with the header files to add
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
macro(add_public_headers)
	if (${ARGC})
		myLog("add_public_headers - ${CMAKE_CURRENT_SOURCE_DIR}")
		foreach(hdr ${ARGN})
			_add_header_file(${CMAKE_CURRENT_SOURCE_DIR}/source/${hdr})
		endforeach()
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_arch_public_headers
#		This macro adds the module public headers to the headers list
#
# INPUT
#		${ARGN}	: list with the header files to add
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
#macro(add_arch_public_headers)
#	if (${ARGC})
#		myLog("add_arch_public_headers - ${CMAKE_CURRENT_SOURCE_DIR}")
#		foreach(hdr ${ARGN})
#			set(hdr_found FALSE)
#			foreach(_arch ${archList})
#				if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/source/arch/${_arch}/${hdr})
#					_add_header_file(${CMAKE_CURRENT_SOURCE_DIR}/source/arch/${_arch}/${hdr})
#					set(hdr_found TRUE)
#				endif()
#			endforeach()
#			if(NOT hdr_found)
#				message(FATAL_ERROR "Header File not found: ${hdr}")
#			endif()
#		endforeach()
#	endif()
#endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_config_arch_public_headers
#		This macro adds the module public headers to the headers list
#
# INPUT
#		${ARGN}	: list with the header files to add
#
# OUTPUT
#		none	: 
#
#		NOTE: 
#-----------------------------------------------------------------------------------------
#macro(add_config_arch_public_headers)
#	if (${ARGC})
#		myLog("add_arch_public_headers - ${CMAKE_CURRENT_SOURCE_DIR}")
#		foreach(hdr ${ARGN})
#			set(hdr_found FALSE)
#			foreach(_arch ${archList})
#				if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/config/arch/${_arch}/${hdr})
#					_add_header_file(${CMAKE_CURRENT_SOURCE_DIR}/config/arch/${_arch}/${hdr})
#					set(hdr_found TRUE)
#				endif()
#			endforeach()
#			if(NOT hdr_found)
#				message(FATAL_ERROR "Header File not found: ${hdr}")
#			endif()
#		endforeach()
#	endif()
#endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	_add_module_lib
#		This macro adds the current module as a static library to the build system
#
# INPUT
#		none	: 
#
# OUTPUT
#		none	: 
#
#		NOTE: This macro also creates a custom project to lint the module
#-----------------------------------------------------------------------------------------
macro(_add_module_lib)
	myLog("_add_module_lib - ${CMAKE_CURRENT_SOURCE_DIR}")
	# Add the version file if exists
	#if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")
	#	list(APPEND ${PROJECT_NAME}_SRC "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")
	#endif()
	add_library(${LIBNAME} STATIC ${${PROJECT_NAME}_SRC})

	if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
		#
		# When building with Visual Studio it doesn't support these dependencies
		#
		add_dependencies(${PROJECT_NAME} ${LIBNAME})
		# Add all the dependencies to the library
		if(${PROJECT_NAME}_DEPENDS)
			add_dependencies(${LIBNAME} ${${PROJECT_NAME}_DEPENDS})
		endif()
		add_dependencies(${LIBNAME} "${PROJECT_NAME}_headers")
	endif()
	# Add the nanopb proto file, this will add a custom target to build them
	if(${PROJECT_NAME}_PROTO_FILES)
		add_nanopb_proto(${${PROJECT_NAME}_PROTO_FILES})
	endif()
	# Add custom Lint target, which will include nanopb proto files if any
	if(${CMAKE_BINARY_DIR} MATCHES "_lint")
		add_pc_lint(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})
	endif()
endmacro()

#
# Copy public header(s) and library to install directory.
# Note: Headers are copied at CMake config time, rest at build time.
#		Optional third argument is public header list.
#
macro(install_module_lib)
	myLog("install_module_lib - ${CMAKE_CURRENT_SOURCE_DIR}")

	if(${PROJECT_NAME}_PUBLIC_PROTO_HEADER)
		list(REMOVE_DUPLICATES ${PROJECT_NAME}_PUBLIC_PROTO_HEADER)
	endif()
	if(${PROJECT_NAME}_PUBLIC_HEADER)
		list(REMOVE_DUPLICATES ${PROJECT_NAME}_PUBLIC_HEADER)
	endif()

	_add_module_lib()

	getLibDirName(LIB_DIR_NAME)
	get_filename_component(_LIB_INSTALL_DIR ${BFW_INSTALL_DIR}/${LIB_DIR_NAME}/${LIBNAME} ABSOLUTE)
	
	#
	# Purge any headers that are no longer part of the public ones.
	#
	file(GLOB _fullfoundhdrs "${_LIB_INSTALL_DIR}/*.h*")
	set(_install_hdrs)
	foreach(_header ${_fullfoundhdrs})
		get_filename_component(_name ${_header} NAME)
		list(APPEND _install_hdrs ${_name})
	endforeach()

	if(_install_hdrs)
		set(_hdrs)
		foreach(_header ${${PROJECT_NAME}_PUBLIC_HEADER})
			get_filename_component(_name ${_header} NAME)
			list(APPEND _hdrs ${_name})
		endforeach()

		foreach(_header ${${PROJECT_NAME}_PUBLIC_PROTO_HEADER})
			get_filename_component(_name ${_header} NAME)
			list(APPEND _hdrs ${_name})
		endforeach()

		foreach(_header ${_hdrs})
			list(REMOVE_ITEM _install_hdrs ${_header})
		endforeach()

		foreach(_header ${_install_hdrs})
			message("Purging dead header file: ${_LIB_INSTALL_DIR}/${_header}")
			execute_process(COMMAND ${CMAKE_COMMAND} -E remove ${_LIB_INSTALL_DIR}/${_header})
		endforeach()
	endif()
	
	#
	# Copy public header files to install dir
	#
	set(_clean_headers)
	foreach(_header ${${PROJECT_NAME}_PUBLIC_HEADER})
		configure_file(${_header} ${_LIB_INSTALL_DIR} COPYONLY)
		if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
			get_filename_component(_name ${_header} NAME)
			list(APPEND _clean_headers ${_LIB_INSTALL_DIR}/${_name})
		endif()
	endforeach()
	set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${_clean_headers}")

	set(OUTPUT_LIB_NAME ${COMPONENT_LIB_INTERMEDIATE_DIR}${CMAKE_STATIC_LIBRARY_PREFIX}${LIBNAME})

	#if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/version.txt")
	#	file(APPEND "${CMAKE_BINARY_DIR}/versions.txt" "${PROJECT_NAME}VersionStr = VVS_${LIBNAME}-${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH};\n")
	#endif()

endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	add_libs_to_exe
#		This macro adds external libraries to the project
#
# INPUT
#		${ARGN}	: list with the libraries to the added, with full path
#
# OUTPUT
#		none	: 
#
#		NOTE:
#-----------------------------------------------------------------------------------------
macro(add_libs_to_exe)
	myLog("add_libs_to_exe - ${CMAKE_CURRENT_SOURCE_DIR}")
	foreach(lib ${ARGN})
		list(APPEND ${PROJECT_NAME}_LIBS ${lib})
	endforeach()
	list(REMOVE_DUPLICATES ${PROJECT_NAME}_LIBS)
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	_add_module_exe
#		This macro adds the current module as an executable to the build system
#
# INPUT
#		none	: 
#
# OUTPUT
#		none	: 
#
#		NOTE: This macro also creates a custom project to lint the module
#-----------------------------------------------------------------------------------------
macro(_add_module_exe)
	myLog("_add_module_exe - ${CMAKE_CURRENT_SOURCE_DIR}")
	# Add the version file if exists
	#if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")
	#	list(APPEND ${PROJECT_NAME}_SRC "${CMAKE_CURRENT_BINARY_DIR}/version.cpp")
	#endif()
	
	add_executable(${LIBNAME} ${${PROJECT_NAME}_SRC})
	target_link_libraries(${LIBNAME} ${${PROJECT_NAME}_LIBS})
	if(DEFINED rts_ti_lib)
		# rts_xxx.lib shall be the last linked library to avoid redefinition problems with other libraries
		target_link_libraries(${LIBNAME} ${rts_ti_lib})
	endif()
	
	# Add custom Lint target
	if(${CMAKE_BINARY_DIR} MATCHES "_lint")
		add_pc_lint(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})
	endif()
	
	if(NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
		#
		# When building with Visual Studio it doesn't support these dependencies
		#
		add_dependencies(${PROJECT_NAME} ${LIBNAME})
	endif()

	# Add all the dependencies to the application
	if(${PROJECT_NAME}_EXE_DEPENDS)
		add_dependencies(${LIBNAME} ${${PROJECT_NAME}_EXE_DEPENDS})
	endif()
	if(${PROJECT_NAME}_DEPENDS)
		add_dependencies(${LIBNAME} ${${PROJECT_NAME}_DEPENDS})
	endif()
endmacro()

#-----------------------------------------------------------------------------------------
# MACRO	install_module_exe
#		This macro adds the current module as an executable to the build system
#
# INPUT
#		none	: 
#
# OUTPUT
#		none	: 
#
#		NOTE: This macro also creates a custom project to lint the module
#-----------------------------------------------------------------------------------------
macro(install_module_exe)
	myLog("install_module_exe - ${CMAKE_CURRENT_SOURCE_DIR}")
	#
	# Set the executable output path
	#
	get_filename_component(EXECUTABLE_OUTPUT_PATH ${BFW_INSTALL_DIR}/images ABSOLUTE)
	#
	# Install folder
	#
	file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH})
	#
	# Extra files to clean
	#
	if(NOT MSVC)
		set_directory_properties(PROPERTIES	ADDITIONAL_MAKE_CLEAN_FILES	${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.map)
		set_directory_properties(PROPERTIES	ADDITIONAL_MAKE_CLEAN_FILES	${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.bin)
	endif()

	_add_module_exe()
endmacro()
