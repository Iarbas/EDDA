# The Config Reader for EDDA
This module handles the readinf of all configuration files of the project. Because of missing XML/YAML/JSON etc. readers 
in the blank Ubuntu installation and the goal to minimize the effort to install additional packages, the EDDA project
gets with this module its own configuration reader with a own syntax. 

Here the example of how a configuration should look like:

&&&&&&&&&&&&&&& Example &&&&&&&&&&&&&&&
path: /home/USERNAME/workspace/blubb
number_int: 12
number_float: 4234.234234
number_bool_1: 1
number_bool_2: false
number_array: [2,3,4.5]
list: {Hello, World, !}
&&&&&&&&&&&&&&& Example &&&&&&&&&&&&&&&

------------------------------------------------
------------------ Change Log ------------------
------------------------------------------------
Version |   Date   |           Changes         |
________|__________|___________________________|
        |          |                           |
  0.1   |08.12.2019|       Initial commit.     |
________|__________|___________________________|
------------------------------------------------

Author:  Andre Alexander Pieper.

Version 1.0

Date:  03.09.2019

License: LGPLv3
