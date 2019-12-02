/**
   \file demo.ino
   \brief Simple test sketch for the LCD06BLR class.
   \author Eyes Blue
   \date 23 November 2019
   \version 1.0
   \copyright BSD license, check the License page on the blog for more information. All this text must be
    included in any redistribution.
    <br><br>
    See https://github.com/eyesblue/LCD06BLR_ArduinoLib for more details.
*/

#include "LCD06BLR.h"

LCD06BLR ht(16, 17, 18); // CSpin, RWpin, DATApin

void setup() {
  ht.begin();
  ht.sendCommand(LCD06BLR::RC256K);
  ht.sendCommand(LCD06BLR::BIAS_THIRD_4_COM);
  ht.sendCommand(LCD06BLR::SYS_EN);
  ht.sendCommand(LCD06BLR::LCD_ON);
  ht.clear();
}

void loop() {
  ht.opposite = !ht.opposite; //Opposite direction
  
  for (int j = 0; j < 5; j++) { // Demo number
      ht.setNum(0, j);
      delay(10);
      ht.setNum(1, j+1);
      delay(1);
      ht.setNum(2, j+2);
      delay(1);
      ht.setNum(3, j+3);
      delay(1);
      ht.setNum(4, j+4);
      delay(1);
      ht.setNum(5, j+5);
      delay(1);

      
      if ((j % 2) == 1) { // Demo colon
        ht.setColon(0, true);
        ht.setColon(1, false);
      } else {
        ht.setColon(0, false);
        ht.setColon(1, true);
      }
      

      ht.setDot(j%5, true);  // Demo dot(0 ~ 4).

      delay(1000);
}
  }
