/*
   This ino file should be used in conjunction with the ArmFunctions.h file.
*/

#include <Servo.h> //Library needed to inpute values to the servo.
#include <math.h> //Math Library needed to do some angle meassurements (Sin/Cos/Tan)
#include "ArmFunctions.h" //Header file to organize all the prebuilt functions.

Servo myservo_5; //There are six servos on this particular robot arm. The bottom servo is labeled Servo_5.
Servo myservo_4; //Servo_4 is the first arm structure from the mainframe of the robot body.
Servo myservo_3; //Servo_3 is the second arm connected directly to the first one.
Servo myservo_2; //Servo_2 is the servo following the second arm. Can be thought of like the "pitch" of the hand.
Servo myservo_1; //Servo_1 is the servo below the hand that lets it control the "roll" of the hand.
Servo myservo_0; //Servo_0 is the servo that dictates how much the hand opens and closes.

float A = 10.5, //A is the length of the first arm. In this robot, it is 10.5cm.
      B = 8.85; //B is the length of the second arm. In this robot, it is 8.85cm.
String InString; //InString is the variable which keyboard inputs will be sent to.
float count; //Count dictates how complete a motion is. Ranges between 0 (Not Complete) to 1000 (Fully Complete)

float startAngles[6] = {75, 90, 90, 90, 90, 90};
float currentAngles[6] = {75, 90, 90, 90, 90, 90};
float endAngles[6] = {75, 90, 90, 90, 90, 90};

/*
   The robot doesn't necessarily know where its moving parts are in 3D space. Therefore, we have an array that keeps track of the angles of each servo.
   If we didn't keep track of the angles of every servo, there would be times where the robot wouldn't know where to go, how fast to go, or even what its position in space is.
   There are six values in this array--one for each of the servos. They follow the following order:

   {Servo_4, Servo_3, Servo_5, Servo_2, Servo_1, Servo_0}

   The reason for the unusual order is because of the way the robot moves. We want our robot to move to points of 3D space. It is easier to visualize a 3D point that we want
   the robot to move to rather than multiple angles of servos moving together to reach a specified point. Since we will be working with 3D points, they are written in the order
   (X,Y,Z), with X being the distance from the origin on the X-Axis, Y being the distance from the origin on the Y-Axis, and Z being the distance from the origin on the Z-Axis.
   The platform of the robot is set up in such a way where the Arduino and wire connections are off to the left on the metal stand, and the robot has free motion in the empty space
   in front of it. Thinking from the perspective of the robot, the X-Axis would go forward and backward, the Y-Axis would go straight up, and the Z-Axis would travel from left to right.
   Additionally, the negative X-Axis is behind the robot, the negative Y-Axis would go down under it, aand the negative Z-Axis would go to the left. The axeses are set up in a way where
   the positive space is in the range of motion of the robot. The video here shows this setup: https://www.youtube.com/watch?v=UsHJvPzx4wk

   Because of this 3D system, the servo labeled Servo_5 can only turn the robot hand left and right, or into the Z-Axis. Therefore, we associate Servo_4 and Servo_3 with the (X,Y) movement
   and Servo_5 with the final Z movement. Servo_2, Servo_1 and Servo_0 are just additional angles used to manipulate the arm after the robot reaches the desired 3D point. The robot can move
   to a point such as (10,9,-8), but Servo_2, Servo_1 and Servo_0 can make it point the hand downward, tilted or even open and close it.

   a. startAngles[] is the array that saves the beginning angles before a motion.
   b. currentAngles[] is the array that updates the current angles the robot is at.
   c. endAngles[] is the array that describes the final angles of a motion.

   NOTE_1: Servo_4 is set at a value of 75 degrees rather than 90. This servo doesn't go directly vertical at 90 degrees. The exact reason is unknown [EDIT NEEDED]. All references to this angle
         need an adjustment of 15 degrees. At 0 degrees, this servo is about 15 degrees off of parallel. This means that at 180 degrees, the servo would caause the arm to over extend. Functions
         throughout this code prevent that from happening. Additionally, any starting position angles can be chosen, these are the angles that work for one particular robot.
*/

void setup() {
  myservo_5.attach(3);  // Attaches the myservo_5 on pin 3 to the servo object.
  myservo_4.attach(5);  // Attaches the myservo_4 on pin 5 to the servo object.
  myservo_3.attach(6);  // Attaches the myservo_3 on pin 6 to the servo object.
  myservo_2.attach(9);  // Attaches the myservo_2 on pin 9 to the servo object.
  myservo_1.attach(10);  // Attaches the myservo_1 on pin 10 to the servo object.
  myservo_0.attach(11);  // Attaches the myservo_0 on pin 11 to the servo object.
  Serial.flush();
  Serial.begin(9600);
  ClearQueue(); //Resets the main queue where points are saved.
  Default(); //Sets the main queue to the default position point.
  MoveFromQueue(); //Moves to the points saved in the queue (currently just the default point).
}

void Deg_5(float a) //This function moves Servo_5 to an angle between 0 and 180.
{
  myservo_5.write(a);
}
void Deg_4(float a) //This function moves Servo_4 to an angle between 0 and 180. To keep the movement consistent, we reverse the values of the servo. Instead of moving right to left from 0 degrees to 180, it now moves left to right.
{
  a = 180 - a;
  myservo_4.write(a);
}
void Deg_3(float a) //This function moves Servo_3 to an angle between 0 and 180.
{
  myservo_3.write(a);
}
void Deg_2(float a) //This function moves Servo_2 to an angle between 0 and 180. This servo has an increased range of 270 degrees, but needs extra equations to understand angle measurements.
{
  a = a + 67.5;
  a = a / 1.5;
  myservo_2.write(a);
}
void Deg_1(float a) //This function moves Servo_1 to an angle between 0 and 180.
{
  myservo_1.write(a);
}
void Deg_0(float a) //This function moves Servo_0 to an angle between 0 and 180.
{
  myservo_0.write(a);
}

float Distance(float px1, float py1, float px2, float py2) //The distance function calculates the distance between two points in (X,Y) space only.
{
  return sqrt(sq(px2 - px1) + sq(py2 - py1));
}

void XY(float m, float n)
{
  /*
     This function takes a point in 2D space, (m,n), and then changes the angles on Servo_4 and Servo_3 to hit that point. It changes the angle in the array endAngles[] so
     future servo moving functions can read from that list. This function doesn't alter Servo_5 at all as Servo_5 is what allows the robot to move left and right.

     This desmos link shows a side view visualization of the first two arms of the robot: https://www.desmos.com/calculator/zgmw47nks6

     The calculations in that program show the following float values being calculated so that the Servo_4 and Servo_3 angles can be figured out.

     NOTE: This point is represented by the end of the second arm, or the connection of Servo_2.
  */

  float C = sq(m) + sq(n) - sq(B) + sq(A); //A constant used to calculate the coordinates of the joint of the robot.
  float x1 = ((4 * m * C - sqrt((64 * sq(m) * sq(A) * sq(n)) + (64 * sq(n) * sq(n) * sq(A)) - (16 * sq(n) * sq(C)))) / ((8 * sq(m)) + (8 * sq(n)))); //The x coordinate of one point of one joint.
  float y1 = (((-2 * m * x1) + C) / (2 * n)); //The y coordinate of one point of one joint.

  if (Distance(0, 0, m, n) < sqrt(sq(A) + sq(B)) || Distance(0, 0, m, n) > (A + B) || n < 0 || y1 < 0)
  {
    /*
       This if statement checks four different things. The first check is to see if the desired 2D point is too close to the origin. Due to each servo having
       a specific length, and only being able to go to angles between 0 and 180, there are certain 2D coordinates close to the origin of the robot that can simply
       not be touched. The second check is to see if the desired point is too far outside the maximum range of the robot. Even when fully exteneded, the robot can only
       reach so far. Anything outside maximum extensions is physically impossible. The robot would have to have longer arms to reach this point. The third check is to see if
       the desired point goes below the ground. This is again physically impossible. The final check is to see if one of the joints of the robot goes below the ground. y1 is the
       y coordinate of one of the joints of the robot. If this goes into the ground, or below 0, one knows that desired point cannot be reached. If all these checks are false,
       the "Out of Range" message isn't printed.

    */

    Serial.println("Out of Range");
    return;
  }
  else
  {
    /*
       Again, each of these floats are just variables needed to determine joint coordinates, slopes, and eventually the angles required for Servo_4 and Servo_3 to successfully
       move to the point in question.

    */

    float s1 = y1 / x1; //The slope the first arm makes.
    float o1 = (n - y1) / (m - x1); //The slope the second arm makes.
    float p1 = -1 / s1; //The perpendicular slope at the connection between the first and second arm.
    float a1 = atan(s1) * (180 / PI); //Servo_4 angle.
    float b1 = atan(((o1 - p1) / (1 + (o1 * p1)))) * (180 / PI); //Servo_3 angle.

    if (a1 < 15 && a1 > 0)
    {
      /*

         Using the triginometry functions here, as well as the previous check, the only time the Servo_4 angle would go between 0 and 15 is if it was trying to go beyond the limitations described
         before in the currentAngles[] NOTE. Therefore, we use a check here to see if an impossible angle is achieved. If so, the Serial prints an error message.

      */
      Serial.println("a1 is below 15 degrees");
      return;
    }
    else
    {
      if (a1 <= 0)
      {
        /*
           The trigonometric functions work in such a way that they give angles in a range of -90 to 90 rather than 0 to 180. The negative values simply represent angles greater than 90. So, if the angle
           does come back negative, we simply subtract it from 180 to give the corrected angle.
        */
        a1 = 180 + a1;
      }
      a1 = a1 - 15; //15 is subtracted from the angle to correct it to the actual value.
      endAngles[0] = a1; //Servo_4's angle gets input into the matrix to be read later.
      endAngles[1] = b1; //Servo_3's angle gets input into the matrix to be read later.
    }
  }
}

float AngleTopView(float j, float m)
{
  /*
     This function determines what angle Servo_5 has to move to in order to match the Z coordinate. Since the entire arm would rotate, the X coordinate is also needed to determine the angle needed to rotate.
     j is the Z coordinate, and m is the X coordinate.
  */
  float t = m / j;
  float theta = atan(t) * (180 / PI);
  if (theta < 0)
  {
    theta = 180 + theta;
  }
  return theta;
}

void XYZ(float m, float n, float j)
{
  /*
     The main function. It takes three values (m,n,j) in reference to the (x,y,z) coordinates.
  */
  if ((sq(m) + sq(n) + sq(j)) > sq(A + B) || n < 0 || Distance(0, 0, sqrt((sq(m) + sq(j))), n) < sqrt(sq(A) + sq(B)))
  {
    /*
       This if statement checks three things. The first check is to see whether the point in question is too far outside the possible range of the robot. The second check
       is to see whether the y coordinate is less than 0. In this case, the robot arm would have to go into the ground which is not possible. The third check is to see
       whether the point in question is too close to the origin of the robot. The equation checks if the distance from thhe origin to the point in quesstion is less than the
       minimum range possible.

    */
    Serial.println("Out of Range");
    return;
  }
  else
  {
    endAngles[2] = AngleTopView(j, m);
    int sign_converter = 1;
    if (m < 0)
    {
      sign_converter = -1;
    }
    m = sign_converter * sqrt((sq(m) + sq(j)));
    /*
         This distance function determines the new value for m. If it was negative beforehand, it is important to make it negative after the square and square root functions.
    */
    XY(m, n); //Finally, after Servo_5 gets its angle, and m is converted, the XY() function solves the angle for Servo_4 and Servo_3.
  }
}


void ClearQueue() //Two for loops that set each value in the queue[][] array to 0.
{
  for ( int i = 0; i <= (sizeof(queue) / sizeof(queue[0])) - 1; i++)
  {
    for (int j = 0; j <= (sizeof(queue[0]) / sizeof(queue[0][0])) - 1; j++)
    {
      queue[i][j] = 0;
    }
  }
}

void ShiftQueue() //Two for loops that take changes the values in queue[x][y] to queue[x+1][y]. Essentially, each array gets shifted left.
{
  for (int i = 0; i <= (sizeof(queue) / sizeof(queue[0])) - 2; i++)
  {
    for (int j = 0; j <= (sizeof(queue[0]) / sizeof(queue[0][0])) - 1; j++)
    {
      queue[i][j] = queue[i + 1][j];
    }
  }
}

bool CheckEmpty()
/*
   Boolean to see if the "t" variable in the queue is 0. Every movement requires a non-zero amount of time, so if this is 0, the point is either invalid,
   or--more likely--the queue is empty.
*/
{
  if (queue[0][6] == 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}

void MoveFromQueue()
{
  if (Serial.available())
  {
    InString = Serial.readString();
    KeyboardRead();
  }
  if (CheckEmpty())
  {
    return; //If the main queue is empty, there is no point in moving. Return and wait for any input.
  }
  else
  {
    PointMove(queue[0][0], queue[0][1], queue[0][2], queue[0][3], queue[0][4], queue[0][5], queue[0][6]); //Instead of moving to angles it is easier to refer to 3D points.
  }
}

void PointMove(float x, float y, float z, float head, float head_tilt, float open_head, int t)
{
  XYZ(x, y, z); //Takes the x,y, and z values and calculates the angles Servo_4, Servo_3 and Servo_5 would need to be at.
  endAngles[3] = head;
  endAngles[4] = head_tilt;
  endAngles[5] = open_head;
  ServoMoveAsynch(endAngles[0], endAngles[1], endAngles[2], endAngles[3], endAngles[4], endAngles[5], t);
}

void ServoMoveAsynch(float a1, float a2, float a3, float a4, float a5, float a6, int t)
{
  startAngles[0] = currentAngles[0];
  startAngles[1] = currentAngles[1];
  startAngles[2] = currentAngles[2];
  startAngles[3] = currentAngles[3];
  startAngles[4] = currentAngles[4];
  startAngles[5] = currentAngles[5];
  /*
     Whatever the current position of the robot is (currentAngles[0-5]), startAngles[0-5] get updated to match the initial angle measurements before the actual movement.
  */
  endAngles[0] = a1;
  endAngles[1] = a2;
  endAngles[2] = a3;
  endAngles[3] = a4;
  endAngles[4] = a5;
  endAngles[5] = a6;
  /*
     The final angles are the values input into the ServoMoveAsynch() function. At this point, the startAngles[] are properly updated, and the endAngles[] are properly
     updated.
  */
  float diff_0 = endAngles[0] - startAngles[0];
  float diff_1 = endAngles[1] - startAngles[1];
  float diff_2 = endAngles[2] - startAngles[2];
  float diff_3 = endAngles[3] - startAngles[3];
  float diff_4 = endAngles[4] - startAngles[4];
  float diff_5 = endAngles[5] - startAngles[5];
  /*
     The difference between the startAngles[] and the endAngles[] are calculated and put into the diff_0 through diff_5 variables. They will determine how much each servo has to
     change angles to actually reach the desired endAngles[].
  */
  unsigned long startmillis = millis();
  unsigned long endmillis = startmillis + t;
  /*
     t is the desired amount of the time the motion should last. Millis() takes the amount of time passed since the arduino got powered on. It is important to save the time as an
     unsigned long instead of an integer because of the size of possible values. An integer can store a 16-bit value while a long can store 32-bits. This is the difference between
     around a minute, and fifty days.
  */
  count = 0;
  /*
     The count variable determines the completion of the motion. It ranges from 0 to 1000 (count_max). It was originally a float that would range from 0 to 1, but because the map function
     only does integer map, it would only produce values of 0 and 1 instead of the decimal points in between.

     Note from Arduino documentation:
     As previously mentioned, the map() function uses integer math. So fractions might get suppressed due to this. For example, fractions like 3/2, 4/3, 5/4 will all be returned as 1 from the
     map() function, despite their different actual values. So if your project requires precise calculations (e.g. voltage accurate to 3 decimal places), please consider avoiding map() and
     implementing the calculations manually in your code yourself.
  */
  int count_max = 1000;
  /*
     Can be increased to enhance precision, but 1000 is a number that provides enough precision.
  */
  while (count <= count_max) //The while loop runs until the count (the variable that determines the completion of the movement) reaches its maximum value.
  {
    count = map(millis(), startmillis, endmillis, 0, count_max);
    /*
       count begins at 0 when the motion starts. As it approaches the endmillis time declared earlier, it approaches the final max value. Essentially, the count variable is mapped from the current
       time to a range of 0% to 100%. This count variable is then used to determine how much to move each servo.
    */
    Deg_4(startAngles[0] + ((count / count_max) * (diff_0)));
    Deg_3(startAngles[1] + ((count / count_max) * (diff_1)));
    Deg_5(startAngles[2] + ((count / count_max) * (diff_2)));
    Deg_2(startAngles[3] + ((count / count_max) * (diff_3)));
    Deg_1(startAngles[4] + ((count / count_max) * (diff_4)));
    Deg_0(startAngles[5] + ((count / count_max) * (diff_5)));
    /*
       count/count_max is the percentage of the movement that is complete. This while loop will run until count exceeds count_max, or in other words, it completed 100% of the desired movement.
       The startAngles[] provide a reference to where the robot initially was, and the diff_x values show how much each servo needs to shift.
    */
    currentAngles[0] = (startAngles[0] + ((count / count_max) * (diff_0)));
    currentAngles[1] = (startAngles[1] + ((count / count_max) * (diff_1)));
    currentAngles[2] = (startAngles[2] + ((count / count_max) * (diff_2)));
    currentAngles[3] = (startAngles[3] + ((count / count_max) * (diff_3)));
    currentAngles[4] = (startAngles[4] + ((count / count_max) * (diff_4)));
    currentAngles[5] = (startAngles[5] + ((count / count_max) * (diff_5)));
    /*
       After every incremental movement of each servo, the currentAngles[] get updated. This is because the movement from point A to point B can get interrupted at any time, and it is important to
       know the current values of the servos at any given time as there is a possibility of another keypress interrupting the action and therefore artificially completing the movement.
    */
    if (Serial.available()) //If a keystroke is sent to the Serial Monitor
    {
      InString = Serial.readString(); //Reads the incoming keystroke
      count = count_max + 1; //Artificially completes the movement by setting the count variable to one above the max.
      KeyboardRead(); //Clears the queue and determines what function needs to fill the queue based on the keystroke sent.
      return; //Doesn't continue the loop and simply returns.
    }
  }
  ShiftQueue(); //If there is no keystroke sent during the movement, this function shifts the queue so the next point (queue[1]) is in the proper poisition (queue[0]).
}


void KeyboardRead()
{
  ClearQueue(); //Important to clear the queue before altering any values in it.
  if (InString == "a")
  {
    Excited();
  }
  if (InString == "s")
  {
    Sad();
  }
  if (InString == "d")
  {
    Default();
  }
  if (InString == "c")
  {
    Circle();
  }
  if (InString == "h")
  {
    HorseShoe();
  }
  if (InString == "t")
  {
    Throw();
  }
  if (InString == "x")
  {
    return;
  }
}

void loop()
{
  MoveFromQueue();
}
