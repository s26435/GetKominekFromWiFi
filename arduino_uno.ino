#include <LiquidCrystal.h>
#define LOOP_DELAY 1000
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




void show(String first_line, String second_line){
  if(second_line=="") second_line="            ";
  lcd.setCursor(0,0);
  lcd.print(first_line);
  lcd.setCursor(0, 1);
  lcd.print(second_line);
  delay(LOOP_DELAY);
}
void scroll(int duration){
  for(int i = 0 ; i < duration; i++){
    for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(LOOP_DELAY);
    }
  }
}


void setup() {
  lcd.begin(16, 2);
}

void loop() {
  lcd.clear();
  show("Dupa hehe", "");
  delay(1000);
  lcd.clear();
  show("Klobus => zycie na krawedzi :DDD","");
  scroll(2);
}

