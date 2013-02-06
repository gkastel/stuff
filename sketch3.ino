#include <math.h>

// Random slowly blinking led lights, controlled with an arduino and a 75HC595 shift register


void randomsines() 
{
    int pins[] = {3, 5, 6, 9, 10, -1};
    float speeds[5];

    for (int i =0; i < 5; i++)
       speeds[i] = 0.3+ float(random(0, 1000))/1000.0;

    for (float x =0.; x < 100.; x+=1.0)
    {
      for (int i=0; i < 5; i++)
      {
        float v = (1.0 +sin( x*speeds[i]/3.14159))/2.0;
        v = 255.0*(v*v);

        analogWrite(pins[i], v);

      }
      delay(50);
    }

}


int SER_Pin = 8;   //pin 14 on the 75HC595
int RCLK_Pin = 9;  //pin 12 on the 75HC595
int SRCLK_Pin = 10; //pin 11 on the 75HC595

//How many of the shift registers - change this
#define number_of_74hc595s 1 

//do not touch
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];

void setup(){
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);

  //reset all register pins
  clearRegisters();
  writeRegisters();

 // Serial.begin(9600);

}               

//set all register pins to LOW
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  }
} 

//Set and display registers
//Only call AFTER all values are set how you would like (slow otherwise)
void writeRegisters(){

  digitalWrite(RCLK_Pin, LOW);

  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(SRCLK_Pin, LOW);
    digitalWrite(SER_Pin, registers[i]);
    digitalWrite(SRCLK_Pin, HIGH);

  }
  digitalWrite(RCLK_Pin, HIGH);

}

//set an individual pin HIGH or LOW
void setRegisterPin(int index, int value){
  registers[index] = value;
}


int lastwait =0;
float speeds[8]  = {.71, .72, .73, .74, .75, .76, .77, .78};
float phases[8]  = {8, 1, 7, 3, 9, 2, 5 , 4};
int  levels[8]  = {50, 50, 50, 50, 50, 50, 50, 50};
int counters[8] = {1,2,3,4,5,6,7,8};



void loop()
{

  float lspeed = 1.0;
  int distl = 200.;
  int bpoint = 100.0;



  for (float k =0; k < 50000; k+=1.0)
  {
      if ( k > bpoint   )
      {
          //distl = analogRead(0);
          if (distl >30)
          {
             lspeed = float(distl)/ 600.;
             for (int j=0; j < 8; j++)
               speeds[j] = 4.0*lspeed + float(j)/20.;
          }

          bpoint += 99;
      }

      float kk = k/30.;
      for (int j =0; j < 8 ; j++)  
      {
        float v = (sin( speeds[j]*kk));
        levels[j]  =32.0*v*v;
      }
    

    for (int r =0 ; r < 2; r++)
      for (int i =0; i<32; i++)
      {
          for (int j =0; j < 8 ; j++)  
          {
            registers[j] =  levels[j] < i ? HIGH : LOW;
          }
          writeRegisters();  //MUST BE CALLED TO DISPLAY CHANGES
          //delay(wait);
      }
    
  }
  


  delay(1000);

}

