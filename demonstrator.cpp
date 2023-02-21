#include <iostream>
#include "lib/simpleshell.h"

int main() {
    simpleshell::shell shell(std::cin, std::cout, std::cerr, "Test > ");
    shell.launch_interactive();
    return 0;
}