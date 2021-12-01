#include <SoftwareSerial.h>
#define PIN_RX 5
#define PIN_TX 6
#define RED 9
#define GREEN 10
#define BLUE 11
uint32_t myTimer;
boolean status_con = false;
String input_message;
SoftwareSerial mySerial(PIN_RX, PIN_TX); 
void setup() {
  Serial.begin(9600);
     mySerial.begin(9600);
  pinMode(RED, OUTPUT); // объявляем пин 6 как выход
   pinMode(GREEN, OUTPUT); // объявляем пин 8 как выход
  pinMode(BLUE, OUTPUT); // объявляем пин 7 как выход
  // инициализация
}
String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void light(int r, int g, int b)
{
  analogWrite(RED, r);
   analogWrite(GREEN, g);
    analogWrite(BLUE, b);
  
  }
void loop() {

  if (millis() - myTimer >= 50) {   // ищем разницу (500 мс)
    myTimer = millis();              // сброс таймера
    if (mySerial.available())
    {
      input_message = mySerial.readStringUntil('#');
      Serial.println(input_message);    
      if (input_message[0] == 'm')
      {
String part01 = (getValue(input_message,':',1));
String part02 = (getValue(input_message,':',2));
String part03 = (getValue(input_message,':',3));
int red = part01.toInt();
int green = part02.toInt();
int blue = part03.toInt();
light(red, green, blue);
Serial.println(part01);
Serial.println(part02);
Serial.println(part03);
Serial.println(red);
Serial.println(green);
Serial.println(blue);
      }
    }
       
}


}
