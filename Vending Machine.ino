#include <Arduino.h>
int motores[15] = {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
int sensores[4] = {2,3,4,5};
int leituras[4] = {2,3,4,5};
int sensores_status_leitura=1;
int NUMERO_MOTOR=0;
int ESTADO_SENSOR=0;
 

void AcionaMotor(int motor, int LigaDesliga){
  
       if(motor > 5 and motor < 21){
        digitalWrite(motor, LigaDesliga);
      Serial.print("MOTOR: ");  
      Serial.print(motor); 
      if(LigaDesliga==1){
        Serial.println(" Acionado");
      }else{
       Serial.println(" Desligado"); 
        }
     }      
 }

void iniciaTudo(){
  NUMERO_MOTOR=0;
  ESTADO_SENSOR=0;
  Serial.println("resetou variaveis");
  }
 
void setup(){
Serial.begin(9600);
// pinos sensores
pinMode(2, INPUT);
pinMode(3, INPUT);
pinMode(4, INPUT);
pinMode(5, INPUT);
// pinos motores 
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);

}

void loop(){   
//
     for(int i=0; i<4; i++) {
     leituras[i]=digitalRead(i+2);
      }

   Serial.println("Digite o motor: ");
   delay(1500); 
   do{
     if(Serial.available()){
       NUMERO_MOTOR = Serial.parseInt();
       Serial.read();
       break;
     }
   }while(true);
   AcionaMotor(NUMERO_MOTOR,HIGH);

     do{
    
       for(int i=0; i<4; i++) {
     
       sensores_status_leitura=digitalRead(i);
       Serial.println(i);   
       Serial.println(sensores_status_leitura); 
 
       if(leituras[i]!=digitalRead(i+2)){
       Serial.println("detectou algo:");
       ESTADO_SENSOR=1;
       break;
          }
       }
     
     }while(ESTADO_SENSOR==0);
     
     if(ESTADO_SENSOR==1){
      AcionaMotor(NUMERO_MOTOR,LOW); 
      iniciaTudo();
      }
   
 
 }