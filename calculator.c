#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <stdio.h>
#include <stdlib.h> 

LiquidCrystal_I2C lcd(32,16,2);

const byte numRows= 4; //number of rows on the keypad
const byte numCols= 4; //number of columns on the keypad
int cursorPos = 0;
String firstNum = "";
String secondNum = "";
char op;
double result = NULL;
bool operatorIn = false;
bool firstNumEnd = false;
bool secondNumEnd = false;


//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]= 
{
  {'1', '2', '3', '+'}, 
  {'4', '5', '6', '-'}, 
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {9,8,7,6}; //Rows 0 to 3
byte colPins[numCols]= {5,4,3,2}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

void setup()
{	
  pinMode(13, OUTPUT);
  lcd.begin(16,2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  Serial.begin(9600);
}

//If key is pressed, this key is stored in 'keypressed' variable
//If key is not equal to 'NO_KEY', then this key is printed out
//if count=17, then count is reset back to 0 (this means no key is pressed during the whole keypad scan process
void loop()
{
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY)
  {	
    if(keypressed == 'C'){
      clear();		
    }
    if (cursorPos == 0) {
      if (keypressed != '+' && keypressed != '-' && keypressed != '*' && keypressed != '/' && keypressed != 'C' && keypressed != '='){
        cursorPos += 1;
        lcd.print(keypressed);
        firstNum = keypressed;
      }
    }
    else if (cursorPos > 0 && cursorPos <= 4){
      if (keypressed != '+' && keypressed != '-' && keypressed != '*' && keypressed != '/' && keypressed != 'C' && keypressed != '='){
        if(!firstNumEnd && firstNum.length() < 3){
          firstNum += keypressed;
          cursorPos += 1;
          lcd.print(keypressed);
        }
        else if (!secondNumEnd && operatorIn){
          secondNum += keypressed;
          cursorPos += 1;
          lcd.print(keypressed);
        }
      }
      else if (keypressed == '+' || keypressed == '-' || keypressed == '*' || keypressed == '/'){
          if (!operatorIn){
          cursorPos += 1;
          lcd.print(keypressed);
          operatorIn = true;
          firstNumEnd = true;
          op = keypressed;
        }
      }
      else if (keypressed == '=' && secondNum.length()>0 && !secondNumEnd && result == NULL && firstNumEnd){
        cursorPos += 1;
		lcd.print(keypressed);
        secondNumEnd = true;
        Serial.println(keypressed);
        calculate();
        lcd.print(result, 1);
        digitalWrite(13, 1);

      }
    }
    else if (cursorPos > 4 && cursorPos <= 8){
      if (keypressed != '+' && keypressed != '-' && keypressed != '*' && keypressed != '/' && keypressed != 'C' && keypressed != '=' && !secondNumEnd && operatorIn && secondNum.length() < 3){
        cursorPos += 1;
        lcd.print(keypressed);
        secondNum += keypressed;       
      }
      else if (keypressed == '=' && secondNum.length()>0 && !secondNumEnd && result == NULL && firstNumEnd){
        cursorPos += 1;
        lcd.print(keypressed);
        secondNumEnd = true;
        Serial.println(keypressed);
        calculate();
        lcd.print(result, 1);
        digitalWrite(13, 1);
      }
    }
  } 
}

void clear(){
  digitalWrite(13, 0);
  lcd.clear();
  lcd.setCursor(0,0);
  cursorPos = 0;
  firstNum = "";
  secondNum = "";
  result = NULL;
  operatorIn = false;
  firstNumEnd = false;
  secondNumEnd = false;
}

void calculate(){
  double num1 = atof(firstNum.c_str());
  double num2 = atof(secondNum.c_str());
  Serial.println(num2 / num1);


  switch(op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if(num2 != 0) {
                 result = num1 / num2;
            }
    		else{
              clear();
              lcd.print("no zero division");
            }
            break;
  }
}