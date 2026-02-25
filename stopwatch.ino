#include <LiquidCrystal.h>
#include <LiquidCrystal.h>
#define btnUP     1
#define btnDOWN   2
#define btnNONE   5
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);        // select the pins used on the LCD panel
int lcd_key     = 0;
int adc_key_in  = 0;

unsigned long starting, finished, elapsed;
void setup()
{
  lcd.begin (16,2);
  lcd.setCursor (0,0);
}
int readButtons()
{
  adc_key_in = analogRead(0);       // read the value from the sensor
  lcd.setCursor(12,1);              //Display analogue value on Pin A0
  lcd.print(adc_key_in);
  lcd.print("   ");
  if (adc_key_in < 250 && adc_key_in > 144 )  return btnUP;
  else if (adc_key_in < 450 && adc_key_in > 251)  return btnDOWN;
  else return btnNONE;
}
void loop()
{
float h, m, s, ms;
  int m1, m2, s1, s2, ms1, ms2, ms3;
  unsigned long over;
  finished = millis();
  elapsed = finished - starting;

h = int(elapsed / 3600000);
  over = elapsed % 3600000;
  m = int(over / 60000);
  over = over % 60000;
  s = int(over / 1000);
  ms = over % 1000;
  
lcd.setCursor(0, 0); //displays each unit on the lcd screen
lcd.print(h);
lcd.setCursor(3, 0);
lcd.print(m);
lcd.setCursor(6, 0);
lcd.print(s);
lcd.setCursor(9, 0);
lcd.print(ms);
lcd_key = readButtons();

switch (lcd_key){
case btnDOWN:{      //resets the stopwatch 
if (digitalRead(2) == HIGH) 
{
starting = millis();
delay(200);                // for debounce
}  
break;
}
case btnUP:{    //pauses the stopwatch for 5 seconds and continues
if (digitalRead(1) == HIGH) 
{
finished = millis();
delay(5000);}
break;}
case btnNONE:{
break;
}}}


