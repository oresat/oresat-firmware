# app_template

This is the template app for new applications.

To create a new app, simply copy the app_template directory and name it whatever you like.

```
cp -R app_template app_<name>
```

If building for a specific board, update the `BOARD =` line to the board
defined in the `boards` directory

Then, open the Makefile and edit the line `PROJECT =` to whatever name you chose:
```
PROJECT   = app_<name>
```
