for N in 1 2 3 4 5 6 7 8 9 10; do
    export OMP_NUM_THREADS=$N;
    echo $N;
    /usr/bin/time ./a.out >> tiempos.txt;
done

    
    
    
