#include "VarSpeedServo.h"  
#define S0 5
#define S1 6
#define S2 7
#define S3 13
#define sensorOut 14
VarSpeedServo RU;  //Destra in alto
VarSpeedServo RL;  //Destra in basso
VarSpeedServo LU;  //Sinistra in alto
VarSpeedServo LL;  //Sinistra in basso
unsigned long r, g, b;

                                                      
const int vel = 20, vel_Back = 10;                   
const int delay_Forward = 750; 
int vel_Applause = 40, delay_Applause = 400;
int vel_Dance1 = 30,    vel_Dance2 = 25,    vel_Dance3 = 40;     
int delay_Dance1 = 300, delay_Dance2 = 750, delay_Dance3 = 200;                                      
const int array_cal[4] = {90,90,90,90}; 
int RU_Degree = 0, LU_Degree = array_cal[2] + 5;

const int num1 = 6;
const int array_forward[num1][4] =  
{
    {0,-40,0,-20},        
    {30,-40,30,-20},
    {30,0,30,0},
    {0,20,0,40},
    {-30,20,-30,40},
    {-30,0,-30,0},
};




const int num_Applause = 20;     
const int array_Applause[num_Applause][4] =
{       
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},    
    {0,-50,0,50},
    {0,0,0,0},
    
};

const int num_dance1 = 10;
const int array_dance1[num_dance1][4] =
{ 

    {0,-20,0,0},  
    {0,-40,0,20},
    {0,-20,0,40},
    {0,0,0,20},
    {0,0,0,0},
    
    {0,0,0,20},  
    {0,-20,0,40},
    {0,-40,0,20},
    {0,-20,0,0},
    {0,0,0,0}, 
};

const int num_dance2 = 32;
const int array_dance2[num_dance2][4] =
{ 

    {20,0,40,0},
    {20,-30,40,-30}, 
    {20,-30,10,-30},
    {20,-30,40,-30}, 
    {20,-30,10,-30},

    {20,-30,40,-30}, 
    {20,0,40,-30},
    {20,80,40,-30},
    {20,0,40,-30},
    {20,-80,40,-30},        
    {20,0,40,-30},
    {20,80,40,-30},
    {20,0,40,-30},
    {20,-30,40,-30},    
    {20,0,40,0},
    {0,0,0,0}, 
     
    {-40,0,-20,0},
    {-40,40,-20,30}, 
    {-20,40,-20,30}, 
    {-40,40,-20,30}, 
    {-20,40,-20,30}, 

    {-40,40,-20,30}, 
    {-40,40,-20,0},
    {-40,40,-20,-80},
    {-40,40,-20,0},
    {-40,40,-20,80},        
    {-40,40,-20,0},
    {-40,40,-20,-80},
    {-40,40,-20,0},
    {-40,40,-20,30},    
    {-40,0,-20,0},
    {0,0,0,0},
};

const int num_dance3 = 8;        //split step
const int array_dance3[num_dance3][4] =
{ 
    {0,-40,0,0},
    {20,-30,20,20},
    {40,0,40,30},   
    {0,0,0,40},
    {-20,-20,-20,30},
    {-40,-30,-40,0},

    {0,-40,0,0},
    {0,0,0,0},
};

#define RUN

void Servo_Init()
{
    RU.attach(9);   // Connessione dei motori ai pin 9,10,11,12
    RL.attach(10);   
    LU.attach(11);   
    LL.attach(12);    
}

void Adjust()                            // porta alla posizione di riposo
{                                        
    for(RU_Degree = array_cal[0] - 5; RU_Degree <= array_cal[0]; RU_Degree += 1) {
        RU.write(RU_Degree);             // A passi di un grado
        LU.write(LU_Degree--);                  
        delay(15);
    }                     
}


void Forward()
{
    for(int x=0; x<num1; x++) {                    
        RU.slowmove (array_cal[0] + array_forward[x][0] , vel);    
        RL.slowmove (array_cal[1] + array_forward[x][1] , vel);
        LU.slowmove (array_cal[2] + array_forward[x][2] , vel);
        LL.slowmove (array_cal[3] + array_forward[x][3] , vel);
        delay(delay_Forward);
    }
}

void Applause()
{  
    for(int z=0; z<Applause; z++) {
       if ( z > 17) {
            vel_Applause = 10;
            delay_Applause = 1500;
            }
       else {
            vel_Applause = 40;
            delay_Applause = 400;
           }
                 
        RU.slowmove (array_cal[0] + array_Applause[z][0] , vel_Applause);   
        RL.slowmove (array_cal[1] + array_Applause[z][1] , vel_Applause);
        LU.slowmove (array_cal[2] + array_Applause[z][2] , vel_Applause);
        LL.slowmove (array_cal[3] + array_Applause[z][3] , vel_Applause);
        delay(delay_Applause); 
    } 
}


void Slide_2_Left(int times)
{
    for(int time1 = 0; time1 < times; time1++) { 
        for(int z=0; z<5; z++) {                     
            RU.slowmove (array_cal[0] + array_dance1[z][0] , vel_Dance1);   
            RL.slowmove (array_cal[1] + array_dance1[z][1] , vel_Dance1);
            LU.slowmove (array_cal[2] + array_dance1[z][2] , vel_Dance1);
            LL.slowmove (array_cal[3] + array_dance1[z][3] , vel_Dance1);
            delay(delay_Dance1); 
        } 
    }
}

void Slide_2_Right(int times)
{
    for(int time1 = 0; time1 < times; time1++) {
        for(int z=5; z<10; z++) {                     
            RU.slowmove (array_cal[0] + array_dance1[z][0] , vel_Dance1);   
            RL.slowmove (array_cal[1] + array_dance1[z][1] , vel_Dance1);
            LU.slowmove (array_cal[2] + array_dance1[z][2] , vel_Dance1);
            LL.slowmove (array_cal[3] + array_dance1[z][3] , vel_Dance1);
            delay(delay_Dance1); 
        }   
    }
}

void Left_Foot_Support()
{
    for(int z=0; z<16; z++) { //z<12
        if ( z > 5 && z < 14) {   //z(1,10)
            vel_Dance2 = 50;
            delay_Dance2 = 200;
        }
        else { 
        vel_Dance2 = 25; 
        delay_Dance2 = 750;
        }
                    
        RU.slowmove (array_cal[0] + array_dance2[z][0] , vel_Dance2);   
        RL.slowmove (array_cal[1] + array_dance2[z][1] , vel_Dance2);
        LU.slowmove (array_cal[2] + array_dance2[z][2] , vel_Dance2);
        LL.slowmove (array_cal[3] + array_dance2[z][3] , vel_Dance2);
        delay(delay_Dance2); 
    }
}

void Right_Foot_Support()
{
    for(int z=16; z<32; z++) { //z<24
        if ( z > 21 && z < 30) {   //z(13,22)
            vel_Dance2 = 50;
            delay_Dance2 = 200;
        }
        else { 
        vel_Dance2 = 25; 
        delay_Dance2 = 750;
        }
                    
        RU.slowmove (array_cal[0] + array_dance2[z][0] , vel_Dance2);   
        RL.slowmove (array_cal[1] + array_dance2[z][1] , vel_Dance2);
        LU.slowmove (array_cal[2] + array_dance2[z][2] , vel_Dance2);
        LL.slowmove (array_cal[3] + array_dance2[z][3] , vel_Dance2);
        delay(delay_Dance2); 
    }
}

void Dancing1_2()
{
    Slide_2_Left(2);
    Left_Foot_Support();
    
    Slide_2_Right(2);
    Right_Foot_Support();
}

void Dancing3(int Times = 1, int Vel = 40, int Delay = 250, int low = 0, int high = 0)
{   
    for(int time3 = 0; time3 < Times; time3++) {
        for(int z=0; z<6; z++) {
            if ( time3 > 1 && time3 < 4) {
            vel_Dance3 = Vel;
            delay_Dance3 = Delay;
            }
            else { 
            vel_Dance3 = 40; 
            delay_Dance3 = 200;
            }                     
            
            RU.slowmove (array_cal[0] + array_dance3[z][0] , vel_Dance3);   
            RL.slowmove (array_cal[1] + array_dance3[z][1] , vel_Dance3);
            LU.slowmove (array_cal[2] + array_dance3[z][2] , vel_Dance3);
            LL.slowmove (array_cal[3] + array_dance3[z][3] , vel_Dance3);
            delay(delay_Dance3); 
        } 
    }
    for(int z=6; z<8; z++) {                     
            RU.slowmove (array_cal[0] + array_dance3[z][0] , vel_Dance3);   
            RL.slowmove (array_cal[1] + array_dance3[z][1] , vel_Dance3);
            LU.slowmove (array_cal[2] + array_dance3[z][2] , vel_Dance3);
            LL.slowmove (array_cal[3] + array_dance3[z][3] , vel_Dance3);
            delay(delay_Dance3); 
        } 
}            
    
 

void setup()  
{
#ifdef INSTALL
    Servo_Init();
  
    RU.slowmove (90 , vel);
    RL.slowmove (90 , vel);
    LU.slowmove (90 , vel);
    LL.slowmove (90 , vel);
    while(1);
#endif

#ifdef CALIBRATION 
    Servo_Init();  
    Adjust();
    
    RL.slowmove (array_cal[1] , vel);
    LL.slowmove (array_cal[3] , vel);
    delay(2000);
    while(1);
#endif

#ifdef RUN 
    Servo_Init();
    Adjust(); 
       
    RL.slowmove (array_cal[1] , vel);
    LL.slowmove (array_cal[3] , vel);
    delay(2000);
#endif
  Serial.begin(9600);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH);
  digitalWrite(S1, HIGH);
}

void loop()
{ 
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  r = pulseIn(sensorOut, LOW);
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  g = pulseIn(sensorOut, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  b = pulseIn(sensorOut, LOW);
        Serial.print("R=");
  Serial.print(r);
  Serial.print("\tG=");
  Serial.print(g);
  Serial.print("\tB=");
  Serial.println(b);
  delay(700);
  
   if ((r>=20 && r<40) && (g>=15 && g<=30) && (b>=80 && b<= 130)){
        Forward();
     //rosso
   }
   else if ( (r>=40 && r<=165)  && (g>20 && g<=30) && (b>=50 && b<= 120) ){
      Applause();
      //blu
   }
  else if ( (r>=40 && r<=165) && (g<=20) && (b>=80 && b<=120)) {
     Dancing1_2();
     delay(500);    
     Dancing3(5,20,400);
     delay(500);
     //verde
  }
  else{
    Servo_Init();
    }
}     
