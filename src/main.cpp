#include <Arduino.h>
#include <Stepper.h> // OLD - Declarãção de biblioteca base placa controladora
#define Chave_1 2
#define Chave_2 4
#define Chave_3 7
#define Rele_1 12
#define Passos 32
#define Speed 500

#define Period_1 3000
#define Period_2 9000
#define Period_3 12000
#define Posicao_encher 1000
#define Copos 9

//Declarar variaveis globais
int aux = 0;
int i = 0;
int qtd = 0;



Stepper mp(Passos, 8, 9, 10, 11); // OLD - ???

//Startup
void setup()
{
  Serial.begin(9600);
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
         (aux == 0 && digitalRead(Chave_1) == HIGH && digitalRead(Chave_2) == HIGH && digitalRead(Chave_3) == LOW) ? 2 : (
         (aux == 0 && digitalRead(Chave_1) == HIGH && digitalRead(Chave_2) == HIGH && digitalRead(Chave_3) == HIGH) ? 3 : (
         (aux == 1 && digitalRead(Chave_1) == HIGH || digitalRead(Chave_2) == HIGH || digitalRead(Chave_3) == HIGH)? -1: 0)
         ));         
}
//Verifica se Chave esta precionada
int verifica_precionado()
{
  return (digitalRead(Chave_1) == HIGH || digitalRead(Chave_2) == HIGH || digitalRead(Chave_3) == HIGH) ? 1 : 0;
}
//Inciiar a Bomba e para ele apos um periodo
int iniciar_bomba(int periodo,int tipo){
  
  Serial.println("INDO PARA A POSICAO DE ENCHER O COPO");
  delay(Posicao_encher); // indo para posicao correta para encher o copo
  //INICIANDO BOMBA
  Serial.println("INICIANDO BOMBA");
  
  mp.setSpeed(1); //Para o Motor
  //Liga a Bomba
  digitalWrite(Rele_1, HIGH);
 //Seta variavel auxiliar

   Serial.println("Enchendo o Copo na situação");
   Serial.println(tipo);
   delay(periodo);
   Serial.println("Finalizando situação ");
   Serial.println(tipo);
  
   
   
  
  //Apos o For parar desliga a bomba
  digitalWrite(Rele_1, LOW);
  return 1;
}

void printerReturn(int aux){
 switch(aux){
   case '0':
     Serial.println("SITUAÇÃO 1 DETECTADA");
   break;
  case '1':
     Serial.println("SITUAÇÃO 2 DETECTADA");
   break;
  case '3':
     Serial.println("SITUAÇÃO 3 DETECTADA");
   break; 
  case '4':
     Serial.println("INICIANDO A BOMBA");
   break; 
  case '5':
     Serial.println("ENCHENDO O FRASCO");
   break;
  case '6':
     Serial.println("SITUAÇÃO FINALIZADA");
   break;    
   default:
     Serial.printl("VALOR NÃO DEFINIDO");
 }
}

//Recursividade
void loop()
{
  if(qtd < Copos){
    //IF QTD
  if(Serial.available()>0)
  {
    int serialValue = Serial.read();
    int serial = 0;
   switch(serialValue)
   {
  Serial.println(verificar_sensores(aux));
  mp.step(1); // OLD - PASSOS QUE O MOTOR VAI DAR
  mp.setSpeed(Speed);

  if(aux == 1){
    Serial.println("Alguma Coisa Precionando os Botões");
    aux = verifica_precionado();
  }
  //Definir Casos de ação do ambinte
  switch (verificar_sensores(aux))
  {
  case 1:
  delay(500);
    //Situação 1
    if(verificar_sensores(aux)!= 1){
      break;
    }
   Serial.println("SITU 1");
   aux = iniciar_bomba(Period_1, 1);
      qtd++;
    break;
  case 2:
    //Situação 2
    Serial.println("SITU 2");
   aux = iniciar_bomba(Period_2, 2);
      qtd++;
    break;
  case 3:
    //Situação 3
    Serial.println("SITU 3");
    aux = iniciar_bomba(Period_3, 3);
      qtd++;
    break;
  default:
    //Situação Padrão
    mp.setSpeed(Speed);
    digitalWrite(Rele_1, LOW);
   }
  }
 }
//Fim if QTD 
}
}
