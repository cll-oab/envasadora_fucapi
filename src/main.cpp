#include <Arduino.h>
#include <Stepper.h> // OLD - Declarãção de biblioteca base placa controladora

#define Chave_1 7
#define Chave_2 4
#define Chave_3 2
#define Rele_1 12
#define Passos 32
#define Speed 5

#define Period_1 3000
#define Period_2 9000
#define Period_3 12000

//Declarar variaveis globais
countint aux = 0;
int i = 0;
unsigned long time_now = 0;

Stepper mp(Passos, 8, 9, 10, 11); // OLD - ???

//Startup
void setup()
{
  pinMode(Rele_1, OUTPUT);
  digitalWrite(Rele_1, LOW);
  mp.setSpeed(Speed); // OLD - VELOCIDADE DO MOTOR EM RPM
  pinMode(Chave_1, INPUT_PULLUP);
  pinMode(Chave_2, INPUT_PULLUP);
  pinMode(Chave_3, INPUT_PULLUP);
}

//Função para Verificar Sensores
int verificar_sensores(int aux)
{
  //Usa o codicionador para determinar o estado das chaves e retornar o valor da situação
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
//Inciiar a Bomba e para ele apos um periodo
int iniciar_bomba(int periodo,int tipo){
  //Para o Motor
  mp.setSpeed(0);
  //Liga a Bomba
  digitalWrite(Rele_1, HIGH);
  //Seta variavel auxiliar
  i = 0;
  for (;;)
  {
    //Inicia Loop para aguardar encher
    if (millis() > time_now + periodo)
    {
      //Para o loop e mostra msg de finalizado
      time_now = millis();
      Serial.println("Finalizando situação "+tipo);
      break;
    }
    //Usa variavel auxiliar para mostra a menssagem de enchendo apenas 1 vez
    if (i == 0){
      i = 1;
      Serial.println("Enchendo o Copo na situação "+tipo+"\n");
    }
  }
  //Apos o For parar desliga a bomba
  digitalWrite(Rele_1, LOW);
  return 1;
}

//Recursividade
void loop()
{
  mp.step(11); // OLD - PASSOS QUE O MOTOR VAI DAR
  mp.setSpeed(Speed);

  if(aux == 1)aux = verifica_precionado();

  //Definir Casos de ação do ambinte
  switch (verificar_sensores(aux))
  {
  case 1:
    //Situação 1
    aux = iniciar_bomba(Period_1, 1);
    break;
  case 2:
    //Situação 2
    aux = iniciar_bomba(Period_2, 2);
    break;
  case 3:
    //Situação 3
    aux = iniciar_bomba(Period_3, 3);
    break;
  default:
    //Situação Padrão
    mp.setSpeed(Speed);
    digitalWrite(Rele_1, LOW);
  }
}