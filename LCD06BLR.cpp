/**
 * \file LCD06BLR.cpp
 * \brief Implementation of a class for dealing with the Holtek HT1621 chip, See https://github.com/eyesblue/LCD06BLR_ArduinoLib for more details.
 * \author Eyes Blue
 * \date 23 November 2019
 * \version 1.0
 * \copyright BSD license, check the License page on the blog for more information. All this text must be included in any redistribution.
 *  <br><br>
 *  modify from Maczinga's code(https://macduino.blogspot.com/2015/02/HT1621.html).
 */

#include "LCD06BLR.h"

void LCD06BLR::begin()
{
    pinMode(_DATA_pin, OUTPUT);
    pinMode(_RW_pin, OUTPUT);
    pinMode(_CS_pin, OUTPUT);
 
    digitalWrite(_CS_pin, HIGH);
    digitalWrite(_RW_pin, HIGH);
    digitalWrite(_DATA_pin, HIGH);

#ifndef __HT1621_READ
    register uint8_t i;
    
    for(i=0; i<16; i++)
        ram[i] = 0;
#endif
}

void LCD06BLR::writeBits(uint8_t data, uint8_t cnt)
{
    register uint8_t i;

    for(i=0;i<cnt;i++,data <<=1)
    {
        digitalWrite(_RW_pin, LOW);
        delayMicroseconds(20);
        digitalWrite(_DATA_pin, data&0x80 ? HIGH : LOW);
        delayMicroseconds(20);
        digitalWrite(_RW_pin, HIGH);
        delayMicroseconds(20);
    }
}

#ifdef __HT1621_READ

uint8_t LCD06BLR::readBits(uint8_t cnt)
{
    uint8_t data, i, state;
    
    
    pinMode(_DATA_pin, INPUT);
    
    for(i=0, data=0; i<cnt; data <<= 1, i++) {
        digitalWrite(_RW_pin, LOW);
        delayMicroseconds(20);
        data |= (digitalRead(_DATA_pin) == HIGH);
        digitalWrite(_RW_pin, HIGH);
        delayMicroseconds(20);
    }
    
    pinMode(_DATA_pin, OUTPUT);
    
    return data;
}

#endif

void LCD06BLR::sendCommand(uint8_t cmd, bool first, bool last)
{
    if (first) {
        TAKE_CS();
        writeBits(COMMAND_MODE, 4);
    }
    
    writeBits(cmd, 8);
    
    if (last)
        RELEASE_CS();
}

void LCD06BLR::write(uint8_t address, uint8_t data)
{
    TAKE_CS();
    
    writeBits(WRITE_MODE, 3);
    writeBits(address<<3, 6); // 6 is because max address is 128
    writeBits(data, 8);
#ifndef __HT1621_READ
    ram[address] = data;
#endif
    
    RELEASE_CS();
}

void LCD06BLR::write(uint8_t address, uint8_t data, uint8_t cnt)
{
    register uint8_t i;
    
    TAKE_CS();
    
    writeBits(WRITE_MODE, 3);
    writeBits(address<<3, 6);
    for (i = 0; i < cnt; i++) {
        writeBits(data, 8);
#ifndef __HT1621_READ
        ram[i] = data;
#endif
    }
    
    RELEASE_CS();
}

void LCD06BLR::write(uint8_t address, uint8_t *data, uint8_t cnt)
{
    register uint8_t i;
    
    TAKE_CS();
    
    writeBits(WRITE_MODE, 3);
    writeBits(address<<3, 6);
    for (i = 0; i < cnt; i++) {
        writeBits(data[i], 8);
#ifndef __HT1621_READ
        ram[i] = data[i];
#endif
    }
    
    RELEASE_CS();
}

#ifdef __HT1621_READ

uint8_t LCD06BLR::read(uint8_t address)
{
    uint8_t data;
    
    TAKE_CS();
    
    writeBits(READ_MODE, 3);
    writeBits(address<<3, 6);
    data = readBits(8);
    
    RELEASE_CS();
    
    return data;
}

void LCD06BLR::read(uint8_t address, uint8_t *data, uint8_t cnt)
{
    register uint8_t i;
    
    TAKE_CS();
    
    writeBits(READ_MODE, 3);
    writeBits(address<<3, 6);
    for (i = 0; i < cnt; i++)
        data[i] = readBits(8);
    
    RELEASE_CS();
}

#else

uint8_t LCD06BLR::read(uint8_t address)
{
    return ram[address];
}

void LCD06BLR::read(uint8_t address, uint8_t *data, uint8_t cnt)
{
    register uint8_t i;
    
    for (i = 0; i < cnt; i++)
        data[i] = ram[address+i];
}

#endif

/*
	Below functions create by Eyes Blue.
*/
void LCD06BLR::clear()
{
	register uint8_t i=0;
	for (; i < 16; i++)
		write(i, 0);
}

void LCD06BLR::setNum(uint8_t index, uint8_t num)
{
  for (int i = 0; i < 8; i++) {
    uint8_t b = bitRead(_numSeg[num], i);
    if (opposite) {
      uint8_t ind;
      if (i < 3)ind = i + 3;
      else if (i < 6)ind = i - 3;
      else ind = i;

		if (b)
			_ledSegBuf[_ledBitMap[5-index][ind][0]] |= _ledBitMap[5-index][ind][1];
		else
			_ledSegBuf[_ledBitMap[5-index][ind][0]] &= (~_ledBitMap[5-index][ind][1]);
    }
    else {
      if (b) 
        _ledSegBuf[_ledBitMap[index][i][0]] |= _ledBitMap[index][i][1];
      else 
        _ledSegBuf[_ledBitMap[index][i][0]] &= (~_ledBitMap[index][i][1]);
    }
  }
  
  byte i = (opposite)?_ledBitMap[5-index][0][0]:_ledBitMap[index][0][0];
  byte b=i+3;
	for (; i < b; i++)
        write(i, _ledSegBuf[i]);

}

void LCD06BLR::setDot(uint8_t index, bool isOn)
{
  if (opposite) {
    if (isOn)
      _ledSegBuf[_ledBitMap[4-index][7][0]] |= _ledBitMap[4-index][7][1];
    else
      _ledSegBuf[_ledBitMap[4-index][7][0]] &= (~_ledBitMap[4-index][7][1]);
	write(_ledBitMap[4-index][7][0], _ledSegBuf[_ledBitMap[4-index][7][0]]);
  }
  else {
    if (isOn)
      _ledSegBuf[_ledBitMap[index][7][0]] |= _ledBitMap[index][7][1];
    else
      _ledSegBuf[_ledBitMap[index][7][0]] &= (~_ledBitMap[index][7][1]);
	write(_ledBitMap[index][7][0], _ledSegBuf[_ledBitMap[index][7][0]]);
  }
}

void LCD06BLR::setColon(uint8_t index, bool isOn)
{
  uint8_t i;
  if (opposite) {
    if (index == 1)i = 0;
    else i = 1;
  }
  else i = index;
  
  if (isOn)
    _ledSegBuf[_colonBitMap[i][0]] |= _colonBitMap[i][1];
  else
    _ledSegBuf[_colonBitMap[i][0]] &= (~_colonBitMap[i][1]);

  write(_colonBitMap[i][0], _ledSegBuf[_colonBitMap[i][0]]);
}
