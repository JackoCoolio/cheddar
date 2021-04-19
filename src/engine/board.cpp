#include <cctype>
#include "board.h"

CHEDDAR_START

std::bitset<64> get_bits(const BitBoard board) {
    return std::bitset<64>(board);
}

std::string bb_to_string(const BitBoard board) {
    std::bitset<64> bits(board);
    std::string bits_str = bits.to_string();
    std::string out = "";
    std::string row = "";
    for (int i = 63; i >= 0; i--) {
        row = bits_str.at(i) + row;
        row = ' ' + row;
        if (i % 8 == 0) {
            out += row + "\n";
            row.clear();
        }
    }
    return out;
}

unsigned int fen_to_bb_index(int i, int skip_offset) {
    int out = i + skip_offset;
    out = 2 * (out % 8) + 56 - out;
    return out;
}

Position from_fen(std::string fen) {
    Position pos = {}; // set to zero
    int stage = 0;
    int skip_offset = 0;
    for (int i = 0; i < fen.length(); i++) {
        char c = fen.at(i);

        if (c == ' ') {
            stage++;
        } else {
            if (stage == 0) { // position
                // skip / characters
                if (c == '/') {
                    skip_offset--;
                    continue;
                }

                if (isdigit(c)) {
                    skip_offset += c - '0' - 1;
                } else {
                    unsigned int index = fen_to_bb_index(i, skip_offset);
                    if (c == 'p') {
                        set_bit(pos.blackPawns, index);
                    } else if (c == 'n') {
                        set_bit(pos.blackKnights, index);
                    } else if (c == 'b') {
                        set_bit(pos.blackBishops, index);
                    } else if (c == 'r') {
                        set_bit(pos.blackRooks, index);
                    } else if (c == 'q') {
                        set_bit(pos.blackQueens, index);
                    } else if (c == 'k') {
                        set_bit(pos.blackKing, index);
                    } else if (c == 'P') {
                        set_bit(pos.whitePawns, index);
                    } else if (c == 'N') {
                        set_bit(pos.whiteKnights, index);
                    } else if (c == 'B') {
                        set_bit(pos.whiteBishops, index);
                    } else if (c == 'R') {
                        set_bit(pos.whiteRooks, index);
                    } else if (c == 'Q') {
                        set_bit(pos.whiteQueens, index);
                    } else if (c == 'K') {
                        set_bit(pos.whiteKing, index);
                    }
                }
            } else if (stage == 1) {
                if (c == 'b') {
                    pos.turn = Black;
                } else {
                    pos.turn = White;
                }
            }

            // worry about castles and en passant later
        }
    }

    return pos;
}

CHEDDAR_END
