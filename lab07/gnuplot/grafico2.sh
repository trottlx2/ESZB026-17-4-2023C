#!/bin/sh
ARQUIVODADOS=/home/pi/ESZB026-17-4-2023C/lab07/gnuplot/dados2.txt
ARQUIVOSAIDA=/home/pi/ESZB026-17-4-2023C/lab07/gnuplot/dados2.png

gnuplot << EOF
set title "Título"
set ylabel "Eixo Y"
set xlabel "Eixo X"
set terminal png
set output "$ARQUIVOSAIDA"
plot "$ARQUIVODADOS" \
     linecolor rgb '#c4f2d9' \
     linetype 4 \
     linewidth 5 \
     pointtype 9 \
     pointsize 3.0 \
     title "meus dados 2" \
     with linespoints
EOF

