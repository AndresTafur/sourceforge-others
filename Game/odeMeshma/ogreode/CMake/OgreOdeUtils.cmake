#-------------------------------------------------------------------
# This file is part of the CMake build system for OgreOde
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------
if (WIN32)
  set(OGREODE_RELEASE_PATH "/Release")
  set(OGREODE_RELWDBG_PATH "/RelWithDebInfo")
  set(OGREODE_MINSIZE_PATH "/MinSizeRel")
  set(OGREODE_DEBUG_PATH "/Debug")
  set(OGREODE_LIB_RELEASE_PATH "/Release")
  set(OGREODE_LIB_RELWDBG_PATH "/RelWithDebInfo")
  set(OGREODE_LIB_MINSIZE_PATH "/MinSizeRel")
  set(OGREODE_LIB_DEBUG_PATH "/Debug")
  ## TODO
  set(OGREODE_BINARY_DIR ${CMAKE_BINARY_DIR} )
elseif (UNIX)
  set(OGREODE_RELEASE_PATH "")
  set(OGREODE_RELWDBG_PATH "")
  set(OGREODE_MINSIZE_PATH "")
  set(OGREODE_DEBUG_PATH "/debug")
  set(OGREODE_LIB_RELEASE_PATH "")
  set(OGREODE_LIB_RELWDBG_PATH "")
  set(OGREODE_LIB_MINSIZE_PATH "")
  set(OGREODE_LIB_DEBUG_PATH "")
  set(OGREODE_BINARY_DIR ${CMAKE_BINARY_DIR} )
endif ()
set (OGREODE_TEMPLATES_DIR ${CMAKE_SOURCE_DIR}/CMake/Templates )
set (OGREODE_PREFIX_PATH ${CMAKE_INSTALL_PREFIX})
set(OGREODE_MEDIA_DIR_REL ${OGREODE_MEDIA_DIR} )
set(OGREODE_MEDIA_DIR_DBG ${OGREODE_MEDIA_DIR} )
set(OGRE_MEDIA_DIR_REL    ${OGRE_HOME}/Samples/Media )
set(OGRE_MEDIA_DIR_DBG    ${OGRE_HOME}/Samples/Media )

# setup common target settings
function(ogreode_config_target TARGETNAME)
   set_target_properties(${TARGETNAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${OGREODE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${OGREODE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY "${OGREODE_BINARY_DIR}/bin"
   )
  install(TARGETS ${TARGETNAME} 
	BUNDLE DESTINATION "bin${OGREODE_RELEASE_PATH}" CONFIGURATIONS Release None ""
	RUNTIME DESTINATION "bin${OGREODE_RELEASE_PATH}" CONFIGURATIONS Release None ""
	LIBRARY DESTINATION "lib${OGREODE_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
	ARCHIVE DESTINATION "lib${OGREODE_LIB_RELEASE_PATH}${SUFFIX}" CONFIGURATIONS Release None ""
	FRAMEWORK DESTINATION "bin${OGREODE_RELEASE_PATH}" CONFIGURATIONS Release None ""
  )

  install(TARGETS ${TARGETNAME} 
    BUNDLE DESTINATION "bin${OGREODE_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
	RUNTIME DESTINATION "bin${OGREODE_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
	LIBRARY DESTINATION "lib${OGREODE_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
	ARCHIVE DESTINATION "lib${OGREODE_LIB_RELWDBG_PATH}${SUFFIX}" CONFIGURATIONS RelWithDebInfo
	FRAMEWORK DESTINATION "bin${OGREODE_RELWDBG_PATH}" CONFIGURATIONS RelWithDebInfo
  )

  install(TARGETS ${TARGETNAME} 
    BUNDLE DESTINATION "bin${OGREODE_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
	RUNTIME DESTINATION "bin${OGREODE_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
	LIBRARY DESTINATION "lib${OGREODE_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
	ARCHIVE DESTINATION "lib${OGREODE_LIB_MINSIZE_PATH}${SUFFIX}" CONFIGURATIONS MinSizeRel
	FRAMEWORK DESTINATION "bin${OGREODE_MINSIZE_PATH}" CONFIGURATIONS MinSizeRel
  )

  install(TARGETS ${TARGETNAME} 
    BUNDLE DESTINATION "bin${OGREODE_DEBUG_PATH}" CONFIGURATIONS Debug
	RUNTIME DESTINATION "bin${OGREODE_DEBUG_PATH}" CONFIGURATIONS Debug
	LIBRARY DESTINATION "lib${OGREODE_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
	ARCHIVE DESTINATION "lib${OGREODE_LIB_DEBUG_PATH}${SUFFIX}" CONFIGURATIONS Debug
	FRAMEWORK DESTINATION "bin${OGREODE_DEBUG_PATH}" CONFIGURATIONS Debug
  )
endfunction(ogreode_config_target)


macro(set_soname PACKAGE)
  #no soname for mingw
  if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
    set(OGREODE_MAJOR_VERSION 1)
    set(OGREODE_MINOR_VERSION 3)
    set(OGREODE_MICRO_VERSION 0)
    set(OGREODE_VERSION ${OGREODE_MAJOR_VERSION}.${OGREODE_MINOR_VERSION}.${OGREODE_MICRO_VERSION})

    # removed soversion since API compatibility is not maintained
    SET_TARGET_PROPERTIES( ${PACKAGE} 
        PROPERTIES VERSION   ${OGREODE_VERSION} )
  endif()
endmacro()

macro(set_rpath TARGET PREFIX)
  # No rpath for minGW
  if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
    SET_TARGET_PROPERTIES(${TARGET} 
        PROPERTIES
            INSTALL_RPATH ${PREFIX}/lib)
  endif()
endmacro()


macro (set_plugin_options OGREODE_PLUGIN_SUFFIX)
	SET(OGRE_PLUGIN_LIBS
		Plugin_OctreeSceneManager
		Plugin_ParticleFX
		Plugin_BSPSceneManager
		Plugin_CgProgramManager
		Plugin_OctreeZone
		Plugin_PCZSceneManager
		libPlugin_PCZSceneManager
		RenderSystem_Direct3D9
		RenderSystem_GL
		RenderSystem_Direct3D10
		RenderSystem_Direct3D11
		RenderSystem_GLES
	)
    FOREACH(OGRE_RS  ${OGRE_PLUGIN_LIBS} )

		string(TOUPPER "OGRE_${OGRE_RS}" TEMP_PLUGINNAME_VAR)
		string(TOUPPER "OGRE_PLUGIN_DIR_${OGREODE_PLUGIN_SUFFIX}" TEMP_PLUGINPATH_VAR)

        set(PLUGIN_NAME ${OGRE_${OGRE_RS}_LIBRARY_${OGREODE_PLUGIN_SUFFIX}} )

        # set plugins*.cfg.in plugin names and path 
        IF (PLUGIN_NAME)
  			GET_FILENAME_COMPONENT(PLUGIN_PATH ${PLUGIN_NAME} PATH)
  			GET_FILENAME_COMPONENT(PLUGIN ${PLUGIN_NAME} NAME_WE)
            set(${TEMP_PLUGINNAME_VAR} ${PLUGIN})
            set(${TEMP_PLUGINPATH_VAR} ${PLUGIN_PATH})
        ELSE()
            set(${TEMP_PLUGINNAME_VAR} ${OGRE_RS})         
        ENDIF() 

        # set plugins*.cfg.in plugin commented out or not
		string(TOUPPER "OGRE_COMMENT_${OGRE_RS}" STEMP)
        if (PLUGIN_NAME) 
			set( ${STEMP} "" )
		else()
			set( ${STEMP} "#" )
		endif()
 	ENDFOREACH(OGRE_RS)


endmacro()

macro(install_ogreode_resourceconfig )

  # create resources.cfg
  configure_file(${OGREODE_TEMPLATES_DIR}/resources_d.cfg.in 
                 ${OGREODE_BINARY_DIR}/inst/bin/debug/resources_d.cfg)
  configure_file(${OGREODE_TEMPLATES_DIR}/resources.cfg.in 
                 ${OGREODE_BINARY_DIR}/inst/bin/release/resources.cfg)

  # create plugins.cfg
  set_plugin_options("DBG")
  set_plugin_options("REL")
  configure_file(${OGREODE_TEMPLATES_DIR}/plugins_d.cfg.in 
				 ${OGREODE_BINARY_DIR}/inst/bin/debug/plugins_d.cfg)
  configure_file(${OGREODE_TEMPLATES_DIR}/plugins.cfg.in 
			     ${OGREODE_BINARY_DIR}/inst/bin/release/plugins.cfg)

  install(FILES 
    ${OGREODE_BINARY_DIR}/inst/bin/debug/resources_d.cfg
    DESTINATION bin${OGREODE_DEBUG_PATH}
    CONFIGURATIONS Debug
    RENAME resources.cfg  
  )
  install(FILES 
    ${OGREODE_BINARY_DIR}/inst/bin/debug/plugins_d.cfg
    DESTINATION bin${OGREODE_DEBUG_PATH}
    CONFIGURATIONS Debug
    RENAME plugins.cfg  
  )
  install(FILES 
    ${OGREODE_BINARY_DIR}/inst/bin/release/resources.cfg
    ${OGREODE_BINARY_DIR}/inst/bin/release/plugins.cfg
    DESTINATION bin${OGREODE_RELEASE_PATH} CONFIGURATIONS Release None ""
  )
  install(FILES 
    ${OGREODE_BINARY_DIR}/inst/bin/release/resources.cfg
    ${OGREODE_BINARY_DIR}/inst/bin/release/plugins.cfg
	DESTINATION bin${OGREODE_RELWDBG_PATH} CONFIGURATIONS RelWithDebInfo
  )
  install(FILES 
    ${OGREODE_BINARY_DIR}/inst/bin/release/resources.cfg
    ${OGREODE_BINARY_DIR}/inst/bin/release/plugins.cfg
	DESTINATION bin${OGRE_MINSIZE_PATH} CONFIGURATIONS MinSizeRel
  )

  if (WIN32 AND NOT MINGW)
	  # create resources.cfg
	  configure_file(${OGREODE_TEMPLATES_DIR}/resources_d.cfg.in 
					 ${OGREODE_BINARY_DIR}/bin/debug/resources_d.cfg)
	  configure_file(${OGREODE_TEMPLATES_DIR}/resources.cfg.in 
					 ${OGREODE_BINARY_DIR}/bin/release/resources.cfg)
	  configure_file(${OGREODE_TEMPLATES_DIR}/resources.cfg.in 
					 ${OGREODE_BINARY_DIR}/bin/relwithdebinfo/resources.cfg)
	  configure_file(${OGREODE_TEMPLATES_DIR}/resources.cfg.in 
					 ${OGREODE_BINARY_DIR}/bin/minsizerel/resources.cfg)
	  # create plugins.cfg
	  configure_file(${OGREODE_TEMPLATES_DIR}/plugins_d.cfg.in 
					 ${OGREODE_BINARY_DIR}/bin/debug/plugins_d.cfg)
	  configure_file(${OGREODE_TEMPLATES_DIR}/plugins.cfg.in 
					 ${OGREODE_BINARY_DIR}/bin/release/plugins.cfg)
	  configure_file(${OGREODE_TEMPLATES_DIR}/plugins.cfg.in 
					 ${OGREODE_BINARY_DIR}/bin/relwithdebinfo/plugins.cfg)
	  configure_file(${OGREODE_TEMPLATES_DIR}/plugins.cfg.in 
					 ${OGREODE_BINARY_DIR}/bin/minsizerel/plugins.cfg)

  else() # other OS only need one cfg file
	  string(TOLOWER "${CMAKE_BUILD_TYPE}" OGRE_BUILD_TYPE)
	  if (OGRE_BUILD_TYPE STREQUAL "debug" AND NOT APPLE)
		set(OGREODE_CFG_SUFFIX "_d")
	  endif ()
	  # create resources.cfg
	  configure_file(${OGREODE_TEMPLATES_DIR}/resources${OGREODE_CFG_SUFFIX}.cfg.in
 					 ${OGREODE_BINARY_DIR}/bin/resources.cfg)
	  # create plugins.cfg
	  configure_file(${OGREODE_TEMPLATES_DIR}/plugins${OGREODE_CFG_SUFFIX}.cfg.in
 					 ${OGREODE_BINARY_DIR}/bin/plugins.cfg)
  endif ()

endmacro()


macro(install_ogreode_pkgconfig PACKAGE)
  # On Linux there is only ever one pkgconfig file for each lib:
  #   - for a debug build it points to -lOgreOde_(Core/Loader/Prefab)_d 
  #   - other builds to -lOgreOde_(Core/Loader/Prefab)

  #The OgreOde_*.pc.in template files contain the following variables:
  # @OGREODE_PREFIX_PATH@    e.g. ${CMAKE_INSTALL_PREFIX}
  # @OGREODE_VERSION@        Library version
  # @OGREODE_PKGLIB_SUFFIX@  "_d" for debug, empty for other builds
  # The template files should not be installed.

  if (CMAKE_COMPILER_IS_GNUCXX AND NOT MINGW)
    # set additional template variables
  	string(TOLOWER "${CMAKE_BUILD_TYPE}" OGREODE_BUILD_TYPE)
  	if (${OGREODE_BUILD_TYPE} STREQUAL "debug")
      set(OGREODE_PKGLIB_SUFFIX  "_d")
  	else()
      set(OGREODE_PKGLIB_SUFFIX  "")
  	endif()

	# Substitutes the above variables in OgreOde_*.pc.in to create an OgreOde_*.pc 
    # file in the build directory
    configure_file(${OGREODE_TEMPLATES_DIR}/${PACKAGE}.pc.in
                   ${OGREODE_BINARY_DIR}/lib/pkgconfig/${PACKAGE}.pc @ONLY)

	# Copies across the OgreOde_*.pc file from the build directory to the install
    # directory 
    install(FILES ${OGREODE_BINARY_DIR}/lib/pkgconfig/${PACKAGE}.pc 
            DESTINATION lib/pkgconfig)
  endif()
endmacro()


macro(install_ogreode_binary PACKAGE)
  ogreode_config_target(${PACKAGE})
  set_rpath(${PACKAGE} ${CMAKE_INSTALL_PREFIX})
endmacro()

macro(install_ogreode_headers PACKAGE HEADERS)
  install(FILES ${HEADERS} DESTINATION include/${PACKAGE} )
endmacro()

macro(install_ogreode_lib PACKAGE)
  ogreode_config_target(${PACKAGE})
  set_soname(${PACKAGE})
  #TODO 
  #set_rpath(${PACKAGE} ${CMAKE_INSTALL_PREFIX})
  install_ogreode_pkgconfig(${PACKAGE})
  IF (WIN32)
        SET_TARGET_PROPERTIES(${PACKAGE}
	        PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:WINDOWS")
	    SET_TARGET_PROPERTIES(${PACKAGE}
	        PROPERTIES LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:WINDOWS")
	    SET_TARGET_PROPERTIES(${PACKAGE}
	        PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
	    SET_TARGET_PROPERTIES(${PACKAGE}
	        PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:WINDOWS")
        ## section: set output directory (don't know what this is) ???
        #SET_TARGET_PROPERTIES(${PACKAGE}
	    #        PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OGREODE_BUILD}/bin)
  ENDIF()
endmacro()

