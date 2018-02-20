# app_template

This is the template app for new applications.

To create a new app, simply copy the app_template directory and name it whatever you like.

```
cp -R app_template app_<name>
```

Next, enter your new app directory and rename the Makefile and the conf directory for the board you want to just `Makefile` and `conf`

For example, if you're building on an STM32F042K6:

```
cd app_<name>

mv Makefile-ST_NUCLEO32_F042K6 Makefile
mv conf-ST_NUCLEO32_F042K6 conf
```

Finally, open the Makefile and edit the line `PROJECT =` to whatever name you chose:
```
PROJECT   = app_<name>
```
