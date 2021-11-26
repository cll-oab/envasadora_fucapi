#include <Stepper.h>

int passos=32; // QUANTOS PASSOS O MOTOR É CAPAZ DE DAR POR VOLTA
const int pinoChave = 7; //PINO DIGITAL UTILIZADO PELA CHAVE FIM DE CURSO
const int pinoChave2 = 4;
const int pinoChave3 = 2;
const int rele = 12;



Stepper mp(passos, 8, 9, 10, 11);
void setup() {
  mp.setSpeed(500); // VELOCIDADE DO MOTOR EM RPM
  pinMode(pinoChave, INPUT_PULLUP);
  pinMode(pinoChave2, INPUT_PULLUP);
  pinMode(pinoChave3, INPUT_PULLUP);
  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);
}


void loop() {
  mp.step(1); // PASSOS QUE O MOTOR VAI DAR
  if(digitalRead(pinoChave) == HIGH && digitalRead(pinoChave2) == LOW && digitalRead(pinoChave3) == LOW){
     mp.step(0);
     digitalWrite(rele, HIGH);
     delay(3000);
     digitalWrite(rele, LOW);
     }else if(digitalRead(pinoChave2) == HIGH && digitalRead(pinoChave) == HIGH && digitalRead(pinoChave3) == LOW){
        mp.step(0);
        digitalWrite(rele, HIGH);
        delay(9000);
        digitalWrite(rele, LOW);
        }else if(digitalRead(pinoChave3) == HIGH && digitalRead(pinoChave) == HIGH && digitalRead(pinoChave3) == HIGH){
            mp.step(0);
            digitalWrite(rele, HIGH);
            delay(9000);
            digitalWrite(rele, LOW);
            }

}