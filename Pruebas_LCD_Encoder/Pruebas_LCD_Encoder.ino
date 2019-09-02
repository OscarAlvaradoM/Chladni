/////////////////////////////////LCD//////////////////////////////////////////
// include the library code:                                                //
#include <LiquidCrystal.h>                                                  //
//
// initialize the library by associating any needed LCD interface pin       //
// with the arduino pin number it is connected to                           //
const int rs = 12, en = 11, d4 = 5, d5 = 7, d6 = 3, d7 = 13;                //
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                                  //
//
//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////ENCODER///////////////////////////////////////////////
int encoderPinA = 2;      //variable A a pin digital 2 (DT en modulo)                       //
int encoderPinB = 4;        //variable B a pin digital 4 (CLK en modulo)                    //
int buttonPin = A1;                                                                         //
int lastEncoded = 0;                                                                        //
int encoderValue = 0;                                                                       //
int lastencoderValue = 0;                                                                   //
//////////////////////////////////////////////////////////////////////////////////////////////

int pinBuzzer = 11;

void setup() {
  Serial.begin (9600);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(pinBuzzer, OUTPUT);

  //get starting position
  int lastMSB = digitalRead(encoderPinA);
  int lastLSB = digitalRead(encoderPinB);

  Serial.print("Starting Position AB  " );
  Serial.print(lastMSB);
  Serial.println(lastLSB);

  //let start be lastEncoded so will index on first click
  lastEncoded = (lastMSB << 1) | lastLSB;

  //Para el contraste de la pantalla
  pinMode(6, OUTPUT);
  analogWrite(6, 100);

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hola mundo!");
}
int contador = 0;
void loop() {

  int MSB = digitalRead(encoderPinA); //MSB = most significant bit
  int LSB = digitalRead(encoderPinB); //LSB = least significant bit

  int encoded = (MSB << 1) | LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue --;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue ++;

  lastEncoded = encoded; //store this value for next time


  if ((encoderValue == lastencoderValue + 2) || (encoderValue == lastencoderValue - 2)) {
    Serial.println(encoderValue / 2);
    lcd.setCursor(0, 2);
    lcd.print(encoderValue / 2);
    lcd.print("           ");

    lastencoderValue = encoderValue;
  }

  //reset index
  if ((analogRead(buttonPin) <= 50) && (contador == 0)) {
    Serial.println(buttonPin);
    lcd.setCursor(0, 2);
    lcd.print("Boton");
    delay(200);
    lcd.setCursor(0, 2);
    lcd.print(encoderValue / 2);
    lcd.print("           ");
    contador = 1;
  }
  if ((analogRead(buttonPin) >= 50) && (contador == 1)) {
    contador = 0;
  }
}
