/*CAT FEEDING arduino    */#include<Servo.h>      //include servo library#include<LiquidCrystal.h>  //include lcd displayLiquidCrystal lcd (8,9,4,5,6,7);  //set up lcd inputServo myPointer;   //initialise servoint lcd_key =0;int press =0;#define RIGHTbtn  0#define UPbtn     1#define DOWNbtn   2#define LEFTbtn   3#define SELECTbtn 4#define NONEbtn   5            //define keypad buttonsbool rightSide = true;int servoPin =2;int servoDelay = 50;int hour =0;int min =0;int press_buttons(){  press = analogRead(0);               //detecting which keypad button activated  if (press<50) return RIGHTbtn;  if (press<195) return UPbtn;  if (press<380) return DOWNbtn;  if (press<555) return LEFTbtn;  if (press<790) return SELECTbtn;  return NONEbtn;}void setup() {  lcd.begin(16,2);  lcd.clear();  lcd.setCursor(0,0);             lcd.print("Set time");              //display "set time" on the first row of the LCD  lcd.setCursor(0,1);  lcd.print("to feed the cat!");      //display "to feed the cat on the second row of the LCD"  printTime();                      //call the printTime method}void loop() {  setTime();}void printTime()                     //print hour and minute in a "hh:mm" format on a LCD screen{  lcd.setCursor(11,0);  if(hour<10)  {    lcd.print("0");   lcd.print(hour,DEC);            }  else  lcd.print(hour,DEC);    lcd.print(":");    if(min<10)  {   lcd.print("0");   lcd.print(min,DEC);  }  else  lcd.print(min,DEC);}void setTime()                         //this method allows users to set time {  lcd_key = press_buttons();    if (lcd_key == RIGHTbtn)              {    rightSide=true;  }  if (lcd_key == LEFTbtn)  {    rightSide=false;  }  if(lcd_key == UPbtn)                   //press one increase one hour/minute  {    if(rightSide==true)                   //if detect users press right button, set minutes     {        if (min<60){                       //maximum 59 minutes          delay(500);        min=min+1;}        else min=0;    }    if(rightSide==false)                 //if detect users press left button, set hours    {      if(hour<24){                      //maximum 23 hours        delay(500);      hour=hour+1;}      else hour=0;    }  }  if(lcd_key==DOWNbtn)                  //press one decrease one hour/minute  {    if(rightSide==true){                //if detect users press right button, set minutes      if (min>0){        delay(500);      min=min-1;}      else min=0;    }    if(rightSide==false) {              //if detect users press left button, set hours      if(hour>0){        delay(500);      hour=hour-1;}      else hour=0;    }  }  if (lcd_key == SELECTbtn)             // if press select button, start the countdown  {      countDown(hour, min);  }  printTime();                         //print time on LCD}void countDown(int H, int M){int S = 0;            // count seconds lcd.clear();   lcd.setCursor(0,0); lcd.print("Set time");  lcd.setCursor(6,1); lcd.print(":"); lcd.setCursor(9,1); lcd.print(":");   while(S>0 || M>0 || H>0){        //set the count down system: if the seconds count down to zero, S--;                             //minutes -1, seconds back to 59, when minutes down to zero, delay(5);                        //hours -1, when hours down to zero, minutes activates back to 59   if(S<0)                          //and so forth until hours/minutes/seconds all countdown to zero { M--; S=59; } if(M<0) { H--; M=59; } if(H<0) { M=59; S=59; }  if(M>9) { lcd.setCursor(7,1); lcd.print(M); } else { lcd.setCursor(7,1); lcd.print("0");  lcd.setCursor(8,1); lcd.print(M); lcd.setCursor(9,1); lcd.print(":"); }   if(S>9) { lcd.setCursor(10,1); lcd.print(S); } else { lcd.setCursor(10,1); lcd.print("0");  lcd.setCursor(11,1); lcd.print(S); lcd.setCursor(12,1); lcd.print(" "); }   if(H>9) { lcd.setCursor(4,1); lcd.print (H); } else { lcd.setCursor(4,1); lcd.print("0");  lcd.setCursor(5,1); lcd.print(H); lcd.setCursor(6,1); lcd.print(":");}}if(H==0 && M==0)                        //when countdown is finished, activate servo, servo turns 80 degrees     {                                  //and turns back so that the cat food can be dispensed      for(int i=20; i<=100;i++)      {        myPointer.attach(servoPin);        myPointer.write(i);        delay(servoDelay);      }      myPointer.detach();    }}