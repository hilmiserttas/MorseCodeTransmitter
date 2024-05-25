#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define EMITTER_PIN D0
#define BUZZER_PIN D7
#define UNITTIME 100



#define LCD_MAX_COLS 16
#define LCD_MAX_ROWS  2

// Morse code timings 
int DOT = 1 * UNITTIME;
int DASH = 3 * UNITTIME;
int INTERSYMBOL = 1 * UNITTIME; 
int INTERLETTER = 3 * UNITTIME;
int INTERWORD = 7 * UNITTIME;


LiquidCrystal_I2C lcd(0x27,LCD_MAX_COLS,LCD_MAX_ROWS);  

/* current cursor position */
int8_t LCD_cursor_col = 0;
int8_t LCD_cursor_row = 0;
String emptyLine = "";


String message = "HELLO MIS";

const char* MorseTable[] = {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, /* ASCI 0-31 has no MORSE code*/
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,        
        /*SPACE*/ NULL, /*!*/ "-.-.--", /*"*/ ".-..-.", /*#*/ NULL, /*$*/ "...-..-", /*%*/ NULL, /*&*/ ".-...", /*'*/ ".----.",
        /*(*/ "-.--.", /*)*/ "-.--.-", /***/ NULL, /*+*/ ".-.-.", /*,*/ "--..--", /*-*/ "-....-", /*.*/ ".-.-.-", /*/*/ "-..-.",
        /*0*/ "-----", /*1*/ ".----", /*2*/ "..---", /*3*/ "...--", /*4*/ "....-", /*5*/ ".....", /*6*/ "-....", /*7*/ "--...",
        /*8*/ "---..", /*9*/ "----.", /*:*/ "---...", /*;*/ "-.-.-.", /*<*/ NULL, /*=*/ "-...-", /*>*/ NULL, /*?*/ "..--..",
        /*@*/ ".--.-.", /*A*/ ".-", /*B*/ "-...", /*C*/ "-.-.", /*D*/ "-..", /*E*/ ".", /*F*/ "..-.", /*G*/ "--.",
        /*H*/ "....", /*I*/ "..", /*J*/ ".---", /*K*/ "-.-", /*L*/ ".-..", /*M*/ "--", /*N*/ "-.", /*O*/ "---", 
        /*P*/ ".--.", /*Q*/ "--.-", /*R*/ ".-.", /*S*/ "...", /*T*/ "-", /*U*/ "..-", /*V*/ "...-",/*W*/ ".--",
        /*X*/ "-..-", /*Y*/ "-.--", /*Z*/ "--.."};


void setup() {  
  pinMode(EMITTER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Wire.begin(4,5,400000U);
  lcd.init();                      
  lcd.backlight();
  
  Serial.begin(115200);


  lcd.setCursor(0,0);
  lcd.print("Morse Code Trans");
  lcd.setCursor(0,1);
  lcd.print("mitter v1.0 :)");  
  delay(2500);
  lcd.clear();  
  lcd.setCursor(0,0);


 
  // send the message
  
  //tone(BUZZER_PIN, 440, DOT);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(DOT);
  digitalWrite(BUZZER_PIN, LOW);

  lcd.clear();
  resetCursor();
  for(int i=0;i<LCD_MAX_COLS;i++){
    emptyLine = emptyLine+' ';
  }
  
  lcd.print("Ready to send");
  delay(500);     
  message = "";    

      
  
}

void resetCursor(){
  lcd.setCursor(0,0);
  LCD_cursor_col=0;
  LCD_cursor_row=0;
}

void increaseLCDCursor(){
  
  LCD_cursor_col ++;
  if(LCD_cursor_col>=LCD_MAX_COLS){
    LCD_cursor_col = 0;
    LCD_cursor_row++;
    if(LCD_cursor_row>=LCD_MAX_ROWS)
      LCD_cursor_row = 0;
    lcd.setCursor(LCD_cursor_col,LCD_cursor_row);    
    lcd.print(emptyLine);
      
    
  }
  lcd.setCursor(LCD_cursor_col,LCD_cursor_row);      
}

void increaseLCDLine(){
  int LCD_cursor_row_save = LCD_cursor_row;
  while(LCD_cursor_row_save == LCD_cursor_row)  
    increaseLCDCursor();
}

void loop() { 
  message = "";
  while (Serial.available()){
    char chr = Serial.read();
    message = message + chr;
    delay(10);
  }
  message.trim();
  if (message!=""){
    sendMessage(message);  
    increaseLCDLine(); 
    lcd.print("Message sent");
  }
  delay(1);

  
}

void sendMessage(String message)
{
  lcd.clear();
  resetCursor();
  
  Serial.print("Sending message: [");Serial.print(message); Serial.println("]");    
  for (int i=0;i< message.length(); i++){
    char ch = message[i];  
    
    if (ch==' '){
      Serial.print("["); Serial.print(ch); Serial.println("]: [ ]"); 
      lcd.write(ch);
      increaseLCDCursor();
      sendSpace();
    }
    else if (ch<92 && ch>32) {
      Serial.print("["); Serial.print(ch); Serial.print("]: [");  
      lcd.write(ch);
      increaseLCDCursor();
      sendChar(MorseTable[ch]);    
    }
    else {
      Serial.println("[Unknown char]:[]");  
    }

    if(ch!=' ')
      delay(INTERLETTER-INTERSYMBOL);        
  }    
  
  delay(1000);
  
}

void sendChar(const char * morseCode) 
{
 
  int i = 0;
  while(morseCode[i] != 0)
  {    if(morseCode[i] == '.'){
      sendDot();
    } else if (morseCode[i] == '-'){
      sendDash();
    }
    i++;
  }
  Serial.print(morseCode);
  Serial.println("]");
}


void sendDot()
{
  digitalWrite(EMITTER_PIN, HIGH);  
  //tone(BUZZER_PIN, 440, DOT);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(DOT);
  digitalWrite(EMITTER_PIN, LOW); 
  //noTone(BUZZER_PIN);
  digitalWrite(BUZZER_PIN, LOW);  
  delay(INTERSYMBOL);
}

void sendDash()
{
  digitalWrite(EMITTER_PIN, HIGH);  
  //tone(BUZZER_PIN, 440, DOT);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(DASH);
  digitalWrite(EMITTER_PIN, LOW); 
  //noTone(BUZZER_PIN);
  digitalWrite(BUZZER_PIN, LOW);  
  delay(INTERSYMBOL);
} 

void sendSpace()
{
  delay(INTERWORD - INTERLETTER);
  
} 
