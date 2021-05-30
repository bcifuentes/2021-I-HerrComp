set title "Grafica de eficiencia paralela en hercules6"
set xlabel "Threads"
set ylabel "Eficiencia paralela"
set terminal postscript enhanced
set output "parallelef.pdf"
set grid
set yrange [0:2]
plot "parallelef.txt" pt 5 , 1 lw 3 lt 4 lc 7