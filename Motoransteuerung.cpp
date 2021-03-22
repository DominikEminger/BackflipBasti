int MotorPWM = 11;                                //Initialiseren der Werte und Zuweisung der Hardware an die jeweiligen I/O Pins
int MotorIN = 10;
int speaker = 12;

int Led_Slow = 2;
int Led_Normal = 3;
int Led_Fast = 4;

int Button_Slow = 5;
int Button_Normal = 6;
int Button_Fast = 7;
int Button_Start = 8;
int Button_Stop = 9;

int Game_State = 0;                               //Setzen der Anfangswerte auf 0 bzw. LOW
int i = 0;
int Start_Value = LOW;
int Stop_Value = LOW;
int Slow_Value = LOW;
int Normal_Value = LOW;
int Fast_Value = LOW;


void setup() {                                    //Setup Funktion zur Zuweisung der In- und Outputs
  pinMode(MotorPWM, OUTPUT);
  pinMode(MotorIN, OUTPUT);
  pinMode(Led_Slow, OUTPUT);
  pinMode(Led_Normal, OUTPUT);
  pinMode(Led_Fast, OUTPUT);

  pinMode(Button_Slow, INPUT);
  pinMode(Button_Normal, INPUT);
  pinMode(Button_Fast, INPUT);
  pinMode(Button_Start, INPUT);
  pinMode(Button_Stop, INPUT);

  delay(500);                                     //Startup-Melodie, die nach Einschalten der Elektronikbox ertönt
  tone(speaker, 90, 300);
  delay(300);
  tone(speaker, 110, 100);
  delay(100);                                     
  tone(speaker, 130, 300);
  delay(300);
  tone(speaker, 110, 100);
  delay(100);
  tone(speaker, 150, 600);
  delay(600);
  tone(speaker, 145, 100);
  delay(100);
  tone(speaker, 130, 300);
}

void loop() {
  switch(Game_State){                             //Endlicher Zustandsautomat mit den verschieden Zuständen der Motorsteuerung
    case 0: Game_State_Startup(); break;

    case 1: Game_State_Slow(); break;

    case 2: Game_State_Normal(); break;

    case 3: Game_State_Fast(); break;
  }
}

int Game_State_Startup(){                         //Startup-Zustand (Zustand 0), wird nach Einschalten sofort ausgeführt

  digitalWrite(Led_Slow, LOW);                    //Ausschalten der LEDs für den Fall, dass noch welche aktiv waren
  digitalWrite(Led_Normal, LOW);
  digitalWrite(Led_Fast, LOW);

  i = 0;                                          //Setzen der Counter-Variable auf 0
  
  Slow_Value = digitalRead(Button_Slow);          //Auslesen der Taster und Zuschreiben der Werte
  Normal_Value = digitalRead(Button_Normal);
  Fast_Value = digitalRead(Button_Fast);

  if(Slow_Value == HIGH){                         //Falls der "Slow" Taster gedrückt wird, auf Zustand 1 wechseln
    return Game_State = 1;
  }
  else if(Normal_Value == HIGH){                  //Falls der "Normal" Taster gedrückt wird, auf Zustand 2 wechseln
    return Game_State = 2;
  }
  else if(Fast_Value == HIGH){                    //Falls der "Fast" Taster gedrückt wird, auf Zustand 3 wechseln
    return Game_State = 3;
  }
}

int Game_State_Slow(){                            //Slow-Zustand (Zustand 1)
  
  digitalWrite(Led_Slow, HIGH);                   //Einschalten der "Slow" LED, Ausschalten der "Normal"- und "Fast" LED
  digitalWrite(Led_Normal, LOW);
  digitalWrite(Led_Fast, LOW);

  while(i < 1){                                   //Schleife, die nur einmal ausgeführt wird, um "Slow"-Tonfolge zu spielen
    tone(speaker, 80, 150);
    delay(150);
    tone(speaker, 90, 150);
    i++;
  }
  
  Start_Value = digitalRead(Button_Start);        //Auslesen der Taster und Zuschreiben der Werte
  Stop_Value = digitalRead(Button_Stop);
  Slow_Value = digitalRead(Button_Slow);
  Normal_Value = digitalRead(Button_Normal);
  Fast_Value = digitalRead(Button_Fast);

  if(Stop_Value != HIGH){                         //Führt Programm aus, solange der "Stop"-Taster nicht gedrückt wird
    
    if(Start_Value == HIGH){                      //Falls der "Start"-Knopf gedrückt wird, wird der Motor mit niedriger Geschwindigkeit angeschalten
      analogWrite(MotorPWM, 50);
      digitalWrite(MotorIN, HIGH);
    }
    else if(Normal_Value == HIGH){                //Falls der "Normal"-Knopf gedrückt wird, wird der Motor ausgeschalten, die Counter-Variable auf 0 gesetzt und auf Zustand 2 gewechselt
      digitalWrite(MotorIN, LOW);
      analogWrite(MotorPWM, 0);
      i = 0;
      
      return Game_State = 2;
    }
    else if(Fast_Value == HIGH){                  //Falls der "Fast"-Knopf gedrückt wird, wird der Motor ausgeschalten, die Counter-Variable auf 0 gesetzt und auf Zustand 3 gewechselt
      digitalWrite(MotorIN, LOW);
      analogWrite(MotorPWM, 0);
      i = 0;
      
      return Game_State = 3;
    }
  }
  else if(Stop_Value == HIGH){                    //Falls der "Stop"-Knopf gedrückt wird, wird der Motor ausgeschalten und wieder zum Anfang von Zustand 1 gewechselt
    digitalWrite(MotorIN, LOW);
    analogWrite(MotorPWM, 0);

    return Game_State = 1;
  }
}

int Game_State_Normal(){                          //Normal-Zustand (Zustand 2)
  
  digitalWrite(Led_Slow, LOW);                    //Einschalten der "Normal" LED, Ausschalten der "Slow"- und "Fast" LED
  digitalWrite(Led_Normal, HIGH);
  digitalWrite(Led_Fast, LOW);

  while(i < 1){                                   //Schleife, die nur einmal ausgeführt wird, um "Normal"-Tonfolge zu spielen
    tone(speaker, 100, 150);
    delay(150);
    tone(speaker, 110, 150);
    i++;
  }
  
  Start_Value = digitalRead(Button_Start);        //Auslesen der Taster und Zuschreiben der Werte
  Stop_Value = digitalRead(Button_Stop);
  Slow_Value = digitalRead(Button_Slow);
  Normal_Value = digitalRead(Button_Normal);
  Fast_Value = digitalRead(Button_Fast);

  if(Stop_Value != HIGH){                         //Führt Programm aus, solange der "Stop"-Taster nicht gedrückt wird
    
    if(Start_Value == HIGH){                      //Falls der "Start"-Knopf gedrückt wird, wird der Motor mit normaler Geschwindigkeit angeschalten
      analogWrite(MotorPWM, 58);
      digitalWrite(MotorIN, HIGH);
    }
    else if(Slow_Value == HIGH){                  //Falls der "Slow"-Knopf gedrückt wird, wird der Motor ausgeschalten, die Counter-Variable auf 0 gesetzt und auf Zustand 1 gewechselt
      digitalWrite(MotorIN, LOW);
      analogWrite(MotorPWM, 0);
      i = 0;
      
      return Game_State = 1;
    }
    else if(Fast_Value == HIGH){                  //Falls der "Fast"-Knopf gedrückt wird, wird der Motor ausgeschalten, die Counter-Variable auf 0 gesetzt und auf Zustand 3 gewechselt
      digitalWrite(MotorIN, LOW);
      analogWrite(MotorPWM, 0);
      i = 0;
      
      return Game_State = 3;
    }
  }
  else if(Stop_Value == HIGH){                    //Falls der "Stop"-Knopf gedrückt wird, wird der Motor ausgeschalten und wieder zum Anfang von Zustand 2 gewechselt
    digitalWrite(MotorIN, LOW);
    analogWrite(MotorPWM, 0);

    return Game_State = 2;
  }
}

int Game_State_Fast(){                            //Fast-Zustand (Zustand 3)
  
  digitalWrite(Led_Slow, LOW);                    //Einschalten der "Fast" LED, Ausschalten der "Slow"- und "Normal" LED
  digitalWrite(Led_Normal, LOW);
  digitalWrite(Led_Fast, HIGH);

  while(i < 1){                                   //Schleife, die nur einmal ausgeführt wird, um "Fast"-Tonfolge zu spielen
    tone(speaker, 130, 150);
    delay(150);
    tone(speaker, 140, 150);
    i++;
  }
  
  Start_Value = digitalRead(Button_Start);        //Auslesen der Taster und Zuschreiben der Werte
  Stop_Value = digitalRead(Button_Stop);
  Slow_Value = digitalRead(Button_Slow);
  Normal_Value = digitalRead(Button_Normal);      
  Fast_Value = digitalRead(Button_Fast);

  if(Stop_Value != HIGH){                         //Führt Programm aus, solange der "Stop"-Taster nicht gedrückt wird
    
    if(Start_Value == HIGH){                      //Falls der "Start"-Knopf gedrückt wird, wird der Motor mit hoher Geschwindigkeit angeschalten
      analogWrite(MotorPWM, 80);
      digitalWrite(MotorIN, HIGH);
    }
    else if(Normal_Value == HIGH){                //Falls der "Normal"-Knopf gedrückt wird, wird der Motor ausgeschalten, die Counter-Variable auf 0 gesetzt und auf Zustand 2 gewechselt
      digitalWrite(MotorIN, LOW);
      analogWrite(MotorPWM, 0);
      i = 0;
      
      return Game_State = 2;
    }
    else if(Slow_Value == HIGH){                  //Falls der "Slow"-Knopf gedrückt wird, wird der Motor ausgeschalten, die Counter-Variable auf 0 gesetzt und auf Zustand 1 gewechselt
      digitalWrite(MotorIN, LOW);
      analogWrite(MotorPWM, 0);
      i = 0;
      
      return Game_State = 1;
    }
  }
  else if(Stop_Value == HIGH){                    //Falls der "Stop"-Knopf gedrückt wird, wird der Motor ausgeschalten und wieder zum Anfang von Zustand 3 gewechselt
    digitalWrite(MotorIN, LOW);
    analogWrite(MotorPWM, 0);

    return Game_State = 3;
  }
}
