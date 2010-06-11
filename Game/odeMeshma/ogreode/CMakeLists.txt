######################################################################
# OGREODE BUILD SYSTEM
# This is the main CMake file where we prepare the general build
# environment and provide build configuration options.
######################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# Works around warnings libraries linked against that don't have absolute paths (e.g. -lOgreMain)
CMAKE_POLICY(SET CMP0003 NEW)

# Works around warnings about escaped quotes in ADD_DEFINITIONS statements.
CMAKE_POLICY(SET CMP0005 NEW)

PROJECT(OgreOde)

SET(OGREODE_BUILD ${CMAKE_CURRENT_BINARY_DIR})
SET(OGREODE_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})

OPTION(OGREODE_DIST "OgreOde Installer Installation" FALSE)

# Somehow, relative paths do not work on Linux when installing files..
IF(UNIX)
	SET(PREFIX ${CMAKE_INSTALL_PREFIX})
ELSE()
	SET(PREFIX "./")
ENDIF()

SET(OGREODE_WORK_DIR ${CMAKE_CURRENT_BINARY_DIR})

# CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up differentiation between debug and release builds.
IF(CMAKE_BUILD_TYPE STREQUAL "")
	SET(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release MinSizeRel RelWithDebInfo." FORCE)
ENDIF()

SET(CMAKE_DEBUG_POSTFIX "_d")

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/;${CMAKE_MODULE_PATH}")

FIND_PACKAGE(ODE REQUIRED)
FIND_PACKAGE(OGRE REQUIRED)
FIND_PACKAGE(OIS REQUIRED)

IF (NOT (("${OGRE_VERSION_NAME}" STREQUAL "Cthugha") OR ("${OGRE_VERSION_NAME}" STREQUAL "Shoggoth")))
	MESSAGE(SEND_ERROR "You need Ogre version 1.6 or 1.7 to build OgreOde.")
ENDIF()

IF(UNIX)
	get_filename_component(OGRE_PLUGIN_DIR_LINUX ${OGRE_Plugin_OctreeSceneManager_LIBRARY_REL} PATH)
	set (OGRE_PLUGIN_DIR_LINUX ${OGRE_PLUGIN_DIR_LINUX} CACHE STRING "Ogre Plugin Dir (Release)")
ENDIF(UNIX)

# Set up the floating point precision preprocessor define
IF(EXISTS ${OGRE_CONFIG_INCLUDE_DIR}/OgreBuildSettings.h)
	file(READ ${OGRE_CONFIG_INCLUDE_DIR}/OgreBuildSettings.h OGRE_SETTINGS)
	get_preprocessor_entry(OGRE_SETTINGS OGRE_DOUBLE_PRECISION USE_DOUBLE_PRECISION)
	GET_FILENAME_COMPONENT(ODE_REL_LIB_NAME ${ODE_LIBRARY_REL} NAME_WE)
ENDIF()

# Check to ensure that floating point precision is consistent in ODE and Ogre
IF(((USE_DOUBLE_PRECISION) AND ("${ODE_REL_LIB_NAME}" STREQUAL "ode_single")) OR (NOT(USE_DOUBLE_PRECISION) AND ("${ODE_REL_LIB_NAME}" STREQUAL "ode_double")))
	MESSAGE(FATAL_ERROR "Floating point precision inconsistent between Ogre and ODE.  Ogre, ODE, and OgreOde must all use the same precision or runtime will fail.")
ENDIF()


INCLUDE_DIRECTORIES(
	BEFORE
	${OGRE_INCLUDE_DIRS}
	${ODE_INCLUDE_DIRS}
)

# Use different Samples includes folder if using Ogre SDK
IF(EXISTS ${OGRE_HOME}/Samples/Common/include)
	# Source
	SET(OGRE_SAMPLES_INCLUDE_DIR ${OGRE_HOME}/Samples/Common/include)
ELSE()
	# SDK
	SET(OGRE_SDK ${OGRE_HOME})
	SET(OGRE_SAMPLES_INCLUDE_DIR ${OGRE_HOME}/samples/include)
ENDIF()

# OgreOde
SET(OGREODE_INCLUDES "${OGREODE_BUILD}/include")
SET(OGREODE_LIBPATH  "${OGREODE_BUILD}/lib")

# Dependencies
SET(OIS_LIBRARY_PATH ${OIS_LIBRARY_PATH})

# Copy CMake lists for ODE into user-defined source directory
#CONFIGURE_FILE(${CMAKE_MODULE_PATH}/ode/CMakeLists_ODE.txt COPYONLY DESTINATION ${ODE_SOURCE}/ode/CMakeLists.txt)

# Setup Dependencies
ADD_SUBDIRECTORY(tinyxml)
ADD_SUBDIRECTORY(Core)
ADD_SUBDIRECTORY(prefab)
ADD_SUBDIRECTORY(loader)
ADD_SUBDIRECTORY(demos/GranTurismOgre)
ADD_SUBDIRECTORY(demos/Landscape)
ADD_SUBDIRECTORY(demos/SimpleScenes)

# Set up install configuration
IF(UNIX)
	SET(MEDIA_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/share/OgreOde)
ELSEIF(WIN32)
	SET(MEDIA_INSTALL_PATH ${CMAKE_INSTALL_PREFIX})
ENDIF()

# Set location of Ogre media files depending on if using OgreSDK or Ogre source
IF(NOT("${OGRE_SDK}" STREQUAL ""))
	SET(OGRE_MEDIA_DIR ${OGRE_HOME}/media)
ELSE()
	SET(OGRE_MEDIA_DIR ${OGRE_HOME}/Samples/Media)
ENDIF()

# Specify Ogre media file subdirectories
SET(OGRE_MEDIA_SUBDIRS fonts
	materials
	models
	particle
)
# Install OgreOde media files
SET(OGREODE_MEDIA_DIR ${OGREODE_SOURCE}/demos/Media)
INSTALL(DIRECTORY ${OGREODE_MEDIA_DIR}
	DESTINATION ${MEDIA_INSTALL_PATH}
	PATTERN ".svn" EXCLUDE
)
# Install Ogre media files
FOREACH(OGRE_MEDIA_SUBDIR ${OGRE_MEDIA_SUBDIRS})
	INSTALL(DIRECTORY ${OGRE_MEDIA_DIR}/${OGRE_MEDIA_SUBDIR}
		DESTINATION ${MEDIA_INSTALL_PATH}/Media
		PATTERN ".svn" EXCLUDE
	)
ENDFOREACH(OGRE_MEDIA_SUBDIR)

# Set up Ogre DLL files to be installed to runtime directory for users who want to run from the bin
OPTION(INSTALL_OGRE_RUNTIME "Install the Ogre DLL files to the runtime directory." FALSE)
IF(INSTALL_OGRE_RUNTIME)
	SET(OGRE_REQUIRED_LIBS OGRE_BINARY
		OGRE_RenderSystem_Direct3D9
		OGRE_RenderSystem_GL
		OGRE_Plugin_OctreeSceneManager
		OGRE_Plugin_ParticleFX
		OIS
	)
	SET(OGRE_OPTIONAL_LIBS OGRE_RenderSystem_Direct3D10
		OGRE_RenderSystem_Direct3D11
		OGRE_RenderSystem_GLES
		OGRE_Plugin_BSPSceneManager
		OGRE_Plugin_CgProgramManager
		OGRE_Plugin_OctreeZone
		OGRE_Plugin_PCZSceneManager
	)
ENDIF()

if (UNIX)
  include(OgreOdeUtils)
  install_ogreode_resourceconfig()
endif()

FOREACH(CONFIG ${CMAKE_CONFIGURATION_TYPES})
	IF(NOT(EXISTS ${CMAKE_INSTALL_PREFIX}/bin))
		FILE(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin")
	ELSEIF(NOT(EXISTS ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}))
		FILE(MAKE_DIRECTORY "${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}")
	ENDIF()
	# Install the resources.cfg file, which is configuration independent
	INSTALL(FILES CMake/Templates/resources.cfg
		DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
		CONFIGURATIONS ${CONFIG}
	)
	IF((${CONFIG} MATCHES "Debug") OR (${CONFIG} MATCHES "debug"))
		IF(INSTALL_OGRE_RUNTIME)
			# Install core Ogre plugins required to run the demos
			FOREACH(OGRE_REQUIRED_LIB ${OGRE_REQUIRED_LIBS})
				INSTALL(FILES ${${OGRE_REQUIRED_LIB}_DBG}
					DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
					CONFIGURATIONS ${CONFIG}
				)
			ENDFOREACH(OGRE_REQUIRED_LIB)
			# Install Ogre plugins not required to run the demos
			FOREACH(OGRE_OPTIONAL_LIB ${OGRE_OPTIONAL_LIBS})
				INSTALL(FILES ${${OGRE_OPTIONAL_LIB}_DBG}
					DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
					CONFIGURATIONS ${CONFIG}
					OPTIONAL
				)
			ENDFOREACH(OGRE_OPTIONAL_LIB)
		ENDIF()
		
		# Install the debug plugin.cfg file with the "_d" suffixes for Debug
		INSTALL(FILES CMake/Templates/plugins_d.cfg
			DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
			CONFIGURATIONS ${CONFIG}
			RENAME plugins.cfg
		)
		# Install the ODE DLL if it exists
		INSTALL(FILES ${ODE_DBG}
			DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
			CONFIGURATIONS ${CONFIG}
			OPTIONAL
		)
	ELSE()
		IF(INSTALL_OGRE_RUNTIME)
			# Install core Ogre plugins required to run the demos
			FOREACH(OGRE_REQUIRED_LIB ${OGRE_REQUIRED_LIBS})
				INSTALL(FILES ${${OGRE_REQUIRED_LIB}_REL}
					DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
					CONFIGURATIONS ${CONFIG}
				)
			ENDFOREACH(OGRE_REQUIRED_LIB)
			# Install Ogre plugins not required to run the demos
			FOREACH(OGRE_OPTIONAL_LIB ${OGRE_OPTIONAL_LIBS})
				INSTALL(FILES ${${OGRE_OPTIONAL_LIB}_REL}
					DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
					CONFIGURATIONS ${CONFIG}
					OPTIONAL
				)
			ENDFOREACH(OGRE_OPTIONAL_LIB)
		ENDIF()
		# Install the release plugin.cfg file
		INSTALL(FILES CMake/Templates/plugins.cfg
			DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
			CONFIGURATIONS ${CONFIG}
		)
		# Install the ODE DLL if it exists
		INSTALL(FILES ${ODE_REL}
			DESTINATION ${CMAKE_INSTALL_PREFIX}/bin/${CONFIG}
			CONFIGURATIONS ${CONFIG}
			OPTIONAL
		)
	ENDIF()
ENDFOREACH(CONFIG)