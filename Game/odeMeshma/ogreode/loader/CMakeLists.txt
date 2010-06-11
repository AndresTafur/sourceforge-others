# -*- cmake -*-

PROJECT(OgreOde_Loader)

## section: include directory
INCLUDE_DIRECTORIES(
	include
	../Core/include
	../prefab/include
	${ODE_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	../tinyxml
)

## section: source files
SET(OgreOde_Loader_SOURCE_FILES
	src/OgreOdeDotLoader.cpp
)

## section: header files
SET(OgreOde_Loader_HEADER_FILES
	include/OgreOde_Loader.h
	include/OgreOde_LoaderPreReqs.h
	include/OgreOdeDotLoader.h
)

SET_SOURCE_FILES_PROPERTIES(OgreOde_Loader_HEADER_FILES
	PROPERTIES HEADER_FILE_ONLY TRUE)
LIST(APPEND OgreOde_Loader_SOURCE_FILES ${OgreOde_Loader_HEADER_FILES})

## section: add definitions
ADD_DEFINITIONS(${OSP_DEFINITIONS} -DOGREODEEXPORT_LOADER)

## section: add target
ADD_LIBRARY(OgreOde_Loader SHARED ${OgreOde_Loader_SOURCE_FILES})

## section: add dependency
ADD_DEPENDENCIES(OgreOde_Loader
	tinyxml
	OgreOde_Core
	OgreOde_Prefab
)

## section: set link libraries
# DO NOT add suffix(.lib .so) to lib name.
TARGET_LINK_LIBRARIES(OgreOde_Loader
	OgreOde_Core
	OgreOde_Prefab
	${OGRE_LIBRARY}
	tinyxml
)

include(OgreOdeUtils)
install_ogreode_headers("OgreOde_Loader" "${OgreOde_Loader_HEADER_FILES}" )
install_ogreode_lib( "OgreOde_Loader" )
