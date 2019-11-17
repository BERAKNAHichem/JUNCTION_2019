#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
char auth[] = "defzqHBlVD7ux94_NiZh5QIVga_zzHMt";   

const char* ssid     = "aalto open";
const char* pass = "";
BlynkTimer timer; 

int space[23] ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int checkIn=D5;

int s=0;
char in;
float number;

int checkinLED=D7;
int checkoutLED=D0;
int led1=D6;
int pos1=D1;
int pos2=D2;
int pos3=D3;
int pos4=D4;
int chrono;

void myTimerEvent(){
    int lightValue = getLightValue();
    Blynk.virtualWrite(V5, lightValue);
    }

  int getLightValue(){
    int sensorValue = analogRead(A0);
    Serial.println(sensorValue);
    return sensorValue;
}

void sendData(int data) {
    if(WiFi.status() != WL_CONNECTED ){
    Serial.println("Wifi not connected...");
    WiFi.begin(ssid, pass); 
  } 
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to: "); Serial.println(WiFi.SSID());
  Serial.print("Your IP: "); Serial.println(WiFi.localIP());
  
  HTTPClient http;
  

  String datatosend = "/light/setdata.php?value=" + String(data);
  //String datatosend2= "/light/setdata2.php?status=" + stat(data);
  Serial.print("Sensor value: "); Serial.println(datatosend);

  http.begin("10.100.30.99", 8080, datatosend);
 
  int httpCode = http.GET();
  
  if(httpCode > 0){
    Serial.printf("GET code: %d\n", httpCode);
    if(httpCode == HTTP_CODE_OK){
      String response = http.getString();
      Serial.println(response);
    }
  } else {
    Serial.printf("GET code: %d\n", httpCode);
    Serial.printf("GET failed: error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}

String stat(int val){
   String statuss;
   if (val<=50){
    statuss="LOW Light";
    return statuss;
   }
   else if (val>50 && val<=200){
    statuss="MEDIUM Light";
    return statuss;
   }
   else if (val>200 && val<=1024){
    statuss="HIGH Light";
    return statuss;
   }
   else{
    Serial.print("ERROR");
   }
   
}


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  pinMode(checkIn,OUTPUT);
  pinMode(checkinLED,OUTPUT);
  pinMode(checkoutLED,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(pos1,OUTPUT);
  pinMode(pos2,OUTPUT);
  pinMode(pos3,OUTPUT);
  pinMode(pos4,OUTPUT);  
}




void loop() {
  digitalWrite(checkinLED,LOW);
  digitalWrite(checkoutLED,LOW);
  
  Blynk.run();
  timer.run(); 
  int lightValue = getLightValue();
  sendData(lightValue);
  stat(lightValue);
  boolean value=digitalRead(checkIn);
  Serial.print(value);
  if(value==0){
    s=0;}
  if(value==1 && s==0){
    for(int i=1;i<23;i++){
      if (space[i]==0){
      //print RFID with ID "i"
      space[i]=1;
      s=1;
      number++;
      digitalWrite(led1,HIGH);
      digitalWrite(checkinLED,HIGH);
      switch (i) {
   case 1:{
     digitalWrite(led1,HIGH);
     digitalWrite(pos1,HIGH);
     digitalWrite(pos2,LOW);
     digitalWrite(pos3,HIGH);
     digitalWrite(pos4,LOW);
     break;}
   case 2:{
    digitalWrite(led1,HIGH);
     digitalWrite(pos1,LOW);
     digitalWrite(pos2,HIGH);
     digitalWrite(pos3,LOW);
     digitalWrite(pos4,HIGH);
     break;}
     case 3:{
      digitalWrite(led1,HIGH);
     digitalWrite(pos1,LOW);
     digitalWrite(pos2,LOW);
     digitalWrite(pos3,HIGH);
     digitalWrite(pos4,LOW);
     break;}
     case 4:{
      digitalWrite(led1,HIGH);
     digitalWrite(pos1,LOW);
     digitalWrite(pos2,LOW);
     digitalWrite(pos3,LOW);
     digitalWrite(pos4,HIGH);
     break;}
     
 }
 
      if (s==1)
      break;
        }
      }
    }
   while (Serial.available() > 0) {
      in = Serial.parseInt();
      Serial.println(in);
      space[in]=0;
      Serial.println(space[in]);
      number-=0.5;
      digitalWrite(checkoutLED,HIGH);
      
  
   }
   
    for(int i = 1 ; i<11;i++){
      Serial.print("  ");
     Serial.print(space[i]);
      Serial.print("  |");
    }
     Serial.print("  ");
      Serial.print(space[11]);
      Serial.println("  ");
    for(int i = 22 ; i>12;i--){
      Serial.print("  ");
     Serial.print(space[i]);
      Serial.print("  |");
    }
      Serial.print("  ");
      Serial.print(space[12]);
      Serial.println("  ");
      Serial.println("  ");
      Serial.println(number);
      chrono++;
      Serial.println(chrono);
      if (chrono==5){
     digitalWrite(led1,LOW);
     digitalWrite(pos1,LOW);
     digitalWrite(pos2,LOW);
     digitalWrite(pos3,LOW);
     digitalWrite(pos4,LOW);
        chrono=0;
      }
      
    
    }
