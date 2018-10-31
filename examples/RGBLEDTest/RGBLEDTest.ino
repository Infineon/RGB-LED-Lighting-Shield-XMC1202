/*!
*	\file		Strip Test.ino
*	\author 	Inderpreet Singh (google.com/+InderpreetSingh)
* 	\license	GPL2(see license.txt)
*
*	\section 	Description
				Example Code to test if everything if OK. If all iz well then the
				strip should cycle through the three basic colors
*
*	\section	HISTORY
*	v1.0
*/
// ----------------------------------------------------------------------------
#include <RGBLEDLighting.h>
#include <Wire.h>

InfineonRGB LEDS;	// Create Object

void setup() {
  // put your setup code here, to run once:
  LEDS.begin();		// Cycle and set everything to zero.
  LEDS.SetDimmingLevel(0x0FFF);	// Maximum Brightness
}

void loop() {
        LEDS.SetDimmingLevel(0x0FFF);
	// Set RED
	LEDS.SetIntensityRGB(0x0FFF, 0x0000, 0x0000);
	delay(1000); // wait 1000ms
	LEDS.SetIntensityRGB(0x000, 0x0FFF, 0x0000);
	// change lamp colour to green
	delay(1000); 
	LEDS.SetIntensityRGB(0x0000, 0x0000, 0x0FFF);
	// change lamp colour to blue
	delay(1000);
	
	// You can set the colors as well to White, Silver, Gray, Black, Red, Maroon, Yellow, Olive, Lime, Green, Aqua, Teal, Blue, Navy, Fuchsia, Purple
	LEDS.SetColor(Fuchsia);
	delay(5000);
	
	// Set the brightness
	LEDS.SetDimmingLevel(0x07FF);	// 50% Brightness
	delay(1000);
	
	LEDS.SetColor(Green);
    delay(2000);
	
    LEDS.SetColor(Olive);
	delay(2000);
}