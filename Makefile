FLAGS= -fconcepts

build: shell
	g++ demonstrator.cpp build/libsimpleshell.a $(FLAGS) -lreadline -o build/demo

shell: shellbase simpleshell builtincommands
	ar rvs build/libsimpleshell.a build/simpleshell.o build/shellbase.o build/builtincommands.o

shellbase: _builddir lib/shellbase.cpp
	g++ -c lib/shellbase.cpp $(FLAGS) -o build/shellbase.o

simpleshell: _builddir lib/simpleshell.cpp
	g++ -c lib/simpleshell.cpp $(FLAGS) -o build/simpleshell.o

builtincommands: _builddir lib/builtincommands.cpp
	g++ -c lib/builtincommands.cpp $(FLAGS) -o build/builtincommands.o

_builddir: 
	mkdir -p build