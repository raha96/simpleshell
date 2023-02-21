#include <iostream>
#include "lib/simpleshell.h"
#include "lib/builtincommands.h"

int main() {
    simpleshell::shell shell(std::cin, std::cout, std::cerr, "Test > ");
    shell.register_command<simpleshell::builtin::exit>();
    shell.register_command<simpleshell::builtin::_inttest>();
    shell.launch_interactive();
    return 0;
}