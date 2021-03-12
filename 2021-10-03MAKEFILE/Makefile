all: datos.pdf

#implicit rules
#$^ : todas las dependencias
#$< : Solo la primera
#$@ : target

%.x:%.cpp
	g++ $< -o $@

datos.txt: updown.x
	./$< > $@

datos.pdf: updown.gp datos.txt
	gnuplot $<
	xdg-open $@

clean:
	rm -f updown.x datos.txt datos.pdf
