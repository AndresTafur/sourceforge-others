# -*- cmake -*-

PROJECT(OgreOde_Core)

## section: include directory
INCLUDE_DIRECTORIES(
	include
	${ODE_INCLUDE_DIRS}
	${OGRE_INCLUDE_DIRS}
)

## section: source files
SET(OgreOde_Core_SOURCE_FILES
	src/OgreOdeBody.cpp
	src/OgreOdeCollision.cpp
	src/OgreOdeDebugContact.cpp
	src/OgreOdeDebugObject.cpp
	src/OgreOdeEigenSolver.cpp
	src/OgreOdeEntityInformer.cpp
	src/OgreOdeGeometry.cpp
	src/OgreOdeJoint.cpp
	src/OgreOdeMaintainedList.cpp
	src/OgreOdeMass.cpp
	src/OgreOdePrecompiledHeaders.cpp
	src/OgreOdeSpace.cpp
	src/OgreOdeStepper.cpp
	src/OgreOdeTriangleMeshData.cpp
	src/OgreOdeTriangleMeshDataManager.cpp
	src/OgreOdeUtility.cpp
	src/OgreOdeWorld.cpp
)

## section: header files
SET(OgreOde_Core_HEADER_FILES
	include/OgreOde_Core.h
	include/OgreOdeBody.h
	include/OgreOdeCollision.h
	include/OgreOdeDebugContact.h
	include/OgreOdeDebugObject.h
	include/OgreOdeEigenSolver.h
	include/OgreOdeEntityInformer.h
	include/OgreOdeFrameListener.h
	include/OgreOdeGeometry.h
	include/OgreOdeJoint.h
	include/OgreOdeMaintainedList.h
	include/OgreOdeMass.h
	include/OgreOdePrecompiledHeaders.h
	include/OgreOdePreReqs.h
	include/OgreOdeSpace.h
	include/OgreOdeStepper.h
	include/OgreOdeTriangleMeshData.h
	include/OgreOdeTriangleMeshDataManager.h
	include/OgreOdeUtility.h
	include/OgreOdeWorld.h
)

SET_SOURCE_FILES_PROPERTIES(OgreOde_Core_HEADER_FILES
	PROPERTIES HEADER_FILE_ONLY TRUE)
LIST(APPEND OgreOde_Core_SOURCE_FILES ${OgreOde_Core_HEADER_FILES})

## section: add definitions
IF(USE_DOUBLE_PRECISION)
	pkg_message(OgreOde_Core "OgreOde set to compile with DOUBLE precision.")
	ADD_DEFINITIONS(${OSP_DEFINITIONS} -DOGREODE_EXPORTS -DdDOUBLE)
ELSE()
	pkg_message(OgreOde_Core "OgreOde set to compile with SINGLE precision.")
	ADD_DEFINITIONS(${OSP_DEFINITIONS} -DOGREODE_EXPORTS -DdSINGLE)
ENDIF()

## section: add target
ADD_LIBRARY(OgreOde_Core SHARED ${OgreOde_Core_SOURCE_FILES})

## section: add dependency
#ADD_DEPENDENCIES(OgreOde_Core)

## section: set link libraries
# DO NOT add suffix(.lib .so) to lib name.
TARGET_LINK_LIBRARIES(OgreOde_Core
	${ODE_LIBRARY}
	${OGRE_LIBRARY}
)

include(OgreOdeUtils)
install_ogreode_headers("OgreOde_Core" "${OgreOde_Core_HEADER_FILES}" )
install_ogreode_lib( "OgreOde_Core" )
