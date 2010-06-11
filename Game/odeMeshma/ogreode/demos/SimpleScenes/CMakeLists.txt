# -*- cmake -*-

PROJECT(Demo_SimpleScenes)

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
SET (Demo_SimpleScenes_SOURCE_FILES
	src/SimpleScenes.cpp
	src/SimpleScenesApplication.cpp
)

## section: header files
SET(Demo_SimpleScenes_HEADER_FILES
	include/SimpleScenes.h
	include/SimpleScenes_BoxStack.h
	include/SimpleScenes_Buggy.h
	include/SimpleScenes_Chain.h
	include/SimpleScenes_Crash.h
	include/SimpleScenes_Joints.h
	include/SimpleScenes_TriMesh.h
	include/SimpleScenes_Zombie.h
	include/SimpleScenesApplication.h
)

SET_SOURCE_FILES_PROPERTIES(Demo_SimpleScenes_HEADER_FILES
	PROPERTIES HEADER_FILE_ONLY TRUE)
LIST(APPEND Demo_SimpleScenes_SOURCE_FILES ${Demo_SimpleScenes_HEADER_FILES})

## section: add definitions
ADD_DEFINITIONS(${OSP_DEFINITIONS})

## section: add target
ADD_EXECUTABLE(Demo_SimpleScenes ${Demo_SimpleScenes_SOURCE_FILES})

IF(WIN32)
	SET_TARGET_PROPERTIES(Demo_SimpleScenes
		PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
	SET_TARGET_PROPERTIES(Demo_SimpleScenes
		PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
	SET_TARGET_PROPERTIES(Demo_SimpleScenes
		PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	SET_TARGET_PROPERTIES(Demo_SimpleScenes
		PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
ENDIF(WIN32)

## section: add dependency
ADD_DEPENDENCIES(Demo_SimpleScenes
	OgreOde_Core
	OgreOde_Prefab
	OgreOde_Loader
)

## section: set link libraries
# DO NOT add suffix(.lib .so) to lib name.
TARGET_LINK_LIBRARIES(Demo_SimpleScenes
	OgreOde_Core
	OgreOde_Loader
	${OGRE_LIBRARY}
	${OIS_LIBRARY}
)
include(OgreOdeUtils)
install_ogreode_binary("Demo_SimpleScenes")

