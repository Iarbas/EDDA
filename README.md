# EDDA
Introduction
------------

The EDDA - Evaluative Data-driven Design Application is a project for a simulation based controller verification and parameter estimation for autonomous driving vehicles. 


Overview
--------

The Platform is subdivided into independent programs for:

    - EDDAsim | Graphical output for the simulated environment (for the time being, this will be a 2D visualization). This includes:
      + A guide to design own test streets.
      + A graphical output of the simulated area.
      + Plots of the validation criteria.
      + A mechanism to save data for post-processing tools.
      + A configuration tool to manipulate the simulation.
    - EDDApath | Planning a path, to give the controller the needed/optimal trajectory of the vehicle.
    - EDDAmodel | The vehicle model as an ordinary differential equation, to calculate the movement of the vehicle in the simulation.
    - EDDAcontrol | A set of controller to validate their quality. The set will consist of the actual controller as PID, H∞, LQR, MPC, non linear etc. and observer, filter and predictions.
    - EDDAestimate | Offline and online parameter estimation algorithm. 
    - EDDAvalidate | Validation of the results. 
    - EDDAoptimal | An optimization tool to enhance the used controller with respect to the result of a simulated drive.

To keep it simple, the project tries to use only the tools coming with a fresh installation of Ubuntu 20.04 LTS. Every additional software will be mentioned in this README and will aslo be explained, how to install it.



Additional Software
-------------------
**REQUIRED**

The project uses CMake for managing the build process:

	$ sudo apt install cmake

For the ODE solver the project uses BOOST:

	$ sudo apt install libboost-dev
	$ sudo apt install libboost-all-dev

**OPTIONAL**

If you want to see the 2D simulation running, you will need to install SFML:

	$ sudo apt-get install libsfml-dev

You can also build and run EDDA without visualization (just a few changes to the CMakeLists.txt and the configuration file), but it is recommended to have a look on what your program is doing. For more information about the library, you can read the Wikipedia aricle:

https://de.wikipedia.org/wiki/Simple_and_Fast_Multimedia_Library



Credits
-------

Author:  Andre Alexander Pieper.

Version 1.0

Date:  29.08.2019

License: LGPLv3
