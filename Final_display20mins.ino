#include "Adafruit_GFX.h"    // Core graphics library
#include "MCUFRIEND_kbv.h"   // Hardware-specific library
MCUFRIEND_kbv tft;

#include <dht.h>
const int buzzer = 53; //buzzer to arduino pin 9

#define dht_apin A9 // Analog Pin sensor is connected to
 
dht DHT;
#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410
//#include "images.h"
#include "Fonts/FreeSans9pt7b.h"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSerif12pt7b.h"
#include "FreeDefaultFonts.h"
int a = 300;
int b = 400;
int j, j2;
int i, i2;
int time;
#define PI 3.1415926535897932384626433832795
int col[8];
long starttime=0, endtime;

// a function to calculate water loss using the concept of heat index
float f(float c, float rh){
  float we,wl,f, hi,loss;
  
  we=60;
    wl=0.6*we; // net water content

    
    f=((9/5)*c+32); //tempreture conversion
    hi=0.5*(f+61+((f-68)*1.2)+(rh*0.094));
    hi=(hi-32)*5/9;
   loss=0;
    if(hi<10)
        loss=0.0015*wl;
    else if(hi>=10 and hi<15)
        loss=0.002*wl;
    else if(hi<20 and hi>=15)
        loss=0.003*wl;

        
    else if(hi>=20 and hi<=25)
        loss=0.005*wl;
   else if(hi<=30 and hi>25)
        loss=0.0075*wl;
   else if(hi>30 and hi<=35)
       loss=0.01*wl;
    else if(hi>35 and hi<=40)
        loss=0.0125*wl;
    else if(hi>40 and hi<=45)
        loss=0.015*wl;
    else if(hi>45 and hi<=50)
        loss=0.0175*wl;
   else if(hi>50)
        loss=0.02*wl;

   
return loss;
}


void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
   int16_t x1, y1;
   uint16_t wid, ht;
 // tft.drawFastHLine(0, y, tft.width(), 0xffff);
   tft.setFont(f);
   tft.setCursor(x, y);
   tft.setTextColor(WHITE);
   tft.setTextSize(sz);
   tft.print(msg);
   //delay(1000);
}
void showmsgXY(int x, int y, int sz, const GFXfont *f, int msg)
{
   int16_t x1, y1;
   uint16_t wid, ht;
 // tft.drawFastHLine(0, y, tft.width(), 0xffff);
   tft.setFont(f);
   tft.setCursor(x, y);
   tft.setTextColor(WHITE);
   tft.setTextSize(sz);
   tft.print(msg);
   //delay(1000);
}
void showmsgXY(int x, int y, int sz, const GFXfont *f, float msg)
{
   int16_t x1, y1;
   uint16_t wid, ht;
 // tft.drawFastHLine(0, y, tft.width(), 0xffff);
   tft.setFont(f);
   tft.setCursor(x, y);
   tft.setTextColor(WHITE);
   tft.setTextSize(sz);
   tft.print(msg);
   //delay(1000);
}
void setup()
{   time = 20;
  tft.reset();
Serial.begin(9600);
uint16_t ID = tft.readID();
tft.begin(ID);
tft.setRotation(1);
tft.invertDisplay(true);
tft.fillScreen(0xffff);
 tft.setTextColor(BLACK);
 tft.setCursor(100, 200);
 tft.setTextSize(2);
 tft.print("Loading...");
//showmsgXY(100, 200, 2, &FreeSans9pt7b, "Loading...");
col[0] = tft.color565(155, 0, 50);
col[1] = tft.color565(170, 30, 80);
col[2] = tft.color565(195, 60, 110);
col[3] = tft.color565(215, 90, 140);
col[4] = tft.color565(230, 120, 170);
col[5] = tft.color565(250, 150, 200);
col[6] = tft.color565(255, 180, 220);
col[7] = tft.color565(255, 210, 240);

pinMode(buzzer, OUTPUT);

endtime = 5000;
while (( starttime) <=5000)
{
  starttime = millis();
for (int i = 8; i > 0; i--) {
tft.fillCircle(160 + 40 * (cos(-i * PI / 4)), 100 + 40 * (sin(-i * PI / 4)), 10, col[0]); delay(15);
tft.fillCircle(160 + 40 * (cos(-(i + 1)*PI / 4)), 100 + 40 * (sin(-(i + 1)*PI / 4)), 10, col[1]); delay(15);
tft.fillCircle(160 + 40 * (cos(-(i + 2)*PI / 4)), 100 + 40 * (sin(-(i + 2)*PI / 4)), 10, col[2]); delay(15);
tft.fillCircle(160 + 40 * (cos(-(i + 3)*PI / 4)), 100 + 40 * (sin(-(i + 3)*PI / 4)), 10, col[3]); delay(15);
tft.fillCircle(160 + 40 * (cos(-(i + 4)*PI / 4)), 100 + 40 * (sin(-(i + 4)*PI / 4)), 10, col[4]); delay(15);
tft.fillCircle(160 + 40 * (cos(-(i + 5)*PI / 4)), 100 + 40 * (sin(-(i + 5)*PI / 4)), 10, col[5]); delay(15);
tft.fillCircle(160 + 40 * (cos(-(i + 6)*PI / 4)), 100 + 40 * (sin(-(i + 6)*PI / 4)), 10, col[6]); delay(15);
tft.fillCircle(160 + 40 * (cos(-(i + 7)*PI / 4)), 100 + 40 * (sin(-(i + 7)*PI / 4)), 10, col[7]); delay(15);
}}


}
int as;
void loop(void)
{
  DHT.read11(dht_apin);

      Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    as = 0;
    if ( time <= 0){
      //tft.reset();
       tft.fillScreen(BLACK);
      showmsgXY(60, 60, 2, &FreeSans12pt7b, "TIME FOR");
      showmsgXY(80, 120, 2, &FreeSans12pt7b, "WATER" );
      showmsgXY(60, 180, 2, &FreeSans12pt7b, " BREAK");
        showmsgXY(20, 220, 1, &FreeSans12pt7b, "You should drink ");
   showmsgXY(200, 220, 1, &FreeSans12pt7b, f(DHT.temperature,DHT.humidity));
    showmsgXY(240, 220, 1, &FreeSans12pt7b, " lit/hour");
     
      while(as<5  )
      {
          tone(buzzer, 2000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(buzzer);     // Stop sound...
  delay(1000);        // ...for 1sec
      
      as++;
      }
      time=20;
      }
 //tft.invertDisplay(true);
 tft.fillScreen(BLACK);

 //tft.setTextSize(2);
 tft.setTextColor(0xffff);
 tft.setCursor(28, 61);
// tft.print("20:45"); 
  // tft.setTextSize(2);
 tft.setTextColor(0xffff);
 showmsgXY(30, 30, 1.9, &FreeSans12pt7b, "T-27   HYDRATION");
 showmsgXY(30, 70, 1.9, &FreeSans12pt7b, "COMPANION");
 showmsgXY(30, 150, 1, &FreeSans12pt7b,int( DHT.humidity));
 showmsgXY(60, 150, 1, &FreeSans12pt7b, "% is current Humidity ");
 showmsgXY(30, 120, 1, &FreeSans12pt7b, int(DHT.temperature));
 showmsgXY(60, 120, 1, &FreeSans12pt7b, "C is current temperature ");
 showmsgXY(30, 180, 1, &FreeSans12pt7b, time);
  showmsgXY(60, 180, 1, &FreeSans12pt7b, " min till next water break");
  showmsgXY(20, 210, 1, &FreeSans12pt7b, "You should drink ");
   showmsgXY(200, 210, 1, &FreeSans12pt7b, f(DHT.temperature,DHT.humidity));
    showmsgXY(240, 210, 1, &FreeSans12pt7b, " lit/hour");
  // while (1);
  time--;
  delay(60000);
} 
