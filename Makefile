CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD
FILEFLAG = -I src

MAIN = src/geom/main.cpp
GEOMETRY = src/libgeom/geometry.cpp

COMPILE = obj/geom/main.o obj/libgeom/libgeom.o 

geometry: $(COMPILE)
	g++ $(COMPILE) -o $@

obj/geom/main.o: $(MAIN)
	g++ -c $(FILEFLAG) $(CFLAGS) $(CPPFLAGS) -o $@ $(MAIN) 

obj/libgeom/libgeom.o: $(GEOMETRY)
	g++ -c $(FILEFLAG) $(CFLAGS) $(CPPFLAGS) -o $@ $(GEOMETRY) 

-include geometry.d hello.d
