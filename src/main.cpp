#include <Arduino.h>

#define Chave_1 2
#define Chave_2 4
#define Chave_3 7
#define Rele_1 12
#define IN1_Motor = 8
#define IN1_Motor = 9
#define Velocidade_Motor = 10

#define Period_1 3000
#define Period_2 9000
#define Period_3 12000
#define Posicao_encher 1000
#define Copos 9

//Declarar variaveis globais
int aux = 0;
int i = 0;
int qtd = 0; // variavel auxiliar para contagem de copos preenchidos
int velocidade = 0; //Controlar a velocidade do motor

//Startup
void setup()
{
  Serial.begin(9600);
  pinMode(Rele_1, OUTPUT);
  digitalWrite(Rele_1, LOW);
  pinMode(Chave_1, INPUT_PULLUP);
  pinMode(Chave_2, INPUT_PULLUP);
  pinMode(Chave_3, INPUT_PULLUP);
  pinMode(IN1_Motor, OUTPUT);
  pinMode(IN2_Motor, OUTPUT);
  pinMode(Velocidade_Motor, OUTPUT);
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
  //Para o motor
  digitalWrite(IN1_Motor, HIGH);
  digitalWrite(IN2_Motor, HIGH);
  //INICIANDO BOMBA
  Serial.println("INICIANDO BOMBA");
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

/*void printerReturn(int aux){
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
}*/

//Recursividade
void loop()
{
  if(qtd < Copos){
    //IF QTD
    // Gira o motor em sentido horario
    digitalWrite(IN1_Motor, HIGH);
    digitalWrite(IN1_Motor, LOW);
    
  if(Serial.available()>0)
  {
    int serialValue = Serial.read();
    int serial = 0;
   switch(serialValue)
   {
  Serial.println(verificar_sensores(aux));
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
   Serial.println("SITUACAO_1");
   aux = iniciar_bomba(Period_1, 1);
      qtd++;
    break;
  case 2:
    //Situação 2
    Serial.println("SITUACAO_2");
   aux = iniciar_bomba(Period_2, 2);
      qtd++;
    break;
  case 3:
    //Situação 3
    Serial.println("SITUACAO_3");
    aux = iniciar_bomba(Period_3, 3);
      qtd++;
    break;
  case 4:
    Serial.println("REALOCANDO_FRASCO");
    break;
  case 5:
    Serial.println("PREENCHENDO_FRASCO");
    break;
  case 6:
    Serial.println("FINALIZADO");
    break;  
  default:
    //Situação Padrão
    digitalWrite(Rele_1, LOW);
   }
  }
 }
//Fim if QTD 
}
}
