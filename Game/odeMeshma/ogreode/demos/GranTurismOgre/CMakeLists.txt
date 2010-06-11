# -*- cmake -*-

PROJECT(Demo_GranTurismOgre)

## section: include directory
INCLUDE_DIRECTORIES(
	include
	../../Core/include
	../../loader/include
	../../prefab/include
	${ODE_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
	${OGRE_SAMPLES_INCLUDE_DIR}
	${OIS_INCLUDE_DIRS}
)

## section: source files
SET(Demo_GranTurismOgre_SOURCE_FILES
	src/GranTurismOgre.cpp
)

## section: header files
SET(Demo_GranTurismOgre_HEADER_FILES
	include/GranTurismOgre.h
)

SET_SOURCE_FILES_PROPERTIES(Demo_GranTurismOgre_HEADER_FILES
	PROPERTIES HEADER_FILE_ONLY TRUE)
LIST(APPEND Demo_GranTurismOgre_SOURCE_FILES ${Demo_GranTurismOgre_HEADER_FILES})

## section: add definitions
ADD_DEFINITIONS(${OSP_DEFINITIONS})

## section: add target
ADD_EXECUTABLE(Demo_GranTurismOgre ${Demo_GranTurismOgre_SOURCE_FILES})

IF(WIN32)
	SET_TARGET_PROPERTIES(Demo_GranTurismOgre
		PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
	SET_TARGET_PROPERTIES(Demo_GranTurismOgre
		PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
	SET_TARGET_PROPERTIES(Demo_GranTurismOgre
		PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	SET_TARGET_PROPERTIES(Demo_GranTurismOgre
		PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
ENDIF(WIN32)

## section: add dependency
ADD_DEPENDENCIES(Demo_GranTurismOgre
	OgreOde_Core
	OgreOde_Loader
)

TARGET_LINK_LIBRARIES(Demo_GranTurismOgre
	OgreOde_Core
	OgreOde_Loader
	${OGRE_LIBRARY}
	${OIS_LIBRARY}
)
include(OgreOdeUtils)
install_ogreode_binary( "Demo_GranTurismOgre" )

