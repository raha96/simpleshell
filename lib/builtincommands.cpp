#include "builtincommands.h"

namespace simpleshell::builtin {
    _command_status exit::exec(std::vector<std::string> params) {
        return COMSTAT_EXIT;
    }

    _command_status _inttest::exec(std::vector<std::string> params) {
        for (auto param : params) {
            *log << name << " `" << param << "`\n";
        }
        return COMSTAT_NORMAL;
    }
}