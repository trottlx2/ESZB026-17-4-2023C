#!/bin/sh
ARQUIVODADOS=/home/pi/ESZB026-17-4-2023C/lab07/gnuplot/dados1.txt 
ARQUIVOSAIDA=/home/pi/ESZB026-17-4-2023C/lab07/gnuplot/dados1.png

gnuplot << EOF
set title "Título"
set ylabel "Eixo Y"
set xlabel "Eixo X"
set terminal png
set output "$ARQUIVOSAIDA"
plot "$ARQUIVODADOS" \
     linecolor rgb '#ad009f' \
     linetype 3 \
     linewidth 1 \
     pointtype 4 \
     pointsize 1.0 \
     title "meus dados 1" \
     with linespoints
EOF

