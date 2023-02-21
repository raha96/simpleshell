#ifndef __BUILTINCOMMANDS_H__
#define __BUILTINCOMMANDS_H__

#include "simpleshell.h"

namespace simpleshell::builtin {
    class exit : public command {
    public:
        exit() { name = "exit"; }
    protected:
        _command_status exec(std::vector<std::string>);
    };
    class _inttest : public command {
    public:
        _inttest() { name = "_inttest"; }
    protected:
        _command_status exec(std::vector<std::string>);
    };
}

#endif
