Readme for OgreOde
==================
1) This version of OgreOde is only supported when compiled against Ogre version 
   1.6 or later.

2) ODE is available from http://www.ode.org/ For the sake of compatibility, you should
	 be using the latest available version. At the time of this document, the latest
	 available version is 0.11.1.

	 IMPORTANT: Using GIMPACT is not fully supported by OgreOde at this time.  To be able to
	 build and run out of the box, OPCODE will need to be used for collision.

3) Version 2.5.3 of TinyXml is included in the tinyxml directory. The project file will
	 be generated with the proper configuration by CMake. There is no need to build the
	 libraries separately. TinyXml is only required by the OgreOde_Prefabs library.

   More information can be found at the following website:
   http://www.grinninglizard.com/tinyxml/

4) You will need CMake version 2.6 or later in order to generate the project files
	 for building the source. CMake is available for download at
	 http://www.cmake.org/. The installation instructions below will provide additional
	 details.

*Please use the Ogre Add-ons forum for support questions and other information.


INSTALLATION
============

ENVIRONMENT VARIABLES
---------------------
Using OgreOde with CMake will assumes that the following environment variables
are set either in your system or in CMake:

	OGRE_HOME=[path to Ogre source files (e.g. C:/Ogre, C:/OgreSDK, etc.)]

CMAKE
-----
The OgreOde source package assumes that you have a C++ compiler installed on your
system. OgreOde is set up to be configured through CMake, the platform independent
project file generator.

CMake is dependent on the ODE and OGRE source packages. They must be built separately
before attempting to compile OgreOde. Additionally, the demos contained within require
the OIS library. OIS is already contained within the OGRE dependencies package, which
is typically extracted to the OGRE source root directory. OIS must also be built
before attempting to build the OgreOde demos.

Once you are sure the dependencies have been built properly, you can begin configuring
OgreOde by opening the CMake GUI. Set the source file location to the root directory
of the extracted package. The build directory can be set as desired, but is commonly
set to "build" in the OgreOde source directory. Next, click 'Configure' and select
the appropriate C++ compiler from the drop-down menu. After clicking 'Finish', CMake
will begin configuring the project files.

When finished, if there are no errors, click 'Configure' once more and the 'Generate'
button should now be active. Click 'Generate' and CMake will create the project files
in the build directory you specified. The project files for building OgreOde will
be found there.

*NOTE* Using CMake to build the OgreOde project has been tested on the most common
platforms. If you are having problems likely because of a yet unsupported OS or
compiler, please use the Ogre Add-ons forum to answer your support questions.

ODE
---
As mentioned above, ODE will need to be built separately prior to building OgreOde.
For more information, please see the README contained in the "ode" subdirectory.