#ifndef UI_H
#define UI_H

#include "../core.h"
#include <string>

#include "../engine/board.h"

CHEDDAR_START

class UI {
private:
    bool m_isready = true;
    Position m_position = {0};
    void unknown_error(std::string command);
public:
    /**
     * Parse a command string from the GUI.
     *
     * @param input the command string
     *
     * @return 1 if the program should exit
     */
    bool command(std::string input);
};

CHEDDAR_END

#endif
