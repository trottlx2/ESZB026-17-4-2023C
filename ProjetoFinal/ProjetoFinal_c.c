#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <math.h>
//#include <>

int insp_flag = 0;
int exp_flag = 0;
int insp_cont = 0;
int exp_cont = 0;

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
   
  /* if ((count = write(file, "0", 1))<0){
      perror("Falha ao escrever na saida.\n");
      return -1;
   }   
   usleep(1000000);                     // Espera 100ms pela resposta do Arduino

   tcflush(file, TCIFLUSH);            // descarta informacao no arquivo
   tcsetattr(file, TCSANOW, &options); // aplica alteracoes imediatamente*/
   

   
   while(1){
       if ((count = write(file, "1", 1))<0){
         perror("Falha ao escrever na saida.\n");
         return -1;
      }   
      usleep(100000);                     // Espera 100ms pela resposta do Arduino
     unsigned char receive[7];         // cria um buffer para receber os dados
      if ((count = read(file, (void*)receive, 7))<0){        // recebe os dados
      	 perror("Falha ao ler da entrada\n");
      	 return -1;
      }
      
      printf("Valores \t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t(%d) \n",receive[0],receive[1],receive[2],receive[3],receive[4],receive[5],receive[6],count);
      /*char *subString; // the "result"
      subString = strtok(receive,"\n");
      int resultado = atoi(subString);
      //printf("Valor [%d] \n",resultado);*/
      int resultado = receive[6];
      if (count==0) ;//printf("Nao houve resposta!\n");
      else{
         //printf("Valor [%d] caracteres\n",resultado);
   
      
         if (resultado < 30){
            insp_flag = 0;
            exp_flag = 1;
            exp_cont = 0;
         }
         else if( resultado > 70){
            insp_flag = 1;
            exp_flag = 0;
            insp_cont = 0;
         }
         
         if (insp_flag == 1){
            insp_cont +=1;
         }
         if (exp_flag == 1){
            exp_cont += 1;
         }
         //printf("Insp_flag = %d; \tInsp_cont = %d, \tExp_flag = %d, \texp_cont = %d; \tvalor = %d\n",insp_flag, insp_cont, exp_flag, exp_cont, resultado);
      }
         
         
      //printf("Detectado expiração \n");
      //while (1){
      //   char *subString; // the "result"
      //   subString = strtok(receive,"\n");
      //    int resultado = atoi(subString);
      //    if (resultado < 35 || resultado < 35){
      //        break;
      //      }
      //    }
      //  softPwmWrite (pino_PWM, 255);       
      //}
      //else{ 
      //   printf("brilho [%d] \n",brilho);
      //   softPwmWrite (pino_PWM, 0);   
      // }

      //  delay (10);
      //usleep(100000); //espera 10ms = 10E-3 s     
   }
   
   close(file);
   return 0;
   
   
}
