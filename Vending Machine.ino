#include <Arduino.h>
//@autor diego felipe
const int numero_motores=40; //quantidade de motores
const int numero_sensores=2; // quantidade de sensores
int motores[numero_motores] = {8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,
33,34,35,36,37,38,39,40,40,42,43,44,45,46,47}; //portas que serao usadas pelos motores, 40
int sensores[numero_sensores] = {2,3}; //portas que serao usadas pelos sensores, 2
int sensores_status_leitura=1;
int NUMERO_MOTOR=0;
int ESTADO_SENSOR=0;
 
void AcionaMotor(int motor, int LigaDesliga){ //metodo de liga/desligar os motores
      digitalWrite(motor, LigaDesliga);
      Serial.print("MOTOR: ");  
      Serial.print(motor); 
      if(LigaDesliga==1){
        Serial.println(" Acionado");
      }else{
       Serial.println(" Desligado"); 
      }
}      

void iniciaTudo(){ //zera as variaveiveis antes de dar um novo loop
  NUMERO_MOTOR=0;
  ESTADO_SENSOR=0;
  Serial.println("\nResetou variaveis");
}
 
void setup(){
Serial.begin(9600);
// pinos sensores 
//sensor manda sinal 1 continuo, ou seja 5V  se detectar algo mando 0v ou seja sinal 0 ate o objeto sair da frente do sensor
for (int i=2;i<=numero_sensores+1;i++){
  pinMode(i, INPUT); // pino 2 ao 4 serao sensores, 2 sensores 
}
//pinos motores 
//manda corrente para ligar o motor e quando para de mandar o motor para de funcionar
for (int i=8;i<=numero_motores+7;i++){
  pinMode(i, OUTPUT); // pino 8 ao 47 serao motores, 40 motores
}
}

void loop(){   
   for(int i=0; i<numero_sensores; i++) { //le os sensores a primeira vez antes de pedir o numero do motor
    sensores[i]=digitalRead(i+2); //passa o valor da porta digital para o indice da lista de sensores
  }
   Serial.println("\n");
   Serial.println("Digite a porta do motor: ");
   delay(1500); 
   do{
     if(Serial.available()){ //se tiver alguma coisa na serial entra aqui
       NUMERO_MOTOR = Serial.parseInt(); //converte o valor recebido para inteiro e passa para a variavel
       Serial.read(); //aqui é para nao pegar o ENTER 
       break; //quebra o while
     }
   }while(true);
   if(NUMERO_MOTOR >= motores[0] and NUMERO_MOTOR <= numero_motores+7){ //verifica se o motor esta dentro da lista de motores
      AcionaMotor(NUMERO_MOTOR,HIGH); //chama o metodo de acionar motor e liga

      do{  
       for(int i=0; i<numero_sensores; i++) { 
        //sensores_status_leitura=digitalRead(i);
        // Serial.println(i);   
        // Serial.println(sensores_status_leitura); 
        Serial.println("Girando o motor");
        if(sensores[i]!=digitalRead(i+2)){ //fica comparando sensor por sensor com a lista de sensores carregadar no inicio do loop... 
          Serial.println("\nDetectou algo."); //se algum sensor da lista detectar algo manda 0V e sinal 0, essa lista vai ser diferente da primeira carregada...
          ESTADO_SENSOR=1; //muda o estado do sensor
          break; //sai do for
         }
       }
     }while(ESTADO_SENSOR==0);    // se detectar algo quebra o while e muda o estado do sensor
   
     if(ESTADO_SENSOR==1){ //se detectar algo vai entrar aqui e vai parar o motor
      AcionaMotor(NUMERO_MOTOR,LOW); //chama o metodo de acionar motor e desliga
      iniciaTudo(); //zera as variaveis para o estado inicial
      delay(500); //espera meio segundo que é o tempo para resetar as variaveis
      Serial.flush(); //limpa o cache da serial
      }
   }else{
      Serial.println("Motor nao cadastrado."); //se o motor nao estiver cadastrado na lista printa isso e pede o motor novamente
   }
 }