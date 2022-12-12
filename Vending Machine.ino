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
for (int i=2;i<=numero_sensores+1;i++){
  pinMode(i, INPUT);
}
// pinos motores 
for (int i=6;i<=numero_motores+5;i++){
  pinMode(i, OUTPUT);
}
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