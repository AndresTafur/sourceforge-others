# -*- cmake -*-

PROJECT(OgreOde_Prefab)

## section: include directory
INCLUDE_DIRECTORIES(
	include
	../Core/include
	${ODE_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIR}
)

## section: source files
SET(OgreOde_Prefab_SOURCE_FILES
	src/OgreOdePrefabObject.cpp
	src/OgreOdeRagdoll.cpp
	src/OgreOdeVehicle.cpp
)

## section: header files
SET(OgreOde_Prefab_HEADER_FILES
	include/OgreOde_Prefab.h
	include/OgreOdePrefabObject.h
	include/OgreOdeRagdoll.h
	include/OgreOdeVehicle.h
	include/OgreOde_PrefabPreReqs.h
)

SET_SOURCE_FILES_PROPERTIES(OgreOde_Prefab_HEADER_FILES
	PROPERTIES HEADER_FILE_ONLY TRUE)
LIST(APPEND OgreOde_Prefab_SOURCE_FILES ${OgreOde_Prefab_HEADER_FILES})

## section: add definitions
ADD_DEFINITIONS(${OSP_DEFINITIONS} -DOGREODEEXPORT_PREFAB)

## section: add target
ADD_LIBRARY(OgreOde_Prefab SHARED ${OgreOde_Prefab_SOURCE_FILES})

## section: add dependency
ADD_DEPENDENCIES(OgreOde_Prefab
	OgreOde_Core
)

## section: set link libraries
# DO NOT add suffix(.lib .so) to lib name.
TARGET_LINK_LIBRARIES(OgreOde_Prefab
	OgreOde_Core
	${OGRE_LIBRARY}
)

include(OgreOdeUtils)
install_ogreode_headers("OgreOde_Prefab" "${OgreOde_Prefab_HEADER_FILES}" )
install_ogreode_lib( "OgreOde_Prefab" )
