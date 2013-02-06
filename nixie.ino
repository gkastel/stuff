#include <SoftwareSerial.h>
#include <stdio.h>

SoftwareSerial mySerial(2, 3, true); // RX, TX

void setup()  
{
  //Serial.begin(9600);
  //Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void stupidanim()
{

  char buf[11] ;
  for (int k=0; k < 10; k++)
  {
    for (int j=10; j >= 0; j--)
    {
      if (k == j+1 || k==j) buf[j] = '1';
      else buf[j]  = ' ';
    }
    for (int i =0; i < 10; i++)
      mySerial.write(buf[i]);
    delay(100);
  }
}

void outTemp(float temp)
{
  //mySerial.write("        ");
  char buf[100];
  sprintf(buf, " %d         ", temp);
  buf[2] = ' ';
  for (int i =0; i < 10; i++)
    mySerial.write(buf[i]);
}

void loop() // run over and over
{
  //Serial.println("loop");
  stupidanim();
  mySerial.write('t');
  delay(10000);
  stupidanim();
  mySerial.write('d');
  delay(3000);
  stupidanim();
  float val = (analogRead(1)*0.004882814 - 0.5)*100;
  outTemp(val);
  delay(3000);

}


