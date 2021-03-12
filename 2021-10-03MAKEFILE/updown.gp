set log y
set xlabel "N"
set ylabel "Delta"
set term pdf
set out "datos.pdf"
plot "datos.txt" u 1:4 t "Percentual diff"