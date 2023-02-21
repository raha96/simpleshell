#include "simpleshell.h"

namespace simpleshell {
    shell::shell (std::istream& _sin, std::ostream& _sout, std::ostream& _serr, std::string prompt) : 
     shell_base(_sin, _sout, _serr, prompt) {
        exit.set_log(_sout);
        _inttest.set_log(_sout);
        register_command(&exit);
        register_command(&_inttest);
    }
}