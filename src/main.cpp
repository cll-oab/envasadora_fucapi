#include <Arduino.h>
#include <Stepper.h> // OLD - Declarãção de biblioteca base placa controladora

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
}

#define Chave_1 7
#define Chave_2 4
#define Chave_3 2
#define Rele_1 12

#define period_1 3000
#define period_2 9000
#define period_3 12000

int passos = 32; //OLD - QUANTOS PASSOS O MOTOR É CAPAZ DE DAR POR VOLTA
int i = 0;
unsigned long time_now = 0;

Stepper mp(passos, 8, 9, 10, 11); // OLD - ???

//Declarar variavel global
countint aux = 0;

//Startup
void setup()
{
  pinMode(Rele_1, OUTPUT);
  digitalWrite(Rele_1, LOW);
  mp.setSpeed(5); // VELOCIDADE DO MOTOR EM RPM
  pinMode(Chave_1, INPUT_PULLUP);
  pinMode(Chave_2, INPUT_PULLUP);
  pinMode(Chave_3, INPUT_PULLUP);
}

//Função para Verificar Sensores
int verificar_sensores(int aux)
{
  return (aux == 0 && digitalRead(Chave_1) == HIGH && digitalRead(Chave_2) == LOW && digitalRead(Chave_3) == LOW) ? 1 : (
         (aux == 0 && digitalRead(Chave_1) == HIGH && digitalRead(Chave_2) == LOW && digitalRead(Chave_3) == LOW) ? 2 : (
         (aux == 0 && digitalRead(Chave_1) == HIGH && digitalRead(Chave_2) == LOW && digitalRead(Chave_3) == LOW) ? 3 : 0)
         );
}
//Verifica se Chave esta precionada
void verifica_precionado()
{
  return (digitalRead(Chave_1) == HIGH || digitalRead(Chave_2) == HIGH || digitalRead(Chave_3) == HIGH) ? 1 : 0;
}

//Recursividade
void loop()
{
  mp.step(12); // OLD - PASSOS QUE O MOTOR VAI DAR
  mp.setSpeed(5);

  if(aux == 1)aux = verifica_precionado();

  //Definir Casos de ação do ambinte
  switch (verificar_sensores(aux))
  {
  case 1:
    //Situação 1
    mp.setSpeed(0);
    digitalWrite(Rele_1, HIGH);
    i = 0;
    for(;;){
      if(millis() > time_now + period_1){
              time_now = millis();
              Serial.println("Finalizando situação 1");
              break;
          }
      if(i==0){
        i = 1;
        Serial.println("Enchendo o Copo na situação 1\n");
      }
    }
    digitalWrite(Rele_1, LOW);
    aux = 1;
    break;
  case 2:
    //Situação 2
    mp.setSpeed(0);
    digitalWrite(Rele_1, HIGH);
    i = 0;
    for(;;){
      if(millis() > time_now + period_2){
              time_now = millis();
              Serial.println("Finalizando situação 2");
              break;
          }
      if(i==0){
        i = 1;
        Serial.println("Enchendo o Copo na situação 2\n");
      }
    }
    digitalWrite(Rele_1, LOW);
    aux = 1;
    break;
  case 3:
    //Situação 3
    mp.setSpeed(0);
    digitalWrite(Rele_1, HIGH);
    i = 0;
    for(;;){
      if(millis() > time_now + period_3){
              time_now = millis();
              Serial.println("Finalizando situação 3");
              break;
          }
      if(i==0){
        i = 1;
        Serial.println("Enchendo o Copo na situação 3\n");
      }
    }
    digitalWrite(Rele_1, LOW);
    aux = 1;
    break;
  default:
    //Situação Padrão
    mp.step(1);
    mp.setSpeed(5);
    digitalWrite(Rele_1, LOW);
  }
}