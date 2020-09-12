/*
   This header file should be used in conjunction with the 3D_Space_w_Robot_Hand_Asynch_Movement.ino file.
*/

float queue[12][7] = {};
/*
   This is the main queue that includes the information needed for the robot to move to specific points. It is a 2D array consisting of twelve 7-long arrays which take
   the inputs of (x_coordinate, y_coordinate, z_coordinate, head angle, head tilt, open hand, time).

   The maximum function here makes the robot perform a movement through 12 different points. If you create a series longer than 12 points long you must change the array length.

   NOTE: Longer arrays may limit the Arduino's limit for memory storage of global variables.
*/

/*
   Each of the following add points to the main queue array.
*/
//--------------------------------------------------------------------------------------------------

void Sad()
{
  float Sad[][7] = {{2.1, 0, 15.1, 0, 90, 90, 500},
    {2.1, 0, 15.1, 0, 45, 90, 500},
    {2.1, 0, 15.1, 0, 90, 90, 500},
    {2.1, 0, 15.1, 0, 135, 90, 500}
  };
  for ( int i = 0; i <= (sizeof(Sad) / sizeof(Sad[0])) - 1; i++)
  {
    for (int j = 0; j <= (sizeof(Sad[0]) / sizeof(Sad[0][0])) - 1; j++)
    {
      queue[i][j] = Sad[i][j];
    }
  }
}

//--------------------------------------------------------------------------------------------------

void Excited()
{
  float Excited[][7] = {{0.1, 0, 19, 102.19, 90, 0, 500},
    {0.1, 0, 14, 138.95, 45, 0, 500},
    {0.1, 0, 19, 102.19, 90, 0, 500},
    {0.1, 0, 14, 138.95, 135, 0, 500}
  };
  for ( int i = 0; i <= (sizeof(Excited) / sizeof(Excited[0])) - 1; i++)
  {
    for (int j = 0; j <= (sizeof(Excited[0]) / sizeof(Excited[0][0])) - 1; j++)
    {
      queue[i][j] = Excited[i][j];
    }
  }
}

//--------------------------------------------------------------------------------------------------

void Default()
{
  float Default[][7] = {{0.1, 0, 19, 102.19, 90, 90, 1000}};
  for ( int i = 0; i <= (sizeof(Default) / sizeof(Default[0])) - 1; i++)
  {
    for (int j = 0; j <= (sizeof(Default[0]) / sizeof(Default[0][0])) - 1; j++)
    {
      queue[i][j] = Default[i][j];
    }
  }
}

//--------------------------------------------------------------------------------------------------

void Circle()
{
  int td = 500;
  float Circle[][7] = {{5, 0, 15, 90, 90, 90, td},
    {5.94, -2.92, 14.05, 90, 90, 90, td},
    {8.42, -4.74, 11.57, 90, 90, 90, td},
    {11.49, -4.77, 8.50, 90, 90, 90, td},
    {14, -3, 6, 90, 90, 90, td},
    {15, -0.08, 5, 90, 90, 90, td},
    {14.10, 2.85, 5.89, 90, 90, 90, td},
    {11.65, 4.71, 8.34, 90, 90, 90, td},
    {8.58, 4.79, 11.41, 90, 90, 90, td},
    {6.04, 3.05, 13.95, 90, 90, 90, td},
    {5, 0.16, 15, 90, 90, 90, td},
    {5, 0.01, 15, 90, 90, 90, td}
  };
  for ( int i = 0; i <= (sizeof(Circle) / sizeof(Circle[0])) - 1; i++)
  {
    for (int j = 0; j <= (sizeof(Circle[0]) / sizeof(Circle[0][0])) - 1; j++)
    {
      queue[i][j] = Circle[i][j];
    }
  }
}

//--------------------------------------------------------------------------------------------------

void HorseShoe()
{
  int td = 800;
  float HorseShoe[][7] = {{7.84318319772311, 3.11229278755168, 11.487305509109, 90, 90, 90, td},
    {10.9765187043221, 3.99412536215932, 13.7832914598922, 90, 90, 90, td},
    {8.66458734618857, 3.36588393923158, 16.1612092234725, 90, 90, 90, td},
    {4.07324452450471, 1.46509011634419, 17.7220304876492, 90, 90, 90, td},
    {3.4896697524385, -0.989615837018091, 17.8756496868425, 90, 90, 90, td},
    {7.71298422259796, -3.0701740089441, 16.5639874326533, 90, 90, 90, td},
    {10.9599699864017, -3.98997994641621, 14.2829488066708, 90, 90, 90, td},
    {8.78434995965517, -3.4012791592738, 11.8949346611827, 90, 90, 90, td},
    {7.84318319772311, -3.11229278755168, 11.487305509109, 90, 90, 90, td}
  };
  for ( int i = 0; i <= (sizeof(HorseShoe) / sizeof(HorseShoe[0])) - 1; i++)
  {
    for (int j = 0; j <= (sizeof(HorseShoe[0]) / sizeof(HorseShoe[0][0])) - 1; j++)
    {
      queue[i][j] = HorseShoe[i][j];
    }
  }
}



//--------------------------------------------------------------------------------------------------

void Throw()
{
  float Throw[][7] = {{10, 0, 15, 0, 90, 45, 1000},
    {10, 0, 15, 0, 90, 45, 1000},
    {10, 0, 15, 0, 90, 90, 1000},
    { -5, 0, 18, 115, 90, 90, 2000},
    { -5, 0, 18, 115, 90, 90, 1000},
    {0.1, 0, 19, 80, 90, 76, 150},
    {0.1, 0, 19, 80, 90, 76, 1000},
    {0.1, 0, 19, 102.19, 90, 0, 500},
    {0.1, 0, 14, 138.95, 45, 0, 500},
    {0.1, 0, 19, 102.19, 90, 0, 500},
    {0.1, 0, 14, 138.95, 135, 0, 500}
  };
  for ( int i = 0; i <= (sizeof(Throw) / sizeof(Throw[0])) - 1; i++)
  {
    for (int j = 0; j <= (sizeof(Throw[0]) / sizeof(Throw[0][0])) - 1; j++)
    {
      queue[i][j] = Throw[i][j];
    }
  }
}

//--------------------------------------------------------------------------------------------------

void UserMadeFunction_1()
{
  float UserMadeFunction_1[][7] = {{}
  };
  for ( int i = 0; i <= (sizeof(UserMadeFunction_1) / sizeof(UserMadeFunction_1[0])) - 1; i++)
  {
    for (int j = 0; j <= (sizeof(UserMadeFunction_1[0]) / sizeof(UserMadeFunction_1[0][0])) - 1; j++)
    {
      queue[i][j] = UserMadeFunction_1[i][j];
    }
  }
}
