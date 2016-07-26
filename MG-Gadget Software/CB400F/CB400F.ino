/*
 Name:		CB400F.ino
 Created:	11/26/2015 4:53:38 PM
 Author:	madsgadebergjensen
*/

#include <Time.h>
#include "motorcycle.h"

Motorcycle mc;
int lastPush = 0;
unsigned long timeStamp = 0;
int pushState = 0;

void setup() {
}

void loop() {
	int push = mc.getPushCombination();

	byte portD = mc.getPortD();


	leftPush(push);
	rightPush(push);
	leftAndRightPush(push);
	
	mc.updateOutput();

	lastPush = push;
}

void leftPush(int push) {
	// left push or hold
	if (push == 1 && pushState == 0) { // vs started
		timeStamp = millis();
		pushState = 100;
	}
	if (push == 0 && pushState == 100)
		if (millis() < timeStamp + HOLDTIME)
			mc.leftPush();
		else
			mc.leftHold();
}

void rightPush(int push) {
	// Right push or hold
	if (push == 2 && pushState == 0) { // hs started
		timeStamp = millis();
		pushState = 110;
	}
	if (push == 0 && pushState == 110)
		if (millis() < timeStamp + HOLDTIME)
			mc.rightPush();
		else
			mc.rightHold();
}

void leftAndRightPush(int push) {
    if (push == 3 && (pushState == 0 | pushState == 100 | pushState == 110)) {      // H-V -- fra whatever
        timeStamp = millis();
        pushState = 1;
    }
    
    else if (push == 0 && (pushState == 1 || pushState == 11 || pushState == 21)){
        if (millis() < timeStamp + HOLDTIME)
            mc.leftAndRightPush();
        else
            mc.leftAndRightHold();
    }
    // On sequence path------------------------------------------------
    else if (push == 1 && pushState == 1)       // V -- fra H-V
        pushState = 11;
    else if (push == 3 && pushState == 11){     // H-V -- fra V
        pushState = 12;
        mc.onCombination();
    }
    // Off sequence path-----------------------------------------------
    else if (push == 2 && pushState == 1)       // H -- fra H-V
        pushState = 21;
    else if (push == 3 && pushState == 21){     // H-V -- fra H
        pushState = 22;
        mc.offCombination();
    }    
    
    if (push == 0)
        pushState = 0;
}

