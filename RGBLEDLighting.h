/*!
*	\file		infineonrgb.h
*	\author 	Inderpreet Singh (google.com/+InderpreetSingh)
* 	\license	GPL2(see license.txt)
*
*	\section 	Description
                        Basic Library for the Infineon RGB Shield
*
*	\section	HISTORY
*	v1.0            Derived from the Example Library from Infineon
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
#ifndef INFINEONRGB_H
#define INFINEONRGB_H

#include <inttypes.h>
#include "Print.h"

#define ADDRESS                    0x15EUL
 
#define INTENSITY_RED              0x11U
#define INTENSITY_GREEN            0x12U
#define INTENSITY_BLUE	     0x13U
#define INTENSITY_RGB              0x14U
#define CURRENT_RED                0x21U
#define CURRENT_GREEN              0x22U
#define CURRENT_BLUE               0x23U
#define CURRENT_RGB                0x24U
#define DMXOFF		     		   0x30U
#define DMXON             	       0x31U
#define DMXSLOT		     		   0x32U
#define DMX8BIT                    0x33U
#define DMX16BIT                   0x34U
#define OFFTIME_RED                0x41U
#define OFFTIME_GREEN              0x42U
#define OFFTIME_BLUE		       0x43U
#define WALKTIME                   0x50U
#define DIMMINGLEVEL               0x60U
#define FADERATE                   0x61U
#define _CHANGE_ADDRESS            0x70U
 
#define READ_INTENSITY_RED         0x81U
#define READ_INTENSITY_GREEN       0x82U
#define READ_INTENSITY_BLUE        0x83U
#define READ_CURRENT_RED           0x84U
#define READ_CURRENT_GREEN         0x85U
#define READ_CURRENT_BLUE          0x86U
#define READ_OFFTIME_RED           0x87U
#define READ_OFFTIME_GREEN         0x88U
#define READ_OFFTIME_BLUE          0x89U
#define READ_WALKTIME              0x8AU
#define READ_DIMMINGLEVEL          0x8BU
#define READ_FADERATE              0x8CU
#define DIRECTACCESS_READ          0x90U // read twice
#define DIRECTACCESS_MOVE   	     0x91U
#define DIRECTACCESS_AND           0x92U
#define DIRECTACCESS_OR            0x93U
 
#define SAVEPARAMETERS             0xA0U

#define BCCUMODID                  0x50030008U
#define CHIPID                     0x40010004U
#define REDINTS                    0x500300A0U // BCCU_CH5
#define REDINT                     0x500300A4U
#define BLUEINTS                   0x50030078U 
#define STARTWALK                  0x50030018U

typedef enum{
	White, Silver, Gray, Black, Red, Maroon, Yellow, Olive, Lime, Green, Aqua, Teal, Blue, Navy, Fuchsia, Purple
	}Colours;
class InfineonRGB{
	public:
		InfineonRGB(void);
		void begin (void);
		void SetIntensityRGB(unsigned int Red, unsigned int Green, unsigned int Blue);
		void SetIntensityRed(unsigned Red);
		void SetIntensityGreen(unsigned Green);
		void SetIntensityBlue(unsigned Blue);
		void SetDimmingLevel(unsigned int Level);
		void SetOffTimesRGB(unsigned char Red, unsigned char Green, unsigned char Blue);
		void SetCurrentRGB(unsigned char Red, unsigned char Green, unsigned char Blue);
		void SetFadeRate(unsigned char FRate);
		void SetWalkTime(unsigned char WTime);
		void SaveParameters(void);
		void SetColor(uint8_t Colour);
		void I2CWRITE2BYTES (int Address, int Command, unsigned int Data);
		void I2CWRITE6BYTES (unsigned int Address, unsigned int Command, unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree); // DataOne: Red, DataTwo: Green, DataThree: Blue
		void I2CWRITE12BYTES (unsigned int Address, unsigned int Command, unsigned int DataOne, unsigned int DataTwo, unsigned int DataThree, unsigned int DataFour, unsigned int DataFive, unsigned int DataSix); // DataOne: Red, DataTwo: Green, DataThree: Blue
		unsigned int I2CREAD (unsigned int Address, unsigned int Command);
		unsigned long I2CREAD_DIRECTACCESS (unsigned int Address, unsigned int Command, unsigned long registerAddress);
		void I2CWRITE_DIRECTACCESS (unsigned int Address, unsigned int Command, unsigned long registerAddress, unsigned long Data); // For accessing registers directly
		void CHANGEADDRESS (unsigned int Address, unsigned int newAddress);
		void I2CDMX (unsigned int Address, unsigned int Command); // Switch off / on the DMX
		void I2CSAVEPARAM (unsigned int Address); 
		
	private:
		unsigned int c[2] = {0};
		unsigned int d[4] = {0};
		unsigned int on;
		unsigned int message;
		unsigned long redcurr;
		unsigned long greencurr;
		unsigned long bluecurr;
		unsigned long redoff;
		unsigned long greenoff;
		unsigned long blueoff;
		unsigned long redint;
		unsigned long greenint;
		unsigned long blueint;
		unsigned long fadetime;
		unsigned long walk;
		unsigned long brightness;
};

#endif