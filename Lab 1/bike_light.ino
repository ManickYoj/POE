const int analogPin = 1;
const int buttonPin = 2;     
const int ledPin_1 =  12;
const int ledPin_2 =  11;
const int ledPin_3 =  10;
unsigned int patternNumber = 0;

void setup() {
  pinMode(ledPin_1, OUTPUT); 
  pinMode(ledPin_2, OUTPUT);      
  pinMode(ledPin_3, OUTPUT);      
  
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);

  attachInterrupt(0, lightISR, FALLING);    
}

void loop(){
  switch (patternNumber%5) {
    case 1:
      clearAll();    
      pattern1();
      break;
    case 2:
      clearAll();    
      pattern2();
      break;
    case 3:
      clearAll();
      pattern3();
      break;
    case 4:
      clearAll();
      pattern4();
      break;
    default:
      clearAll();
      break;
  }
}


// ----- PATTERNS ----- //

void pattern1() {
  digitalWrite(ledPin_1, HIGH); 
  delay (val()/2);
  digitalWrite(ledPin_2, HIGH); 
  delay (val());
  digitalWrite(ledPin_3, HIGH); 
  delay (val()*2);
  clearAll();
  delay(val());
}

void pattern2 () {
  // Turn on and off in travelling pattern
  digitalWrite(ledPin_3, HIGH);
  delay(val()/2);
  digitalWrite(ledPin_2, HIGH);
  delay(val()/2);
  digitalWrite(ledPin_3, LOW);
  digitalWrite(ledPin_1, HIGH);
  delay(val()/2);
  digitalWrite(ledPin_2, LOW);
  delay(val()/2);
  digitalWrite(ledPin_1, LOW);
}

void pattern3() {
  digitalWrite(ledPin_1, HIGH); 
  delay (val()*random(1, 3));
  digitalWrite(ledPin_2, HIGH); 
  delay (val()*random(1, 3));
  digitalWrite(ledPin_3, HIGH); 
  delay (val()*random(1, 3));   
  clearAll();
  delay(val());
}

void pattern4() {
  digitalWrite(ledPin_1, HIGH); 
  digitalWrite(ledPin_3, HIGH);
  digitalWrite(ledPin_2, LOW);
  delay(val()/2);
  digitalWrite(ledPin_2, HIGH);
  digitalWrite(ledPin_1, LOW);
  digitalWrite(ledPin_3, LOW);
  delay(val()/2);
}

void clearAll() {
  digitalWrite(ledPin_1, LOW);
  digitalWrite(ledPin_2, LOW); 
  digitalWrite(ledPin_3, LOW);
}


// ----- UTILITY FUNCTIONS -----//

int val(){
  return analogRead(analogPin);
}

/*
 * Interrupt for button push
 * Deals with debouncing switch. Advances and cycle
 * the pattern once for each button push
*/
void lightISR() {
  static volatile unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  
  if (interruptTime - lastInterruptTime > 200) {
    // Code for switching patterns
    patternNumber++;
  }
  
  lastInterruptTime = interruptTime;
}
