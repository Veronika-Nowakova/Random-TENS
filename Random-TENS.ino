/*
Created by Veronika Nowaková 2020 
under CC license
Attribution (CC BY-NC-SA 4.0)
" https://creativecommons.org/licenses/by-nc-sa/4.0/ "
VERSION 0.9.5
language EN
*/

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// SETTINGS

// SETTING THE INTENSITY OF MAX VALUE
int inte_1 = 5;
int inte_2 = 5;
int inte_3 = 4;
int inte_4 = 4;
int inte_5 = 3;

// CALIBRATE FLOW METER ML/SEC FOR PUMP MIN MAX VALUES
long min_mn = 1000;             // m sec
long max_mn = 5000;             // m sec

// SETTING THE MAXIMUM NUMBER FOR THE PUMP
int max_pocet_cerpani = 10;

// set min max time range
float time_min_minuts = 30;    // sec
float time_max_minuts = 1;     // min

// SETTING RANDOM RANGE OF TRUE ANSWER BEFORE RELEASE
int number_of_answer_min = 1;
int number_of_answer_max = 4;

// pin connection settings ( change only if you change connections )

const int pin_on_off = 2;         // switch on off              
const int pin_mode = 3;           // switch mode                       
const int pin_intensity = 4;      // switch intensity +                 
const int pin_safety_switch = 5;  // safety switch off if pc or power conect off.      

const int pin_lock = 8;           // release lock                       
const int pin_prog_6 = 9;         // relay for external device                       
const int pin_alternative = 10;   // alternative options for program 6 ( in develop )     
const int pin_correct_switch = 11;// switch triger correct response
const int pin_start_switch = 12;  // switch to triger random tens

// TEXT FOR LCD AND SERIA OUT ( you can easily translate output)
String text_test = "test of line";
String text_correct_answer_1 = "Correct answer ";
String text_TOTAL_1 = "TOTAL ";
String text_correct_answer_2 = "Correct  answer";
String text_Answers_needed = "Answers needed";
String text_max_Time = "max Time";
String text_answers = "answers";
String text_you_will_be_free = "text you will be free";
String text_Added_correct_answers_1 = "Added correct answers ";
String text_Added_correct_answers_2 = " Added correct answers";
String text_total_correct_answers_1 = "total correct answers needed ";
String text_intensity_1 = "Intensity";
String text_intensity_2 = " Intensity ";
String text_Length = "Length ";
String text_minute_1 = " min";
String text_minute_2 = " minute ";
String text_seconds_1 = " sec ";
String text_seconds_2 = " seconds ";
String text_st_1 = "One more intensity";
String text_st_2 = "Two more intensity";
String text_more_time = "More time ";
String text_nothing = "nothing added";
String text_CONTINUE = "CONTINUE";
String text_time = "the rest of the time";
String text_end_lesson_1 = " END OF LESSON ";
String text_end_lesson_2 = "END OF LESSON";
String text_mistake = "don't make a mistake";
String text_Second_event = "Second eventuality";
String text_volume_1 = "volume";
String text_volume_2 = " volume ";
String text_Program_1_1 = "Program 1"; 
String text_Program_1_2 = "Program 1 ";
String text_program_2_1 = "Program 2";
String text_program_2_2 = "Program 2 ";
String text_program_3_1 = "Program 3";
String text_program_3_2 = "Program 3 ";
String text_program_4_1 = "Program 4";
String text_program_4_2 = "Program 4 ";
String text_program_5_1 = "Program 5";
String text_program_5_2 = "Program 5 ";
String text_program_6 = "Program 6";

// -------------------------------------------------- //
// ----------- VARIABLES DO NOT CHANGE -------------- //
// -------------------------------------------------- //

int extra;
int start_switch;
int true_switch;
int program;
int number_of_true_answer = 0;
int number_of_true_for_release;
int extra_for_release;
int extra_answer;
int intensity;
int number_of_pump;
int total_stop;
int stop_repetition = 0;
int banned = 0;
int V_text_nothing = 0;

float volume;
float time = 0.0;
float time_min =  (time_min_minuts * 1000); // ms
float time_max =  (time_max_minuts * 1000 * 60);
float extra_time = 0.0;

char input;
char start;
char true_answer;
char test;

LiquidCrystal_I2C lcd (0x27, 20, 4);

void setup ()
{

  lcd.init ();
  lcd.backlight ();
  lcd.setCursor (0, 0);

  randomSeed (analogRead (0));

  Serial.begin (9600);

  pinMode (pin_start_switch, INPUT_PULLUP);   
  pinMode (pin_on_off, OUTPUT);                  
  pinMode (pin_mode, OUTPUT);             
  pinMode (pin_intensity, OUTPUT);             
  pinMode (pin_prog_6, OUTPUT);              
  pinMode (pin_safety_switch, OUTPUT);        
  pinMode (pin_lock, OUTPUT);            
  pinMode (pin_correct_switch, INPUT_PULLUP); 

  digitalWrite   (pin_lock, HIGH);

  number_of_true_for_release = random (number_of_answer_min, number_of_answer_max);

  lcd.clear ();
  lcd.setCursor  (1, 0);
  lcd.print  (text_max_Time);
  lcd.setCursor  (11, 0);
  lcd.print  (time_max_minuts);
  lcd.setCursor  (1, 1);
  lcd.print  (text_answers);
  lcd.setCursor  (11, 1);
  lcd.print  (number_of_true_for_release);
  delay  (10000);

}

void loop ()
{
  start:

  if  (banned == 0)
  {
    while  (Serial.available ())        // externí příkaz
    {
      input = Serial.read  ();

      if  (input == 'a')
      {
        true_answer = input;
      }

      else if  (input == 'b')
      {
        start = input;
      }

      else if (input == 't')
      {
        test = input;
      }
    }
  }

  if (test == 't')
  {
    test = ' ';
    Serial.print (text_test);
    Serial.print (test);

    lcd.clear();
    lcd.setCursor (4, 1);
    lcd.print (text_test);
    lcd.setCursor (12, 1);
    lcd.print (test);
    delay (5000);
    lcd.clear();
  }

  if  (banned == 0)
  {
    true_switch = digitalRead  (pin_correct_switch);
  }

  if  ((true_answer == 'a') ||  (true_switch == LOW)) // spusteni spravne odpovedi
  {
    banned = 1;

    number_of_true_answer =  (number_of_true_answer + 1);

    true_answer = ' ';

    Serial.println (text_correct_answer_1);
    Serial.print (text_TOTAL_1);
    Serial.println (number_of_true_answer);

    lcd.setCursor (3, 1);
    lcd.print (text_correct_answer_2);
    lcd.setCursor (6, 2);
    lcd.print (text_TOTAL_1);  
    lcd.setCursor (14, 2);
    lcd.print (number_of_true_answer);
    lcd.setCursor  (5, 3);
    lcd.print  (text_Answers_needed);
    lcd.setCursor  (14, 3);
    lcd.print  (number_of_true_for_release);
    delay (3000);
    lcd.setCursor (0, 2);
    lcd.print ("                    ");
    lcd.setCursor (0, 3);
    lcd.print ("                    ");

    banned = 0;
  }

  if  (number_of_true_answer == number_of_true_for_release) // HLAVNI UVOLNENI
  {
    extra_for_release = random (1, 10);

    switch  (extra_for_release)
    {
    case 1:
    case 10:
    case 9:
    case 4:
    case 5:

    ukonceni:

      digitalWrite   (pin_lock, LOW);

      lcd.clear ();
      lcd.setCursor (3, 2);
      lcd.print (text_you_will_be_free);

      for  (;;)
      {
        Serial.println (text_you_will_be_free);
        delay (1000);
      }

      delay (500);
      break;

    case 6:
    case 7:
    case 8:
    case 3:
    case 2:

      if  (stop_repetition == 1)
      {
        goto ukonceni;
      }

      else
      {
        extra_answer = random (1, 10);
        number_of_true_for_release =  (number_of_true_for_release + extra_answer);

        stop_repetition = 1; // Disable Repeat

        Serial.print (text_Added_correct_answers_1);
        Serial.print (extra_answer);
        Serial.println ('\n');
        Serial.print (text_total_correct_answers_1);
        Serial.print (number_of_true_for_release);

        lcd.clear ();
        lcd.setCursor (2, 1);
        lcd.print (extra_answer);
        lcd.print (text_Added_correct_answers_2);

        delay (5000);

        goto start;
      }
    }
  }

  if (banned == 0)
  {
    start_switch = digitalRead (pin_start_switch);
  }

  if (total_stop == 0)
  {
    delay (300000);
    if  ( (start_switch == HIGH) || (start == 'b'))
    {
      start = ' ';

      banned = 1;

      program = random (1, 12); 

      switch  (program)
      {
        case 12:
        case 1: // program 1 TR.   ( 2 )

        lcd.clear ();
        lcd.setCursor (1, 0);
        lcd.print (text_Program_1_1);

        Serial.println ('\n');
        Serial.print (text_Program_1_2);

        digitalWrite (pin_on_off, HIGH); // ON
        delay (250);
        digitalWrite (pin_on_off, LOW);
        delay (250);

        digitalWrite (pin_mode, HIGH);   // mode
        delay (250);
        digitalWrite (pin_mode, LOW);
        delay (250);

        intensity = random (1, inte_1); // intensity

        lcd.setCursor (1, 1);
        lcd.print (text_intensity_1);
        lcd.setCursor (11, 1);
        lcd.print (intensity);

        Serial.print (" ");
        Serial.print (text_intensity_2);
        Serial.print (intensity);
        Serial.print (" ");

        digitalWrite  (pin_safety_switch, HIGH);

        lcd.setCursor (16, 0);
        lcd.print ("   ");

        time = random (time_min, time_max); // delka

        lcd.setCursor (1, 2);
        lcd.print (text_Length);
        lcd.setCursor (7, 2);
        lcd.print (time / 1000 / 60);
        lcd.setCursor (12, 2);
        lcd.print (text_minute_1);

        Serial.print (text_Length);
        Serial.print (time / 1000);
        Serial.print (text_seconds_2);
        Serial.print (time / 1000 / 60);
        Serial.print (text_minute_2);
        Serial.println ('\n');

        delay (5000);
        
        for  (int i = 0; i < intensity; i++)
        {
          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (1000);
        }

        
        delay (time / 4 * 3);

        extra = random (100, 116); // volba pridavku

        Serial.println (extra);

        switch  (extra)
        {
          case 100:
          lcd.setCursor (1, 3);
          lcd.print (text_st_1);

          Serial.println ('\n');
          Serial.print (text_st_1);
          Serial.println ('\n');

          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (250);

          goto pokracovat_1;

          case 111:
          lcd.setCursor (1, 3);
          lcd.print (text_st_2);

          Serial.println ('\n');
          Serial.print (text_st_2);
          Serial.println ('\n');

          for  (int i = 0; i < 3; i++)
          {
            digitalWrite  (pin_intensity, HIGH);
            delay (250);
            digitalWrite  (pin_intensity, LOW);
            delay (1000);
          }

          goto pokracovat_1;

          case 112:
          extra_time = random ((time / 10), (time /2));

          lcd.setCursor (1, 3);
          lcd.print (text_more_time);
          lcd.setCursor (7, 3);
          lcd.print (extra_time / 1000);
          lcd.setCursor (11, 3);
          lcd.print ("s ");

          Serial.println ('\n');
          Serial.print (text_more_time);
          Serial.print (extra_time / 1000);
          Serial.print (text_seconds_1); 
          Serial.print (extra_time / 1000 / 60);
          Serial.print (text_minute_2); 

          delay (extra_time);

          goto pokracovat_1;

          default:
          V_text_nothing = true;

          lcd.setCursor (0, 3);
          lcd.print (text_nothing); 

          Serial.println ('\n');
          Serial.print (text_nothing);
          Serial.println ('\n');

          goto pokracovat_1;
        }

        pokracovat_1:
        if (V_text_nothing == true)
        {
          lcd.setCursor (10, 3);
          lcd.print (text_CONTINUE);
        }

        Serial.println ('\n');
        Serial.print (text_time);

        delay (time / 4);

        Serial.println ('\n');
        Serial.print (text_end_lesson_1);
        Serial.println ('\n');

        digitalWrite  (pin_on_off, HIGH); // vypnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        digitalWrite  (pin_safety_switch, LOW);

        Serial.println ('\n');

        lcd.clear ();
        lcd.setCursor (4, 1);
        lcd.print (text_end_lesson_2);

        delay (3000);

         banned = 0;

        break;

        case 11:
        case 2: // program 2 ST.   ( 4 )

        lcd.clear ();
        lcd.setCursor (1, 0);
        lcd.print (text_program_2_1);

        Serial.println ('\n');
        Serial.print (text_program_2_2);

        digitalWrite  (pin_on_off, HIGH); // zapnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        for  (int i = 0; i < 3; i++) // 3x mode
        {
          digitalWrite  (pin_mode, HIGH);
          delay (250);
          digitalWrite  (pin_mode, LOW);
          delay (250);
        }

        intensity = random (1, inte_2); // intenzita

        lcd.setCursor (1, 1);
        lcd.print (text_intensity_1);
        lcd.setCursor (11, 1);
        lcd.print (intensity);

        Serial.print (" ");
        Serial.print (text_intensity_2);
        Serial.print (intensity);
        Serial.print (" ");

        digitalWrite  (pin_safety_switch, HIGH);

        lcd.setCursor (16, 0);
        lcd.print ("   ");

        time = random (time_min, time_max); // delka

        lcd.setCursor (1, 2);
        lcd.print (text_Length);
        lcd.setCursor (7, 2);
        lcd.print (time / 1000 / 60);
        lcd.setCursor (12, 2);
        lcd.print (text_minute_1);

        Serial.print (text_Length);
        Serial.print (time / 1000);
        Serial.print (text_seconds_2);
        Serial.print (time / 1000 / 60);
        Serial.print (text_minute_2);
        Serial.println ('\n');

        delay (5000);
        
        for  (int i = 0; i < intensity; i++)
        {
          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (1000);
        }
        
        delay (time / 4 * 3);

        extra = random (20, 26); // volba pridavku

        switch  (extra)
        {
          case 20:
          lcd.setCursor (1, 3);
          lcd.print (text_st_1);

          Serial.println ('\n');
          Serial.print (text_st_1);
          Serial.println ('\n');

          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (250);

          delay  (3000);

          goto pokracovat_2;

          case 21:
          lcd.setCursor (1, 3);
          lcd.print (text_st_2);

          Serial.println ('\n');
          Serial.print (text_st_2);
          Serial.println ('\n');

          for  (int i = 0; i < 3; i++)
          {
            digitalWrite  (pin_intensity, HIGH);
            delay (250);
            digitalWrite  (pin_intensity, LOW);
            delay (1000);
          }

          delay  (3000);

          goto pokracovat_2;

          case 22:
          extra_time = random ((time / 10), (time /2));

          lcd.setCursor (1, 3);
          lcd.print (text_more_time);
          lcd.setCursor (7, 3);
          lcd.print (extra_time / 1000);
          lcd.setCursor (11, 3);
          lcd.print ("s ");

          Serial.println ('\n');
          Serial.print (text_more_time);
          Serial.print (extra_time / 1000);
          Serial.print (text_seconds_1);
          Serial.print (extra_time / 1000 / 60);
          Serial.print (text_minute_2);

          delay (extra_time);

          goto pokracovat_2;

          default:
          V_text_nothing = true;

          lcd.setCursor (0, 3);
          lcd.print (text_nothing);

          Serial.println ('\n');
          Serial.print (text_nothing);
          Serial.println ('\n');

          goto pokracovat_2;
        }

        pokracovat_2:
        if (V_text_nothing == true)
        {
          lcd.setCursor (10, 3);
          lcd.print (text_CONTINUE);
        }

        Serial.println ('\n');
        Serial.print (text_time);

        delay (time / 4);

        Serial.println ('\n');
        Serial.print (text_end_lesson_1);
        Serial.println ('\n');

        digitalWrite  (pin_on_off, HIGH); // vypnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        digitalWrite  (pin_safety_switch, LOW);

        lcd.clear ();
        lcd.setCursor (4, 1);
        lcd.print (text_end_lesson_2);

        delay (3000);

        banned = 0;

        break;

        case 10:
        case 3: // program 3 ST.   ( 5 )

        lcd.clear ();
        lcd.setCursor (1, 0);
        lcd.print (text_program_3_1);

        Serial.println ('\n');
        Serial.print (text_program_3_2);

        digitalWrite  (pin_on_off, HIGH); // zapnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        for  (int i = 0; i < 4; i++) // 4x mode
        {
          digitalWrite  (pin_mode, HIGH);
          delay (250);
          digitalWrite  (pin_mode, LOW);
          delay (250);
        }

        intensity = random (1, inte_3); // intenzita

        lcd.setCursor (1, 1);
        lcd.print (text_intensity_1);
        lcd.setCursor (11, 1);
        lcd.print (intensity);

        Serial.print (" ");
        Serial.print (text_intensity_2);
        Serial.print (intensity);
        Serial.print (" ");

        digitalWrite  (pin_safety_switch, HIGH);

        lcd.setCursor (16, 0);
        lcd.print ("   ");

        time = random (time_min, time_max); // delka

        lcd.setCursor (1, 2);
        lcd.print (text_Length);
        lcd.setCursor (7, 2);
        lcd.print (time / 1000 / 60);
        lcd.setCursor (12, 2);
        lcd.print (text_minute_1);

        Serial.print (text_Length);
        Serial.print (time / 1000);
        Serial.print (text_seconds_2);
        Serial.print (time / 1000 / 60);
        Serial.print (text_minute_2);
        Serial.println ('\n');

        delay (5000);
        
        for  (int i = 0; i < intensity; i++)
        {
          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (1000);
        }
        
        delay (time / 4 * 3);

        extra = random (30, 36); // volba pridavku

        switch  (extra)
        {
          case 30:
          lcd.setCursor (1, 3);
          lcd.print (text_st_1);

          Serial.println ('\n');
          Serial.print (text_st_1);
          Serial.println ('\n');

          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (250);

          delay  (3000);

          goto pokracovat_3;

          case 31:
          lcd.setCursor (1, 3);
          lcd.print (text_st_2);

          Serial.println ('\n');
          Serial.print (text_st_2);
          Serial.println ('\n');

          for  (int i = 0; i < 3; i++)
          {
            digitalWrite  (pin_intensity, HIGH);
            delay (250);
            digitalWrite  (pin_intensity, LOW);
            delay (1000);
          }

          delay  (3000);

          goto pokracovat_3;

          case 32:
          extra_time = random ((time / 10), (time /2));

          lcd.setCursor (1, 3);
          lcd.print (text_more_time);
          lcd.setCursor (7, 3);
          lcd.print (extra_time / 1000);
          lcd.setCursor (11, 3);
          lcd.print ("s ");

          Serial.println ('\n');
          Serial.print (text_more_time);
          Serial.print (extra_time / 1000);
          Serial.print (text_seconds_1);
          Serial.print (extra_time / 1000 / 60);
          Serial.print (text_minute_2);

          delay (extra_time);

          goto pokracovat_3;

          default:
          V_text_nothing = true;

          lcd.setCursor (0, 3);
          lcd.print (text_nothing);

          Serial.println ('\n');
          Serial.print (text_nothing);
          Serial.println ('\n');

          goto pokracovat_3;
        }

        pokracovat_3:
        if (V_text_nothing == true)
        {
          lcd.setCursor (10, 3);
          lcd.print (text_CONTINUE);
        }

        Serial.println ('\n');
        Serial.print (text_time);

        delay (time / 4);

        Serial.println ('\n');
        Serial.print (text_end_lesson_1);
        Serial.println('\n');

        digitalWrite  (pin_on_off, HIGH); // vypnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        digitalWrite  (pin_safety_switch, LOW);

        lcd.clear ();
        lcd.setCursor (4, 1);
        lcd.print (text_end_lesson_2);

        banned = 0;

        break;

        case 9:
        case 4: // program 4 ST.   ( 6 )

        lcd.clear ();
        lcd.setCursor (1, 0);
        lcd.print (text_program_4_1);

        Serial.println ('\n');
        Serial.print (text_program_4_2);

        digitalWrite  (pin_on_off, HIGH); // zapnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        for  (int i = 0; i < 5; i++) // 5x mode
        {
          digitalWrite  (pin_mode, HIGH);
          delay (250);
          digitalWrite  (pin_mode, LOW);
          delay (250);
        }

        intensity = random (1, inte_4); // intenzita

        lcd.setCursor (1, 1);
        lcd.print (text_intensity_1);
        lcd.setCursor (11, 1);
        lcd.print (intensity);

        Serial.print (" ");
        Serial.print ("Intenzita ");
        Serial.print (intensity);
        Serial.print (" ");

        digitalWrite  (pin_safety_switch, HIGH);

        lcd.setCursor (16, 0);
        lcd.print ("   ");

        time = random (time_min, time_max); // delka

        lcd.setCursor (1, 2);
        lcd.print (text_Length);
        lcd.setCursor (7, 2);
        lcd.print (time / 1000 / 60);
        lcd.setCursor (12, 2);
        lcd.print (text_minute_1);

        Serial.print (text_Length);
        Serial.print (time / 1000);
        Serial.print (text_seconds_2);
        Serial.print (time / 1000 / 60);
        Serial.print (text_minute_2);
        Serial.println ('\n');

        delay (5000);
        
        for  (int i = 0; i < intensity; i++)
        {
          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (1000);
        }

        delay (time / 4 * 3);

        extra = random (40, 46); // volba pridavku

        switch  (extra)
        {
          case 40:
          lcd.setCursor (1, 3);
          lcd.print (text_st_1);

          Serial.println ('\n');
          Serial.print (text_st_1);
          Serial.println ('\n');

          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (250);

          delay  (3000);

          goto pokracovat_4;

          case 41:
          lcd.setCursor (1, 3);
          lcd.print (text_st_2);

          Serial.println ('\n');
          Serial.print (text_st_2);
          Serial.println ('\n');

          for  (int i = 0; i < 3; i++)
          {
            digitalWrite  (pin_intensity, HIGH);
            delay (250);
            digitalWrite  (pin_intensity, LOW);
            delay (1000);
          }

          delay  (3000);

          goto pokracovat_4;

          case 42:
          extra_time = random ((time / 10), (time /2));

          lcd.setCursor (1, 3);
          lcd.print (text_more_time);
          lcd.setCursor (7, 3);
          lcd.print (extra_time / 1000);
          lcd.setCursor (11, 3);
          lcd.print ("s ");

          Serial.println ('\n');
          Serial.print (text_more_time);
          Serial.print (extra_time / 1000);
          Serial.print (text_seconds_1);
          Serial.print (extra_time / 1000 / 60);
          Serial.print (text_minute_2);

          delay (extra_time);

          goto pokracovat_4;

          default:
          V_text_nothing = true;

          lcd.setCursor (0, 3);
          lcd.print (text_nothing);

          Serial.println ('\n');
          Serial.print (text_nothing);
          Serial.println ('\n');

          goto pokracovat_4;
        }

        pokracovat_4:
        if (V_text_nothing == true)
        {
          lcd.setCursor (10, 3);
          lcd.print (text_CONTINUE);
        }

        Serial.println ('\n');
        Serial.print (text_time);

        delay (time / 4);

        Serial.println ('\n');
        Serial.print (text_end_lesson_1);
        Serial.println ('\n');

        digitalWrite  (pin_on_off, HIGH); // vypnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        digitalWrite  (pin_safety_switch, LOW);

        lcd.clear ();
        lcd.setCursor (4, 1);
        lcd.print (text_end_lesson_2);

        delay (3000);

        banned = 0;

        break;

        case 7:
        case 5: // program 5 TR.   ( 7 )

        lcd.clear ();
        lcd.setCursor (1, 0);
        lcd.print (text_program_5_2);

        Serial.println ('\n');
        Serial.print (text_program_5_1);

        digitalWrite  (pin_on_off, HIGH); // zapnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        for  (int i = 0; i < 6; i++) // 6x mode
        {
          digitalWrite  (pin_mode, HIGH);
          delay (250);
          digitalWrite  (pin_mode, LOW);
          delay (250);
        }

        intensity = random (1, inte_5); // intenzita

        lcd.setCursor (1, 1);
        lcd.print (text_intensity_1);
        lcd.setCursor (11, 1);
        lcd.print (intensity);

        Serial.print (" ");
        Serial.print ("Intenzita ");
        Serial.print (intensity);
        Serial.print (" ");

        digitalWrite  (pin_safety_switch, HIGH);

        lcd.setCursor (16, 0);
        lcd.print ("   ");

        time = random (time_min, time_max); // delka

        lcd.setCursor (1, 2);
        lcd.print (text_Length);
        lcd.setCursor (7, 2);
        lcd.print (time / 1000 / 60);
        lcd.setCursor (12, 2);
        lcd.print (text_minute_1);

        Serial.print (text_Length);
        Serial.print (time / 1000);
        Serial.print (text_seconds_2);
        Serial.print (time / 1000 / 60);
        Serial.print (text_minute_2);
        Serial.println ('\n');

        delay (5000);
        
        for  (int i = 0; i < intensity; i++)
        {
          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (1000);
        }

        delay (time / 4 * 3);

        extra = random (50, 56); // volba pridavku

        switch  (extra)
        {
          case 50:
          lcd.setCursor (1, 3);
          lcd.print (text_st_1);

          Serial.println ('\n');
          Serial.print (text_st_1);
          Serial.println ('\n');

          digitalWrite  (pin_intensity, HIGH);
          delay (250);
          digitalWrite  (pin_intensity, LOW);
          delay (250);

          delay  (3000);

          goto pokracovat_5;

          case 51:
          lcd.setCursor (1, 3);
          lcd.print (text_st_2);

          Serial.println ('\n');
          Serial.print (text_st_2);
          Serial.println ('\n');

          for  (int i = 0; i < 3; i++)
          {
            digitalWrite  (pin_intensity, HIGH);
            delay (250);
            digitalWrite  (pin_intensity, LOW);
            delay (1000);
          }

          delay  (3000);

          goto pokracovat_5;

          case 52:
          extra_time = random ((time / 10), (time /2));

          lcd.setCursor (1, 3);
          lcd.print (text_more_time);
          lcd.setCursor (7, 3);
          lcd.print (extra_time / 1000);
          lcd.setCursor (11, 3);
          lcd.print ("s ");

          Serial.println ('\n');
          Serial.print (text_more_time);
          Serial.print (extra_time / 1000);
          Serial.print (text_seconds_1);
          Serial.print (extra_time / 1000 / 60);
          Serial.print (text_minute_2);

          delay (extra_time);

          goto pokracovat_5;

          default:
          V_text_nothing = true;

          lcd.setCursor (0, 3);
          lcd.print (text_nothing);

          Serial.println ('\n');
          Serial.print (text_nothing);
          Serial.println ('\n');

          goto pokracovat_5;
        }

        pokracovat_5:
        if (V_text_nothing == true)
        {
          lcd.setCursor (10, 3);
          lcd.print (text_CONTINUE);
        }

        Serial.println ('\n');
        Serial.print (text_time);

        delay (time / 4);

        Serial.println ('\n');
        Serial.print (text_end_lesson_1);
        Serial.println ('\n');

        digitalWrite  (pin_on_off, HIGH); // vypnuto
        delay (250);
        digitalWrite  (pin_on_off, LOW);
        delay (250);

        digitalWrite  (pin_safety_switch, LOW);

        lcd.clear ();
        lcd.setCursor (4, 1);
        lcd.print (text_end_lesson_2);
        delay (3000);

        banned = 0;

        break;

        case 8:
        case 6: // program 6  tr. zad.

        lcd.clear ();
        lcd.setCursor (1, 0);
        lcd.print (text_program_6);

        Serial.println ('\n');
        Serial.print (text_program_6);

        if (number_of_pump <= max_pocet_cerpani)
        {
          volume = random (min_mn, max_mn);

          lcd.setCursor (0, 1);
          lcd.print (text_volume_1);
          lcd.setCursor (11, 1);
          lcd.print (volume);

          Serial.print (text_volume_2);
          Serial.print (" ");
          Serial.print (volume / 1000);
          Serial.println ('\n');

          number_of_pump = (number_of_pump + 1);

          digitalWrite  (pin_prog_6, HIGH);
          delay (volume);
          digitalWrite  (pin_prog_6, LOW);
          delay (250);
        }
        else
        {
          lcd.setCursor (0, 2);
          lcd.print (text_Second_event);

          Serial.println (text_Second_event);

          digitalWrite (pin_alternative, HIGH);
          delay (1000);
          digitalWrite (pin_alternative, LOW);
        }

         banned = 0;

        break;
      }
    }
    
    else
    {
      lcd.clear ();
      lcd.setCursor (4, 0);
      lcd.print (text_mistake);
      
      Serial.println ('\n');
      Serial.print (text_mistake);
      Serial.println ('\n');
    }

    delay (1000);

  }
}
