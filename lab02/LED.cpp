/** Programa baseado no código disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
*/

#include<iostream>
#include<fstream>
#include<string>
#include<unistd.h>
using namespace std;

//Definindo as portas e caminhos de cada LED, 16 = AMARELO // 21 = VERDE // 20 = VERMELHO
#define GPIO_NUMBER3 "16"
#define GPIO_NUMBER2 "21"
#define GPIO_NUMBER1 "20"
#define GPIO_PATH3 "/sys/class/gpio/gpio16/"
#define GPIO_PATH2 "/sys/class/gpio/gpio21/"
#define GPIO_PATH1 "/sys/class/gpio/gpio20/"
//Definindo caminho geral para usar as funções seguintes
#define GPIO_SYSFS "/sys/class/gpio/"

// Criando a função principal para fazer alterações no caminho da porta do LED
void writeGPIO(string path, string filename, string value){
   fstream fs;
   fs.open((path + filename).c_str(), fstream::out);
   fs << value;
   fs.close();
}


int main(int argc, char* argv[]){
   // Primeiro foram habilitadas as portas de cada LED através da função Export e Direction do writeGPIO para que se pudesse acessar e fazer modificações na mesma
   cout << "Habilitando a gpio" << endl;
   writeGPIO(string(GPIO_SYSFS), "export", GPIO_NUMBER1);
   usleep(100000);
   writeGPIO(string(GPIO_PATH1), "direction", "out");
   
   writeGPIO(string(GPIO_SYSFS), "export", GPIO_NUMBER2);
   usleep(100000);
   writeGPIO(string(GPIO_PATH2), "direction", "out");
   
   writeGPIO(string(GPIO_SYSFS), "export", GPIO_NUMBER3);
   usleep(100000);
   writeGPIO(string(GPIO_PATH3), "direction", "out");

    // Aqui é inserido um loop for, para rodar 5 vezes a rotina de ligar os leds Vermelho (2seg) -> Verde (1seg) -> Amarelo (1seg)
   for(int n = 0; n <= 5; n++){
      // Para se acender um LED se utiliza a função writeGPIO no caminho do LED e dando o value = 1, para apagar value = 0
      // A mesma função é rodada apra cada LED, sendo o tempo de espera definido pela função usleep
      cout << "Acendendo o LED" << endl;
      writeGPIO(string(GPIO_PATH1), "value", "1");
      usleep(2000000);
      cout << "Desligando o LED" << endl;
      writeGPIO(string(GPIO_PATH1), "value", "0");

      cout << "Acendendo o LED" << endl;
      writeGPIO(string(GPIO_PATH2), "value", "1");
      usleep(1000000);
      cout << "Desligando o LED" << endl;
      writeGPIO(string(GPIO_PATH2), "value", "0");

      cout << "Acendendo o LED" << endl;
      writeGPIO(string(GPIO_PATH3), "value", "1");
      usleep(1000000);
      cout << "Desligando o LED" << endl;
      writeGPIO(string(GPIO_PATH3), "value", "0");
    }

   // Por fim foram desabilitadas as portas de cada LED através da função unexport do writeGPIO 
   cout << "Desabilitando a gpio" << endl;
   writeGPIO(string(GPIO_SYSFS), "unexport", GPIO_NUMBER1);
   writeGPIO(string(GPIO_SYSFS), "unexport", GPIO_NUMBER2);
   writeGPIO(string(GPIO_SYSFS), "unexport", GPIO_NUMBER3);


   cout << "Fim do programa em C++." << endl;
   return 0;
}
