/*
 * This header file should be used in conjunction with the 3D_Space_w_Robot_Hand_Asynch_Movement.ino file.
 */

float queue[20][7] = {};

//--------------------------------------------------------------------------------------------------

void Sad()
{
  float Sad[][7] = {{2.1,15.1,0,0,90,90,500},
                    {2.1,15.1,0,0,45,90,500},
                    {2.1,15.1,0,0,90,90,500},
                    {2.1,15.1,0,0,135,90,500}};
  for( int i = 0; i<= (sizeof(Sad)/sizeof(Sad[0]))-1; i++)
  {
    for (int j = 0; j <= (sizeof(Sad[0])/sizeof(Sad[0][0]))-1; j++)
    {
      queue[i][j] = Sad[i][j];
    }
  }  
}

//--------------------------------------------------------------------------------------------------

void Excited()
{
  float Excited[][7] = {{0.1,19,0,102.19,90,0,500},
                        {0.1,14,0,138.95,45,0,500},
                        {0.1,19,0,102.19,90,0,500},
                        {0.1,14,0,138.95,135,0,500}};
  for( int i = 0; i<= (sizeof(Excited)/sizeof(Excited[0]))-1; i++)
  {
    for (int j = 0; j <= (sizeof(Excited[0])/sizeof(Excited[0][0]))-1; j++)
    {
      queue[i][j] = Excited[i][j];
    }
  }  
}

//--------------------------------------------------------------------------------------------------

void Default()
{
  float Default[][7] = {{0.1,19,0,102.19,90,90,1000}};
  for( int i = 0; i<= (sizeof(Default)/sizeof(Default[0]))-1; i++)
  {
    for (int j = 0; j <= (sizeof(Default[0])/sizeof(Default[0][0]))-1; j++)
    {
      queue[i][j] = Default[i][j];
    }
  }   
}

//--------------------------------------------------------------------------------------------------

void Circle()
{

 int td =500;
   
 float Circle[][7] = {{5,15,0,90,90,90,td},
{5.94518440247391,14.054815597526,2.92548636470231,90,90,90,td},
{8.42338818802365,11.5766118119763,4.74492309677793,90,90,90,td},
{11.4976675309478,8.50233246905213,4.77042890804846,90,90,90,td},
{14.0057180777346,5.99428192226533,2.99236072051978,90,90,90,td},
{14.9993117254084,5.00068827459156,0.0829594611467395,90,90,90,td},
{14.1027967866978,5.89720321330219,-2.85780659371171,90,90,90,td},
{11.6551220362644,8.34487796373556,-4.71811096150481,90,90,90,td},
{8.58168907268386,11.4183109273161,-4.79462137331569,90,90,90,td},
{6.0444822556463,13.9555177443536,-3.05841124999615,90,90,90,td},
{5.0027529088775,14.9972470911224,-0.165896082737784,90,90,90,td},
{5.00002536543312,14.9999746345668,-0.0159265089656899,90,90,90,td}};
  for( int i = 0; i<= (sizeof(Circle)/sizeof(Circle[0]))-1; i++)
  {
    for (int j = 0; j <= (sizeof(Circle[0])/sizeof(Circle[0][0]))-1; j++)
    {
      queue[i][j] = Circle[i][j];
    }
  }  
}

//--------------------------------------------------------------------------------------------------

void HorseShoe()
{

 int td = 300;
   
 float HorseShoe[][7] = {{7.84318319772311,11.487305509109,-3.11229278755168,90,90,90,td},
{10.9765187043221,13.7832914598922,-3.99412536215932,90,90,90,td},
{8.66458734618857,16.1612092234725,-3.36588393923158,90,90,90,td},
{4.07324452450471,17.7220304876492,-1.46509011634419,90,90,90,td},
{3.4896697524385,17.8756496868425,0.989615837018091,90,90,90,td},
{7.71298422259796,16.5639874326533,3.0701740089441,90,90,90,td},
{10.9599699864017,14.2829488066708,3.98997994641621,90,90,90,td},
{8.78434995965517,11.8949346611827,3.4012791592738,90,90,90,td},
{7.84318319772311,11.487305509109,3.11229278755168,90,90,90,td}};
  for( int i = 0; i<= (sizeof(HorseShoe)/sizeof(HorseShoe[0]))-1; i++)
  {
    for (int j = 0; j <= (sizeof(HorseShoe[0])/sizeof(HorseShoe[0][0]))-1; j++)
    {
      queue[i][j] = HorseShoe[i][j];
    }
  }  
}