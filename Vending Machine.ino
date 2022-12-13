#include <Arduino.h>
const int numero_motores=40; //quantidade de motores
const int numero_sensores=6; // quantidade de sensores
int motores[numero_motores] = {8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
33,34,35,36,37,38,39,40,40,42,43,44,45,46,47}; //portas que serao usadas pelos motores
int sensores[numero_sensores] = {2,3,4,5,6,7}; //portas que serao usadas pelos sensores
int sensores_status_leitura=1;
int NUMERO_MOTOR=0;
int ESTADO_SENSOR=0;
 
void AcionaMotor(int motor, int LigaDesliga){
      digitalWrite(motor, LigaDesliga);
      Serial.print("MOTOR: ");  
      Serial.print(motor); 
      if(LigaDesliga==1){
        Serial.println(" Acionado");
      }else{
       Serial.println(" Desligado"); 
        }
}      

void iniciaTudo(){
  NUMERO_MOTOR=0;
  ESTADO_SENSOR=0;
  Serial.println("\nResetou variaveis");
}
 
void setup(){
Serial.begin(9600);
// pinos sensores
for (int i=2;i<=numero_sensores+1;i++){
  pinMode(i, INPUT); // pino 2 ao 7 serao sensores, 6 sensores 
}

// pinos motores 
for (int i=8;i<=numero_motores+7;i++){
  pinMode(i, OUTPUT); // pino 8 ao 47 serao motores, 40 motores
}
}

void loop(){   
     for(int i=0; i<numero_sensores; i++) {
      sensores[i]=digitalRead(i+2);
      }
   Serial.println("\n");
   Serial.println("Digite a porta do motor: ");
   delay(1500); 
   do{
     if(Serial.available()){
       NUMERO_MOTOR = Serial.parseInt();
       Serial.read();
       break;
     }
   }while(true);
   if(NUMERO_MOTOR >= 8 and NUMERO_MOTOR <= numero_motores+7){
      AcionaMotor(NUMERO_MOTOR,HIGH);
      do{  
       for(int i=0; i<numero_sensores; i++) { 
        sensores_status_leitura=digitalRead(i);
        // Serial.println(i);   
        // Serial.println(sensores_status_leitura); 
        Serial.println("Girando o motor");
        if(sensores[i]!=digitalRead(i+2)){
          Serial.println("\nDetectou algo.");
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
   }else{
      Serial.println("Motor nao cadastrado.");
   }
   
 }