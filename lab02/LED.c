/** Programa baseado no código disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GPIO_NUMBER3 "16"
#define GPIO_NUMBER2 "21"
#define GPIO_NUMBER1 "20"

#define GPIO4_PATH3 "/sys/class/gpio/gpio16/"
#define GPIO4_PATH2 "/sys/class/gpio/gpio20/"
#define GPIO4_PATH1 "/sys/class/gpio/gpio21/"

#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(char filename[], char value[]) {
   FILE* fp;
   fp = fopen(filename, "w+");
   fprintf(fp, "%s", value);
   fclose(fp);
}

int main(int argc, char* argv[]) {
   printf("Habilitando a gpio\n");
   writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER1);
   usleep(100000);
   writeGPIO(GPIO4_PATH1 "direction", "out");

   writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER2);
   usleep(100000);
   writeGPIO(GPIO4_PATH2 "direction", "out");

   writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER3);
   usleep(100000);
   writeGPIO(GPIO4_PATH3 "direction", "out");

   int contador;
   for (contador = 0; contador < 5; contador++) {
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

   printf("Desabilitando a gpio\n");
   writeGPIO(GPIO_SYSFS "unexport", GPIO_NUMBER1);
   writeGPIO(GPIO_SYSFS "unexport", GPIO_NUMBER2);
   writeGPIO(GPIO_SYSFS "unexport", GPIO_NUMBER3);

   printf("Fim do programa em C.\n");
   return 0;
}
