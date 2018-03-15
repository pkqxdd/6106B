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

.. contents::
	:local:

If you want to use our code, please **fork** this repository. You can make changes in the forked repository. It also help us to know how many people are using the code, so please do so even if you are not actually updating anything.

To use our code, you don't necessarily have to have similar mechanical structures as ours, you just need to have the following sensors installed:

- 2 gyroscopes
- 4 potentiometers
- 4 shaft encoders


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
:Driver.h: This file contains all function/task definitions that are not in ``autonomousHelper.h``,except for :C:`void pre_auton`, :C:`task autonomous` and :C:`task usercontrol`. It must be included before ``autonomousHelper.h``. The driver in filename is as in "hardware driver"

I highly suggest anyone who want to use our code to read `C++ Preprocessor Documentation <http://www.cplusplus.com/doc/tutorial/preprocessor/>`_ first.

Driver.h
--------

All constants at the beginning of the file are measured using the remote debugger. They are specific to our robot only. To use our code, you will need to change almost all of them.

The keymap section will be explained later.

Functions Explanation
*********************


:definition: :C:`bool approxEq(const float a, const float b, const float tolerance)`



