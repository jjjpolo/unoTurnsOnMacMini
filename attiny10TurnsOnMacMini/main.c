/*
 * attiny10TurnsOnMacMini.c
 *
 * Created: 2023/01/28 20:15hrs
 * Author : Jose Juan Jaramillo Polo
 *
 * Note: I could not get the frequency that a servo needs (1/20 ms) using the internal timer
 *       of this micro controller so I ended up using delays from the util/delay.h library.
 * TODO: Find out if it is possible to do the same as this project using the PWM of
 *			 this micro controller.
 */ 

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

#define periodDelay 1300	// Some how a _delay_us(1300) is equivalent to 20ms (50Hz) needed for the PWM servomotor signal.
							// Trying to improve the readability of this code 
							// I am adding this define to "represent" the 20ms const data. 
							//TODO: Investigate since it does not make sense.

// Configures the registers for the attiny10. 
void setup ()
{
	DDRB = 1;       // PB0 as an output for the servomotor signal.
	CLKPSR = 0;		//No divider
}


// Provides a delay in microseconds. 
// @param us: the amount of microseconds to wait for.
void wait(unsigned int us)
{
	for(unsigned int i=0; i < us; i++)
	{
		_delay_us(1);
	}
}

// This was the best way I found to generate a PWM that 
// emulates the signal needed to control a servomotor (50hz = 1/20ms)
// @param mainDelay: The amount of ms (less than periodDelay which means 20ms = 20000us)
//					 that the high state will last.
void crappyPWM(unsigned int mainDelay, unsigned int angleCycles)
{
	for(uint8_t i =0; i<angleCycles; ++i)
	{
		PORTB = 1;
		wait(mainDelay);
		PORTB = 0;
		wait(periodDelay-mainDelay); //1300 somehow allows to get a 20ms (20000us) delay.
	}
}


// Sets (emulates) the percent of the high state in for the PWM signal. 
// @param percent: The percentage of the high state for the PWM signal. 
void setPWM(unsigned int percent, unsigned int angleCyles)
{
	crappyPWM((percent * periodDelay)/100, angleCyles); // rule of three
}


// Sets the angle of the servomotor.
void setServo(unsigned int angle, unsigned int angleCycles)
{
	//90 is equal to 2ms high 18ms low (PWM (50Hz) = 10%)
	setPWM((angle*10)/90, angleCycles);
}

void servoAnimationForPoweringOnThePc()
{
	//setServo(30,45); //Somehow my servo motor needs to start in 30 degrees.
	setServo(45, 50);
	
	for (unsigned int angle=45; angle <=95; angle+=10)
	{
		setServo(angle, 5);
	}
	
	setServo(110, 25); //Press the Power-on-button for 500ms (25 cycles of the PWM).
	//This angle needs to be modified according to the servo motor,
	//its position and some other external factors that I have not
	//standardized yet.
	
	while (1)
	{
		setServo(45,1024);	//Keep the servomotor in 454 degrees until the power source
		// gets disconnected.
	}
}

int main(void)
{
	setup();
	servoAnimationForPoweringOnThePc();	
}
