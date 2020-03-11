#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
//Define SPI Connections:
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
 
#define OLED_RESET 13

int len;
int minLen = 20;
int maxLen = SCREEN_WIDTH;
int startRow = 29;
const int buttonPin = 5;
int buttonState = 0;
int prog = 0;
int second = 30;
String strSecond;
int minute = 23;
String strMinute;
int hour = 23;
String strHour;
unsigned long now = millis();
double timeNow = millis();
int timeOffset = 495;

void setup(){           
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //I2C address
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  pinMode(buttonPin, INPUT_PULLUP);
}

void runTars(){
  //drawLine
  len = random(minLen, maxLen);
  for (int i = 0; i<len; i+=2){
    display.drawPixel(i, startRow, WHITE);
    display.display();
  }
  //scrollUp
  for (int i=0; i<SCREEN_WIDTH; i++)
  {
    for (int j=2; j<SCREEN_HEIGHT; j++){
      display.drawPixel(i, j-2, display.getPixel(i, j));
    }
  }
  display.display();
}

void runTime(){
  if (hour < 10){
    strHour = "0" + String(hour);
  }
  else{
    strHour = String(hour);
  }
  if (minute < 10){
    strMinute = "0" + String(minute);
  }
  else{
    strMinute = String(minute);
  }
  if (second < 10){
    strSecond = "0" + String(second);
  }
  else{
    strSecond = String(second);
  }
  display.print(strHour + ":" + strMinute + ":" + strSecond);
  if (millis() > timeNow + timeOffset){
    timeNow = millis() + timeOffset;
    second ++;
  }
  if (second > 59){
    minute ++;
    second = 0;
  }
  if (minute > 59){
    hour ++;
    minute = 0;
  }
  if (hour > 23){
    hour = 0;
  }
  display.display();
  display.clearDisplay();
  display.setCursor(0,0);
}

void loop(){
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW and millis() > now + 1000){
    now = millis();
    if (prog == 0){
      prog = 1;
      timeNow = millis();
    }else{
      prog = 0;
    }
  }
  if (prog == 1){
    runTars();
  }else{
    runTime();
  }
}
