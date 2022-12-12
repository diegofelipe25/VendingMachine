#include <Arduino.h>
const int numero_motores=20; //quantidade de motores
const int numero_sensores=4; // quantidade de sensores
int motores[numero_motores] = {6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25}; //portas que serao usadas pelos motores
int sensores[numero_sensores] = {2,3,4,5}; //portas que serao usadas pelos sensores
int sensores_status_leitura=1;
int NUMERO_MOTOR=0;
int ESTADO_SENSOR=0;
 

void AcionaMotor(int motor, int LigaDesliga){
       if(motor > 5 and motor < 26){
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
  Serial.println("Resetou variaveis");
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
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
pinMode(14, OUTPUT);
pinMode(15, OUTPUT);
pinMode(16, OUTPUT);
pinMode(17, OUTPUT);
pinMode(18, OUTPUT);
pinMode(19, OUTPUT);
pinMode(20, OUTPUT);
pinMode(21, OUTPUT);
pinMode(22, OUTPUT);
pinMode(23, OUTPUT);
pinMode(24, OUTPUT);
pinMode(25, OUTPUT);
}

void loop(){   
     for(int i=0; i<numero_sensores; i++) {
      sensores[i]=digitalRead(i+2);
      }
   Serial.println("\n");
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
       for(int i=0; i<numero_sensores; i++) { 
        sensores_status_leitura=digitalRead(i);
        Serial.println(i);   
        Serial.println(sensores_status_leitura); 
       if(sensores[i]!=digitalRead(i+2)){
        Serial.println("Detectou algo.");
        ESTADO_SENSOR=1;
        break;
          }
       }
     }while(ESTADO_SENSOR==0);    
     if(ESTADO_SENSOR==1){
      AcionaMotor(NUMERO_MOTOR,LOW); 
      iniciaTudo();
      delay(500);
      Serial.flush();
      }
 }