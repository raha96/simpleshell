#ifndef __SHELLBASE_H__
#define __SHELLBASE_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <any>

#define SS_WHITESPACES " \t"

namespace simpleshell {
    enum _command_status {
        COMSTAT_NORMAL, 
        COMSTAT_EXIT
    };

    class command {
        friend class shell_base;
    public:
        std::string name;
        inline void set_log(std::ostream& sout) { log = &sout; }
    protected:
        // This should never be called, but it must be implemented to allow use in commands<> map.
        virtual _command_status exec (std::vector<std::string>) { assert(0); };
        std::ostream* log;
    };

    class shell_base {
    public:
        shell_base (std::istream& _sin, std::ostream& _sout, std::ostream& _serr, std::string prompt);
        void launch_interactive();
        inline void register_command(command* comm) {
            commands[comm->name] = comm;
        }
    private:
        std::istream& sin;
        std::ostream& sout;
        std::ostream& serr;
        std::string prompt;
        std::vector<std::string> split(std::string, char);
        std::vector<std::string> split(std::string, std::string);
        char delimiter = ';';
        std::map<std::string,command*> commands;
        std::string getline(std::istream&);
    };
}

#endif
