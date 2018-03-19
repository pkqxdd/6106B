.. role:: C(code)
	:language: C

:Author: Jerry Wang
:Date: Mar 15, 2018

===================
General Information
===================

This repository contains codes written solely by VEX 6106B team for VEX In the Zone. It is currently under active development and maintenance. If you have and question, you can open a ticket in Issues or send us messages with Discord.


If you want to be notified for every update to this repository, don't watch it. It won't work. Instead, send us the link of a **Discord webhook** and we will add it to the list.

============
Members List
============

:Jack Fenton: builder, driver
:Jerry Wang: programmer
:Xavier Shattuck: driver

For all team members, this is our first and last year of VEX Robotics Competition.

==============
Reuse Our Code
==============

Contents:

.. contents::
	:local:

----------------------

If you want to use our code, please **fork** this repository. You can make changes in the forked repository. It also help us to know how many people are using the code, so please do so even if you are not actually updating anything.

To use our code, you don't necessarily have to have similar mechanical structures as ours, you just need to have the following sensors installed:

- 2 gyroscopes (minimum 1, requires to modify ``currLoc`` in ``void gyro()`` in ``autonomousHelper.h``)
- 4 potentiometers (minimum 3, requires to modify ``task lockChainbar()`` and ``task lockFourBar()`` in ``Driver.h``)
- 4 shaft encoders (minimum 2, requires to modify ``currLoc`` in ``task moveWheels()`` in ``autonomousHelper.h``)


General Code Structures
=======================

There are several files you can compile: 

:competition.c: The main file of the program. This file is downloaded to the robot prior to each match
:SkillChallengeCompetition.c: This file is downloaded to the robot only before skill challenge
:testAutonomous.c: This file includes maps buttons to different functions in ``autonomousHelper.h``, it is for debug only
:testDriverControl.c: only contains the part for driver controls, not used

There a lot of unused functions/constants and they generate a lot of warnings. You can disable those warnings in settings. If you can't find settings in the menu, well, we hate RobotC too.

For the other files, you should be able to tell their functions based on their filenames. I apologize for giving some of them ``.h`` extension, as they are not actually header files by definition.


The Framework
=============

We like to think of our code as a framework/library, especially for autonomous. It abstracts away all the details and makes it very easy to write new autonomous/keep existing autonomous working after rebuild.

There are two files essential to the framework:

:autonomousHelper.h: This file contains all function/task definitions that will be useful **only** during autonomous
:Driver.h: This file contains all function/task definitions that are not in ``autonomousHelper.h``,except for :code:`void pre_auton()`, :code:`task autonomous()` and :code:`task usercontrol()`. It must be included before ``autonomousHelper.h``. The driver in filename is as in "hardware driver"

I highly suggest anyone who want to use our code to read `C++ Preprocessor Documentation <http://www.cplusplus.com/doc/tutorial/preprocessor/>`_ first. 

Driver.h
--------

All constants at the beginning of the file are measured using the remote debugger. They are specific to our robot only. To use our code, you will need to change almost all of them. This section will omit functions that are under 4 lines. The key map part will be explained in Key Maps section below

:Function: :code:`bool userIntervention()`
:Returns: true if the remote is touched

------------

:Task: :code:`lockChainbar()` 
:Explanation: Locks the chainbar at ``chainbarTarget``. PID loop. See section PID Loops below for a more detailed explanation.

------------

:Task: :code:`lockFourBar()` 
:Explanation: Locks the fourbar at ``fourbarTarget``. PID loop. See section PID Loops below for a more detailed explanation.

-----------

:Function: :code:`void holdChainBar(const int target)` 
:Explanation: Proxy function to task ``lockChainbar``, returns immediately

-----------

:Function: :code:`void holdChainBar(const int target, const float tolerance)` 
:Explanation: Proxy function to task ``lockChainbar()``, blocks until the difference between current location and ``target`` is within ``tolerance``

-----------

:Function: :code:`void holdFourBar(const int target)` 
:Explanation: Proxy function to task ``lockFourBar``, returns immediately

-----------

:Function: :code:`void holdFourBar(const int target, const float tolerance)` 
:Explanation: Proxy function to task ``lockFourBar``, blocks until the difference between current location and ``target`` is within ``tolerance``

-----------

:Function: :code:`void readyForDroppingCone(const int count)`
:Explanation: Move chainbar and fourbar to the best place to drop a cone for ``count`` cones inside the robot

-----------

:Task: :code:`WheelControls()` 
:Explanation: Allows drivers to control wheels via remote

-----------

:Task: :code:`MobileGoalControls()`
:Explanation: Allow drivers to control mobile goal lift via remote

-----------

:Task: :code:`FourBarControls()`
:Explanation: Allow drivers to control four bar via remote

-----------

:Task: :code:`RollerControls()`
:Explanation: Allow drivers to control roller via remote

-----------

:Task: :code:`ChainBarControls()`
:Explanation: Allow drivers to control chain bar via remote

-----------

:Task: :code:`SpecialControls()`
:Explanations: Allow drivers to press one button to move a structure to a preset location

autonomousHelper.h
------------------

All name begins with ``t`` are tasks


:Function: :code:`int gyro()`
:Returns: Average reading of two gyroscopes. If you only have one gyro installed, change this accordingly.

------------------

:Task: :code:`tTurn()` 
:Explanation: PID loop to turn the robot. Controlled by proxy function :code:`Turn`.

------------------

:Task: :code:`tMoveWheels()` 
:Explanation: PID loop to control the wheels (drive train). Controlled by proxy function :code:`void MoveWheels`.

------------------

:Task: :code:`tMoveMobileGoal()` 
:Explanation: PID loop to control the mobile goal lift of the robot. Controlled by proxy function :code:`mobileGoal`.

------------------

:Function: :code:`void releaseWheels()`
:Explanation: This function stops all PID loops that control the wheels. Note that this function does not stop the movement of wheels. To do that, set all motors on wheels to 0. E.g. call :code:`moveLeftWheels(0);moveRightWheels(0);`

------------------

:Function: :code:`void moveWheels(const float distance, const bool straight = true, const float tolerance = 0.5, const bool shouldResetGyroscope = true)`
:Arguments:
	:Distance: distance the robot should travel. Positive value moves the robot forward. Measured in inches.
	:straight: When set to true, the robot will true to adjust its path based on gyro reading to keep going as straight as possible.
	:tolerance: this value determines when the function returns. Set it to a very high value if you want it to return immediately. We call the target to be "within tolerance" if :code:`abs(currentLocation - target) <= tolerance` Note that :code:`task tMoveWheels` is not stopped when the function returns. This is useful because, after the target is reached, the robot can switch to do something else while the wheels are doing some micro-adjustments. 
	:shouldResetGyroscope: Determine whether the robot should reset the gyroscopes to 0 at the beginning of the function. Based on our experience, setting it to false is only useful in some rare occasion during skill challenge.
:Explanation: This is the proxy function to invoke :code:`task tMoveWheels`. Blocks until the target is within tolerance. Note that the constant :code:`ticksPerInch` is specific to our robot. There is one more occurrence of this constant in :code:`task tMoveWheels`.  It is calculated based on the gearing ratio from shaft encoder to the wheels and the diameter of the wheels. The shaft encoder produces 360 ticks for every revolution inside. 

------------------

:Function: :code:`void turn(const int degrees, int tolerance = 10)` 
:Arguments: 
	:degrees: how many degrees the robot should turn. Positive for turning clockwise unless you mount the gyro upside-down. 
	:tolerance: this value determines when the function returns. Set it to a very high value if you want it to return immediately. We call the target to be "within tolerance" if :code:`abs(gyro() - target) <= tolerance` Note that :code:`task tTurn` is not stopped when the function returns. This is useful because, after the target is reached, the robot can switch to do something else while the wheels are doing some micro-adjustments. Measured in one tenth of a degree.
:Explanation: This is the proxy function to invoke :code:`task tTurn`. Blocks until the target is within tolerance. 

------------------

:Function: :code:`void mobileGoal(const int target, bool block = false, int tolerance = 30, int delay=0)`
:Arguments: 
	:target: the target reading of ``pot_mb ``
	:block: determine whether the function blocks or not.
	:tolerance: if block is set to true, this value determines when the function returns.
	:delay: not used. Exist only for backward-compatibility.
:Explanation: This is the proxy function to invoke :code:`task tMoveMobileGoal`. 

-----------------

Function ``mb_in``, ``mb_mid``, ``mb_out``, and ``outOfSize`` are shortcut functions specific to our robot only.


.. _keymap:

Key Maps
--------

This file contains the settings to map different buttons on the joystick to different functions. Its existence allow us to change key maps easily like in video games. Write ``key1 or key2 or key3 ... keyn`` if you want to map multiple keys to the same function. If you don't want to use a specific function, set it to ``false`` instead of deleting it to avoid compilation errors. 


PID Loops
=========

Read PID Controller article in Wikipedia for more details. Only the first part of "Fundamental Operations" and "Pseudocode" are useful for our purpose.

Based on our experience, only the P and D term are useful. When tuning the constants, remember that oscillation is inevitable. It may be very small, but you can never completely get rid of it. That is the reason why we have :code:`wait1Msec` in our autonomous code almost every other line – to allow oscillations. Ideally though, the oscillation should look somewhat like the positive part of graph of 10sin(x)/x^2

I recommend to start with a relatively big constant – big enough so that it is having visible oscillation – and reduce it gradually to decrease the oscillation.


