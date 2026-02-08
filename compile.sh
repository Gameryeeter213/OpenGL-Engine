gcc src/main.c glad/src/gl.c -Iglad/include -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -o Engine
./Engine
