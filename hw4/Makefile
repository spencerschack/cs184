CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin
	LDFLAGS = -lglut -lGLU
endif
	
RM = /bin/rm -f 
all: ik 
ik: ik.o 
	$(CC) $(CFLAGS) -o ik ik.o $(LDFLAGS) 
ik.o: ik.cpp
	$(CC) $(CFLAGS) -c ik.cpp -o ik.o
clean: 
	$(RM) *.o as1
 


