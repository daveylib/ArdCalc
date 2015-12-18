#include <LiquidCrystal.h>
#include "pcf8574.h"
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
PCF8574 expander;

int state = 0;
// State 0 = start
// State 1 = first number
// State 2 = second number
int state_operation = 0;
// State operation 0 = null
// State operation 1 = sum
// State operation 2 = sub
// State operation 3 = mul
// State operation 4 = div

int curs = 0; // cursor position

int digit = 0; // digit position

bool error = false; // Too big number

long int number1[16]; // first number
long int number2[16]; // second number

int number1_length = 0; // length of first number
int number2_length = 0; // length of second number

// Key definitions

int keyExpander[8];
int keyArduino[7];

int keyExpanderValue[8];
int keyArduinoValue[7];

// Number pressed ?
int numberPressed()
{
    int num = 999;
    
    for( int i = 1; i <= 6; i++ )
        if( keyExpanderValue[i] == 0 )
            num = i-1;
    
    for( int i = 0; i <= 3; i++ )
        if( keyArduinoValue[i] == 1 )
            num = i+6;
    
    return num;
}

// Count precision
int countPrec(double b)
{
    int a = 7;
    char x2[16];
    dtostrf(b, 0, a-1, x2);
    
    for( a; a>1; a-- )
        if( (int)x2[a] >= 48 && (int)x2[a] <= 57 )
            if( x2[a] != '0' )
                break;
    
    return a-1;
}

// Combine all digits to final number
long int final( long int a[], int len ) {
    long int mnoznik = 1;
    long int suma = 0;
    
    for( int i = len; i >= 0; --i )
    {
        suma += a[i]*mnoznik;
        mnoznik *= 10;
    }
    
    if( ( error == false ) and ( suma >= 999999 ) )
        error = true;
    
    return suma;
}

void setup() {
    // Key definitions
    
    keyExpander[0] = 4; // ENTER - expander P4

    keyExpander[1] = 5; // 0 - expander P5
    keyExpander[2] = 6; // 1 - expander P6
    keyExpander[3] = 7; // 2 - expander P7
    keyExpander[4] = 1; // 3 - expander P1
    keyExpander[5] = 2; // 4 - expander P2
     keyExpander[6] = 3; // 5 - expander P3
    keyArduino[0] = 6;  // 6 - Arduino D6
    keyArduino[1] = 7;  // 7 - Arduino D7
    keyArduino[2] = 8;  // 8 - Arduino D8
    keyArduino[3] = 9;  // 9 - Arduino D9

    keyExpander[7] = 0; // SUM - expander P0
    keyArduino[4] = 14; // SUB - Arduino A0
    keyArduino[5] = 15; // MUL - Arduino A1
    keyArduino[6] = 16; // DIV - Arduino A2
  
    lcd.begin(16, 2);
    expander.begin(0x20);
    
    for( int i = 0; i < 8; i++ )
    {
        expander.pinMode( keyExpander[i], INPUT) ;
        expander.pullUp( keyExpander[i] );
    }
    
    for( int i = 0; i < 7; i++ )
        pinMode( keyArduino[i], INPUT );
    
    lcd.print("== Arduino");
    lcd.setCursor(0, 1);
    lcd.print("   Calculator ==");
}

void loop() {
    for( int i = 0; i < 8; i++ )
        keyExpanderValue[i] = expander.digitalRead( keyExpander[i] );
    
    for( int i = 0; i < 7; i++ )
        keyArduinoValue[i] = digitalRead( keyArduino[i] );
    
    // ### ENTER BUTTON ###
    
    if( keyExpanderValue[0] == 0 )
    {
        
        if( state == 0 )
        {
            state = 1;
            lcd.clear();
            lcd.print("First number:");
            error = false;
        }
        
        if( state == 2 )
        {
            state = 0;
            number2_length = digit-1;
            digit = 0;
            curs = 0;
            lcd.clear();
            
            long int k;
            double l;
            
            if( state_operation == 1 )
            {
                lcd.print("Addition:");
                lcd.setCursor(0,1);
                k = final(number1, number1_length) + final(number2, number2_length);
            }
            
            if( state_operation == 2 )
            {
                lcd.print("Subtraction:");
                lcd.setCursor(0,1);
                k = final(number1, number1_length) - final(number2, number2_length);
            }
            
            if( state_operation == 3 )
            {
                lcd.print("Multiplication:");
                lcd.setCursor(0,1);
                k = final(number1, number1_length) * final(number2, number2_length);
            }
            
            if( state_operation == 4 )
            {
                lcd.print("Division:");
                lcd.setCursor(0,1);
                l = (double)final(number1, number1_length) / (double)final(number2, number2_length);
            }
            
            if( !error )
                if( state_operation == 4 )
                    lcd.print( l, countPrec(l) );
                else
                    lcd.print( k );
            else
                lcd.print("error");
            delay(300);
            
            state_operation = 0;
        }
    }
    
    // ### NUMBERS ###
    
    if( numberPressed() != 999 )
    {
        if( state == 1 or state == 2 )
        {
            if( digit < 16 )
            {
                int num = numberPressed();
                
                lcd.setCursor(curs, 1);
                lcd.print(num);
                curs++;
                
                if( state == 1 ) // FIRST NUMBER
                    number1[digit] = num;
                else if ( state == 2 ) // SECOND NUMBER
                    number2[digit] = num;
                
                digit++;
            }
        }
    }
    
    // ### OPERATIONS ###
    
    if( keyExpanderValue[7] == 0 or keyArduinoValue[4] == 1 or keyArduinoValue[5] == 1 or keyArduinoValue[6] == 1 )
    {
        if( state == 1 )
        {
            if( keyExpanderValue[7] == 0 ) // ADDITION
                state_operation = 1;
            
            if( keyArduinoValue[4] == 1 ) // SUBTRACTION
                state_operation = 2;
            
            if( keyArduinoValue[5] == 1 ) // MULTIPLICATION
                state_operation = 3;
            
            if( keyArduinoValue[6] == 1 ) // DIVISION
                state_operation = 4;
            
            state = 2;
            lcd.clear();
            lcd.print("Second number:");
            number1_length = digit-1;
            digit = 0;
            curs = 0;
        }
    }
    
    // ### WAIT ###
    
    if( state != 0 )
        delay(200);
}
