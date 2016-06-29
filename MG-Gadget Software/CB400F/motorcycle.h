// motorcycle.h


#ifndef _MOTORCYCLE_h
#define _MOTORCYCLE_h
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
#define HOLDTIME 250
#define BLINK_PERIOD 1600

// input pins NOTE IT IS PINS!!!
#define turnLeftSwitch 2
#define turnRightSwitch 3
#define hornSwitch 4
#define brakeSwitch 5
#define configSwitch 6


// output terminals NOTE IT IS THE 328 Terminals instead! Fix will later be added
#define positionLight 28
#define lowBeam 27
#define highBeam 26
#define brakeLight 25
#define turnLeft 24
#define turnRight 23
#define horn 19
#define starter 18
#define engineOn 17

class Motorcycle {
	// debounce functionality
	long debounceDelay = 10;
	long lastDebounceTime = 0;
	int push = 0;
	int tmpPush = 0;


	int pinState0;
	int pinState1;
	int pinState2;
	int pinState3;
	byte shiftRegister0;
	byte shiftRegister1;
	byte shiftRegister2;
	byte shiftRegister3;
	byte portD = 0;
	byte lastReading = 0;
	unsigned long portDDebounceTime = 10;

	// states
	int systemState = 0, engineKillState;
	int turnLeftState = 0, turnRightState = 0;
	int highBeamState = 0, mainLightsState = 0, positionLightState = 0;

	// pushfunctionality bits
	int lastPush = 0;
	int pushState = 0;
	unsigned long timeStamp = 0;
	// turn signals functionality
	unsigned long turnTimeStamp = 0;

	// engineKill functionality
	unsigned long engineKilled = 0;
	
	// functionality functions
	int read(int pin);
	void write(int pin, int bit);
	void powerOn();
	void powerOff();
	void engineKill();
	void mainLightsToggle();
	void beamToggle();
	void turnLeftToggle();
	void turnRightToggle();
	void positionLightToggle();
	void systemOnBlinkSequence();
	void systemOffBlinkSequence();

public:
	// constructor
	Motorcycle();

	// functions
	int getPushCombination();
	byte getPortD();

	// push functions
	void leftPush();
	void leftHold();
	void rightPush();
	void rightHold();
	void leftAndRightPush();
	void leftAndRightHold();
	void onCombination();
	void offCombination();

	// output
	void updateOutput();
};