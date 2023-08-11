#!/bin/sh
ARQUIVODADOS=/home/pi/ESZB026-17-4-2023C/ProjetoFinal/Projeto.txt
ARQUIVOSAIDA=/home/pi/ESZB026-17-4-2023C/ProjetoFinal/dados.png

gnuplot << EOF
set title "Monitoramento de Apneia"
set ylabel "Eixo Y"
set xlabel "Eixo X"
set terminal png
set output "$ARQUIVOSAIDA"
plot "$ARQUIVODADOS" \
     linecolor rgb '#0060ad' \
     linetype 1 \
     linewidth 1 \
     pointtype 2 \
     pointsize 1.0 \
     title "meus dados" \
     with linespoints
EOF

