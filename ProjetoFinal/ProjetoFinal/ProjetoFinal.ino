#include <Thermistor.h>
const int analogInPin = A0;                  // o potenciômetro esta ligado ao pino A0
//Thermistor temp(0);

void setup(){
   // Configura a serial: baud rate de 115200, 8-bit, sem paridade, 1 stop bit
   Serial.begin(115200, SERIAL_8N1);
}

void loop(){
   byte charIn;                  // cria uma variavel para armazenar o caractere recebido
   //int temperatura = temp.getTemp();
   char comando = '1';
   if(Serial.available()){       // verifica se recebeu algo pela serial
      charIn = Serial.read();    // le o caractere recebido
      
      
      if(charIn==comando){
          int valor = analogRead(analogInPin);// cria uma variavel para armazenar o caractere recebido
          Serial.println(valor);// envia o valor
      }
   }
}
