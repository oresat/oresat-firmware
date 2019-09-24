# STM32F042K6

This is the source directory for all STM32F042K6 applications.
This device contains an ARM Cortex-M0, and is also known as an M0 or F0.

This MCU typically implements low power OreSat subsystems,
such as solar panels, batteries, and some sensors.

## Creating an app
The template to copy for new applications is [app_template](app_template).
To create a new app, simply make a copy of the app_template directory
and name it whatever you like.

```
cp -R app_template app_<name>
```

If building for a specific board, update the `BOARD =` line to the board
defined in the `boards` directory.

Then, open the Makefile and edit the line `PROJECT =` to whatever name
you've chosen:
```
PROJECT   = app_<name>
```

At this point, you simply write code in source files under the `sources`
directory, include the appropriate header file in the main.c file,
and finally register your worker with the main OreSat application.

See the doc folder for further documentation.
