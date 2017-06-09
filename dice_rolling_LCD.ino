/* User controlled dice rolling simulator. Can roll up to 
10 dice, with 2, 4, 6, 8, 12, 20, or custom sides. User selects
amount of dice to roll with buttons, then is prompted for the # of sides of 
dice x, returns its result, then asks for input of next dice's sides.*/


#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int ledPin = 13;

int d_num;
int sel_state = 0; //reading of selector switch
int right_state = 0; // reading of right switch
int left_state = 0; // reading of left switch
int dice;

int dice_sel(){
  if(digitalRead(7) == HIGH && d_num <= 10){
      d_num += 1; //increments d_num +1 per right switch press, up to 10
      delay(100); // so button doesn't immediately increment to maximum value
      
      /*if(10 >= d_num){ 
      lcd.setCursor(9,1);
      lcd.print(String(d_num));*/ //prints incremented value to LCD if d_num <= 10
      }
      else if(digitalRead(6) == HIGH && d_num > 0){
      d_num -= 1; //increments d_num -1 per left switch press
      delay(100); //so button doesn't immediately increment to minimum value
      
      /*if(0 < d_num){
      lcd.setCursor(10,1);  
      lcd.print(" ");           //if 10 has been selected, pos (10, 1) on LCD 
      lcd.setCursor(9,1);       //will have a 0. Line 27 gets rid of the 0.
      lcd.print(String(d_num));*/ //prints value to LCD if d_num > 0
      }
    return d_num;
}

int how_many(int x){
  lcd.setCursor(0,0);
  lcd.print("How many dice");
  lcd.setCursor(0,1);
  lcd.print("to roll: ");
  lcd.setCursor(9,1);
  lcd.print(String(x));
}

/*int select_d_num(){
  if(right_state == HIGH && d_num <= 10){
      d_num += 1; //increments d_num +1 per right switch press, up to 10
      delay(100); // so button doesn't immediately increment to maximum value
      
      if(10 >= d_num){ 
      lcd.setCursor(9,1);
      lcd.print(String(d_num)); //prints incremented value to LCD if d_num <= 10
      }
      
    }
    else if(left_state == HIGH && d_num > 0){
      d_num -= 1; //increments d_num -1 per left switch press
      delay(100); //so button doesn't immediately increment to minimum value
      
      if(0 < d_num){
      lcd.setCursor(10,1);  
      lcd.print(" ");           //if 10 has been selected, pos (10, 1) on LCD 
      lcd.setCursor(9,1);       //will have a 0. Line 27 gets rid of the 0.
      lcd.print(String(d_num)); //prints value to LCD if d_num > 0
      }
    }
    else if(sel_state == HIGH){
      return d_num;
    }
  }*/


void setup() {

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  // setting switches as inputs
  pinMode(6, INPUT); // left switch
  pinMode(7, INPUT); // right switch
  pinMode(8, INPUT); // selector switch
  
  lcd.begin(16, 2); // # of columns & rows on LCD

  while(sel_state ==  LOW){
    int x = dice_sel();

    int y = how_many(x);
    if(digitalRead(8) == HIGH){
      break;
    }
  }

  digitalWrite(ledPin, LOW);

}

void loop() { 
  
  sel_state = digitalRead(8); //reading of selector switch
  right_state = digitalRead(7); // reading of right switch
  left_state = digitalRead(6); // reading of left switch

  if(sel_state == HIGH){
    lcd.clear();
    lcd.print("# of sides of");
    lcd.setCursor(0,1);
    lcd.print("first die: ");
   }
    
}

