#!/bin/bash

# script baseado no código disponibilizado em:
# Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
# Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

#Definindo as portas e caminhos de cada LED, 16 = AMARELO // 21 = VERDE // 20 = VERMELHO
LED_GPIO1=20 #vermelho
LED_GPIO2=21 #verde
LED_GPIO3=16 #amarelo

# funcoes Bash
#Criando função principal para fazer alterações no caminho das portas dos LEDs
function setLED
{                                      # $1 eh o primeiro argumento passado para a funcao
	echo $1 >> "/sys/class/gpio/gpio$2/value"
}

# Primeiro foram habilitadas as portas de cada LED através da função Export e Direction do writeGPIO para que se pudesse acessar e fazer modificações na mesma
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

# Aqui é inserido um loop for, para rodar 5 vezes a rotina de ligar os leds Vermelho (2seg) -> Verde (1seg) -> Amarelo (1seg)
for i in 1 2 3 4 5; do
	# Para se acender um LED se utiliza a função setLED no caminho da porta de cada LED e dando o value = 1, para apagar value = 0
      	# A mesma função é rodada apra cada LED, sendo o tempo de espera definido pela função sleep
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

# Por fim foram desabilitadas as portas de cada LED através da função unexport no writeLED
echo "Desabilitando a GPIO numero $LED_GPIO1"
echo $LED_GPIO1 >> "/sys/class/gpio/unexport"

echo "Desabilitando a GPIO numero $LED_GPIO2"
echo $LED_GPIO2 >> "/sys/class/gpio/unexport"

echo "Desabilitando a GPIO numero $LED_GPIO3"
echo $LED_GPIO3 >> "/sys/class/gpio/unexport"

fi
