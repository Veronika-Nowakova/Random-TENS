/*
Created by Veronika Nowaková 2020 
under CC license
Attribution (CC BY-NC-SA 4.0)
" https://creativecommons.org/licenses/by-nc-sa/4.0/ "
VERSION 0.9 
language EN
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// SETTING THE INTENSITY OF MAX VALUE
int int_2 = 5;
int int_4 = 5;
int int_5 = 4;
int int_6 = 4;
int int_7 = 3;

// CALIBRATE FLOW METER ML/SEC FOR PUMP MIN MAX VALUES
float min_flow = 1;             // Seconds
float max_flow = 10;

// set min max time range
float time_min_minuts = 1;      // Minutes
float time_max_minuts = 10;

// VARIABLES DO NOT CHANGE
float min_FL = min_flow * 1000; // milliseconds
float max_FL = max_flow * 1000;
int extra;
int tl_start;
int program;
long intenzita;
float mnozstvi;
float time = 0.0;
float time_min = (time_min_minuts * 1000 * 60); // milliseconds
float time_max = (time_max_minuts * 1000 * 60);
float extra_time = 0.0;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

  randomSeed(analogRead(0));

  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP); // START BUTTON
  pinMode(3, OUTPUT);       // switch on off
  pinMode(4, OUTPUT);       // mode BUTTON
  pinMode(5, OUTPUT);       // intensity +
  pinMode(6, OUTPUT);       // intensity -
  pinMode(7, OUTPUT);       // butt plug enema FLOW
  pinMode(8, OUTPUT);       // control LED
  pinMode(9, OUTPUT);       // safety switch
}
void loop()
{

  tl_start = digitalRead(2);
  if (tl_start == HIGH)
  {

    int start_time = 10;    // start countdown
    for (int i = 10; i >= 0; i--)
    {
      lcd.clear();
      start_time = (start_time - 1);
      lcd.setCursor(1, 0);
      lcd.print(start_time);
      delay(1000);
    }

    program = random(1, 7); // program selection

    switch (program)
    {
      case 1: // program 1 TR.  ( 2 )

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Program 1");

      Serial.print('\n');
      Serial.print("Program 1 ");

      digitalWrite(3, HIGH); // ON
      

      delay(250);
      digitalWrite(3, LOW);
      delay(250);
      delay(250);
      digitalWrite(4, LOW);
      delay(250);

      intenzita = random(1, int_2); // intensity selection

      lcd.setCursor(1, 1);
      lcd.print("intensity");
      lcd.setCursor(11, 1);
      lcd.print(intenzita);

      Serial.print(" ");
      Serial.print(" intensity ");
      Serial.print(intenzita);
      Serial.print(" ");

      for (int i = 0; i < intenzita; i++)
      {
        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);
      }

      time = random(time_min, time_max); // TIME RANGE

      lcd.setCursor(1, 2);
      lcd.print("Time ");
      lcd.setCursor(7, 2);
      lcd.print(time / 1000 / 60);
      lcd.setCursor(12, 2);
      lcd.print(" min");

      Serial.print("Time ");
      Serial.print(time / 1000);
      Serial.print(" sec ");
      Serial.print(time / 1000 / 60);
      Serial.print(" minute ");
      Serial.print('\n');

      digitalWrite(8, HIGH);

      digitalWrite(9, HIGH);

      delay (time/4*3);

      extra = random(10, 16); // EXTRA selection

      Serial.print('\n');
      Serial.print(" extra ");
      Serial.print(extra);
      Serial.print('\n');

      switch (extra)
      {
        case 10:
        lcd.setCursor(1, 3);
        lcd.print("one more intensity");

        Serial.print('\n');
        Serial.print("one more intensity");
        Serial.print('\n');

        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);

        goto Continue_1;
    
        case 11:
        lcd.setCursor(1, 3);
        lcd.print("two more intensity");

        Serial.print('\n');
        Serial.print("two more intensity");
        Serial.print('\n');

        for (int i = 0; i < 3; i++)
        {
          digitalWrite(5, HIGH);
          delay(250);
          digitalWrite(5, LOW);
          delay(250);
        }

        goto Continue_1;
    
        case 12:
        extra_time = random (time_min, time / 2);

        lcd.setCursor(1, 3);
        lcd.print("extra time ");
        lcd.setCursor(12, 3);
        lcd.print(extra_time / 1000);
        lcd.setCursor(11, 3);
        lcd.print("sec ");

        Serial.print('\n');
        Serial.print("extra time ");
        Serial.print(extra_time / 1000);
        Serial.print(" sec ");
        Serial.print(extra_time / 1000 / 60);
        Serial.print(" min ");

        delay(extra_time);

        goto Continue_1;

        default:
        lcd.setCursor(1, 3);
        lcd.print("NOTHING EXTRA");

        Serial.print('\n');
        Serial.print("NOTHING EXTRA");
        Serial.print('\n');

        goto Continue_1;
      }
      
      Continue_1:
      lcd.setCursor(1, 3);
      lcd.print("Continue        ");

      Serial.print('\n');
      Serial.print (" the rest of the time ");
      Serial.print (time/4/1000);

      delay (time/4);

      Serial.print('\n');
      Serial.print (" END ");
      Serial.print('\n');

      digitalWrite(8, LOW);
      delay(250);

      digitalWrite(3, HIGH); // vypnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      digitalWrite(9, LOW);

      Serial.print('\n');

      lcd.clear();
      lcd.setCursor (10, 1);
      lcd.print (" END ");
      delay (3000);

      break;

      case 2: // program 2 ST.  ( 4 )

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Program 2");

      Serial.print('\n');
      Serial.print("Program 2 ");

      digitalWrite(3, HIGH); // zapnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      for (int i = 0; i < 3; i++) // 3x mode
      {
        digitalWrite(4, HIGH);
        delay(250);
        digitalWrite(4, LOW);
        delay(250);
      }

      intenzita = random(1, int_4); // intenzita

      lcd.setCursor(1, 1);
      lcd.print("intensity");
      lcd.setCursor(11, 1);
      lcd.print(intenzita);

      Serial.print(" ");
      Serial.print(" intensity ");
      Serial.print(intenzita);
      Serial.print(" ");

      for (int i = 0; i < intenzita; i++)
      {
        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);
      }

      time = random(time_min, time_max); // delka

      lcd.setCursor(1, 2);
      lcd.print("Time ");
      lcd.setCursor(7, 2);
      lcd.print(time / 1000 / 60);
      lcd.setCursor(12, 2);
      lcd.print(" min");

      Serial.print("Time ");
      Serial.print(time / 1000);
      Serial.print(" sec ");
      Serial.print(time / 1000 / 60);
      Serial.print(" minutes ");
      Serial.print('\n');

      digitalWrite(8, HIGH);

      digitalWrite(9, HIGH);

      delay (time/4*3);

      extra = random(20, 26); // volba pridavku

      Serial.print('\n');
      Serial.print(" extra ");
      Serial.print(extra);
      Serial.print('\n');

      switch (extra)
      {
        case 20:
        lcd.setCursor(1, 3);
        lcd.print("one more intensity");

        Serial.print('\n');
        Serial.print("one more intensity");
        Serial.print('\n');

        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);

        goto Continue_2;
    
        case 21:
        lcd.setCursor(1, 3);
        lcd.print("two more intensity");

        Serial.print('\n');
        Serial.print("two more intensity");
        Serial.print('\n');

        for (int i = 0; i < 3; i++)
        {
          digitalWrite(5, HIGH);
          delay(250);
          digitalWrite(5, LOW);
          delay(250);
        }

        goto Continue_2;
    
        case 22:
        extra_time = random (time_min, time / 2);

        lcd.setCursor(1, 3);
        lcd.print("extra time ");
        lcd.setCursor(12, 3);
        lcd.print(extra_time / 1000);
        lcd.setCursor(11, 3);
        lcd.print("sec ");

        Serial.print('\n');
        Serial.print("extra time ");
        Serial.print(extra_time / 1000);
        Serial.print(" sec ");
        Serial.print(extra_time / 1000 / 60);
        Serial.print(" min ");

        delay(extra_time);

        goto Continue_1;

        default:
        lcd.setCursor(1, 3);
        lcd.print("NOTHING EXTRA");

        Serial.print('\n');
        Serial.print("NOTHING EXTRA");
        Serial.print('\n');

        goto Continue_2;
      }
      
      Continue_2:
      lcd.setCursor(1, 3);
      lcd.print("Continue        ");

      Serial.print('\n');
      Serial.print (" the rest of the time ");
      Serial.print (time/4/1000);

      delay (time/4);

      Serial.print('\n');
      Serial.print (" END ");
      Serial.print('\n');

      digitalWrite(8, LOW);
      delay(250);

      digitalWrite(3, HIGH); // vypnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      digitalWrite(9, LOW);

      lcd.clear();
      lcd.setCursor (10, 1);
      lcd.print ("END");
      delay (3000);

      break;

      case 3: // program 3 ST.  ( 5 )

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Program 3");

      Serial.print('\n');
      Serial.print("Program 3 ");

      digitalWrite(3, HIGH); // zapnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      for (int i = 0; i < 4; i++) // 4x mode
      {
        digitalWrite(4, HIGH);
        delay(250);
        digitalWrite(4, LOW);
        delay(250);
      }

      intenzita = random(1, int_5); // intenzita

      lcd.setCursor(1, 1);
      lcd.print("intensity");
      lcd.setCursor(11, 1);
      lcd.print(intenzita);

      Serial.print(" ");
      Serial.print(" intensity ");
      Serial.print(intenzita);
      Serial.print(" ");

      for (int i = 0; i < intenzita; i++)
      {
        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);
      }

      time = random(time_min, time_max); // delka

      lcd.setCursor(1, 2);
      lcd.print("Time ");
      lcd.setCursor(7, 2);
      lcd.print(time / 1000 / 60);
      lcd.setCursor(12, 2);
      lcd.print(" min");

      Serial.print("Time ");
      Serial.print(time / 1000);
      Serial.print(" sec ");
      Serial.print(time / 1000 / 60);
      Serial.print(" minutes ");
      Serial.print('\n');

      digitalWrite(8, HIGH);

      digitalWrite(9, HIGH);

      delay (time/4*3);

      extra = random(30, 36); // volba pridavku

      Serial.print('\n');
      Serial.print(" extra ");
      Serial.print(extra);
      Serial.print('\n');

      switch (extra)
      {
        case 30:
        lcd.setCursor(1, 3);
        lcd.print("one more intensity");

        Serial.print('\n');
        Serial.print("one more intensity");
        Serial.print('\n');

        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);

        goto Continue_3;
    
        case 31:
        lcd.setCursor(1, 3);
        lcd.print("two more intensity");

        Serial.print('\n');
        Serial.print("two more intensity");
        Serial.print('\n');

        for (int i = 0; i < 3; i++)
        {
          digitalWrite(5, HIGH);
          delay(250);
          digitalWrite(5, LOW);
          delay(250);
        }

        goto Continue_3;
    
        case 32:
        extra_time = random (time_min, time / 2);

        lcd.setCursor(1, 3);
        lcd.print("extra time ");
        lcd.setCursor(12, 3);
        lcd.print(extra_time / 1000);
        lcd.setCursor(11, 3);
        lcd.print("sec ");

        Serial.print('\n');
        Serial.print("extra time ");
        Serial.print(extra_time / 1000);
        Serial.print(" sec ");
        Serial.print(extra_time / 1000 / 60);
        Serial.print(" min ");

        delay(extra_time);

        goto Continue_1;

        default:
        lcd.setCursor(1, 3);
        lcd.print("NOTHING EXTRA");

        Serial.print('\n');
        Serial.print("NOTHING EXTRA");
        Serial.print('\n');

        goto Continue_3;
      }

      Continue_3:
      lcd.setCursor(1, 3);
      lcd.print("Continue        ");

      Serial.print('\n');
      Serial.print (" the rest of the time ");
      Serial.print (time/4/1000);

      delay (time/4);

      Serial.print('\n');
      Serial.print (" END ");
      Serial.print('\n');

      digitalWrite(8, LOW);
      delay(250);

      digitalWrite(3, HIGH); // vypnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      digitalWrite(9, LOW);

      lcd.clear();
      lcd.setCursor (10, 1);
      lcd.print ("END");
      delay (3000);

      break;

      case 4: // program 4 ST.  ( 6 )

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Program 4");

      Serial.print('\n');
      Serial.print("Program 4 ");

      digitalWrite(3, HIGH); // zapnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      for (int i = 0; i < 5; i++) // 5x mode
      {
        digitalWrite(4, HIGH);
        delay(250);
        digitalWrite(4, LOW);
        delay(250);
      }

      intenzita = random(1, int_6); // intenzita

      lcd.setCursor(1, 1);
      lcd.print("intensity");
      lcd.setCursor(11, 1);
      lcd.print(intenzita);

      Serial.print(" ");
      Serial.print("intensity ");
      Serial.print(intenzita);
      Serial.print(" ");

      for (int i = 0; i < intenzita; i++)
      {
        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);
      }

      time = random(time_min, time_max); // delka

      lcd.setCursor(1, 2);
      lcd.print("Time ");
      lcd.setCursor(7, 2);
      lcd.print(time / 1000 / 60);
      lcd.setCursor(12, 2);
      lcd.print(" min");

      Serial.print("Time ");
      Serial.print(time / 1000);
      Serial.print(" sec ");
      Serial.print(time / 1000 / 60);
      Serial.print(" minutes ");
      Serial.print('\n');

      digitalWrite(8, HIGH);

      digitalWrite(9, HIGH);

      delay (time/4*3);

      extra = random(40, 46); // volba pridavku

      Serial.print('\n');
      Serial.print(" extra ");
      Serial.print(extra);
      Serial.print('\n');

      switch (extra)
      {
        case 40:
        lcd.setCursor(1, 3);
        lcd.print("one more intensity");

        Serial.print('\n');
        Serial.print("one more intensity");
        Serial.print('\n');

        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);

        goto Continue_4;
    
        case 41:
        lcd.setCursor(1, 3);
        lcd.print("two more intensity");

        Serial.print('\n');
        Serial.print("two more intensity");
        Serial.print('\n');

        for (int i = 0; i < 3; i++)
        {
          digitalWrite(5, HIGH);
          delay(250);
          digitalWrite(5, LOW);
          delay(250);
        }

        goto Continue_4;
    
        case 42:
        extra_time = random (time_min, time / 2);

        lcd.setCursor(1, 3);
        lcd.print("extra time ");
        lcd.setCursor(12, 3);
        lcd.print(extra_time / 1000);
        lcd.setCursor(11, 3);
        lcd.print("sec ");

        Serial.print('\n');
        Serial.print("extra time ");
        Serial.print(extra_time / 1000);
        Serial.print(" sec ");
        Serial.print(extra_time / 1000 / 60);
        Serial.print(" min ");

        delay(extra_time);

        goto Continue_1;

        default:
        lcd.setCursor(1, 3);
        lcd.print("NOTHING EXTRA");

        Serial.print('\n');
        Serial.print("NOTHING EXTRA");
        Serial.print('\n');

        goto Continue_4;
      }

      Continue_4:

      Serial.print('\n');
      Serial.print (" the rest of the time ");
      Serial.print (time/4/1000);

      delay (time/4);

      Serial.print('\n');
      Serial.print (" END ");
      Serial.print('\n');

      digitalWrite(8, LOW);
      delay(250);

      digitalWrite(3, HIGH); // vypnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      digitalWrite(9, LOW);

      lcd.clear();
      lcd.setCursor (10, 1);
      lcd.print ("END");
      delay (3000);

      break;

      case 5: // program 5 TR.  ( 7 )

      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Program 5");

      Serial.print('\n');
      Serial.print("Program 5 ");

      digitalWrite(3, HIGH); // zapnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      for (int i = 0; i < 6; i++) // 6x mode
      {
        digitalWrite(4, HIGH);
        delay(250);
        digitalWrite(4, LOW);
        delay(250);
      }

      intenzita = random(1, int_7); // intenzita

      lcd.setCursor(1, 1);
      lcd.print("intensity");
      lcd.setCursor(11, 1);
      lcd.print(intenzita);

      Serial.print(" ");
      Serial.print("intensity ");
      Serial.print(intenzita);
      Serial.print(" ");

      for (int i = 0; i < intenzita; i++)
      {
        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);
      }

      time = random(time_min, time_max); // delka

      lcd.setCursor(1, 2);
      lcd.print("Time ");
      lcd.setCursor(7, 2);
      lcd.print(time / 1000 / 60);
      lcd.setCursor(12, 2);
      lcd.print(" min");

      Serial.print("Time ");
      Serial.print(time / 1000);
      Serial.print(" sec ");
      Serial.print(time / 1000 / 60);
      Serial.print(" minutes ");
      Serial.print('\n');

      digitalWrite(8, HIGH);

      digitalWrite(9, HIGH);

      delay (time/4*3);

      extra = random(50, 56); // volba pridavku

      Serial.print('\n');
      Serial.print(" extra ");
      Serial.print(extra);
      Serial.print('\n');

      switch (extra)
      {
        case 50:
        lcd.setCursor(1, 3);
        lcd.print("one more intensity");

        Serial.print('\n');
        Serial.print("one more intensity");
        Serial.print('\n');

        digitalWrite(5, HIGH);
        delay(250);
        digitalWrite(5, LOW);
        delay(250);

        goto Continue_5;
    
        case 51:
        lcd.setCursor(1, 3);
        lcd.print("two more intensity");

        Serial.print('\n');
        Serial.print("two more intensity");
        Serial.print('\n');

        for (int i = 0; i < 3; i++)
        {
          digitalWrite(5, HIGH);
          delay(250);
          digitalWrite(5, LOW);
          delay(250);
        }

        goto Continue_5;
    
        case 52:
        extra_time = random (time_min, time / 2);

        lcd.setCursor(1, 3);
        lcd.print("extra time ");
        lcd.setCursor(12, 3);
        lcd.print(extra_time / 1000);
        lcd.setCursor(11, 3);
        lcd.print("sec ");

        Serial.print('\n');
        Serial.print("extra time ");
        Serial.print(extra_time / 1000);
        Serial.print(" sec ");
        Serial.print(extra_time / 1000 / 60);
        Serial.print(" min ");

        delay(extra_time);

        goto Continue_1;

        default:
        lcd.setCursor(1, 3);
        lcd.print("NOTHING EXTRA");

        Serial.print('\n');
        Serial.print("NOTHING EXTRA");
        Serial.print('\n');

        goto Continue_5;
      }

      Continue_5:
      Serial.print('\n');
      Serial.print (" the rest of the time ");
      Serial.print (time/4/1000);

      delay (time/4);

      Serial.print('\n');
      Serial.print (" END ");
      Serial.print('\n');

      digitalWrite(8, LOW);
      delay(250);

      digitalWrite(3, HIGH); // vypnuto
      delay(250);
      digitalWrite(3, LOW);
      delay(250);

      digitalWrite(9, LOW);

      lcd.clear();
      lcd.setCursor (10, 1);
      lcd.print ("END");
      delay (3000);

      break;

      case 6: // program 6  tr. zad.
    
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Program 6");

      Serial.print('\n');
      Serial.print("Program 6 ");

      mnozstvi = random(min_FL, max_FL);

      lcd.setCursor(0, 1);
      lcd.print("Quantity");
      lcd.setCursor(11, 1);
      lcd.print(mnozstvi);

      Serial.print(" Quantity ");
      Serial.print(" ");
      Serial.print(mnozstvi / 1000);
      Serial.print('\n');

      digitalWrite(7, HIGH);
      delay(mnozstvi);
      digitalWrite(7, LOW);
      delay(250);

      break;
    }
  }
  else
  {
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("WAIT FOR TRIGGER");

    Serial.println("WAIT FOR TRIGGER");
  }

  delay(1000);
}
