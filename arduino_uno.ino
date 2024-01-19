#include <LiquidCrystal.h>
#define LOOP_DELAY 1000
#define ENERGY_BUTTON_PIN 8

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
const String headers[3] = {"Temperatura:","Tryb:", "Kolor:"};
String data[3];
int show_count = 0;

//funkcja pobierająca dane z NMCU 
//TODO
void get_furnace_data(){
  data[0] = "25";
  data[1] = "Pulse";
  data[2] = "#000000";
}

//funkcja wyświetlająca dwie linie 
void show(String first_line, String second_line){
  lcd.clear();
  if(second_line=="") second_line="            ";
  if(first_line=="") first_line="            ";

  lcd.setCursor(0,0);
  lcd.print(first_line);

  lcd.setCursor(0, 1);
  lcd.print(second_line);
}


//funkcja przesuwająca cały tekst w lewo 'duration' ilość razy
void scroll(int duration){
  for(int i = 0 ; i < duration; i++){
    for (int positionCounter = 0; positionCounter < 13; positionCounter++) {
      lcd.scrollDisplayLeft();
      delay(LOOP_DELAY);
    }
  }
}

//Funkcja updatująca rzeczy z servera i incrementująca w mod3 show_count
void next(){
    get_furnace_data();
    if(show_count==2) show_count = 0;
    else show_count++;
}

void setup() {
  Serial.begin(9600); // TODELETE
  //ustawianie wymiarów wyświetlacza
  lcd.begin(16, 2);
  //ustawianie pina do przycisku dodającego energię
  pinMode(ENERGY_BUTTON_PIN, INPUT);
  //inicjalizowanie danych
  get_furnace_data();
}

//TODO
//funkcja wysyłająca 
void add_energy_usage(int value){
  Serial.write("Done\n"); 
}


void loop() {
  //jeśli nacisnięty guzik to dodaje energie
  if(digitalRead(ENERGY_BUTTON_PIN)==HIGH) add_energy_usage(100);
  else  Serial.write("Not Done\n"); //TODELETE
  next();
  delay(2000);
  show(headers[show_count], data[show_count]);
}
