project2 : main.o partOne.o point.o cluster.o linkage.o kMeans.o dunn.o
	g++ -std=c++11 -o project2 main.o partOne.o point.o cluster.o linkage.o kMeans.o dunn.o
main.o : main.cpp partOne.h linkage.h kMeans.h dunn.h
	g++ -std=c++11 -c main.cpp
partOne.o : partOne.cpp partOne.h cluster.h point.h
	g++ -std=c++11 -c partOne.cpp
point.o : point.cpp point.h
	g++ -std=c++11 -c point.cpp
cluster.o : cluster.cpp cluster.h point.h
	g++ -std=c++11 -c cluster.cpp
linkage.o : linkage.cpp linkage.h cluster.h point.h dunn.h
	g++ -std=c++11 -c linkage.cpp
kMeans.o : kMeans.cpp kMeans.h cluster.h point.h dunn.h
	g++ -std=c++11 -c kMeans.cpp
dunn.o : dunn.cpp dunn.h cluster.h point.h
	g++ -std=c++11 -c dunn.cpp

clean :
	rm -f *.o project2

run : project2
	./project2
