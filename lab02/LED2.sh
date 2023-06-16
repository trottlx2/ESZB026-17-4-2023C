#!/bin/bash

# script baseado no código disponibilizado em:
# Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
# Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

LED_GPIO1=20 #vermelho
LED_GPIO2=21 #verde
LED_GPIO3=16 #amarelo

# funcoes Bash
function setLED
{                                      # $1 eh o primeiro argumento passado para a funcao
	echo $1 >> "/sys/class/gpio/gpio$2/value"
}
for i in 1 2 3 4 5; do

	echo "Habilitando a GPIO numero $LED_GPIO1"
	echo $LED_GPIO1 >> "/sys/class/gpio/export"
	sleep 1                        # esperar 1 segundo para garantir que a gpio foi exportada
	echo "out" >> "/sys/class/gpio/gpio$LED_GPIO1/direction"
	
	echo "Habilitando a GPIO numero $LED_GPIO2"
	echo $LED_GPIO2 >> "/sys/class/gpio/export"
	sleep 1                        # esperar 1 segundo para garantir que a gpio foi exportada
	echo "out" >> "/sys/class/gpio/gpio$LED_GPIO2/direction"
	
	echo "Habilitando a GPIO numero $LED_GPIO3"
	echo $LED_GPIO3 >> "/sys/class/gpio/export"
	sleep 1                        # esperar 1 segundo para garantir que a gpio foi exportada
	echo "out" >> "/sys/class/gpio/gpio$LED_GPIO3/direction"
	
	echo "Acendendo o LED"
	setLED 1 $LED_GPIO1 
	sleep 2
	setLED 0 $LED_GPIO1 
	
	setLED 1 $LED_GPIO2 
	sleep 1
	setLED 0 $LED_GPIO2 
	
	setLED 1 $LED_GPIO3 
	sleep 1
	setLED 0 $LED_GPIO3
	
	echo "Piscou: $i"
done

fi
