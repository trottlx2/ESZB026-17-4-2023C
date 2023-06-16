#!/usr/bin/python3

# script baseado no código disponibilizado em:
# Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
# Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

import sys
from time import sleep
LED_PATH01 = "/sys/class/gpio/gpio20/"
LED_PATH02 = "/sys/class/gpio/gpio21/"
LED_PATH03 = "/sys/class/gpio/gpio16/"
SYSFS_DIR = "/sys/class/gpio/"

LED_GPIO1= "20" #vermelho
LED_GPIO2= "21" #verde
LED_GPIO3= "16" #amarelo

def writeLED ( filename, value, path):
	"Esta funcao escreve o valor 'value' no arquivo 'path+filename'"
	fo = open( path + filename,"w")
	fo.write(value)
	fo.close()
	return


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


for i in range (5):
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



print("Desabilitando a gpio")
writeLED (filename="unexport", value="21", path=SYSFS_DIR)
writeLED (filename="unexport", value="20", path=SYSFS_DIR)
writeLED (filename="unexport", value="16", path=SYSFS_DIR)


print("Fim do script Python.")
