#include <Servo.h>

Servo servoLeft;                                                                          //Sätter en Servo till servoLeft
Servo servoRight;                                                                         //Sätter en Servo till servoRight
int adPin = 3;                                               
void goBack(int tid){                                                                     //Åker bakåt i (tid) antal mili sekunder 
    servoLeft.writeMicroseconds(1300);                                                    
    servoRight.writeMicroseconds(1700);
    delay(tid);                                                                           
}

void goForward(int tid){                                                                  //Åker framåt i (tid) antal mili sekunder 
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1300);
    delay(tid);
}
                                                                                          //Svänger höger i (tid) antal mili sekunder 
void goRight(int tid){
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1700);
   delay(tid);
} 
                                                                                          //Svänger vänster i (tid) antal mili sekunder 
void goLeft(int tid){
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1300);
   delay(tid);
}
                                                                        
void servAT() {                                                                            //Sätter motorerna till pin 13 och 12. 
  servoLeft.attach(13);                                           
  servoRight.attach(12);                                        
}

int irDetect(int irLedPin, int irReceiverPin, long frequency){                            //Metod med värden som man sätter in för att få ut ett annat värde. 
  tone(irLedPin, frequency, 8); // IRLED 38 kHz for at least 1 ms                         //Skickar ut en ton med de värden man sätter in i metoden
  delay(1); // Wait 1 ms                                                                  //Väntar i en milisekund
  int ir = digitalRead(irReceiverPin); // IR receiver -> ir variable                      //Sätter värdet från pinnen man läser av till ir
  delay(1); // Down time before recheck                                                   //Väntar i en milisekund
  return ir;                                                                              //Sänder ut (ir): 1 om den känner av något och 0 om inte
}


void setup() {                                                                            // Gör så att pin 7 och 10 att 
  servAT();
  pinMode(10,INPUT);                                                     
  pinMode(7,INPUT);                                                      
}


void loop() {                                                                       //huvud itterationens
int leftIR = irDetect(9, 10, 38000);                                                //till delar variabeln LeftIr värdet från metoden irDetect
int rightIR = irDetect(2, 3, 38000);                                                                              
float notIMP = (analogRead(adPin)) * 5.0 / 1024.0;                                 //Värdet från ljus sensorn tilldelas till ett notIMP
   if (notIMP < 0.3){                                                              //Om det är nog mörkt så åkter den bakåt och sedan vänster
    goBack(300);
    goLeft(200);
    }else if(leftIR == 0) {                                                        //Om vänstra ögat känner av något så åker den höger
    goRight(150); 
  } else if(rightIR == 0) {                                                        //Samma som den vänstra fast den åker åt vänster
    goLeft(150);
    } else {                                                                        //Annars åker roboten framåt. 
        goForward(20);
      }
  
  
  //Gamal kod
  
  /*
  byte whiskL = digitalRead(5);
  byte whiskR = digitalRead(7); 
 
    if((whiskL == 0) && (whiskR == 0)) {
    goBack(2000);
    goLeft(250);
  } else if (whiskL == 0){                                               // Om det vänstra morrhåret gör kontakt så backar roboten bakåt och svänger höger
    goBack(1000);
    goRight(250);
    } else if (whiskR == 0){                                             // Om det högra morrhåret gör kontakt så backar roboten bakåt och svänger vänster.
     goBack(1000);
     goLeft(250); 
    } else {                                                             // Om inget är true så åker den framåt.
      goForward(20);
    }
    */
}
