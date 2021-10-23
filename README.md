# SciFiLighting
Code for Sci fi Backlight.
Main file is SciFiLighting.ino, name your fоlder like that after cloning the repoitory(if it is not named properly).
# How to upload code into arduino UNO R3:
 - Download all files
 - Rename folder to SciFiLighting if needed
 - Open main file
 - Select your arduino type and corresponding port
 - Upload
# How to build a prototype
 - Download [3D models](https://www.thingiverse.com/thing:4830996)
 - Print them with 3D-printer
 - Sold elecronics(IR sensor with resistors and LEDs strip)
 - For pins and settings see main .ino file.
# IR sensor soldering scheme
![image](https://user-images.githubusercontent.com/48696470/133154790-29a05724-290a-40bf-b3e0-974b26cc56b0.png)


# RF protocol(control via RF)
First of all, message is looking something like {"code": 1234}.
The field "code" contains decimal number representing a code of operation.
This program uses ArduinoJson, so too big messages are restricted(40 characters for now).

**Memory usage is too high, some modes are temporarily disabled.**

# Commands
| HEX      	| DEC      	| DESCRIPTION                        	|
|----------	|----------	|------------------------------------	|
| 0xFFA857 	| 16754775 	| Pressed Plus: Increase brightness  	|
| 0xFFE01F 	| 16769055 	| Pressed Minus: Decrease brightness 	|
| 0xFFC23D 	| 16761405 	| Pressed Play/Pause: TurnOff        	|
| 0xFF6897 	| 16738455 	| Pressed 0: Just light              	|
| 0xFF30CF 	| 16724175 	| Pressed 1: Twinkle fox             	|
| 0xFF18E7 	| 16718055 	| Pressed 2: Pacifica                	|
| 0xFF7A85 	| 16743045 	| Pressed 3: Pride2015               	|
| 0xFF10EF 	| 16716015 	| Pressed 4: First light             	|
| 0xFF38C7 	| 16726215 	| Pressed 5: Blink                   	|
| 0xFF5AA5 	| 16734885 	| Pressed 6: Color temperature       	|
| 0xFF42BD 	| 16728765 	| Pressed 7: Demo reel 100           	|
| 0xFF4AB5 	| 16730805 	| Pressed 8: Just blue               	|
| 0xFF52AD 	| 16732845 	| Pressed 9: Just green              	|