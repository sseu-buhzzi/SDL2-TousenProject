cd "$(dirname "$0")"
mkdir -p build
g++ TousenProject.cpp $(sdl2-config --cflags --libs) -lGL -lGLU -o build/TousenProject
ln -fs TousenProject build/東綫ПРОЖЕКТ
