#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <math.h>

int main(){
   int file, count;
   if ((file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Falha ao abrir o arquivo.\n");
      return -1;
   }
   struct termios options;             // cria estruturas para configurar a comunicacao
   tcgetattr(file, &options);          // ajusta os parametros do arquivo

   // Configura a comunicacao
   // 115200 baud, 8-bit, enable receiver, no modem control lines
   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;   // ignora erros de paridade
   tcflush(file, TCIFLUSH);            // descarta informacao no arquivo
   tcsetattr(file, TCSANOW, &options); // aplica alteracoes imediatamente
   
   while(1){
      if ((count = write(file, "1", 1))<0){
	 perror("Falha ao escrever na saida.\n");
	 return -1;
      }   
      usleep(100000);                     // Espera 100ms pela resposta do Arduino

      unsigned char receive[6];         // cria um buffer para receber os dados
      if ((count = read(file, (void*)receive, 6))<0){        // recebe os dados
	 perror("Falha ao ler da entrada\n");
	 return -1;
      }
      
      char *subString; // the "result"
      subString = strtok(receive,"\n");
      int resultado = atoi(subString);
	 
      if (count==0) printf("Nao houve resposta!\n");
      else printf("Valor [%d] caracteres: %s\n",resultado,subString);


      int pino_PWM = 23;                         // pwm por software na GPIO23
      int brilho;
      int range = 100;                           // periodo do PWM = 100us*range
      wiringPiSetupGpio();                       // usar a numeracao GPIO, nao WPi
      pinMode(pino_PWM,OUTPUT);	           // configura GPIO23 como saida
      softPwmCreate(pino_PWM, 1, range);         // inicializa PWM por software
      
      brilho = floor(resultado / 4);
      printf("brilho [%d] \n",brilho);
      softPwmWrite (pino_PWM, brilho);
      delay (10);
   }
   
   close(file);
   return 0;
   
   
}
