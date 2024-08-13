#include <LiquidCrystal.h>
#include <Servo.h>

// Declaring constants for the LCD pins
const int rs = 12, en = 11, d4 = 8, d5 = 7, d6 = 6, d7 = 5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Servo myservo1;

//choose the input pin for entry gate IR sensors
int ir_s1 = 2;
int ir_s2 = 4;

//choose the input pin for parking slot IR sensors
int ir_p_1 = 13;
int ir_p_2 = 9;
int ir_p_3 = 10;

int total = 0;
int slot = 3; // Total capacity of the parking 
int flag1 = 0;
int flag2 = 0;

int s1 = 0, s2 = 0, s3 = 0;

void setup()
{
    Serial.begin(9600);  // Initializing the Serial Monitor
    
    //declare sensor as input
    pinMode(ir_s1, INPUT);
    pinMode(ir_s2, INPUT);
    pinMode(ir_p_1, INPUT);
    pinMode(ir_p_2, INPUT);
    pinMode(ir_p_3, INPUT);

    myservo1.attach(3);   // attaches the servo on pin 3 to the servo object
    myservo1.write(180);

    lcd.begin(16, 2); //Initializing the Lcd display
    lcd.print("Smart Parking"); // Initial message display on the screen
    delay(5000);  //It will provide the delay of 5000 milliseconds
    lcd.clear();  // after delay clearing the lcd display
}

void loop()
{

    read_sensor();
   
   /* When working with a 16x2 LCD display, it means you can write up to 16 characters horizontally and have 2 rows. 
       The indexing for these rows and characters starts from 0. 
   */ 
   lcd.setCursor(0, 0);  
    lcd.print("Have Slots:");
    lcd.print(slot);

    lcd.setCursor(0, 1);
    if (s1 == 1) {
        lcd.print("s1:F");
    }
    else {
        lcd.print("s1:E");
    }

    lcd.setCursor(5, 1);
    if (s2 == 1) {
        lcd.print("s2:F");
    }
    else {
        lcd.print("s2:E");
    }

    lcd.setCursor(10, 1);
    if (s3 == 1) {
        lcd.print("s3:F");
    }
    else {
        lcd.print("s3:E");
    }
    
   // Here the logic begins for opening and closing the gate i.e. servo motor
    if (digitalRead(ir_s1) == 0 && flag1 == 0)
    {

        if (slot > 0)
        {
            flag1 = 1;
            if (flag2 == 0) 
             {
                myservo1.write(90);
                slot = slot - 1;
            }
        }
        else 
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Parking ");
            lcd.setCursor(0, 1);
            lcd.print("Full ");
            // delay(5000);
            delay(1500);
        }
   }
   
    if (digitalRead(ir_s2) == 0 && flag2 == 0) 
    {
        flag2 = 1;
        if (flag1 == 0) 
        {
            myservo1.write(90);
            slot = slot + 1;
        }
     }
    if (flag1 == 1 && flag2 == 1) 
    {
        delay(1000);
        myservo1.write(180);
        flag1 = 0;
        flag2 = 0;
    }
    delay(10);
  }
 
void read_sensor() //function for keeping track of the parking slots status 
{
    s1 = 0, s2 = 0, s3 = 0;
    if (digitalRead(ir_p_1) == 0) {
        s1 = 1;
    }
    if (digitalRead(ir_p_2) == 0) {
        s2 = 1;
    }
    if (digitalRead(ir_p_3) == 0) {
        s3 = 1;
    }
}