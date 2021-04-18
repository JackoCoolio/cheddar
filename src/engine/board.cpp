#include "board.h"

CHEDDAR_START

Position from_fen(std::string fen) {
    Position pos;
    for (int i = 0; i < fen.length(); i++) {
        char c = fen.at(i);

        if (c == ' ') {

        }
    }

    return pos;
}

CHEDDAR_END
