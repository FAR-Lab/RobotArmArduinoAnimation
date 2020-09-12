# Robot Arm Arduino Animation

### Summary
A six servo robotic hand is controlled in 3D space with the help of an Arduino Mini--more specifically an Adafruit Micro Mini. The code defines a 3D point based system for the robot to move around in, and has functions that help calculate movements to points in space. The user inputs points the robot would like to move to and the code calculates the required angles each servo must move to in order to reach that point.

### Robot Specs + Assembly + Schematic
The name of the particular robot arm I used to build and test on was called the **LewanSoul 6DOF**.

[Buy the robot](https://www.amazon.com/LewanSoul-Robotic-Arduino-Software-Tutorial/dp/B074T6DPKX)

[Watch the assembly video](https://www.youtube.com/watch?v=8U6sWG6N5w8&list=PLQYW5Ukp-1D_z2C-tdKFFuJjK9zoAfM57&index=2)

[Tinkercad Schematic](https://www.tinkercad.com/things/fWX9UZN7YsP-terrific-elzing-wluff/editel?tenant=circuits)

[PNG Schematic](https://imgur.com/a/ABNZXcD)

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
Open the 3D_Space_w_Robot_Hand_Asynch_Movement.ino file and locate the KeyboardRead() method. There will be an if statement that reads,
```
if(InString == "tutorial")
{
  UserMadeFunction_1();
}
```
Change the InString string check to whatever string you want, but double check to make sure no other movement is using that specific string. For example, Sad() uses "s", and Throw() uses "t". If you want to change the method UserMadeFunction_1() to something else, be sure to change all instances of UserMadeFunction_1() in the attached header file, "ArmFunctions.h".

**Step 2:**
Open the ArmFunctions.h header file and locate the UserMadeFunctin_1() method definition. Again, if you changed the name of this, be sure to change all instances of it to match your desired name. In the definition of the array include two brackets and list out the seven parameters for the point you want the robot to reach. For example, if you want the robot to move to point (10,3,5), have a pitch of 45 degrees, a wrist rotation of 180 degrees, an open hand of 0 degrees, and want to make the robot take 2000 milliseconds to reach that point, the first array will look like the following,
```
void UserMadeFunction_1()
{
  float UserMadeFunction_1[][7] = {{10,3,5,45,180,0,2000}
  };
  //...
  //...
}
```
If you would like more information on the definition of the parameters, watch the explanatory video [here](https://youtu.be/jFfA_24hS0Y).

**Step 3:**
Follow step 2 to add more points--if wanted. A series of points is listed below. Be sure to include commass between sets of curly brackets.
```
void UserMadeFunction_1()
{
  float UserMadeFunction_1[][7] = {{10,3,5,45,180,0,2000},
                                   {5,-5,16,135,0,180,1500},
                                   {3,-12,14,90,90,90,1000}
  };
  //...
  //...
}
```
