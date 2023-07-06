#include <Thermistor.h>
const int analogInPin = A0;                  // o potenciômetro esta ligado ao pino A0
//Thermistor temp(0);
float media;
boolean inicial = true;
boolean coleta = false;
int contador = 0;
void setup(){
   // Configura a serial: baud rate de 115200, 8-bit, sem paridade, 1 stop bit
   Serial.begin(115200, SERIAL_8N1);
}

void loop(){
   byte charIn;                  // cria uma variavel para armazenar o caractere recebido

   char comando = '1';
   if(Serial.available()){       // verifica se recebeu algo pela serial
      charIn = Serial.read();    // le o caractere recebido
      if(charIn=='1'){
        coleta = true;
      }
      else if(charIn=='0'){
        coleta = false;
      }
   }
   
   
   
   if (coleta){
      
      
          int valor = analogRead(analogInPin);// cria uma variavel para armazenar o caractere recebido
          float voltagem = valor*5.0/1023.0;
          
          if(inicial){
            inicial = false;
            media = voltagem;
          }
          
         /* else if (contador = 10){
            contador = 0;
            media = voltagem;
          
          }*/
          else{
            media = media*0.5 + voltagem*0.5;
//''            contador = contador + 1;
          }
          int final = (50-((voltagem-media)*1000.0));
          //int final = (((voltagem)*1000.0) - 3000);
          Serial.println(final);// envia o valor
   }
   
   delay(100);
}
