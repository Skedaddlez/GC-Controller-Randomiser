# Gamecube Controller Randomiser
This is just some basic Arduino code that uses Nicohood's Nintendo library to randomise all the digital and analog inputs of Gamecube controllers. It's daft.

Nicohood's library: https://github.com/NicoHood/Nintendo

![Alt text](https://github.com/Skedaddlez/GC-Controller-Randomiser/blob/master/20190419_093832.jpg)

When the tactile switch is pressed, the digital inputs A, B, X, Y, Z, START, DPAD, and DLeft/DRight are all mixed randomly, as are the analog inputs from the Left Stick, the C-stick, the left trigger and the right trigger. The analog shuffling in particular is alot of fun.

--------------------------------------------------------------

![Alt text](https://github.com/Skedaddlez/GC-Controller-Randomiser/blob/master/GCRandomiser_bb.png)

This project was utterly painful, but is my first really successful Arduino project.
I say painful, because diagnosing bugs is incredibly demoralising when you understand as little as I do about electronics and digital signals etc. -_-

Getting the Arduino to mirror the default controls was easy enough - Nicohood had an example already for that. When it came to randomising, I decided to store controller values in an array (based on Nicohood's preset variables for each button), shuffle the array indexes of each button (in global variables, so it's not random every poll cycle), then reassign the values and write to the console. Unfortunately, this bug kept happening where the Arduino would randomly send a digital signal, usually 'A', 'B' or 'START'.

Eventually, I sifted through the source code of Nicohood's library and opted to directly edit the bits in each controller data byte - this seemed to prevent the random signals. It worked nearly instantly, thank god. Something about shuffling Nicohood's variables caused random signalling. Oh well.
