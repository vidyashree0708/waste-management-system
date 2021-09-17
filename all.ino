#include <Servo.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
#include <SoftwareSerial.h>
#include<Wire.h>
Adafruit_SSD1306 display(OLED_RESET);
#include <TinyGPS++.h>
Servo myservo;  
SoftwareSerial mySerial(3, 4);

int pos = 0;
int i;  
const int trigPin1 = 6;
const int echoPin1 = 7;
const  int trigPin2=8;                       //connect RX to pin 4 , connect TX to pin 3
const int  echoPin2=9;
float  distance2,distance1, duration2,duration1;

void setup() 

{
  {
  myservo.attach(5);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT); 
  myservo.write(pos);
  }
  {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600); 
  pinMode(trigPin2, OUTPUT); //define ultrasonic tri pin as output pin 
  pinMode(echoPin2, INPUT);  //define ultrasonic echo as input pin
  delay(100);
  for(i=11;i<=13;i++){
    pinMode(i,OUTPUT);
  }
  }
}
void loop() 
{
  //Serial.begin(9600);
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = 0.034*(duration1/2);
  //Serial.println(distance1);
  if (distance1 <=27)
  {
    myservo.write(pos+180);
    delay(1000);
  }
  else 
  {
      myservo.write(pos);
  }
  delay(300);

   digitalWrite(trigPin2, HIGH); 
    digitalWrite(trigPin2, LOW);
    duration2 = pulseIn(echoPin2, HIGH);
    distance2 =0.034*(duration2/2);
    display.setTextSize(2);
    display.setTextColor(WHITE);
   
    
     if(distance2<=20)
    {
      digitalWrite(13,HIGH);
      display.setCursor(0,0);
   display.println("LOW"); 
    display.display();
     display.clearDisplay();  
    } else {
      digitalWrite(13,LOW);
    }

      if(distance2<=12)
    {
      digitalWrite(12,HIGH);
      display.setCursor(0,0);
   display.println("MEDIUM ");
   display.display(); 
    display.clearDisplay();   
    } else {
      digitalWrite(12,LOW);
    }
     if(distance2<=7)
    {
   
      digitalWrite(11,HIGH);
      display.setCursor(0,0);
   display.println("FULL "); 
   display.display(); 
    display.clearDisplay(); 
      Serial.println("object detected \n");
        Serial.print("distance= ");              
        Serial.print(distance2);    

           // code for send SMS

  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91XXXXXXXXXX\"\r");
 // Replace x with your mobile number(not the number which insert in to gsm module)
  delay(1000);
  mySerial.println("ALERT BIN IS FULL!!!! ");
  delay(100);
    mySerial.print("Latitude :");
     mySerial.println(gps.location.lat(),6);
       mySerial.print("Longitude:");
      mySerial.println(gps.location.lng(),6);
      delay(1000);
         mySerial.print("https://www.google.com/maps/?q=");
 mySerial.print(gps.location.lat(),6);
      mySerial.print(",");
    mySerial.print(gps.location.lng(),6);
       delay(1000);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(10000);
    }else {
    
      digitalWrite(11,LOW); 
       Serial.println("no object detected");
        Serial.print("distance= ");              
        Serial.print(distance2);
          delay(1000);
}
 
}
