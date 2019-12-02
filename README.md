# LCD06BLR_ArduinoLib
The drive of LCD06BLR for Arduino.

LCD06BLR library
=====

The project provide a arduino library for LCD06BLR which use HT1621 drive LCD.
I bought the displayer from china, there are 6 7-segment for display number, 5 dot between every number 
and 2 colon separate every 2 number, there are 8 arrows locate side of display(4 at right and 4 at left 
side), I didn't implement these arrows, you can reference develop.ino if you need implement it.

Special variable - opposite
=====
There is a special feature on segment LCD - display angle, LCD06BLR display angel at 6:00 direction, it 
mean the color of segment is clear and rich if you watch it from 6:00 direction(from below), and light 
if you watch it from other angel, the opposite variable control the LCD show number and colon opposite, 
that mean you can change the angel become 12:00(from above), but the dot will become show on above, it 
useful for show time.


![image](https://github.com/eyesblue/LCD06BLR_ArduinoLib/blob/master/images/1.jpg)
![image](https://github.com/eyesblue/LCD06BLR_ArduinoLib/blob/master/images/2.jpg)
![image](https://github.com/eyesblue/LCD06BLR_ArduinoLib/blob/master/images/3.jpg)
![image](https://github.com/eyesblue/LCD06BLR_ArduinoLib/blob/master/images/4.jpg)

The library is modify from Maczinga's code(https://macduino.blogspot.com/2015/02/HT1621.html).

USAGE NOTES
---

Just put the files on a LCD06BLR directory under "arduino/libraries" on your arduino IDE instalation.
