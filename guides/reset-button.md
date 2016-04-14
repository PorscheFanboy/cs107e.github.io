---
layout: page
title: Creating a reset button on the Pi
---

*Written by Anna Zeng*

To reboot the Pi without unplugging and replugging in the USB-to-Serial Dongle, we will make use of the reset pins on the Pi. To do so, we will solder the headers to the spot circled in red, then use jumpers to connect both ends to a button.

![Things you will need](images/reset.pin.ingredients.jpg)

After you have attained two headers and found the place to put the headers, place the pins into the Pi's reset pin.

![Pin placement](images/reset.pin.placement.jpg)

Now, turn on the soldering iron to about 600 degrees F (60 on the dial), and wait until the light blinks rapidly.

![Soldering Light](images/reset.pin.solder.light.jpg)

While holding the soldering iron like a pen, on the foam, hold the solder on one side of the pin you wish to apply solder to, and hold the soldering iron on the other side.

![Soldering Position](images/reset.pin.soldering.jpg)

![Soldering Action](images/reset.pin.action.jpg)

Once the liquid solder has covered both the Raspberry Pi's electric contacts and the pin, remove the soldering iron and the solder. Repeat for the second pin! The contacts will look sort of like this:

![Finished Soldering](images/reset.pin.done.jpg)

Now connect the pins to a button on your breadboard like so:

![Button connected to reset](images/reset.pin.button.jpg)

Whenever you push a button and release it, you will restart the Raspberry Pi!