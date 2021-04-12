test: test.x


%.o : %.cpp
	g++ -g -c $< -o $@

codigo.x:codigo.o factorial.o
	g++ -g  $^ -o $@

test.x: factorial.o example_Catch2.o 
	g++ -g $^ -o $@

run-test: test.x
	./$<
clean:
	rm -f *.x *.o a.out
