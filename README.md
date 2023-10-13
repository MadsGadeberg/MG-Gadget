English README
Features that the controller has.
Lock/unlock
The motorcycle can be locked and unlocked using key combinations with the right and left push buttons.
To unlock/turn on the motorcycle, press both buttons down, then release the right one, followed by pressing both buttons down again.
To lock the motorcycle, use the aforementioned combination in reverse. That is, release and press the left button. These combinations will of course be changed before the final version.

When turning on/off, the turn signals blink with different numbers of flashes, providing confirmation whether the motorcycle is off or on.

Both the right and left buttons have 2 different functions depending on whether you press them or hold them down. These functions can be inverted by using the "config0" port. This is useful if, for example, you have a motorcycle without turn signals. Then you would like to have some other functions upon a normal press instead of the turn signals.

Left push button
A press turns the driving light off/on.
Holding the button down triggers the blinkers.
These functions can be inverted by setting the "config0" port to plus.
If the motorcycle is off, the position light can be turned on by holding down the left push button.

Right push button
A press switches between low/high beam.
Holding the button down activates the blinkers.
These functions can also be inverted by setting the "config0" port to plus.

Right and Left
Pressing both buttons cuts the power to the ignition coils for 5 seconds. "Engine Kill"
