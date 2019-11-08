//function for printing to LCD in readable manner. Pass a string for each of 2 rows for 16x2 LCD display.
//message scrolls and reprint to allow enough time for human to read message before clearing
void displayPrint(String string1,String string2){

  String line_1 = string1;
  String line_2 = string2;

  lcd.setCursor(0,0);
  lcd.print(line_1);
  lcd.setCursor(0,1);
  lcd.print(line_2);
  delay(1000);

  //setting up iterating integer to scroll message
  int message_length = line_1.length();
  if(line_1.length() < line_2.length()){
    message_length = line_2.length();
  }

  //scroll left
  for(int position = 0 ; position < message_length ; position++){
    lcd.scrollDisplayLeft();
    delay(300);
  }

  delay(500);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print(line_1);
  lcd.setCursor(0,1);
  lcd.print(line_2);
  delay(1000);

  //scroll back left
  for(int position = 0 ; position < message_length / 3 ; position++){
    lcd.scrollDisplayLeft();
    delay(300);
  }

  delay(1000);
  lcd.clear();
  
}
