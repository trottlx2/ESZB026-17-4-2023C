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

#define TAMANHO 100

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
   

   
   //while(1){
      unsigned char lista_valores[TAMANHO];
      if ((count = write(file, "1", 1))<0){
         perror("Falha ao escrever na saida.\n");
         return -1;
      }   
      usleep(100000);                     // Espera 100ms pela resposta do Arduino
      unsigned char receive[TAMANHO+7];         // cria um buffer para receber os dados
      if ((count = read(file, (void*)receive, TAMANHO+7))<0){        // recebe os dados
      	 perror("Falha ao ler da entrada\n");
      	 return -1;
      }
      
      printf("Valores \t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t[%d]\t(%d)\n",receive[0],receive[1],receive[2],receive[3],receive[4],receive[5],receive[6],count);
      
      for (int i = 7; i< TAMANHO+7; i++){
         lista_valores[i-7] = receive[i];
         //printf("%d ",i);
      }
      
      printf("\npegou\n");
     
      FILE *fp_saida;
      fp_saida = fopen ("/home/pi/Projeto.txt", "w+");
      for ( int ii = 0; ii < TAMANHO; ii++ )
      {
		   fprintf(fp_saida,"%f %d\n", ii/10.0, lista_valores[ii]);
	   }
	   fclose(fp_saida);
      
      printf("gravou\n");

      /*int resultado = receive[6];
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
      }*/
  // }
   
   close(file);
   return 0;
   
   
}
