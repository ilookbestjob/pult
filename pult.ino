/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include <WiFiClient.h>
struct Button {
  String name;
  String description;
  byte pin;
  byte state; 
  String command;
} ;



struct InputDevice
{

  byte pin;
  char* description;
  byte type;
  byte controllertype;
  byte controlleradress;
  byte Inputstate = LOW;
  byte Inputprevstate = LOW;
  byte StateSounds[5];
  byte States = 0;
  byte StatesSpan = 2;
  byte InternalState = 0;
  byte State = 0;
  byte PrevState = -1;
  byte NextState = 1;
  long startTime = 0;
  bool enabled = true;
  word Date, Month, Year, Hour, Minute, Second;
};
InputDevice devices[15];


int pinscount=3;
int Pins[] = {0, 2, 3};


WiFiMulti WiFiMulti;


//////инициализация кнопок////////////////////

String BasicURL;


 Button Buttons[16];

 Button temp;


/*
Buttons[0].name="Кнопка 2";
Buttons[0].description="Каретка на позиции 10 метров";
Buttons[0].pin=2;

Buttons[0].name="Кнопка 3";
Buttons[0].description="Каретка на позиции 15 метров";
Buttons[0].pin=2;

Buttons[0].name="Кнопка 4";
Buttons[0].description="Каретка на позиции 20 метров";
Buttons[0].pin=2;

Buttons[0].name="Кнопка 5";
Buttons[0].description="Каретка на позиции 25 метров";
Buttons[0].pin=2;

Buttons[0].name="Кнопка 6";
Buttons[0].description="Каретка на позиции 30 метров";
Buttons[0].pin=2;

Buttons[0].name="Кнопка 7";
Buttons[0].description="Каретка на позиции 40 метров";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 8";
Buttons[0].description="Каретка на позиции 50 метров";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 9";
Buttons[0].description="Каретка на позиции 60 метров";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 10";
Buttons[0].description="Каретка на позиции 70 метров";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 11";
Buttons[0].description="Каретка на позиции 80 метров";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 12";
Buttons[0].description="Каретка на позиции 90 метров";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 13";
Buttons[0].description="Каретка на позиции 100 метров";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 14";
Buttons[0].description="Каретка на позиции 110 метров";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 15";
Buttons[0].description="Движение каретки вперед";
Buttons[0].pin=2;


Buttons[0].name="Кнопка 16";
Buttons[0].description="Движение каретки назад";*/
//Buttons[0].pin=2;

////////////////////////

int checkState(){
int res=0;
res=-1;

for (int t=1;t<=5;t++){
  pinMode(Pins[t],INPUT_PULLUP);
 res=digitalRead(t)?t:res;
  }
for (int t=12;t<=19;t++){
  pinMode(Pins[t],INPUT_PULLUP);
 res=digitalRead(t)?t:res;
  }
for (int t=21;t<=23;t++){
  pinMode(Pins[t],INPUT_PULLUP);
 res=digitalRead(t)?t:res;
  }
  for (int t=25;t<=27;t++){
  pinMode(Pins[t],INPUT_PULLUP);
 res=digitalRead(t)?t:res;
  }
for (int t=32;t<=33;t++){
  pinMode(Pins[t],INPUT_PULLUP);
 res=digitalRead(t)?t:res;
  }

  
  

  
  
return res;
  
}

void setup() {

  
temp.name="Кнопка 1";
temp.description="";
temp.pin=1;

Buttons[0]=temp;

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("aquarius", "Red11cat42");
   Serial.println("connected");
}

void loop() {
  // wait for WiFi connection
  Serial.println(WiFiMulti.run());
  Serial.println(WL_CONNECTED);
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {
  
     Get( checkState());
    

 
  }

 
}

void Get(int s){
   WiFiClient client;

    HTTPClient http;

       Serial.println("=====================================");
      Serial.println("http://192.168.0.7/pult/index.php?on=");  
  Serial.println("http://192.168.0.7/pult/index.php?on="+String(s));
   Serial.println("=====================================");
    if (http.begin(client, "http://192.168.0.7/pult/index.php?on="+String(s))) {  // HTTP
   
      int httpCode = http.GET();

    
      if (httpCode > 0) {
    
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  
}

//пин 1–5, 12–19, 21–23, 25–27, 32 и 33
