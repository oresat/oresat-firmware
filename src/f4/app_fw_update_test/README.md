# OreSat C3 Firmware Application
This application implements the core C3 firmware, responsible for
interfacing with and managing all subsystems on OreSat, as well as
communicating with ground stations. This initial version simply
implements a command interface via radio, and responds with telemetry
indicating subsystem health status.

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
