# Applications Directory

This is where project applications are kept.
Directory structure splits applications into "F0" and "F4" associated apps.

`app_blinky` is a simple LED blinker app for newcomers to build and write in order to test their systems toolchain.
It is designed to build for all simple devboard targets.
Prerequisites are `openocd` and the ARM version of `gcc` specific to their platform. `gdb` for ARM is also encouraged.

`app_template` is a template app for new projects.
The basic idea is you copy it as a new directory and configure it to whichever board you are building for.
View the README.md in the app_template directory for details.
