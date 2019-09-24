# STM32L452RE

This is the source directory for all STM32L452RE applications.
This device contains an ARM Cortex-M4, and is also known as an L4.

This MCU typically implements higher power OreSat subsystems,
such as Reaction Wheels and Magnetorquers.

## Testing the toolchain
After having installed the required toolchain components as described in
the Prerequesites section of the main README, it is good to test that
they all function as expected. This can be done by building and flashing
the `app_blinky` application that simply blinks an LED.

In order to accomplish this, from this directory simply execute the
following:

```
cd app_blinky
make
make write
```
This should result in a clean no-error build, followed by a successful
write to the board and a flashing green LED. If this all works,
congratulations! Your toolchain is working and you can begin developing.

## Creating an app
The template to copy for new applications is [app_template](app_template).
To create a new app, simply make a copy of the app_template directory
and name it whatever you like. From this directory:

```
cp -R app_template app_<name>
```

Then, open the Makefile `app_<name>/Makefile` and edit the line `PROJECT =` to whatever name
you've chosen:

If building for a specific board, also update the `BOARD =` line to the
board defined in the `boards` directory.
```
PROJECT   = app_<name>
```

At this point, you simply write code in source files under the `sources`
directory, include the appropriate header file in the main.c file,
and finally register your worker with the main OreSat application.

See the doc folder for further documentation.
