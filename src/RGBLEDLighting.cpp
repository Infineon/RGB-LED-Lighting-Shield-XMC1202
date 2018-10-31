/*!
*	\file		infineonrgb.cpp
*	\author 	Inderpreet Singh (google.com/+InderpreetSingh)
* 	\license	GPL2(see license.txt)
*
*	\section 	Description
                        Basic Library for the Infineon RGB Shield
*
*	\section	HISTORY
*	v1.0            Derived from the Example Library from InfineonRGB
*	v1.1			Added The SaveParameter() 
*
* I put a lot of time and effort into our project and hence this copyright 
* notice ensures that people contribute as well as each contribution is 
* acknowledged. Please retain this original notice and if you make changes
* please document them along with your details.
*
* The latest copy of this project/library can be found at: 
* https://github.com/inderpreet/
*
*/
// ----------------------------------------------------------------------------
#include "InfineonRGB.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#if defined(ARDUINO) && (ARDUINO >= 100) //scl
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#if defined (__AVR_ATtiny84__) || defined(__AVR_ATtiny85__) || (__AVR_ATtiny2313__)
#include "TinyWireM.h"
#define Wire TinyWireM
#else
#include "Wire.h"
#endif

// The Constructor
InfineonRGB:: InfineonRGB(){
	// The constructor Stuff
	on = 0;
	message = 0;
	redcurr = 0;
	greencurr = 0;
	bluecurr = 0;
	redoff = 0;
	greenoff = 0;
	blueoff = 0;
	redint = 0x00;
	greenint = 0x00;
	blueint = 0x00;
	fadetime = 0x00;
	walk = 0x00;
	brightness = 1;	
}

// Start Things up
void InfineonRGB::begin(void){
	
	Wire.begin();
	
	while (on != 1) // Wait for shield to respond
    {
      I2CDMX (ADDRESS, DMXOFF); // disable DMX
      I2CWRITE2BYTES (ADDRESS, FADERATE, 0x0000); // Immediate fade
      I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, 0x0000); // 0% brightness level
      on = I2CREAD(ADDRESS, READ_DIMMINGLEVEL); // Request for brightness level
      if (message == 1 && on == 0) // If message received and brightness level = 9%
      {
        message = 0;
        on = 1; // break out of loop
      }
    }
	
    while (redcurr != 0x15 || greencurr != 0x15 || bluecurr != 0x15 || redoff != 0x38 || greenoff != 0x39 || blueoff != 0x38 || brightness != 0)
    {
        I2CWRITE6BYTES (ADDRESS, INTENSITY_RGB, 0x0000, 0x000, 0x0000); // Off Light
	// Ensure that parameters are set up correctly. Read back and check. If wrong, write and read again.
        redcurr = I2CREAD (ADDRESS, READ_CURRENT_RED); // Read the red current intensity
	greencurr = I2CREAD (ADDRESS, READ_CURRENT_GREEN); // Read the green current intensity
	bluecurr = I2CREAD (ADDRESS, READ_CURRENT_BLUE); // Read the blue current intensity
	redoff = I2CREAD (ADDRESS, READ_OFFTIME_RED); // Read the off-time of the red channel
	greenoff = I2CREAD (ADDRESS, READ_OFFTIME_GREEN); // Read the off-time of the green channel
	blueoff = I2CREAD (ADDRESS, READ_OFFTIME_BLUE); // Read the off-time of the blue channel
	brightness = I2CREAD (ADDRESS, READ_DIMMINGLEVEL); // Read the dimming level
        
        I2CWRITE2BYTES (ADDRESS, OFFTIME_RED, 0x38); // Set off-time of red channel to 0x38
	I2CWRITE2BYTES (ADDRESS, OFFTIME_GREEN, 0x39); // Set off-time of green channel to 0x39
	I2CWRITE2BYTES (ADDRESS, OFFTIME_BLUE, 0x38); // Set off-time of blue channel to 0x38
	I2CWRITE2BYTES (ADDRESS, CURRENT_RED, 0x15); // Set current intensity of red channel to 0x15
	I2CWRITE2BYTES (ADDRESS, CURRENT_GREEN, 0x15); // Set current intensity of green channel to 0x15
	I2CWRITE2BYTES (ADDRESS, CURRENT_BLUE, 0x15); // Set current intensity of blue channel to 0x15
	I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, 0x0000);
    }    
}
// ----------------------------------------------------------------------------
// Wrapper Functions
void InfineonRGB::SetIntensityRGB(unsigned int Red, unsigned int Green, unsigned int Blue){
	I2CWRITE6BYTES (ADDRESS, INTENSITY_RGB, Red, Green, Blue);
}

void InfineonRGB::SetIntensityRed(unsigned Red){
	I2CWRITE2BYTES (ADDRESS, INTENSITY_RED, Red); // change red colour intensity to 0xFFF
}

void InfineonRGB::SetIntensityGreen(unsigned Green){
	I2CWRITE2BYTES (ADDRESS, INTENSITY_GREEN, Green); // change red colour intensity to 0xFFF
}

void InfineonRGB::SetIntensityBlue(unsigned Blue){
	I2CWRITE2BYTES (ADDRESS, INTENSITY_BLUE, Blue); // change red colour intensity to 0xFFF
}

void InfineonRGB::SetDimmingLevel(unsigned int Level){
	I2CWRITE2BYTES (ADDRESS, DIMMINGLEVEL, Level);
}

void InfineonRGB::SetOffTimesRGB(unsigned char Red, unsigned char Green, unsigned char Blue){
	I2CWRITE2BYTES (ADDRESS, OFFTIME_RED, Red); 
	I2CWRITE2BYTES (ADDRESS, OFFTIME_GREEN, Green);
	I2CWRITE2BYTES (ADDRESS, OFFTIME_BLUE, Blue); 	
}

void InfineonRGB::SetCurrentRGB(unsigned char Red, unsigned char Green, unsigned char Blue){
	I2CWRITE2BYTES (ADDRESS, CURRENT_RED, Red); 
	I2CWRITE2BYTES (ADDRESS, CURRENT_GREEN, Green);
	I2CWRITE2BYTES (ADDRESS, CURRENT_BLUE, Blue);
}

void InfineonRGB::SetFadeRate(unsigned char FRate){
	I2CWRITE2BYTES (ADDRESS, FADERATE, FRate);// 0x0014); // Fade Rate --> 0.7s
}

void InfineonRGB::SetWalkTime(unsigned char WTime){
	I2CWRITE2BYTES (ADDRESS, WALKTIME, WTime);// 0F);
}

void InfineonRGB::SaveParameters(void){		// Save parameters to EEPROM
	I2CSAVEPARAM(ADDRESS);
}
// ----------------------------------------------------------------------------
void InfineonRGB:: I2CWRITE2BYTES (int Address, int Command, unsigned int Data)
{
  unsigned int upperByte, lowerByte; // Separate 4 byte data into 2 byte values
  lowerByte = Data;
  upperByte = Data >> 8;

  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF); // Putting address into correct format
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

  Wire.beginTransmission(byte(upperSLAD)); // Start I2C transmission
  Wire.write(byte(lowerSLAD)); // address lower 8 bits of i2c address
  Wire.write(byte(Command)); // write command
  Wire.write(byte(upperByte)); // write data
  Wire.write(byte(lowerByte));
  Wire.endTransmission(true);

}

// COLOR Function From Peter Oakes
void InfineonRGB::SetColor(uint8_t Colour){
	switch(Colour){
		case White: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x800, 0x800, 0x800);
			break;
		case Silver: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0xC00, 0xC00, 0xC00);
			break;
		case Gray: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x800, 0x800, 0x800);
			break;
		case Black: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x0, 0x0, 0x0);
			break;
		case Red: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0xFFF, 0x0, 0x0);
			break;
		case Maroon: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x800, 0x0, 0x0);
			break;
		case Yellow: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0xFFF, 0xFFF, 0x0);
			break;
		case Olive: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x800, 0x800, 0x0);
			break;
		case Lime:
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x0, 0xFFF, 0x0);
			break;
		case Green: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x0, 0x800, 0x0);
			break;
		case Aqua: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x0, 0xFFF, 0xFFF);
			break;
		case Teal: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x0, 0x800, 0x800);
			break;
		case Blue: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x0, 0x0, 0xFFF);
			break;
		case Navy: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x0, 0x0, 0x800);
			break;
		case Fuchsia: 
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0xFFF, 0x0, 0xFFF);
			break;
		case Purple:
			I2CWRITE6BYTES(ADDRESS, INTENSITY_RGB, 0x800, 0x0, 0x800);
			break;
		default: 
			break;
	}
}
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - Defined I2C Commands i.e. INTENSITY_RGB, CURRENT_RGB
                unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree - Three 16bit data to be written to slave
Parameters (OUT): None
Return Value: None
Description: This function will write 6 bytes of word to the I2C bus line
*/

void InfineonRGB:: I2CWRITE6BYTES (unsigned int Address, unsigned int Command, unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree) // DataOne: Red, DataTwo: Green, DataThree: Blue
{
  unsigned int upperByte, lowerByte; // Split each Data parameter into upper and lower 8 bytes because I2C format sends 8 bytes of data each time
  lowerByte = DataOne;
  upperByte = DataOne >> 8;

  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

  Wire.beginTransmission(byte(upperSLAD)); // Red
  Wire.write(byte(lowerSLAD));
  Wire.write(byte(Command));
  Wire.write(byte(upperByte));
  Wire.write(byte(lowerByte));
  lowerByte = DataTwo;
  upperByte = DataTwo >> 8;
  Wire.write(byte(upperByte));
  Wire.write(byte(lowerByte));
  lowerByte = DataThree;
  upperByte = DataThree >> 8;
  Wire.write(byte(upperByte));
  Wire.write(byte(lowerByte));
  Wire.endTransmission(true);

}

/*
 Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                  int Command - Defined I2C Commands i.e. DMX16Bit
                  unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree, usigned int DataFour, unsigned int DataFive - Three 16bit data to be written to slave
 Parameters (OUT): None
 Return Value: None
 Description: This function will write 12 bytes of word to the I2C bus line
 */

void InfineonRGB:: I2CWRITE12BYTES (unsigned int Address, unsigned int Command, unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree, unsigned int DataFour, unsigned int DataFive, unsigned int DataSix) // DataOne: Red, DataTwo: Green, DataThree: Blue
{
  unsigned int upperByte, lowerByte;
  lowerByte = DataOne;
  upperByte = DataOne >> 8;

  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

  Wire.beginTransmission(byte(upperSLAD));
  Wire.write(byte(lowerSLAD));
  Wire.write(byte(Command)); // write command
  Wire.write(byte(upperByte)); // write 2 bytes
  Wire.write(byte(lowerByte));

  lowerByte = DataTwo;
  upperByte = DataTwo >> 8;
  Wire.write(byte(upperByte)); // write next two bytes
  Wire.write(byte(lowerByte));

  lowerByte = DataThree;
  upperByte = DataThree >> 8;
  Wire.write(byte(upperByte));
  Wire.write(byte(lowerByte));

  lowerByte = DataFour;
  upperByte = DataFour >> 8;
  Wire.write(byte(upperByte));
  Wire.write(byte(lowerByte));

  lowerByte = DataFive;
  upperByte = DataFive >> 8;
  Wire.write(byte(upperByte));
  Wire.write(byte(lowerByte));

  lowerByte = DataSix;
  upperByte = DataSix >> 8;
  Wire.write(byte(upperByte));
  Wire.write(byte(lowerByte));
  Wire.endTransmission(true);

}

/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - Defined read I2C Commands i.e. READ_INTENSITY_RED, READ_INTENSITY_GREEN, READ_INTENSITY_BLUE
Parameters (OUT): None
Return Value: Requested data from Shield will be sent back
Description: This function will request 2 bytes of word from the shield
*/

unsigned int InfineonRGB:: I2CREAD (unsigned int Address, unsigned int Command) // Returns data sent by slave
{
  int i = 0;
  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79;

  Wire.beginTransmission(byte(upperSLAD)); // Red
  Wire.write(byte(lowerSLAD));
  Wire.write(byte(Command));
  Wire.endTransmission(false); // false for Repeated Start

  Wire.beginTransmission(byte(upperSLAD));
  Wire.write(byte(lowerSLAD));
  Wire.requestFrom(upperSLAD, 2, true);
  unsigned int data = 0;

  while (Wire.available())   // slave may send less than requested. Print out received data byte
  {
    message = 1;
    c[i] = Wire.read(); // receive a byte as character
    i++;

  }
  Wire.endTransmission(true);

  data = c[1]; // write data to serial monitor. c[1] is higher byte
  data = (data << 8) | c[0];  // shift left and combine with lower byte
  //Serial.print("0x");
  if (data < 0x1000)
    //Serial.print("0");
    //Serial.println(data, HEX);
    return data;
}

/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - DIRECTACCESS_READ
Parameters (OUT): None
Return Value: Requested data from the Shield will be returned
Description: This function will request 4 bytes of data from shield.
*/

unsigned long InfineonRGB:: I2CREAD_DIRECTACCESS (unsigned int Address, unsigned int Command, unsigned long registerAddress)
{
  int i = 0;
  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF); // sending command + address
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

  Wire.beginTransmission(byte(upperSLAD));
  Wire.write(byte(lowerSLAD));
  Wire.write(byte(Command));

  unsigned int firstByte, secondByte, thirdByte, fourthByte;
  firstByte = registerAddress >> 24; // top byte
  secondByte = registerAddress >> 16;
  thirdByte = registerAddress >> 8;
  fourthByte = registerAddress; // bottom byte

  Wire.write(byte(firstByte));
  Wire.write(byte(secondByte));
  Wire.write(byte(thirdByte));
  Wire.write(byte(fourthByte));

  Wire.endTransmission(false); // false for Repeated Start

  Wire.beginTransmission(byte(upperSLAD)); // request for read
  Wire.write(byte(lowerSLAD));
  Wire.requestFrom(upperSLAD, 4, true);
  unsigned long data = 0;

  while (Wire.available())   // slave may send less than requested. Print out received data byte
  {
    d[i] = 0;
    d[i] = Wire.read(); // receive a byte as character
    i++;
  }

  Wire.endTransmission(true);

  data = d[3]; // combining into one variable. Highest byte received first
  data = (data << 8) | d[2];
  data = (data << 8) | d[1];
  data = (data << 8) | d[0];
  //Serial.print("0x");
  if (data < 0x10000000)
    //Serial.print("0");
    //Serial.println(data, HEX);
    return data;
}
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                int Command - Defined I2C Commands i.e. DIRECTACCESS_OR, DIRECTACCESS_AND, DIRECTACCESS_MOVE
                unsigned long registerAddress - address of target register
                unsigned long Data - 32 bits data to be written to register
Parameters (OUT): None
Return Value: None
Description: This function will write 4 bytes of data to specified register
*/
void InfineonRGB:: I2CWRITE_DIRECTACCESS (unsigned int Address, unsigned int Command, unsigned long registerAddress, unsigned long Data) // For accessing registers directly
{
  int i = 0;
  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF); // sending command + address
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

  Wire.beginTransmission(byte(upperSLAD));
  Wire.write(byte(lowerSLAD));
  Wire.write(byte(Command));

  unsigned int firstByte, secondByte, thirdByte, fourthByte; // Send address of register first
  firstByte = registerAddress >> 24; // top byte
  secondByte = registerAddress >> 16;
  thirdByte = registerAddress >> 8;
  fourthByte = registerAddress; // bottom byte

  Wire.write(byte(firstByte));
  Wire.write(byte(secondByte));
  Wire.write(byte(thirdByte));
  Wire.write(byte(fourthByte));

  firstByte = Data >> 24; // top byte
  secondByte = Data >> 16;
  thirdByte = Data >> 8;
  fourthByte = Data; // bottom byte

  Wire.write(byte(firstByte)); // send 4 bytes of data
  Wire.write(byte(secondByte));
  Wire.write(byte(thirdByte));
  Wire.write(byte(fourthByte));
  Wire.endTransmission(true);

}
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                unsigned int newAddress - Address the shield should change to
Parameters (OUT): None
Return Value: None
Description: This function will change the I2C address of the slave
*/

void InfineonRGB:: CHANGEADDRESS (unsigned int Address, unsigned int newAddress)
{
  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79; // First 5 bits 11110 and last bit '1' for a write

  Wire.beginTransmission(byte(upperSLAD)); // Red
  Wire.write(byte(lowerSLAD));
  Wire.write(byte(0x70)); // Command to change address
  lowerSLAD = (unsigned int) (newAddress & 0x00FF);
  upperSLAD = newAddress >> 7; // Split address into 2 bytes
  upperSLAD |= 0xF0; // 10 bit addressing: First 5 bits have to be 11110.
  upperSLAD &= 0xFE;
  Wire.write(byte(upperSLAD));
  Wire.write(byte(lowerSLAD));
  Wire.endTransmission(true);
}

/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
                unsigned int Command - DMXON, DMXOFF
Parameters (OUT): None
Return Value: None
Description: This function will enable or disable DMX512 control on shield
*/

void InfineonRGB:: I2CDMX (unsigned int Address, unsigned int Command) // Switch off / on the DMX
{
  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF); // Putting address into correct format
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79;

  Wire.beginTransmission(byte(upperSLAD)); // Start I2C transmission
  Wire.write(byte(lowerSLAD));
  Wire.write(byte(Command));
  Wire.endTransmission(true);

}
/*
Parameters (IN): int Address - Address of RGB LED Shield, Default 0x15E
Parameters (OUT): None
Return Value: None
Description: This function will request the shield to save configurations to flash memory
*/

void InfineonRGB:: I2CSAVEPARAM (unsigned int Address)
{
  int i = 0;
  unsigned int lowerSLAD = (unsigned int) (Address & 0x00FF);
  unsigned int upperSLAD = Address >> 8;
  upperSLAD |= 0x79;

  Wire.beginTransmission(byte(upperSLAD));
  Wire.write(byte(lowerSLAD));
  Wire.write(byte(SAVEPARAMETERS)); // write SAVEPARAMETERS command
  Wire.endTransmission(false); // false for Repeated Start

  Wire.beginTransmission(byte(upperSLAD));
  Wire.write(byte(lowerSLAD)); // write to address lower 8 bits of slave address
  Wire.requestFrom(upperSLAD, 2, true);  // send READ request with upper slave address
  unsigned int data = 0;

  while (Wire.available())   // slave may send less than requested. Print out received data byte
  {
    message = 1;
    c[i] = Wire.read(); // receive a byte as character
    i++;
  }
  Wire.endTransmission(true); // STOP condition

  data = c[1]; // print the data on serial monitor
  data = (data << 8) | c[0];
  //Serial.print("0x");
  //if (data < 0x1000)
    //Serial.print("0");
    //Serial.println(data, HEX);

}
