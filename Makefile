FLAGS= -std=c++17 -lreadline

build: shellbase simpleshell builtincommands
	g++ demonstrator.cpp build/simpleshell.o build/shellbase.o build/builtincommands.o $(FLAGS) -o build/demo

shellbase: _builddir lib/shellbase.cpp
	g++ $(FLAGS) -c lib/shellbase.cpp -o build/shellbase.o

simpleshell: _builddir lib/simpleshell.cpp
	g++ $(FLAGS) -c lib/simpleshell.cpp -o build/simpleshell.o

builtincommands: _builddir lib/builtincommands.cpp
	g++ $(FLAGS) -c lib/builtincommands.cpp -o build/builtincommands.o

_builddir: 
	mkdir -p build