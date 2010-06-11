#-------------------------------------------------------------------
# This file is part of the CMake build system for OgreODE
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

# - Try to find ODE
# Once done, this will define
#
#  ODE_FOUND - system has ODE
#  ODE_INCLUDE_DIRS - the ODE include directories
#  ODE_LIBRARIES - link these to use ODE

include(FindPkgMacros)
include(PreprocessorUtils)

findpkg_begin(ODE)

# construct search paths
getenv_path(ODE_SOURCE)
find_path(ODE_SOURCE NAMES include/ode/odeconfig.h HINTS ${ODE_SOURCE} ${CMAKE_CURRENT_SOURCE_DIR}/ode)
set(ODE_PREFIX_PATH ${ODE_SOURCE} ${ENV_ODE_SOURCE})

create_search_paths(ode)

# Redo search if prefix path changed
clear_if_changed(ODE_PREFIX_PATH
  ODE_LIBRARY_REL
  ODE_LIBRARY_DBG
  ODE_INCLUDE_DIR
)

# Set variable based on precision for which ODE library to use
IF(USE_DOUBLE_PRECISION)
	SET(ODE_PRECISION double)
ELSE()
	SET(ODE_PRECISION single)
ENDIF()

set(ODE_LIBRARY_NAMES ode ode_${ODE_PRECISION} libode libode_${ODE_PRECISION})

get_debug_names(ODE_LIBRARY_NAMES)

findpkg_framework(ode)

use_pkgconfig(ODE_PKGC ode)

# Find ODE include and library directories
find_path(ODE_INCLUDE_DIR NAMES ode.h HINTS ${ODE_PKGC_INCLUDE_DIRS} ${ODE_SOURCE}/include/ode PATH_SUFFIXES ode)
find_library(ODE_LIBRARY_REL NAMES ${ODE_LIBRARY_NAMES} HINTS ${ODE_PKGC_LIBRARY_DIRS} ${ODE_SOURCE}/lib ${ODE_SOURCE}/lib/ReleaseSingleDLL ${ODE_SOURCE}/lib/ReleaseDoubleDLL)
find_library(ODE_LIBRARY_DBG NAMES ${ODE_LIBRARY_NAMES_DBG} HINTS ${ODE_PKGC_LIBRARY_DIRS} ${ODE_SOURCE}/lib ${ODE_SOURCE}/lib/DebugSingleDLL ${ODE_SOURCE}/lib/DebugDoubleDLL)
make_library_set(ODE_LIBRARY)

IF(NOT("${ODE_INCLUDE_DIR}" STREQUAL "ODE_INCLUDE_DIR-NOTFOUND"))
	SET(ODE_FOUND TRUE)
ENDIF()

# Add variable for runtime library
GET_FILENAME_COMPONENT(ODE_LIB_PATH_REL ${ODE_LIBRARY_REL} PATH)
GET_FILENAME_COMPONENT(ODE_LIB_PATH_DBG ${ODE_LIBRARY_DBG} PATH)
GET_FILENAME_COMPONENT(ODE_BINARY_NAME ${ODE_LIBRARY_REL} NAME_WE)
IF(WIN32)
	find_file(ODE_REL NAMES ${ODE_BINARY_NAME}.dll HINTS ${ODE_LIB_PATH_REL})
	find_file(ODE_DBG NAMES ${ODE_BINARY_NAME}d.dll HINTS ${ODE_LIB_PATH_DBG})
ENDIF()
mark_as_advanced(ODE_REL ODE_DBG)	

findpkg_finish(ODE)

add_parent_dir(ODE_INCLUDE_DIRS ODE_INCLUDE_DIR)

