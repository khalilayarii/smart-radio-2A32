#include <Adafruit_Keypad.h>
#include <Adafruit_Keypad_Ringbuffer.h>

#include <Keypad.h>
#define ROWS 4
#define COLS 4
const char kp4x4Keys[ROWS][COLS]  = {{'1', '2', '3', 'A'}, {'4', '5', '6', 'B'}, {'7', '8', '9', 'C'}, {'*', '0', '#', 'D'}};
byte rowKp4x4Pin [4] = {9, 8, 7, 6};
byte colKp4x4Pin [4] = {5, 4, 3, 2};
Keypad kp4x4  = Keypad(makeKeymap(kp4x4Keys), rowKp4x4Pin, colKp4x4Pin, ROWS, COLS);
//configuration de clavier arduino
int k = 0;
char arr[7]; 
void setup()
{
 Serial.begin(9600);
}

void loop()
{
  char whichKey = kp4x4.getKey();
  if (whichKey == '*' || whichKey == '#' || whichKey == 'A' || // define invalid keys
      whichKey == 'B' || whichKey == 'C' || whichKey == 'D')
  {
 
    for(int j=0;j<6;j++)
    arr[j] = "";  
   //Serial.print("  Invalid Key!");
   delay(1000);
 
    k = 0;
  }
  // define valid keys
  else if (whichKey == '0' || whichKey == '1' || whichKey == '2' || whichKey == '3' || whichKey == '4' || whichKey == '5' || whichKey == '6' || whichKey == '7' || whichKey == '8' || whichKey == '9')
  {
   
    arr[k] = whichKey;
    k++;
  }
  //envoi du code au qt pour le tester
  if(k==6){
    Serial.write(arr);
  k=0;
  for(int j=0;j<6;j++)
    {
    arr[j]= "";
    }
}
}
