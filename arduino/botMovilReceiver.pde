#include <Spi.h>
#include <mirf.h>
#include <nRF24L01.h>

#define INPUT_A 2
#define INPUT_B 4
#define INPUT_C 8
#define INPUT_D 7

#define PWM_1 3
#define PWM_2 5


//motors velocity
int velocity=220;

void SetNewVelocity(int newVelocity){
  velocity=newVelocity;
}

void SetVelocity(){
  analogWrite(PWM_1,velocity);
  analogWrite(PWM_2,velocity);
}


void StopMotors(){
 digitalWrite (INPUT_A, LOW); 
 digitalWrite (INPUT_B, LOW);
 digitalWrite (INPUT_C, LOW);   
 digitalWrite (INPUT_D, LOW); 
}

void FastStop(){
 digitalWrite (INPUT_A, HIGH); 
 digitalWrite (INPUT_B, HIGH);
 digitalWrite (INPUT_C, HIGH);   
 digitalWrite (INPUT_D, HIGH);
}


void TurnRight(){
 digitalWrite (INPUT_A, HIGH); 
 digitalWrite (INPUT_B, LOW);
 digitalWrite (INPUT_C, HIGH); 
 digitalWrite (INPUT_D, LOW);
}


void TurnLeft(){
 digitalWrite (INPUT_A, LOW); 
 digitalWrite (INPUT_B, HIGH);
 digitalWrite (INPUT_C, LOW); 
 digitalWrite (INPUT_D, HIGH);
}
 
void GoStraight(){
 
 digitalWrite (INPUT_A, HIGH); 
 digitalWrite (INPUT_B, LOW); 
 digitalWrite (INPUT_C, LOW); 
 digitalWrite (INPUT_D, HIGH); 
}

void GoDown(){

}




 
void setup(){  
  Serial.begin(9600);
  
  //PWM & H-bridge
  pinMode (INPUT_A, OUTPUT); 
  pinMode (INPUT_B, OUTPUT); 
  pinMode (INPUT_C, OUTPUT); 
  pinMode (INPUT_D, OUTPUT);  
  pinMode (PWM_1, OUTPUT);   
  pinMode (PWM_2, OUTPUT); 
    
  
  //radio RX
  Mirf.csnPin = 9;
  Mirf.cePin =6;
  Mirf.init();
  byte rx_addr[5] = {0x41, 0x49, 0x53, 0x4F, 0x59};
  Mirf.setRADDR(rx_addr);
  Mirf.payload = 1;
  Mirf.channel = 64;
  Mirf.config();  
  Mirf.configRegister(RF_SETUP, 0x07); //Air data rate 1Mbit, 0dBm, Setup LNA
  Mirf.configRegister(EN_AA, 0x00); //Disable auto-acknowledge
  Mirf.configRegister(SETUP_RETR, 0x00);
  Mirf.configRegister(CONFIG, 0x4B);
  Mirf.flushRx();
  
} 

 
void loop() {
  
  byte c=0;
  
  if(Mirf.dataReady()){
	Mirf.getData(&c);
        Serial.println(c);
        
        
        switch(c){
         case 'u':
            Serial.print("UP movement, vel=");
            Serial.println(velocity);
            SetVelocity();
            GoStraight(); 
            delay(1000);
            SetVelocity();
            FastStop();
         break;
        
         
         case 'd':
         break;
         
         case 'l':
            Serial.print("LEFT movement, vel=");
            Serial.println(velocity);
            SetVelocity();
            TurnLeft();
            delay(1000);
            SetVelocity();
            FastStop();
         break;
         
         case 'r':
            Serial.print("RIGHT movement, vel=");
            Serial.println(velocity);
            SetVelocity();
            TurnRight();
            delay(1000);
            SetVelocity();
            FastStop();
         break;  
   
   
         case 's':
            //Serial.print("STOP");
            SetVelocity();
            FastStop();
         break;   
     
     
         default:
           int vel=(int)c;
           Serial.print("Nueva velocidad: ");
           Serial.println(vel);
           SetNewVelocity(vel);  
       }
   
  }
  
  delay(50);
  c=0;
  
} 

