#include "simpleshell.h"

namespace simpleshell {
    shell::shell (std::istream& _sin, std::ostream& _sout, std::ostream& _serr, std::string _prompt) : 
        sin{_sin}, sout{_sout}, serr{_serr}, prompt{_prompt} {}

    void shell::launch_interactive() {
        bool exit = false;
        std::string line;
        char ch = 'x';
        while (!exit) {
            sout << prompt;
            std::getline(sin, line);
            for (std::string single_command : split(line, delimiter)) {
                auto tokens = split(single_command, SS_WHITESPACES);
                auto commandname = tokens[0];
                auto it = commands.find(commandname);
                if (it != commands.end()) {
                    //auto comm = (command*)(it->second);
                    serr << "Calling " << it->first << std::endl;
                    auto retval = static_cast<command*>(it->second)->exec(tokens);
                    if (retval == COMSTAT_EXIT) {
                        exit = true;
                        break;
                    }
                }
                else {
                    sout << "Unknown command `" << commandname << "`\n";
                }
            }
        }
    }

    std::vector<std::string> shell::split (std::string str, char splitter) {
        std::vector<std::string> out;
        std::string sbuf = "";
        str = str + splitter;
        for (char ch : str) {
            if (ch == splitter) {
                if (sbuf != "") {
                    out.push_back(sbuf);
                    sbuf = "";
                }
            }
            else {
                sbuf = sbuf + ch;
            }
        }
        return out;
    }

    std::vector<std::string> shell::split (std::string str, std::string delim) {
        std::vector<std::string> out;
        std::string sbuf = "";
        str = str + delim[0];
        for (char ch : str) {
            if (delim.find(ch) != std::string::npos) {
                if (sbuf != "") {
                    out.push_back(sbuf);
                    sbuf = "";
                }
            }
            else {
                sbuf = sbuf + ch;
            }
        }
        return out;
    }
}