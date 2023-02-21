#include "builtincommands.h"

namespace simpleshell::builtin {
    _command_status exit::exec(std::vector<std::string> params) {
        return COMSTAT_EXIT;
    }
    std::string exit::_help() {
        return "Exit the shell.";
    }

    _command_status _inttest::exec(std::vector<std::string> params) {
        for (auto param : params) {
            *log << name << " `" << param << "`\n";
        }
        return COMSTAT_NORMAL;
    }
    std::string _inttest::_help() {
        return "Intended for testing the internals.";
    }
}