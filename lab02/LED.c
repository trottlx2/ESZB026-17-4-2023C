#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Definindo as portas e caminhos de cada LED, 16 = AMARELO // 21 = VERDE // 20 = VERMELHO
#define GPIO_NUMBER3 "16"
#define GPIO_NUMBER2 "21"
#define GPIO_NUMBER1 "20"

#define GPIO4_PATH3 "/sys/class/gpio/gpio16/"
#define GPIO4_PATH2 "/sys/class/gpio/gpio21/"
#define GPIO4_PATH1 "/sys/class/gpio/gpio20/"

//Definindo caminho geral para usar as funções seguintes
#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(char filename[], char value[]){
   FILE* fp;                           // cria um ponteiro fp
   fp = fopen(filename, "w+");         // abre o arquivo para escrita
   fprintf(fp, "%s", value);           // grava o valor no arquivo
   fclose(fp);                         // fecha o arquivo
}

int main(int argc, char* argv[]){

   // Primeiro foram habilitadas as portas de cada LED através da função Export e Direction do writeGPIO para que se pudesse acessar e fazer modificações na mesma
   printf("Habilitando a gpio\n");
   writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER1);
   usleep(100000);                  // aguarda 100ms
   writeGPIO(GPIO4_PATH1 "direction", "out");
   
   printf("Habilitando a gpio\n");
   writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER2);
   usleep(100000);                  // aguarda 100ms
   writeGPIO(GPIO4_PATH2 "direction", "out");
   
   printf("Habilitando a gpio\n");
   writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER3);
   usleep(100000);                  // aguarda 100ms
   writeGPIO(GPIO4_PATH3 "direction", "out");

   // Aqui é inserido um loop for, para rodar 5 vezes a rotina de ligar os leds Vermelho (2seg) -> Verde (1seg) -> Amarelo (1seg)
   int contador;
   for (contador = 0; contador < 5; contador++) {
      // Para se acender um LED se utiliza a função writeGPIO no caminho do LED e dando o value = 1, para apagar value = 0
      // A mesma função é rodada apra cada LED, sendo o tempo de espera definido pela função usleep
      printf("Acendendo o LED\n");
      writeGPIO(GPIO4_PATH1 "value", "1");
      usleep(2000000);
      printf("Desligando o LED\n");
      writeGPIO(GPIO4_PATH1 "value", "0");

      printf("Acendendo o LED\n");
      writeGPIO(GPIO4_PATH2 "value", "1");
      usleep(1000000);
      printf("Desligando o LED\n");
      writeGPIO(GPIO4_PATH2 "value", "0");

      printf("Acendendo o LED\n");
      writeGPIO(GPIO4_PATH3 "value", "1");
      usleep(1000000);
      printf("Desligando o LED\n");
      writeGPIO(GPIO4_PATH3 "value", "0");
   }

   // Por fim foram desabilitadas as portas de cada LED através da função unexport do writeGPIO 
   printf("Desabilitando a gpio\n");
   writeGPIO(GPIO_SYSFS "unexport", GPIO_NUMBER1);
   writeGPIO(GPIO_SYSFS "unexport", GPIO_NUMBER2);
   writeGPIO(GPIO_SYSFS "unexport", GPIO_NUMBER3);

   printf("Fim do programa em C.\n");
   return 0;
}
