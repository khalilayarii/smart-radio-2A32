#define PIN_LED1 11 //le numéro de la broche sur laquelle la lampe 2  est branchée
#define PIN_LED2 8// Le numéro de la broche sur laquelle la lampe 1 
#include <LiquidCrystal_I2C.h>
//(par défaut intégrée dans la carte) est branchée 
#define pas  20 // incrément de l'intensité
char data; // variable contenant le caractère lu
String message;
int x; // variable contenant l'intensité de la deuxième lampe
LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  lcd.init() ; 
  lcd.backlight(); 
  lcd.setCursor(0,0);
  lcd.print("Smart radio ");

  lcd.setCursor(5,1);
  lcd.print("siwar");
  // Configure la broche 11 sur laquelle est reliée notre LED  en sortie
 /* pinMode(PIN_LED1,OUTPUT);
//La LED reliée à la broche 11 est intialisé à l'état LOW
  digitalWrite(PIN_LED2,LOW);
  // Configure la broche 13 sur laquelle est reliée notre LED  en sortie
  pinMode(PIN_LED2,OUTPUT);
//La LED reliée à la broche 13 est intialisé à l'état LOW
pinMode(PIN_LED1,OUTPUT);
  analogWrite(PIN_LED1, 0);*/
  Serial.begin(9600); //Permet d'initialiser le moniteur série à 9600 bauds 
  x=0; // Intialiser l'intensité de la deuxième lampe 

}



void loop() {
  
  if (Serial.available()){     
    //Si un message a été reçu  faire ceci
     data=Serial.read();  
     // controler la lampe 1 reliée à la broche 13
     //récuperer le caractère reçu
     if(data=='1') //si le caractère lu est égale à 1
    {
      //digitalWrite(PIN_LED2,HIGH); // alumer la lampe 
      Serial.write('1'); //envoyer le nouvel état de la lampe  
     }  
     else if(data=='0') //si le caractère lu est égale à 0

     {
        digitalWrite(PIN_LED2,LOW); //éteindre la lampe
        Serial.write('0'); //envoyer le nouvel état de la lampe
     
     }   
     else if (data!=' ')
     {
      message=Serial.readString();
        lcd.init() ; 
  lcd.backlight(); 
    lcd.setCursor(3,0);
  lcd.print("bonjour");
  lcd.setCursor(5,1);
  lcd.print(message);

 
      } 
  }
}
