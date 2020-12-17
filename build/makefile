
CXX=g++
CXXFLAGS= -Wall -Wextra -lncurses

%.o: ../src/%.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

main: main.o archer.o unite.o catapulte.o fantassin.o super_soldat.o jeu.o player.o ia.o
	$(CXX) $^ -o $@

.PHONY: clean

clean:
	rm -f *.o *~ core 

