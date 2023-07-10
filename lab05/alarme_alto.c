/** Programa baseado no codigo disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
*/

// Ajustando o PWM por HARDWARE na Raspberry Pi
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>

#define pino_PWM0 18                    // o PWM sera acionado na GPIO18

int main() {                            // este programa deve ser rodado com 'sudo'
   int i, j;
   wiringPiSetupGpio();                 // usa a numeracao da GPIO
   pinMode(pino_PWM0, PWM_OUTPUT);      // configura a GPIO18 com o PWM por hardware

   // Ajustando a frequencia do PWM em 10kHz com 128 passos de duty cycle
   // frequencia PWM = 261,6 Hz / (divisor * range)
   // 261.6  = 19.2MHz  / (divisor * range) => divisor = 15
   pwmSetMode(PWM_MODE_MS);             // usando frequencia fixa
   pwmSetRange(302);                    // passos do duty cycle (max=4096)
   pwmSetClock(243);                     // fornece uma frequencia de 10kHz (max=4096)
   printf("Iniciando...\n");
  // variando o duty cycle
   for (i = 0; i<3;i++){
   	pwmWrite(pino_PWM0, 151);
   	usleep(150000);
   	pwmWrite(pino_PWM0,0);
   	usleep(150000); 
   } 
   usleep(300000);
   for (j = 0; j<2; j++){
       pwmWrite(pino_PWM0,151);
       usleep(150000);
       pwmWrite(pino_PWM0,0);
       usleep(150000);
   }
   printf("Fim.\n");
   return 0;                            // a saida PWM permanece ligada apos o termino do programa
}
