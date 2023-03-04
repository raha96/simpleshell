#include "simpleshell.h"
#include "builtincommands.h"

#include <readline/readline.h>
#include <readline/history.h>

namespace simpleshell {

    shell_base::shell_base (std::istream& _sin, std::ostream& _sout, std::ostream& _serr, std::string _prompt) : 
        sin{_sin}, sout{_sout}, serr{_serr}, prompt{_prompt} {
        getline_init();
        _help.set_log(sout);
        register_command(&_help);
        _help.sh = this;
    }

    void shell_base::launch_interactive (std::string init_script) {
        bool exit = false;
        bool first = true;
        std::string line;
        char ch = 'x';
        while (!exit) {
            if (first && init_script != "") {
                line = init_script;
                first = false;
            }
            else
                line = getline(sin);
            for (std::string single_command : split(line, delimiter)) {
                auto tokens = split(single_command, SS_WHITESPACES);
                auto commandname = tokens[0];
                auto it = commands.find(commandname);
                if (it != commands.end()) {
                    //auto comm = (command*)(it->second);
                    auto retval = static_cast<command*>(it->second)->exec(tokens, shared_object);
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

    // Dirty workaround
    std::vector<std::string>* _command_names;
    char** _getline_name_tab_completion(const char*, int, int);
    void shell_base::getline_init() {
        _command_names = &command_names;
        rl_attempted_completion_function = _getline_name_tab_completion;
    }

    char* _getline_name_generator(const char* pref, int state) {
        static int index, length;
        if (state == 0) {
            index = 0;
            length = strlen(pref);
        }
        for (; index < _command_names->size(); index++) {
            bool match = true;
            auto cname = (*_command_names)[index];
            for (int i = 0; i < SS_MIN(length, cname.length()); i++) {
                if (cname[i] != pref[i]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                index++;
                return strdup((*_command_names)[index - 1].c_str());
            }
        }
        return NULL;
    }

    char** _getline_name_tab_completion(const char* text, int start, int end) {
        return rl_completion_matches(text, _getline_name_generator);
    }

    _command_status help::exec(std::vector<std::string> params, void* shared_object = 0) {
        if (params.size() == 1) {
            *log << "Usage: help <command>\n";
            for (auto command : sh->command_names) {
                if (command != "help")
                    *log << "    " << command << std::endl;
            }
        }
        else {
            auto it = sh->commands.find(params[1]);
            if (it != sh->commands.end()) {
                *log << static_cast<command*>(it->second)->_help() << std::endl;
            }
            else {
                *log << "Unknown command `" << params[1] << "`\n";
            }

        }
        return COMSTAT_NORMAL;
    }

    bool command::check_param_num (std::vector<std::string>& params, int expected) {
        // If the number of parameters does not match the expectation, print an error message and the _help() and return false;
        // otherwise return true.
        if (params.size() < expected) {
            *log << "Too few parameters. Usage: " << std::endl << _help() << std::endl;
        }
        else if (params.size() > expected) {
            *log << "Too many parameters. Usage: " << std::endl << _help() << std::endl;
        }
        else
            return true;
        return false;
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