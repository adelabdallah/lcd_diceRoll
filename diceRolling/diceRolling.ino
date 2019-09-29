/*
    User controlled dice rolling simulator. Select number of sides,
    between 2, 4, 6, 8, 12, 20, shows result, then resets.
*/


#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int ledPin = 13;

int sel_counter = 0; // how many times select button has been pressed during execution
int sides[] = {2, 4, 6, 8, 12, 20};
int i  = 0; // index for sides[]
int x = 0; // # of sides selected


int side_sel() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Num of sides");
  lcd.setCursor(0, 1);
  lcd.print(String(2));

  while (digitalRead(8) == LOW) {

    if (digitalRead(7) == HIGH && i < 5) {
      i += 1;
      delay(200);
    }
    else if (digitalRead(6) == HIGH && i >= 0) {
      i -= 1;
      delay(200);
    }
    if (i < 4) { // removes second character from display after select 12 or 20 then going down to 8 or lower
      lcd.setCursor(1, 1);
      lcd.print(" ");
      lcd.setCursor(0, 1);
    }
    if (i < 0) {
      i = 0;
      }
    lcd.print(String(sides[i]));
    lcd.setCursor(0, 1);
  }
  return sides[i];
}

void result(int x) {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Result");
  lcd.setCursor(0, 1);
  lcd.print(String(random(1, x + 1)));
}

void setup() {

  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);      //using onboard LED to signal beginning
  digitalWrite(ledPin, HIGH);   //and end of dice # selection process

  // setting switches as inputs
  pinMode(6, INPUT); // left switch
  pinMode(7, INPUT); // right switch
  pinMode(8, INPUT); // selector switch

  lcd.begin(16, 2); // # of columns & rows on LCD

  digitalWrite(ledPin, LOW);

  randomSeed(analogRead(13)); // set random seed based on noise from empty pin

  lcd.clear();
}

void loop() {

  if (sel_counter == 0) {
    x = side_sel();
    sel_counter++;
  }

  if (sel_counter == 1) {
    result(x);
    sel_counter = 0;
    x = 0;
    i = 0;
  }
  delay(1500);
  lcd.clear();
  randomSeed(analogRead(13));
}
