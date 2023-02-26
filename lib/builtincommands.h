#ifndef __BUILTINCOMMANDS_H__
#define __BUILTINCOMMANDS_H__

#include "shellbase.h"

namespace simpleshell::builtin {
    class exit : public command {
    public:
        exit() { name = "exit"; }
    protected:
        _command_status exec(std::vector<std::string>, void*);
        std::string _help();
    };
    
    class _inttest : public command {
    public:
        _inttest() { name = "_inttest"; }
    protected:
        _command_status exec(std::vector<std::string>, void*);
        std::string _help();
    };
}

#endif
