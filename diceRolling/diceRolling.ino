/* User controlled dice rolling simulator. Can roll up to 
10 dice, with 2, 4, 6, 8, 12, 20 sides. User selects
amount of dice to roll with buttons, then is prompted for the # of sides of 
dice x, returns its result, then asks for input of next die's sides.*/


#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int ledPin = 13;

int d_num = 1;
int sel_state = 0; //reading of selector switch (selects value)
int right_state = 0; // reading of right switch (increments by +1)
int left_state = 0; // reading of left switch (increments by -1)
int dice = 1;
int sides[] = {2, 4, 6, 8, 12, 20}; 
int i  = 0; //index for sides[]

int dice_sel(){
  if(digitalRead(7) == HIGH && d_num < 10){
      d_num += 1; //increments d_num +1 per right switch press, up to 10
      delay(100); // so button doesn't immediately increment to maximum value
     
      }
      else if(digitalRead(6) == HIGH && d_num > 1){
      d_num -= 1; //increments d_num -1 per left switch press
      delay(100); //so button doesn't immediately increment to minimum value
      
      }
    return d_num;
}

int side_sel(){
  if(digitalRead(7) == HIGH && i < 5){
    i += 1;
    delay(100);
  }
  else if(digitalRead(6) == HIGH && i > 0){
    i -= 1;
    delay(100);
  }
  return sides[i];
}
  
int how_many(int x){
  lcd.setCursor(0,0);
  lcd.print("How many dice");
  lcd.setCursor(0,1);
  lcd.print("to roll: " + String(x));
  if(x!=10){                //this gets rid of the zero in the (10,1) position on the LCD
    lcd.setCursor(10,1);    //after de-incrementing from 10
    lcd.print(' ');
  }
}

void setup() {

  pinMode(ledPin, OUTPUT);      //using onboard LED to signal beginning
  digitalWrite(ledPin, HIGH);   //and end of dice # selection process

  // setting switches as inputs
  pinMode(6, INPUT); // left switch
  pinMode(7, INPUT); // right switch
  pinMode(8, INPUT); // selector switch
  
  sel_state = digitalRead(8); //reading of selector switch
  right_state = digitalRead(7); // reading of right switch
  left_state = digitalRead(6); // reading of left switch
  
  lcd.begin(16, 2); // # of columns & rows on LCD

  while(digitalRead(8) ==  LOW){
    
    int x = dice_sel();
    int y = how_many(x);
    
    if(digitalRead(8) == HIGH){
      break;
    }
  }

  digitalWrite(ledPin, LOW);

  lcd.clear();
    
  while(sel_state == LOW){
    lcd.setCursor(0,0);
    lcd.print("Sides of die "+ String(dice));
    
    lcd.setCursor(0,1);
    lcd.print(String(side_sel()));
    if(i < 4){
      lcd.setCursor(1,1);
      lcd.print(" ");
    }
    
    delay(100);
  }

}

void loop() { 
  
}

