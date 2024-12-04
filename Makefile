all:
	g++ -Wall -g -c main.cpp
	g++ -Wall -g -c Path.cpp
	g++ -Wall -g -c TerrainMap.cpp
	g++ -Wall -g -c Letadlo.cpp
	g++ -Wall -g -c Lod.cpp
	g++ -o findpath main.o Path.o TerrainMap.o Letadlo.o Lod.o

clean:
	rm -f *.o findpath