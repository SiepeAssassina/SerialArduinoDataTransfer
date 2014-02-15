#include <LiquidCrystal.h>
#define IDLE 0x0
#define READING_DATA 0x1
#define DATA_END 0x2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  lcd.begin(16, 2);
  Serial.begin(115200);
}
byte ca[8] = {
  '=', '=', '=', '=', '=', '=', '=', '='};
int state = 0x0;
void loop() 
{
  Serial.flush();
  if(Serial.read() == 'R')  //RQT
  {    
    lcd.clear();
    lcd.write("RQT");
    lcd.clear();
    Serial.write('A');      //ACK
    lcd.write("WAITING..."); 
    while(Serial.available() == 0) ;      
    while(state != DATA_END) 
    {       
      switch (Serial.read())
      {
      case 'D':
        if(state == IDLE)
         for(int i = 0; i < 8; i++)
         ca[i] = ' ';
        state = READING_DATA; 
        Serial.write('A');
        lcd.setCursor(0, 0);
        lcd.clear();
        lcd.write("DATA");          
        while(Serial.available() < 2) ;
        ca[Serial.read()] = Serial.read();    
        delay(100);        
        break;
      case 'C':
        lcd.clear();
        break;
      case 'S':
        state = DATA_END;
        break;
      } 
    }
    lcd.clear();
    lcd.write("DATA_END");
    state = IDLE;
    lcd.clear();
    lcd.write("WRITING");
    for(int i = 0; i < 8; i++)
    {
      lcd.setCursor(i, 1);
      lcd.write(ca[i]);
    }
  }
}




