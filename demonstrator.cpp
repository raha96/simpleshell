#include <iostream>
#include "lib/simpleshell.h"
#include "lib/builtincommands.h"

int main() {
    simpleshell::shell shell(std::cin, std::cout, std::cerr, "Test > ");
    simpleshell::builtin::exit exit;
    simpleshell::builtin::_inttest _inttest;
    exit.set_log(std::cout);
    _inttest.set_log(std::cout);
    shell.register_command(&exit);
    shell.register_command(&_inttest);
    shell.launch_interactive();
    return 0;
}