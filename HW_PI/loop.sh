for N in 1 2 3 4 5 6 7 8 9 10; do \
	mpirun -np N -oversubscribe ./a.out 2000000000 >> data.txt ;\
done ;\
