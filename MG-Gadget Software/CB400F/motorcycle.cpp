#include "motorcycle.h"
#include "time.h"

// initializer
Motorcycle::Motorcycle() {
	/*
	// setting ports as digital input
	DDRD &= ~(1 << DDD0);	//turnLeft
	DDRD &= ~(1 << DDD1);	//turnRight
	DDRD &= ~(1 << DDD2);	//Horn
	DDRD &= ~(1 << DDD3);	//Brake
	DDRD &= ~(1 << DDD4);	//ConfigSwitch

	// setting ports as digital out
	DDRC |= 1 << DDC5;	// pin 9 - t28
	DDRC |= 1 << DDC4;	// pin 10 - t27
	DDRC |= 1 << DDC3;	// pin 11 - t26
	DDRC |= 1 << DDC2;	// pin 12 - t25
	DDRC |= 1 << DDC1;	// pin 13 - t24
	DDRC |= 1 << DDC0;	// pin 14 - t23
	DDRB |= 1 << DDB5;	// pin 15 - t19
	DDRB |= 1 << DDB4;	// pin 16 - t18
	DDRB |= 1 << DDB3;	// pin 17 - t17
	*/
	///*
	// for arduino testing
	pinMode(turnLeftSwitch, INPUT);
	pinMode(turnRightSwitch, INPUT);
	pinMode(hornSwitch, INPUT);
	pinMode(brakeSwitch, INPUT);
	pinMode(configSwitch, INPUT_PULLUP);

	pinMode(positionLight, OUTPUT);
	pinMode(lowBeam, OUTPUT);
	pinMode(highBeam, OUTPUT);
	pinMode(brakeLight, OUTPUT);
	pinMode(turnLeft, OUTPUT);
	pinMode(turnRight, OUTPUT);
	pinMode(horn, OUTPUT);
	pinMode(engineOn, OUTPUT);
	//*/
}

// reads a pin
int Motorcycle::read(int pin) {
	/*
	if (pin == 0) {
		// shifting values into register
		shiftRegister0 = shiftRegister0 << 1;
		if (digitalRead(0) == 1)
			shiftRegister0 = shiftRegister0 | 1;

		// setting state upon verified register
		if (shiftRegister0 == 0x0)
			pinState0 = 0;
		else if (shiftRegister0 == 0xF)
			pinState0 = 1;

		return pinState0;
	}
	else if (pin == 1) {
		// shifting values into register
		shiftRegister1 = shiftRegister1 << 1;
		if (digitalRead(1) == 1)
			shiftRegister1 = shiftRegister1 | 1;

		// setting state upon verified register
		if (shiftRegister1 == 0x0)
			pinState1 = 0;
		else if (shiftRegister1 == 0xF)
			pinState1 = 1;

		return pinState1;
	}
	else if (pin == 2) {
		// shifting values into register
		shiftRegister2 = shiftRegister2 << 1;
		if (digitalRead(2) == 1)
			shiftRegister2 = shiftRegister2 | 1;

		// setting state upon verified register
		if (shiftRegister2 == 0x0) {
			pinState2 = 0;
		}
		else if (shiftRegister2 == 0xF) {
			pinState2 = 1;
		}

		return pinState2;
	}
	else if (pin == 3)
	{
		// shifting values into register
		shiftRegister3 = shiftRegister3 << 1;
		if (digitalRead(3) == 1)
			shiftRegister3 = shiftRegister3 | 1;

		// setting state upon verified register
		if (shiftRegister3 == 0x0) {
			pinState3 = 0;
		}
		else if (shiftRegister3 == 0xF) {
			pinState3 = 1;
		}

		return pinState3;
	}
	*/
	return digitalRead(pin);
}
// writes to pin
void Motorcycle::write(int pin, int bit) {
	if (pin == positionLight && bit == 1)
		PORTC |= 1 << PORTC5;
	else if (pin == positionLight && bit == 0)
		PORTC &= ~(1 << PORTC5);
	else if (pin == lowBeam && bit == 1)
		PORTC |= 1 << PORTC4;
	else if (pin == lowBeam && bit == 0)
		PORTC &= ~(1 << PORTC4);
	else if (pin == highBeam && bit == 1)
		PORTC |= 1 << PORTC3;
	else if (pin == highBeam && bit == 0)
		PORTC &= ~(1 << PORTC3);
	//Brake
	else if (pin == brakeLight && bit == 1)
		PORTC |= 1 << PORTC2;
	else if (pin == brakeLight && bit == 0)
		PORTC &= ~(1 << PORTC2);
	// blink L
	else if (pin == turnLeft && bit == 1)
		PORTC |= 1 << PORTC1;
	else if (pin == turnLeft && bit == 0)
		PORTC &= ~(1 << PORTC1);
	// blink R
	else if (pin == turnRight && bit == 1)
		PORTC |= 1 << PORTC0;
	else if (pin == turnRight && bit == 0)
		PORTC &= ~(1 << PORTC0);
	// Horn
	else if (pin == horn && bit == 1)
		PORTB |= 1 << PORTB5;
	else if (pin == horn && bit == 0)
		PORTB &= ~(1 << PORTB5);
	// start
	else if (pin == starter && bit == 1)
		PORTB |= 1 << PORTB4;
	else if (pin == starter && bit == 0)
		PORTB &= ~(1 << PORTB4);
	// engine on
	else if (pin == engineOn && bit == 1)
		PORTB |= 1 << PORTB3;
	else if (pin == engineOn && bit == 0)
		PORTB &= ~(1 << PORTB3);
}

// returns the actual push combination
int Motorcycle::getPushCombination() {
	int newPush = 0;
	if (!read(turnLeftSwitch) && !read(turnRightSwitch))
		newPush = 0;
	else if (read(turnLeftSwitch) && !read(turnRightSwitch))
		newPush = 1;
	else if (!read(turnLeftSwitch) && read(turnRightSwitch))
		newPush = 2;
	else if (read(turnLeftSwitch) && read(turnRightSwitch))
		newPush = 3;

	// Debounce functionality
	// if push change log the time.
	if (push != newPush) {
		if (tmpPush != newPush)
			lastDebounceTime = millis();
		tmpPush = newPush;

		//if the readings didnt change for the entire debounceTime assign the new push to the accepted push state.
		if ((lastDebounceTime + debounceDelay) < millis()) {
			push = newPush;
		}
	}

	return push;
}

// Push functions
void Motorcycle::leftPush() {
	if (systemState && mainLightsState)
		if (configSwitch)
			turnLeftToggle();
		else if (!configSwitch)
			beamToggle();
}
void Motorcycle::leftHold() {
	if (systemState) {
		if (configSwitch)
			beamToggle();
		else if (!configSwitch)
			turnLeftToggle();
	}
	else if (!systemState)
		positionLightToggle();
}
void Motorcycle::rightPush() {
	if (systemState && mainLightsState)
		if (configSwitch)
			turnRightToggle();
		else if (!configSwitch)
			mainLightsToggle();
}
void Motorcycle::rightHold() {
	if (systemState)
		if (configSwitch)
			mainLightsToggle();
		else if (!configSwitch)
			turnRightToggle();
}
void Motorcycle::leftAndRightPush() {}
void Motorcycle::leftAndRightHold() {
	if (systemState)
		engineKill();
}
void Motorcycle::onCombination() {
	if (!systemState) {
		powerOn();
	}
}
void Motorcycle::offCombination() {
	if (systemState) {
		powerOff();
	}
}

// functionality functions
void Motorcycle::powerOn() {
	systemOnBlinkSequence();
	systemState = 1;
	turnLeftState = 0;
	turnRightState = 0;
	highBeamState = 0;
	mainLightsState = 1;
	positionLightState = 0;
	Serial.println("System on");
}
void Motorcycle::powerOff() {
	systemOffBlinkSequence();
	systemState = 0;
	turnLeftState = 0;
	turnRightState = 0;
	highBeamState = 0;
	mainLightsState = 0;
	positionLightState = 0;
	Serial.println("System off");
}
void Motorcycle::turnLeftToggle() {
	if (turnLeftState) {
		turnLeftState = 0;
		Serial.println("Left off");
	}
	else if (!turnLeftState && !turnRightState) {
		turnLeftState = 1;
		turnTimeStamp = millis();
		Serial.println("Left on");
	}
}
void Motorcycle::turnRightToggle() {
	if (!turnRightState && !turnLeftState){
		turnRightState = 1;
		Serial.println("Right on");
	}
	else if (turnRightState){
		turnRightState = 0;
		Serial.println("Right off");
	}
}
void Motorcycle::beamToggle() {	
	if (!highBeamState && mainLightsState){
		highBeamState = 1;
		Serial.println("Beam On");
	} else if (highBeamState && mainLightsState){
		highBeamState = 0;
		Serial.println("Beam Off");
	}
}
void Motorcycle::mainLightsToggle() {
	if (!mainLightsState) {
		mainLightsState = 1;
		Serial.println("Main lights on");
	}
	else{
		mainLightsState = 0;
		highBeamState = 0;
		turnLeftState = 0;
		turnRightState = 0;
		Serial.println("Main lights off");
	}
}
void Motorcycle::positionLightToggle() {
	if (!positionLightState) {
		positionLightState = 1;
		Serial.println("pos On");
	}
	else {
		positionLightState = 0;
		Serial.println("pos off");
	}
}
void Motorcycle::engineKill() {
	// not implemented
	engineKilled = millis();
	Serial.println("Engine kill");
}
void Motorcycle::systemOnBlinkSequence()
{
	// blink 2 times
	write(turnLeft, 1);
	write(turnRight, 1);
	write(lowBeam, 1);
	delay(200);
	write(turnLeft, 0);
	write(turnRight, 0);
	write(lowBeam, 0);
	delay(200);
	write(turnLeft, 1);
	write(turnRight, 1);
	write(lowBeam, 1);
	delay(200);
	write(turnLeft, 0);
	write(turnRight, 0);
	write(lowBeam, 0);
}
void Motorcycle::systemOffBlinkSequence(){
	// blink 3 times
	write(turnLeft, 1);
	write(turnRight, 1);
	write(lowBeam, 1);
	delay(200);
	write(turnLeft, 0);
	write(turnRight, 0);
	write(lowBeam, 0);
	delay(200);
	write(turnLeft, 1);
	write(turnRight, 1);
	write(lowBeam, 1);
	delay(200);
	write(turnLeft, 0);
	write(turnRight, 0);
	write(lowBeam, 0);
	delay(200);
	write(turnLeft, 1);
	write(turnRight, 1);
	write(lowBeam, 1);
	delay(200);
	write(turnLeft, 0);
	write(turnRight, 0);
	write(lowBeam, 0);
}

void Motorcycle::updateOutput() {
	// engine on/off
	if (systemState) {
		if (engineKilled + 5000 > millis()) {
			write(engineOn, 0);
		}
		else {
			write(engineOn, 1);
		}
	}
	else if (!systemState) {
		write(engineOn, 0);
	}

	// PositionLight
	if (positionLightState == 1 || mainLightsState == 1)
		write(positionLight, 1);
	else
		write(positionLight, 0);

	// low/high beam
	if (mainLightsState == 1) {
		if (highBeamState == 0) {
			write(lowBeam, 1);
			write(highBeam, 0);
		}
		else if (highBeamState == 1) {
			write(lowBeam, 0);
			write(highBeam, 1);
		}
	}
	else if (mainLightsState == 0) {
		write(lowBeam, 0);
		write(highBeam, 0);
	}

	// brakeLight
	if (read(brakeSwitch) && systemState)
		write(brakeLight, 1);
	else
		write(brakeLight, 0);
	
	// Turn Left
	if (turnLeftState){
		int turnTime = millis() - turnTimeStamp;
		int turnBit = (turnTime % BLINK_PERIOD) < (BLINK_PERIOD/2) ? 1 : 0;
		write(turnLeft, turnBit);
	} else
		write(turnLeft, 0);
		
	// Turn Right
	if (turnRightState){
		int turnTime = millis() - turnTimeStamp;
		int turnBit = (turnTime % BLINK_PERIOD) < (BLINK_PERIOD/2) ? 1 : 0;
		write(turnRight, turnBit);
	} else
		write(turnRight, 0);
		
	// horn
	write(horn, hornSwitch);
}