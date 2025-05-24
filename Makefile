CC = g++
FLAGS =

touken: ToukenProject.cpp lib\freeglut.lib lib\glu32.lib lib\opengl32.lib lib\SDL2.dll
	${CC} ${FLAGS} ToukenProject.cpp lib\freeglut.lib lib\glu32.lib lib\opengl32.lib lib\SDL2.dll
