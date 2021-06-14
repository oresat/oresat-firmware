# Field-Oriented Control Application Main Directory


`app_foc` is an attempt to port [Version 2.1](https://github.com/simplefoc/Arduino-FOC/tree/v2.1) of the [Simple FOC project](https://simplefoc.com/) from Arduino to ChibiOS.


## Directory Structure
This folder contains the root of an applications sources. It contains
several files and folders:
* [main.c](main.c): The main program file called by ChibiOS. Contains
  initialization code and registers threads and functions.
* [Makefile](Makefile): The main Makefile for the application. Sources
  all other build files.
* [cfg](cfg): The directory containing ChibiOS's configuration files for
  this application.
* [source](source): The directory where application code is put.
  Everything within this directory automatically builds.
