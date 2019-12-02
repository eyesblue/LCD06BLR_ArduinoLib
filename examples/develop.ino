/**
   \file develop.ino
   \brief Show every segment for the LCD06BLR class.
   \author Eyes Blue
   \date 2 December 2019
   \version 1.0
   \copyright BSD license, check the License page on the blog for more information. All this text must be
    included in any redistribution.
    <br><br>
    See https://github.com/eyesblue/LCD06BLR_ArduinoLib for more details.
*/

#include "LCD06BLR.h"

LCD06BLR ht(16, 17, 18);

void setup() {
  ht.begin();
  ht.sendCommand(LCD06BLR::RC256K);
  ht.sendCommand(LCD06BLR::BIAS_THIRD_4_COM);
  ht.sendCommand(LCD06BLR::SYS_EN);
  ht.sendCommand(LCD06BLR::LCD_ON);
  ht.clear();
}

void loop() {
  /* For number display
                  0     1     2     3     4     5     6     7     8     9    10    11    12    13    14    15
  byte buf[] = {0x00, 0x0C, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x80, 0x00, 0x00};
  
    For arrow display
      13    14    15
   { 0x0C, 0xC0, 0xCC }
  */
  
  for(uint8_t i=1;i<16;i++)
      ht.write(i, 0xFF);
  delay(3000);

  ht.clear();
  
  uint8_t a[4]={0x80, 0x40, 0x08, 0x04};
  for(uint8_t i=1;i<16;i++){
    for(uint8_t j=0;j<4;j++){
      ht.write(i, a[j]);
      delay(500);
      ht.write(i,0);
    }
  }
}
