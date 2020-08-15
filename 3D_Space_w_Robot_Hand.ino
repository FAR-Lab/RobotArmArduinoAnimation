#include <Servo.h> //Library needed to inpute values to the servo.
#include <math.h> //Math Library needed to do some angle meassurements (Sin/Cos/Tan)

Servo myservo_5; //There are six servos on this particular robot arm. The bottom servo is labeled Servo_5. 
Servo myservo_4; //Servo_4 is the first arm structure from the mainframe of the robot body.
Servo myservo_3; //Servo_3 is the second arm connected directly to the first one.
Servo myservo_2; //Servo_2 is the servo following the second arm. Can be thought of like the "pitch" of the hand.
Servo myservo_1; //Servo_1 is the servo below the hand that lets it control the "roll" of the hand.
Servo myservo_0; //Servo_0 is the servo that dictates how much the hand opens and closes.

float A = 10.5, //A is the length of the first arm. In this robot, it is 10.5cm.
      B = 8.85; //B is the length of the second arm. In this robot, it is 8.85cm. 
int potentvalue = 0, potent = A0; //An optional potentiometer variable is made here. Connect the potentiometer to A0.
int button_1 = 4, buttonstate_1 = 0, lastbuttonstate_1=0, //Variables for an optional button. Variables include the pin location (4) and current/last states.
    button_2 = 2, buttonstate_2 = 0, lastbuttonstate_2=0; //Variables for a second optional button. Variables include the pin location (2) and current/last states.
int buttoncount = 0; //Variable used to count how many times a button was pressed.

float currentAngles[6] = {75,90,90,90,90,90};
/* 
 * The robot doesn't necessarily know where its moving parts are in 3D space. Therefore, we have an array that keeps track of the angles at each servo. 
 * If we didn't keep track of the angles at every servo, there would be times where the robot wouldn't know where to go, how fast to go, and on occasion just move randomly.
 * There are six values in this array; one for each of the servos. They follow the following order.
 * 
 * {Servo_4, Servo_3, Servo_5, Servo_2, Servo_1, Servo_0}
 * 
 * The reason for the unusual order is because of the way the robot moves. We want our robot to move to points of 3D space. It is easier to visualize a 3D point that we want
 * the robot to move to rather than multiple angles of servos moving together to reach a specified point. Since we will be working with 3D points, they are written in the order
 * (X,Y,Z), with X being the distance from the origin on the X-Axis, Y being the distance from the origin on the Y-Axis, and Z being the distance from the origin on the Z-Axis.
 * The platform of the robot is set up in such a way where the Arduino and wire connections are off to the left on the metal stand, and the robot has free motion in the empty space
 * in front of it. Thinking from the perspective of the robot, the X-Axis would go forward and backward, the Y-Axis would go straight up, and the Z-Axis would travel from left to right.
 * Additionally, the negative X-Axis is behind the robot, the negative Y-Axis would go down under it, aand the negative Z-Axis would go to the left. The axeses are set up in a way where
 * the positive space is in the range of motion of the robot.
 * 
 * Because of this 3D system, the servo labeled Servo_5 can only turn the robot hand left and right, or into the Z-Axis. Therefore, we associate Servo_4 and Servo_3 with the (X,Y) movement
 * and Servo_5 with the final Z movement. Servo_2, Servo_1 and Servo_0 are just additional angles used to manipulate the arm after the robot reaches the desired 3D point. The robot can move
 * to a point such as (10,9,-8), but Servo_2, Servo_1 and Servo_0 can make it point the hand downward, tilted or even open and close it.
 * 
 * By having an array with the angles of each servo, it provides a bassis for many functions to calculate where each servo to move to. The current value of the array sets the robot in a 
 * straight up, "default", position.
 * 
 * NOTE: Servo_4 is set at a value of 75 degrees rather than 90. This servo doesn't go directly vertical at 90 degrees. The exact reason is unknown [EDIT NEEDED]. All references to this angle
 *       need an adjustment of 15 degrees. At 0 degrees, this servo is about 15 degrees off of parallel. This means that at 180 degrees, the servo would caause the arm to over extend. Functions
 *       here prevent that from happening. If a different servo is being used, this starting position in currentAngles[] and newAngles[] can be switched from 75 to 90. Additionally, any starting
 *       position angles can be chosen, these are the angles that work for one particular robot.
 * 
 */
float newAngles[6] = {75,90,90,90,90,90}; 
/*
 * Similar to currentAngles[], but this array is used to determine what angle each servo needs to move to. Currently, both arrays are the same and will change with functions altering the
 * movement of the robot.
 * 
 * NOTE: Servo_4 is set at a value of 75 degrees rather than 90. This servo doesn't go directly vertical at 90 degrees. The exact reason is unknown [EDIT NEEDED]. All references to this angle
 *       need an adjustment of 15 degrees. At 0 degrees, this servo is about 15 degrees off of parallel. This means that at 180 degrees, the servo would caause the arm to over extend. Functions
 *       here prevent that from happening. If a different servo is being used, this starting position in currentAngles[] and newAngles[] can be switched from 75 to 90. Additionally, any starting
 *       position angles can be chosen, these are the angles that work for one particular robot.
 */

void setup() {
  myservo_5.attach(3);  // Attaches the myservo_5 on pin 3 to the servo object.
  myservo_4.attach(5);  // Attaches the myservo_4 on pin 5 to the servo object.  
  myservo_3.attach(6);  // Attaches the myservo_3 on pin 6 to the servo object.
  myservo_2.attach(9);  // Attaches the myservo_2 on pin 9 to the servo object.
  myservo_1.attach(10);  // Attaches the myservo_1 on pin 10 to the servo object.
  myservo_0.attach(11);  // Attaches the myservo_0 on pin 11 to the servo object.
  Serial.flush();
  Serial.begin(9600); //Sets up the serial monitor in order to debug and see angle values.
  pinMode(potent,INPUT); //Optional Potentiometer is set as an input.
  pinMode(button_1,INPUT); //Optional Button_1 is set as an input.
  pinMode(button_2,INPUT); //Optional Button_2 is set as an input.
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

void Button1Pressed()
{
  buttonstate_1 = digitalRead(button_1); //Optional Button function that is called only when the button is pressed from off to on. In this case, pressing the button increments the buttoncount variable.
  if (buttonstate_1 != lastbuttonstate_1)
  {
    if (buttonstate_1 == 1)
    {
      buttoncount = buttoncount + 1;
      Serial.println(buttoncount);  
    }
  }
  lastbuttonstate_1 = buttonstate_1;
}

void Button2Pressed() //Optional Button function that is called only when the button is pressed from off to on. In this case, pressing the button resets the buttoncount variable to 0.
{
  buttonstate_2 = digitalRead(button_2);
  if (buttonstate_2 != lastbuttonstate_2)
  {
    if (buttonstate_2 == 1)
    {
      buttoncount = 0;
      Serial.println(buttoncount);  
    }
  }
  lastbuttonstate_2 = buttonstate_2;
}

void Potentiometer() //Optional Potentiometer function that maps the analog values of (0 -> 1023) to (0 -> 180).
{
  potentvalue = analogRead(potent); 
  potentvalue = map(potentvalue,0,1023,0,180);
}

float Distance(float px1, float py1, float px2, float py2) //The distance function calculates the distance between two points in (X,Y) space only.
{                                                          
  return sqrt(sq(px2-px1) + sq(py2-py1));
}

void XY(float m, float n) 
{
  /*
   * This function takes a point in 2D space, (m,n), and then changes the angles on Servo_4 and Servo_3 to hit that point. It changes the angle in the array newAngles[] so
   * future servo moving functions can read from that list. This function doesn't alter Servo_5 at all as Servo_5 is what allows the robot to move left and right. 
   * 
   * This desmos link shows a side view visualization of the first two arms of the robot: https://www.desmos.com/calculator/zgmw47nks6
   * 
   * The calculations in that program show the following float values being calculated so that the Servo_4 and Servo_3 angles can be figured out.
   * 
   * NOTE: This point is represented by the end of the second arm, or the connection of Servo_2.
   */
   
  float C = sq(m) + sq(n) - sq(B) + sq(A); //A constant used to calculate the coordinates of the joint of the robot.
  float x1 = ((4*m*C - sqrt((64 * sq(m) * sq(A) * sq(n))+(64 * sq(n) * sq(n) * sq(A))-(16 * sq(n) * sq(C))))/((8*sq(m))+(8*sq(n)))); //The x coordinate of one point of one joint.
  float y1 = (((-2*m*x1) + C)/(2*n)); //The y coordinate of one point of one joint.
  
  if (Distance(0,0,m,n) < sqrt(sq(A) + sq(B)) || Distance(0,0,m,n) > (A + B) || n < 0 || y1 < 0) 
  { 
    /*                                                                                             
     * This if statement checks four different things. The first check is to see if the desired 2D point is too close to the origin. Due to each servo having                                                                                             
     * a specific length, and only being able to go to angles between 0 and 180, there are certain 2D coordinates close to the origin of the robot that can simply                                                                                              
     * not be touched. The second check is to see if the desired point is too far outside the maximum range of the robot. Even when fully exteneded, the robot can only
     * reach so far. Anything outside maximum extensions is physically impossible. The robot would have to have longer arms to reach this point. The third check is to see if
     * the desired point goes below the ground. This is again physically impossible. The final check is to see if one of the joints of the robot goes below the ground. y1 is the
     * y coordinate of one of the joints of the robot. If this goes into the ground, or below 0, one knows that desired point cannot be reached. If all these checks are false,
     * the "Out of Range" message isn't printed.
     * 
     */
     
    Serial.println("Out of Range");                                                         
    return;
  }
  else
  {
    /*
     * Again, each of these floats are just variables needed to determine joint coordinates, slopes, and eventually the angles required for Servo_4 and Servo_3 to successfully
     * move to the point in question.
     * 
     */
     
    float s1 = y1/x1; //The slope the first arm makes.
    float x2 = ((4*m*C + sqrt((64 * sq(m) * sq(A) * sq(n))+(64 * sq(n) * sq(n) * sq(A))-(16 * sq(n) * sq(C))))/((8*sq(m))+(8*sq(n)))); //The x coordinate of one point of an alternate joint.
    float y2 = (((-2*m*x2) + C)/(2*n)); //The y coordinate of one point of an alternate joint.
    float s2 = y2/x2; //The slope the first arm would make if another path to the point was taken.
    float o1 = (n-y1)/(m-x1); //The slope the second arm makes.
    float o2 = (n-y2)/(m-x2); //The slope the second arm makes if another path to the point was taken.
    float p1 = -1/s1; //The perpendicular slope at the connection between the first and second arm.
    float p2 = -1/s2; //The perpendicular slope at the connection between the first and second arm if another path to the point was taken.
    float a1 = atan(s1) * (180/PI); //Servo_4 angle.
    float a2 = atan(s2)* (180/PI); //Servo_4 angle if another path to the point was taken.
    float b1 = atan(((o1-p1)/(1+(o1*p1))))* (180/PI); //Servo_3 angle.
    float b2 = atan(((o2-p2)/(1+(o2*p2))))* (180/PI); //Servo_3 angle if another path to the point was taken.
    
    if (a1<15 && a1>0)
    {
      /*
       * 
       * Using the triginometry functions here, as well as the previous check, the only time the Servo_4 angle would go between 0 and 15 is if it was trying to go beyond the limitations described
       * before in the currentAngles[] NOTE. Therefore, we use a check here to see if an impossible angle is achieved. If so, the Serial prints an error message.
       * 
       */
      Serial.println("a1 is below 15 degrees");
      return;                                
    }                                         
    else                                      
    {
      if(a1<=0)
      {
        /*                     
         * The trigonometric functions work in such a way that they give angles in a range of -90 to 90 rather than 0 to 180. The negative values simply represent angles greater than 90. So, if the angle                    
         * does come back negative, we simply subtract it from 180 to give the corrected angle.
         */
        a1 = 180 + a1;      
      }
      a1 = a1-15; //15 is subtracted from the angle to correct it to the actual value.
      newAngles[0] = a1; //Servo_4's angle gets input into the matrix to be read later.
      newAngles[1] = b1; //Servo_3's angle gets input into the matrix to be read later.
    }
  }
}

float AngleTopView(float j, float m)
{ 
  /*                                    
   * This function determines what angle Servo_5 has to move to in order to match the Z coordinate. Since the entire arm would rotate, the X coordinate is also needed to determine the angle needed to rotate.                                    
   * j is the Z coordinate, and m is the X coordinate.
   */
  float t = m/j;
  float theta = atan(t) * (180/PI);
  if (theta < 0)
  {
    theta = 180 + theta;
  }
  return theta;
}

void XYZ(float m, float n, float j)
{
  /*
   * The main function. It takes three values (m,n,j) in reference to the (x,y,z) coordinates.
   */
  if((sq(m) + sq(n) + sq(j)) > sq(A+B) || n < 0 || Distance(0,0,sqrt((sq(m)+sq(j))),n) < sqrt(sq(A) + sq(B)))
  {
    /*
     * This if statement checks three things. The first check is to see whether the point in question is too far outside the possible range of the robot. The second check 
     * is to see whether the y coordinate is less than 0. In this case, the robot arm would have to go into the ground which is not possible. The third check is to see 
     * whether the point in question is too close to the origin of the robot. The equation checks if the distance from thhe origin to the point in quesstion is less than the
     * minimum range possible.
     *
     */
    Serial.println("Out of Range");   
    return;                         
  }
  else
  {          
    newAngles[2] = AngleTopView(j,m);
    /*
     * If none of those checks return true, that means that the point is possible in the robot's operable range. Servo_5 can now move to meet the Z value, and AngleTopView()
     * determines the value of that angle.
     */
    int sign_converter = 1;
    if(m<0)                          
    {                                
      sign_converter = -1;            
    }
    m = sign_converter * sqrt((sq(m)+sq(j)));
    /*  
     *   This distance function determines the new value for m. If it was negative beforehand, it is important to make it negative after the square and square root functions.
     */
    XY(m,n); //Finally, after Servo_5 gets its angle, and m is converted, the XY() function solves the angle for Servo_4 and Servo_3.
  }                                   
}

void ServoMove(float a1, float a2, float a3,float a4,float a5, float a6,int steps)
{ 
  /*
   * This ServoMove function takes seven parameters. The first six represent Servo_4, Servo_3, Servo_5, Servo_2, Servo_1, and Servo_0. The last is steps, which determines how fluid
   * the actual servo movement will be. Each of these floats is an angle the respective servo will move to. 
   * 
   * a1 = Servo_4 - Combined with Servo_3 to make up the XY movement to the point.
   * a2 = Servo_3 - Combined with Servo_4 to make up the XY movement to the point.
   * a3 = Servo_5 - Moves the robot into the plane of the Z coordinate of the point.
   * a4 = Servo_2 - Dictates angle of hand (PITCH)
   * a5 = Servo_1 - Dictates angle of wrist (ROLL)
   * a6 = Servo_0 - Dictates how open the hand is.
   */
 float diff_1 = a1 - currentAngles[0];
 float diff_2 = a2 - currentAngles[1];
 float diff_3 = a3 - currentAngles[2];
 float diff_4 = a4 - currentAngles[3];
 float diff_5 = a5 - currentAngles[4]; 
 float diff_6 = a6 - currentAngles[5]; 
 /*
  * Each of these floats shows the difference between each angle in each servo. currentAngles[] are the angles where the servos are already at. The a1 through a6 floats show where the 
  * servos have to move to. 
  *
  */
 for(int i=1; i<=steps; i++)                
 {                                          
    Deg_4(currentAngles[0] + (i*(diff_1/steps)));
    Deg_3(currentAngles[1] + (i*(diff_2/steps)));
    Deg_5(currentAngles[2] + (i*(diff_3/steps)));
    Deg_2(currentAngles[3] + (i*(diff_4/steps)));
    Deg_1(currentAngles[4] + (i*(diff_5/steps)));
    Deg_0(currentAngles[5] + (i*(diff_6/steps)));
    Button1Pressed();
    Button2Pressed();
    /*
     * This for function runs "steps" amount of times. The larger the number of steps determined by the user, the less jarring each step of the servo. We need to alternate between each of the
     * servos for each step to produce a fluid movement. Otherwise it would be one servo at a time reaching the required position. The steps allow a fluid motion in increments.
     */
 }
 currentAngles[0] = a1;
 currentAngles[1] = a2;
 currentAngles[2] = a3;
 currentAngles[3] = a4;
 currentAngles[4] = a5;
 currentAngles[5] = a6;
 /*
  * After completing the motion, the currentAngles[] of the robot need to be reset as they are now different.
  */
}

void PointMove(float x, float y, float z, float head, float head_tilt, float open_head, int steps)
{
  /*
   * Similar to ServoMove() but it is more user friendly. This function allows the user to input the 3D point they
   * want the robot to move to, as well as the head position, the head tilt, and how open the hand is.
   */
  XYZ(x,y,z);
  newAngles[3] = head;
  newAngles[4] = head_tilt;
  newAngles[5] = open_head;
  ServoMove(newAngles[0],newAngles[1],newAngles[2],newAngles[3],newAngles[4],newAngles[5],steps);    
}
 
float FuncX_1(float t) //Parametric function for the x coordinate of the funtion_1.
{
  return -3*cos(t)+12;      
}

float FuncY_1(float t) //Parametric function for the y coordinate of the funtion_1.
{
  return 3*cos(t)+12;
}

float FuncZ_1(float t) //Parametric function for the z coordinate of the funtion_1.
{
  return 3*sin(t);
}

void Parent_Function_1(float tmin, float tmax, int samples, int steps)
/*
 * The way this function works is by calculating multiple points
/* in space between a range determined by the variable "t". 
/* Points are determined between t_min and t_max, and there
/* are "sample" amount of points between those two values.
/* x is a_0, y is a_1, and z is a_2. XYZ then converts those points
/* to angles the robot has to reach, and then moves the servos to
/* those angles.
 */
{  
  float inc = (tmax-tmin)/(samples-1);
  for (int i = 0; i<samples; i++)
  {
    float a_0 = FuncX_1(tmin + (i * inc));
    float a_1 = FuncY_1(tmin + (i * inc));
    float a_2 = FuncZ_1(tmin + (i * inc));
    float array_points[4] = {a_0,a_1,a_2,steps}; //A new array is made to store the updated points the robot needs to move to.
    XYZ(array_points[0],array_points[1],array_points[2]);
    if (i == 0) //If the robot is doing the first increment, we make sure the amount of steps is 2000 to prevent sudden jerking.
    {   
        ServoMove(newAngles[0],newAngles[1],newAngles[2],newAngles[3],newAngles[4],newAngles[5],2000);   
    }
    else
    {
        ServoMove(newAngles[0],newAngles[1],newAngles[2],newAngles[3],newAngles[4],newAngles[5],array_points[3]);
    }
  }
}

void loop() 
{
  Potentiometer();
  if(potentvalue<=90)
  { 
    Button1Pressed();
    Button2Pressed();
    switch (buttoncount)
    {
      case 0:
      PointMove(0.1,19,0,102.19,90,0,1000);
      PointMove(0.1,14,0,138.95,45,0,1000);
      PointMove(0.1,19,0,102.19,90,0,1000);
      PointMove(0.1,14,0,138.95,135,0,1000);
      //Excited
      break;
      case 1:
      PointMove(2.1,15.1,0,0,90,90,1000);
      PointMove(2.1,15.1,0,0,45,90,1000);
      PointMove(2.1,15.1,0,0,90,90,1000);
      PointMove(2.1,15.1,0,0,135,90,1000);
      //Sad
      break;
      case 2:
      PointMove(15,9,0,135,90,90,100);
      Parent_Function_1(-3.1415,3.1415,25,100);
      //Circular     
      break;
      default:
      ServoMove(75.00,90.00,90.00,90.00,90.00,90.00,3000);
      break;
    }   

  }
  else
  { 
    ServoMove(75.00,90.00,90.00,90.00,90.00,90.00,3000);
    buttoncount = 0;
  }
  
}
