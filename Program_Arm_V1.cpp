int ResetButton = 8;                          //Initialiseren der Werte und Zuweisung der Hardware an die jeweiligen I/O Pins
int led_1Pin = 9;
int led_2Pin = 10;
int led_3Pin = 11;
int sensorPin = A0;
int sensorValue = 0;
int ButtonValue = LOW;

int LedOff = 0;                               //Setzen der PWM-Werte für Helligkeit der LEDs, höherer Wert = helleres Leuchten
int LedLow = 30;
int LedHigh = 255;
int Game_State = 0;                           //Setzen des Anfangszustands zu 0

void setup() {                                //Setup Funktion zur Zuweisung der In- und Outputs
  pinMode(led_1Pin, OUTPUT);
  pinMode(led_2Pin, OUTPUT);
  pinMode(led_3Pin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(ResetButton, INPUT);
}

void loop() {  
  switch(Game_State){                         //Endlicher Zustandsautomat mit den verschiedenen Zuständen des Spielarms
    case 0: Game_State_0(); break;
      
    case 1: Game_State_1(); break;
    
    case 2: Game_State_2(); break;
    
    case 3: Game_State_3(); break;
  }
}

int Game_State_0(){ 
  sensorValue = analogRead(sensorPin);        //Auslesen des Sensors und Zuschreiben des Wertes
  ButtonValue = LOW;                          //Wert des Reset-Buttons auf 0 setzen
  
  analogWrite(led_1Pin, LedLow);              //Alle LEDs auf mittlere Helligkeit setzen
  analogWrite(led_2Pin, LedLow);
  analogWrite(led_3Pin, LedLow);

  ButtonValue = digitalRead(ResetButton);     //Auslesen des Tasters und Zuschreiben des Wertes
  if(ButtonValue == HIGH){                    //Falls Taster gedrückt wird, wieder auf Zustand 0 zurückgehen
    return Game_State = 0;
  }
  
  if(sensorValue >= 500){                     //Falls Lichtschranke ein Signal bekommt, erste LED blinken lassen
    analogWrite(led_1Pin, LedHigh);
    delay(280);
    analogWrite(led_1Pin, LedOff);
    delay(280);
    analogWrite(led_1Pin, LedHigh);
    delay(280);
    analogWrite(led_1Pin, LedOff);
    delay(280);
    analogWrite(led_1Pin, LedHigh);
    delay(280);

    return Game_State = 1;                    //Übergang zu Zustand 1
  }
}

int Game_State_1(){
  sensorValue = analogRead(sensorPin);        //Auslesen des Sensors und Zuschreiben des Wertes
  ButtonValue = LOW;                          //Wert des Reset-Buttons auf 0 setzen

  analogWrite(led_1Pin, LedOff);              //LED 1 ausschalten, LED 2 und LED 3 auf mittlere Helligkeit setzen
  analogWrite(led_2Pin, LedLow);
  analogWrite(led_3Pin, LedLow);

  ButtonValue = digitalRead(ResetButton);     //Auslesen des Tasters und Zuschreiben des Wertes
  if(ButtonValue == HIGH){                    //Falls Taster gedrückt wird, wieder auf Zustand 0 zurückgehen
    return Game_State = 0;
  }
  
  if(sensorValue >= 500){                     //Falls Lichtschranke ein Signal bekommt, zweite LED blinken lassen
    analogWrite(led_2Pin, LedHigh);
    delay(280);
    analogWrite(led_2Pin, LedOff);
    delay(280);
    analogWrite(led_2Pin, LedHigh);
    delay(280);
    analogWrite(led_2Pin, LedOff);
    delay(280);
    analogWrite(led_2Pin, LedHigh);
    delay(280);

    return Game_State = 2;                    //Übergang zu Zustand 2
  }
} 

int Game_State_2(){
  sensorValue = analogRead(sensorPin);        //Auslesen des Sensors und Zuschreiben des Wertes
  ButtonValue = LOW;                          //Wert des Reset-Buttons auf 0 setzen

  analogWrite(led_1Pin, LedOff);              //LED 1 und LED 2 ausschalten, LED 3 auf mittlere Helligkeit setzen
  analogWrite(led_2Pin, LedOff);
  analogWrite(led_3Pin, LedLow);

  ButtonValue = digitalRead(ResetButton);     //Auslesen des Tasters und Zuschreiben des Wertes
  if(ButtonValue == HIGH){                    //Falls Taster gedrückt wird, wieder auf Zustand 0 zurückgehen
    return Game_State = 0;
  }
  
  if(sensorValue >= 500){                     //Falls Lichtschranke ein Signal bekommt, dritte LED blinken lassen
    analogWrite(led_3Pin, LedHigh);
    delay(280);
    analogWrite(led_3Pin, LedOff);
    delay(280);
    analogWrite(led_3Pin, LedHigh);
    delay(280);
    analogWrite(led_3Pin, LedOff);
    delay(280);
    analogWrite(led_3Pin, LedHigh);
    delay(280);

    return Game_State = 3;
  }
}

int Game_State_3(){
  ButtonValue = LOW;                          //Wert des Reset-Buttons auf 0 setzen
    
  analogWrite(led_1Pin, LedOff);              //Alle LEDs ausschalten
  analogWrite(led_2Pin, LedOff);
  analogWrite(led_3Pin, LedOff);

  ButtonValue = digitalRead(ResetButton);     //Auslesen des Tasters und Zuschreiben des Wertes
  if(ButtonValue == HIGH){                    //Falls Taster gedrückt wird, wieder auf Zustand 0 zurückgehen
    return Game_State = 0;
  }
}
