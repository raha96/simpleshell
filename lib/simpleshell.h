#ifndef __SIMPLESHELL_H__
#define __SIMPLESHELL_H__

#include "shellbase.h"
#include "builtincommands.h"

namespace simpleshell {
    class shell : public shell_base {
    public:
        shell (std::istream& _sin, std::ostream& _sout, std::ostream& _serr, std::string prompt);
    private:
        builtin::exit exit;
        builtin::_inttest _inttest;
    };
}

#endif
