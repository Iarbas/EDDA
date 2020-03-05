# EDDAsim
This module handles all graphical output and simulation parameter. Therefore it is seperated into:

    - A guide for creating 2D test areas. This includes also the needed test ground information.
      The infomation consists of: 
        + The ratio between horizontal and vertical pixel to mm. 
        + Distance (with tolerances) between left and right street lanes.

    - A window to show the test area (only 2D for now) and the most important parameter.
      Inside that window will be displayed:
        + The test track
        + The planned path + tolerances
        + The graphical model of the vehicle and its movements
        + Distance lines from the vehicle to the planned path (shortest way) and the value to this
        + Steering angle as a curve, similar to park assistants in real cars
        + Frame rate and ratio between real and simulated time
        + Actual velocity
        + Control values: Actual and target

    - A mechanism to save all values and replay them.

    - A configuration file to manipulate the simulation:
        + Test track selection
        + Start conditions (position, orientation, velocity etc.) of the vehicle
        + Period of the simulation
        + Abort criteria
        + Ratio of real to simulation time
        + Graphical output yes or no
        + Storage path for the recorded data
        + Selection for the movement model of the vehicle

#### For Later ####
    Planned functions for the future:
    - Post-processing tools as plots, bars etc.
    - Monte-Carlo support
    - ODE solver selection


------------------------------------------------
------------------ Change Log ------------------
------------------------------------------------
Version |   Date   |           Changes         |
________|__________|___________________________|
        |          | Initial commit. Program   |
  0.1   |03.09.2019| shows a blank window.     |
________|__________|___________________________|
------------------------------------------------

Author:  Andre Alexander Pieper.

Version 1.0

Date:  03.09.2019

License: LGPLv3
