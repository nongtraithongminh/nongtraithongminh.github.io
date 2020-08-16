
#include <Wire.h> 
#include <Servo.h>  
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2); 
#include "DHT.h"           
#include <IRremote.h> // thư viện hỗ trợ IR remote 
const int DHTPIN = 2;       //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11;  //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
int tam=0;
Servo myservo;
int servoPin = 9;       // Khai báo chân điều khiển servo
 
DHT dht(DHTPIN, DHTTYPE);
int nhietdoset=25;
#include <IRremote.h>

/*Edit these settings*/
//Password and security
String pass = "1234"; //Password to unlock. be sure to edit the '5' inside '[]' to password length +1.
int chances = 3; //Chances before buzzer will start to buzz continuously.
bool afterChances = true; 
int RECV_PIN = 11; //IR Reciever pin (PWM).

//remote buttons
String btn1 = "ff30cf"; //Your button 1 IR HEX code (in lower case). eg.: ff63ad
String btn2 = "ff18e7"; //Your button 2 IR HEX code (in lower case).
String btn3 = "ff7a85";
String btn4 = "ff10ef";
String btn5 = "ff38c7";
String btn6 = "ff5aa5";
String btn7 = "ff42bd";
String btn8 = "ff4ab5";
String btn9 = "ff32ad";
String btn0 = "ff6897";
String btnReset = "ffa25d"; //Your Reset button IR hex code.

bool locked = true;
String cPass = "";
int chance = 0;
String cmp = "password:";
IRrecv irrecv(RECV_PIN);
decode_results results;
int Analog=0;
void setup() {
  
  irrecv.enableIRIn();
  Serial.begin(9600);
  myservo.attach(servoPin);
  
  

  lcd.init();       
  irrecv.enableIRIn(); // start the IR receiver             
  lcd.backlight();
  Serial.begin(9600);
  dht.begin();         // Khởi động cảm biến
  lcd.print(cmp);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(A0, INPUT);
  pinMode(12, OUTPUT);
  myservo.write(0);
}

void loop() {
    digitalWrite(12,1);
    if (irrecv.decode(&results)) {
     

      if (String(results.value, HEX) == btn1) {
        Serial.print("1");
        updatePass("1");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btn2) {
        Serial.print("2");
        updatePass("2");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btn3) {
        Serial.print("3");
        updatePass("3");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btn4) {
        Serial.print("4");
        updatePass("4");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btn5) {
        Serial.print("5");
        updatePass("5");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btn6) {
        Serial.print("6");
        updatePass("6");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btn7) {
        Serial.print("7");
        updatePass("7");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btn8) {
        Serial.print("8");
        updatePass("8");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btn9) {
        Serial.print("9");
        updatePass("9");
      }
      else if (String(results.value, HEX) == btn0) {
        Serial.print("0");
        updatePass("0");
        lcd.print("*");
      }
      else if (String(results.value, HEX) == btnReset) {
        resetPass();
        Serial.println("\nRESET");
        lcd.clear();
        lcd.print("RESET");
        delay(1000);
        lcd.clear();
        lcd.print("PASSWORD:");
      }
      irrecv.resume(); // Receive the next value
    }
    if (chance > chances)
     // digitalWrite(buzzer, HIGH);//buzzer

    if (locked == true) {
     // digitalWrite(redLed, HIGH);
     // digitalWrite(greenLed, LOW);
    }
    else {
     // digitalWrite(redLed, LOW);
      //digitalWrite(greenLed, HIGH);
    }
}

bool updatePass(String ch) {
  if (locked == false)
    return false;
  //beep();
  if (updatable() == true) {
    cPass += ch;
    if (cPass.length() < pass.length()) {

    }
    else {
      if (pass == cPass) {
        delay(500);
        lcd.clear();
        digitalWrite(12,0);
        lcd.print("OPEN DOOR");
        //myservo.write(90);
        delay(3000);
        lcd.clear();
        digitalWrite(12,1);
        lcd.print("CLOSE DOOR");
        delay(500);
        myservo.write(0);
        locked = false;
        chance = 0;
        Serial.println("\nUNLOCKED");
        while(1)
        {
                      digitalWrite(12,1);
                      int value = analogRead(A0);
                      int h = dht.readHumidity();    //Đọc độ ẩm
                      int t = dht.readTemperature(); //Đọc nhiệt độ
                      lcd.setCursor(0,0);
                      lcd.print("t: ");
                      lcd.print(t);               //Xuất nhiệt độ
                      lcd.setCursor(0,1);
                      lcd.print("h: ");
                      lcd.print(h);               //Xuất độ ẩm
                      lcd.setCursor(8,0);
                      lcd.print("t set");
                      lcd.setCursor(8,1);
                      lcd.print(nhietdoset);
                      if (irrecv.decode(&results)) // nếu nhận được tín hiệu
                      {
                          lcd.clear();
                          switch(results.value)
                          {
                              
                            case 0xFFA857: 
                                           
                                            
                                            nhietdoset++;
                                            break;
                                     
                            case 0xFFE01F:  
                                            
                                            nhietdoset--;
                                            break;
                            case 0xFFE21D:
                                   
                                             asm volatile ( "jmp 0");
                                             break;
                            case 0xFFC23D:
                                              lcd.clear();
                                              lcd.print("OPEN DOOR");
                                              digitalWrite(12,0);
                                              
                                              delay(500);
                                             
                                              lcd.clear();
                                              break;
                                              
                             case 0xFF02FD:
                                              lcd.clear();
                                              digitalWrite(12,1);
                                              lcd.print("CLOSE DOOR");
                                              
                                              delay(500);
                                              lcd.clear();
                                              break;
                                            
                                     
                          }
                        
                        Serial.println(results.value, HEX);
                        delay(200);
                        irrecv.resume(); // nhận giá trị tiếp theo
                      }
                      if(t<=nhietdoset)
                      {
                        digitalWrite(7,1);   
                        digitalWrite(8,0);
                        
                      }
                      else
                      {
                         digitalWrite(7,0);
                         digitalWrite(8,1);
                      }
                      /*if (Analog >515 )
                      {
                       digitalWrite (12, HIGH);
                      }
                      else
                      {
                      digitalWrite (12, LOW);
                      } 
                      //Serial.println(analogRead(A0));
                      
                      /*if(tam==10)
                      {
                      lcd.setCursor(11,1);
                      lcd.print(analogRead(A0));
                      Analog=analogRead(A0);
                      tam=0;
                      }
                      tam++;*/
                      
        }
      }
      else {
        cPass = "";
        chance += 1;
        Serial.println("\nWRONG PASSWORD!");
      }
    }
  }
}

bool updatable() {
  if (chance <= chances)
    return true;
  return afterChances;
}

void resetPass() {
  cPass = "";
  locked = true;
}
