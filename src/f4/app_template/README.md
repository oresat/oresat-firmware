# Application Main Directory
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
