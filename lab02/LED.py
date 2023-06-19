#!/usr/bin/python3

# script baseado no código disponibilizado em:
# Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
# Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

import sys
from time import sleep

#Definindo as portas e caminhos de cada LED, 16 = AMARELO // 21 = VERDE // 20 = VERMELHO
LED_PATH01 = "/sys/class/gpio/gpio20/"
LED_PATH02 = "/sys/class/gpio/gpio21/"
LED_PATH03 = "/sys/class/gpio/gpio16/"

LED_GPIO1= "20" #vermelho
LED_GPIO2= "21" #verde
LED_GPIO3= "16" #amarelo

#Definindo caminho geral para usar as funções seguintes
SYSFS_DIR = "/sys/class/gpio/"

#Criando função principal para fazer alterações no caminho das portas dos LEDs
def writeLED ( filename, value, path):
	"Esta funcao escreve o valor 'value' no arquivo 'path+filename'"
	fo = open( path + filename,"w")
	fo.write(value)
	fo.close()
	return

# Primeiro foram habilitadas as portas de cada LED através da função Export e Direction do writeGPIO para que se pudesse acessar e fazer modificações na mesma
print("Habilitando a gpio")
writeLED (filename="export", value="20", path=SYSFS_DIR)
sleep(0.1)
writeLED (filename="direction", value="out", path = LED_PATH01)

writeLED (filename="export", value="21", path=SYSFS_DIR)
sleep(0.1)
writeLED (filename="direction", value="out", path = LED_PATH02)

writeLED (filename="export", value="16", path=SYSFS_DIR)
sleep(0.1)
writeLED (filename="direction", value="out", path = LED_PATH03)

# Aqui é inserido um loop for, para rodar 5 vezes a rotina de ligar os leds Vermelho (2seg) -> Verde (1seg) -> Amarelo (1seg)
for i in range (5):
	# Para se acender um LED se utiliza a função writeLED no caminho do LED e dando o value = 1, para apagar value = 0
      	# A mesma função é rodada apra cada LED, sendo o tempo de espera definido pela função usleep
      	printf("Acendendo o LED\n");
	print("Acendendo o LED")
	writeLED (filename="value", value="1", path = LED_PATH01)
	sleep(2)
	print("Desligando o LED")
	writeLED (filename="value", value="0", path = LED_PATH01)

	print("Acendendo o LED")
	writeLED (filename="value", value="1", path = LED_PATH02)
	sleep(1)
	print("Desligando o LED")
	writeLED (filename="value", value="0", path = LED_PATH02)

	print("Acendendo o LED")
	writeLED (filename="value", value="1", path = LED_PATH03)
	sleep(1)
	print("Desligando o LED")
	writeLED (filename="value", value="0", path = LED_PATH03)


# Por fim foram desabilitadas as portas de cada LED através da função unexport no writeLED
print("Desabilitando a gpio")
writeLED (filename="unexport", value="21", path=SYSFS_DIR)
writeLED (filename="unexport", value="20", path=SYSFS_DIR)
writeLED (filename="unexport", value="16", path=SYSFS_DIR)


print("Fim do script Python.")
