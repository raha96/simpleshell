#include "simpleshell.h"
#include "builtincommands.h"

#include <readline/readline.h>
#include <readline/history.h>

namespace simpleshell {

    shell_base::shell_base (std::istream& _sin, std::ostream& _sout, std::ostream& _serr, std::string _prompt) : 
        sin{_sin}, sout{_sout}, serr{_serr}, prompt{_prompt} {
        getline_init();
    }

    void shell_base::launch_interactive() {
        bool exit = false;
        std::string line;
        char ch = 'x';
        while (!exit) {
            line = getline(sin);
            for (std::string single_command : split(line, delimiter)) {
                auto tokens = split(single_command, SS_WHITESPACES);
                auto commandname = tokens[0];
                auto it = commands.find(commandname);
                if (it != commands.end()) {
                    //auto comm = (command*)(it->second);
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

    std::string shell_base::getline (std::istream& stream) {
        char* linebuf;
        linebuf = readline(prompt.c_str());
        std::string out(linebuf);
        if (linebuf != nullptr && linebuf[0] != 0)
            add_history(linebuf);
        free(linebuf);
        return out;
    }

    void shell_base::getline_init() {
    }

    std::vector<std::string> shell_base::split (std::string str, char splitter) {
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

    std::vector<std::string> shell_base::split (std::string str, std::string delim) {
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