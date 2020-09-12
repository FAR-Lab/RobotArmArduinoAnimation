# Robot Arm Arduino Animation

### Summary
A six servo robotic hand is controlled in 3D space with the help of an Arduino Mini--more specifically an Adafruit Micro Mini. The code defines a 3D point based system for the robot to move around in, and has functions that help calculate movements to points in space. The user inputs points the robot would like to move to and the code calculates the required angles each servo must move to in order to reach that point.

### Robot Specs + Assembly + Schematic
The name of the particular robot arm I used to build and test on was called the **LewanSoul 6DOF**.

[Buy the robot](https://www.amazon.com/LewanSoul-Robotic-Arduino-Software-Tutorial/dp/B074T6DPKX)

[Watch the assembly video](https://www.youtube.com/watch?v=8U6sWG6N5w8&list=PLQYW5Ukp-1D_z2C-tdKFFuJjK9zoAfM57&index=2)

[Schematic for arduino and servo connections (TINKERCAD)](https://www.tinkercad.com/things/fWX9UZN7YsP-terrific-elzing-wluff/editel?tenant=circuits)

[Schematic for arduino and servo connections (IMAGE)](https://imgur.com/a/ABNZXcD)

### Explanatory Video
[Here](https://youtu.be/jFfA_24hS0Y) is a video that showcases the code one might find here. It describes how the robot works and gives the user a tutorial to create their own paths and movements.

[Here](https://imgur.com/a/TPxrWXB) are two images that show the difference in coordinate systems between the robot code and the additional 3D Calculator program.

### Youtube Links
These videos showcase some of the actions I have been able to complete with my robot.

In order from most recent to least recent:
[Explanatory Video](https://youtu.be/jFfA_24hS0Y)

[Robot Arm Throwing Ball](https://youtu.be/CUMaveZK-uk)

[Robot Arm Dancing](https://www.youtube.com/watch?v=UsHJvPzx4wk)

[Robot Arm Drawing Horizontal Lines](https://www.youtube.com/watch?v=711mE4_5Rwk)

[Robot Arm Drawing Smiley Face](https://www.youtube.com/watch?v=ATHjjI4BhdQ)

### Desmos Graphing Tool
Desmos was an important tool in defining the necessary functions to allow the robot to move correctly.

[Main Desmos Graph](https://www.desmos.com/calculator/zgmw47nks6)

### 3D Graphing Calculator Software
Runiter was used to create 3D paths, as well as create a solid visualization for the possible range of the robot.

[Runiter](https://www.runiter.com)

### How To Add Your Own Movements:
The robot moves to different 3D points stored in a two dimensional array called "queue". The main way of actually making the servos move is to read keyboard inputs, run specific functions based on the keystroke sent to the arduino, change the "queue" array with desired points, and finally read from the "queue" array to know which points to move to. 

**Step 1:**
```
Serial.println("Hello World!);
```
**Step 2:**
```
Serial.println("Hello World2!);
```
