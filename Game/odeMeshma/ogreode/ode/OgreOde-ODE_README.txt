*******************************************************************************
							 IMPORTANT NOTE ABOUT BUILDING OGREODE WITH ODE
*******************************************************************************

OgreOde expects that the user already has a built library of ODE before attempting to build OgreOde.

*NOTE* The ODE library must be built using the same floating point precision as Ogre (single or double).  If you are not sure, it is most likely that you are using 32-bit floats, and should build the Release/Debug SingleLib build configurations for ODE after generating the project file with premake (which, at the time of this document, is located in ode/build/premake).

CMake will need to be able to find the built libraries and headers for ODE as part of configuring the OgreOde project.  The simplest way to ensure this is done is to drop the OgreOde source files you plan to use inside of this directory ("OgreOde/ode").  If you plan to use a different location, please set ODE_SOURCE in CMake to the proper ODE source root.

The necessary files can be found at the official ODE website below.  Please follow the instructions provided for building the ODE libraries.

 * ODE official website: http://ode.org/