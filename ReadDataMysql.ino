
/*
 Create Omkabel 03 oktober 2019
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>
#include <fonts/Arial_Black_16.h>


const int WIDTH = 6;
const uint8_t *FONT = Arial_Black_16;

SPIDMD dmd(WIDTH,4);  
DMD_TextBox box(dmd);  
 
const char* ssid = "CariscoVariasi";
const char* password = "kacafilm";
String url = "http://192.168.1.12/Led2019/getdata.php?id_panel=2";
String text ="DISHUB KOTA BANDAR LAMPUNG 2019   ";


void setup () {
    
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  delay(1000);
  wifiConnecting();

  dmd.setBrightness(255);
  dmd.selectFont(FONT);
  dmd.begin();
}
 
void loop() {
 
  wifi();  
}


void wifi(){
  
  if (WiFi.status() == WL_CONNECTED) {    
  get_data();
  }else
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("NodeMCU tidak terhubung ke WIFI");
//    teks_tambahan ();
    wifiConnecting();
  }
  delay(5000);
  }

void wifiConnecting(){
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Menghubungkan Ke WIFI");
//    teks_tambahan ();
    for(int c=0;c<3;c++){
      Serial.print(" .");
      delay(1000);  
    }
    Serial.println();
  }

}

void get_data(){
    HTTPClient http;  
    http.begin(url);  
    int httpCode = http.GET();                                                       
    if (httpCode > 0) { 
      String payload = http.getString();
      Serial.println("HTTP Response Code : ");
      Serial.println(httpCode);
      Serial.println("HTTP Response Payload : ");
      Serial.println(payload);
      delay(2000);
   String next = payload;
   while(next) {
    Serial.print(next);
    box.print(next);
    delay(5000);

    Serial.println("Persiapan Reset");
    delay(5000);
    restart_esp();
  }  
   http.end();
        
    }
    
    }


void restart_esp(){
  int i;
  for(i=0;i<10;i++)
  {
    if(i==6)
    {
      Serial.println("Resetting");
      ESP.restart(); 
    }
  }
  }

   void teks_tambahan (){
    while(text) {
    Serial.print(text);
    box.print(text);
    delay(20);
   }
   }   
    
