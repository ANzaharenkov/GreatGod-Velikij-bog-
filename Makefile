all:
	g++ --std=c++17 src/main.cpp -I"SFML-2.5.1/include" -o main -L"SFML-2.5.1/lib" -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system