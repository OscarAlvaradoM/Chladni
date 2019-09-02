//Added start up position check to make index +1/-1 from first move
//Polled rather than interrupts

int encoderPinA = 2;
int encoderPinB = 4;
int buttonPin = A1;

int lastEncoded = 0;
int encoderValue = 0;

int lastencoderValue = 0;

void setup() {
  Serial.begin (9600);

  pinMode(encoderPinA, INPUT_PULLUP);
  pinMode(encoderPinB, INPUT_PULLUP);
  pinMode(buttonPin, INPUT_PULLUP);

  //get starting position
  int lastMSB = digitalRead(encoderPinA);
  int lastLSB = digitalRead(encoderPinB);

  Serial.print("Starting Position AB  " );
  Serial.print(lastMSB);
  Serial.println(lastLSB);

  //let start be lastEncoded so will index on first click
  lastEncoded = (lastMSB << 1) | lastLSB;
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
    Serial.println();
    lastencoderValue = encoderValue;
    //contador = 1;
  }
  
  //reset index
  if ((analogRead(buttonPin) <= 50) && (contador == 0)) {
    Serial.println(buttonPin);
    contador = 1;
  }
   if ((analogRead(buttonPin) >= 50) && (contador == 1)){
    contador = 0;
   }
}
