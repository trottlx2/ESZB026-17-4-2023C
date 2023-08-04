#include <Thermistor.h>
const int analogInPin = A0; // o potenciômetro esta ligado ao pino A0

//Thermistor temp(0);
float media;
boolean inicial = true;
boolean coleta = false;
int contador = 0;
int insp_flag = 0;
int exp_flag = 0;
int insp_cont = 0;
int exp_cont = 0;
int apneia = 0;
int apneia_grave = 0;
int tmp_insp = 0;
int tmp_exp = 0;
void setup(){
   // Configura a serial: baud rate de 115200, 8-bit, sem paridade, 1 stop bit
   Serial.begin(115200, SERIAL_8N1);
   pinMode(7, OUTPUT);
   pinMode(10,OUTPUT);
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
          
          else{
            media = media*0.65 + voltagem*0.35;
     
          }
          int final = (50-((voltagem-media)*1000.0));
          
          //int final = (((voltagem)*1000.0) - 3000);
          //Serial.println(final);// envia o valor
          
          
       //  int pino_PWM = 23;                         // pwm por software na GPIO23
       //  int brilho;
       //  int range = 100;                           // periodo do PWM = 100us*range
        // wiringPiSetupGpio();                       // usar a numeracao GPIO, nao WPi
        // pinMode(pino_PWM,OUTPUT);	           // configura GPIO23 como saida
        // softPwmCreate(pino_PWM, 1, range);         // inicializa PWM por software
         
         if (final < 30){
            insp_flag = 0;
            exp_flag = 1;
            exp_cont = 0;
            tmp_exp = 0;
            digitalWrite(7, LOW);
         }
         else if( final > 70){
            insp_flag = 1;
            exp_flag = 0;
            insp_cont = 0;
            tmp_insp = 0;
            digitalWrite(7, LOW);
         }
         
         if (insp_flag == 1){
            insp_cont +=1;
         }
         if (exp_flag == 1){
            exp_cont += 1;
         }
         if (insp_cont > 100 && tmp_insp ==0){
           digitalWrite(7, HIGH);
           apneia = apneia + 1;
           tmp_insp = 1;
         }
         if (exp_cont > 100 && tmp_exp ==0){
           digitalWrite(7, HIGH);
           apneia = apneia + 1;
           tmp_exp = 1;
         }
         if (insp_cont > 200 || insp_cont > 200){
            delay(1000);
            int tempo = 400;
            tone(10,440,tempo); //LA
            delay(tempo);
            tone(10,294,tempo); //RE
            delay(tempo);
            tone(10,349,tempo/2); //FA - O tempo/2 faz com que demore metade do valor estipulado anteriormente, pois essa parte é mais rápida
            delay(tempo/2);
            tone(10,392,tempo/2); //SOL
            delay(tempo/2);
            tone(10,440,tempo); //LA
            delay(tempo);
            tone(10,294,tempo); //RE
            delay(tempo);
            tone(10,349,tempo/2); //FA
            delay(tempo/2);
            tone(10,392,tempo/2); //SOL
            delay(tempo/2);
            tone(10,330,tempo); //MI
            delay(tempo);
            apneia_grave = apneia_grave + 1;
         }
         //Serial.println("Insp_flag = %d; \tInsp_cont = %d, \tExp_flag = %d, \texp_cont = %d; \tvalor = %d\n",insp_flag, insp_cont, exp_flag, exp_cont, final);
         Serial.print("Insp_flag:"); Serial.println(insp_flag); 
         Serial.print("Insp_cont:"); Serial.println(insp_cont);
         Serial.print("Exp_flag 1:"); Serial.println(exp_flag);
         Serial.print("exp_cont:"); Serial.println(exp_cont);
         Serial.print("Apneia:"); Serial.println(apneia);
         Serial.print("valor:");Serial.println(final);
      }
      
   delay(100);     
          
   }
   
   
