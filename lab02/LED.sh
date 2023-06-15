#!/bin/bash

# script baseado no código disponibilizado em:
# Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
# Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

LED_GPIO1=20 #vermelho
LED_GPIO2=21 #verde
LED_GPIO3=16 #amarelo
# Usar uma variavel facilita alteracoes futuras na porta usada

# funcoes Bash
function setLED
{                                      # $1 eh o primeiro argumento passado para a funcao
	echo $1 >> "/sys/class/gpio/gpio$LED_GPIO1/value"
 	echo $2 >> "/sys/class/gpio/gpio$LED_GPIO2/value"
  	echo $3 >> "/sys/class/gpio/gpio$LED_GPIO3/value"
}

# Inicio do programa
if [ $# -ne 1 ]; then                  # se nao houver exatamente um argumento passado ao programa
	echo "Nenhum comando passado. Uso: ./LED.sh command,"
	echo "onde comando pode ser: setup, on, off, status e close"
	echo -e " ex.: ./LED.sh setup, e em seguinda, ./LED.sh on"
	exit 2                         # erro que indica numero invalido de argumentos
fi

echo "O comando passado foi: $1"

if [ "$1" == "setup" ]; then
	echo "Habilitando a GPIO numero $LED_GPIO1"
	echo $LED_GPIO1 >> "/sys/class/gpio/export"
	sleep 1                        # esperar 1 segundo para garantir que a gpio foi exportada
	
 
	echo "Acendendo o LED"
	setLED 1                       # 1 eh recebido como $1 na funcao setLED

	sleep 2   
	echo "Desligando o LED"
	setLED 0                       # 0 eh recebido como $1 na funcao setLED
 
 	echo "out" >> "/sys/class/gpio/gpio$LED_GPIO1/direction"

 	echo "Habilitando a GPIO numero $LED_GPIO2"
	echo $LED_GPIO2 >> "/sys/class/gpio/export"
	sleep 1                        # esperar 1 segundo para garantir que a gpio foi exportada
	

	echo "Acendendo o LED"
	setLED 1                       # 1 eh recebido como $1 na funcao setLED

  	sleep 2  
   	echo "Desligando o LED"
	setLED 0  
 
	echo "out" >> "/sys/class/gpio/gpio$LED_GPIO2/direction"
  		echo "Desabilitando a GPIO numero $LED_GPIO2"
    
	echo $LED_GPIO2 >> "/sys/class/gpio/unexport"


	echo "Habilitando a GPIO numero $LED_GPIO3"
	echo $LED_GPIO3 >> "/sys/class/gpio/export"
	sleep 1                        # esperar 1 segundo para garantir que a gpio foi exportada
	
	echo "Acendendo o LED"
	setLED 1                       # 1 eh recebido como $1 na funcao setLED
	sleep 2   
	echo "Desligando o LED"
	setLED 0                       # 0 eh recebido como $1 na funcao setLED
 
 	echo "out" >> "/sys/class/gpio/gpio$LED_GPIO3/direction"


fi
