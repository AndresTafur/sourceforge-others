# -*- cmake -*-

PROJECT(tinyxml)

## section: include directory
# add your target-specific include directory here.

INCLUDE_DIRECTORIES(
)

## section: source files
# add your source files here
SET (tinyxml_SOURCE_FILES
	changes.txt
	readme.txt
	tinystr.cpp
	tinyxml.cpp
	tinyxmlerror.cpp
	tinyxmlparser.cpp
)

SET(tinyxml_COMPILER_WARNING_FLAGS "-Wall -Wno-long-double -Wno-long-long -fPIC")
ADD_DEFINITIONS(-fPIC)


## section: header files
# add your header files here
SET(tinyxml_HEADER_FILES
	tinystr.h
	tinyxml.h
)

SET_SOURCE_FILES_PROPERTIES(tinyxml_HEADER_FILES
	PROPERTIES HEADER_FILE_ONLY TRUE)
LIST(APPEND tinyxml_SOURCE_FILES ${tinyxml_HEADER_FILES})

## section: add definitions
ADD_DEFINITIONS(${OSP_DEFINITIONS})

## section: add target
ADD_LIBRARY(tinyxml STATIC ${tinyxml_SOURCE_FILES} )

## section: set link libraries
# DO NOT add suffix(.lib .so) to lib name.
TARGET_LINK_LIBRARIES(tinyxml)
