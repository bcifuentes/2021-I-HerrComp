#!/bin/bash
for i in 1 2 3 4 5 6 7 8 9 10
do
   mpirun -np $i -oversubscribe ./a.out 2000000000 >> datos.txt
done
