#include <cctype>
#include "board.h"

CHEDDAR_START

std::bitset<64> get_bits(const BitBoard board) {
    return std::bitset<64>(board);
}

std::string bb_to_string(const BitBoard board) {
    std::string out = "";
    std::string row = "";
    for (int i = 63; i >= 0; i--) {
        unsigned int bit = get_bit(board, i);

        char c = bit ? 'x' : '-';
        row = c + (" " + row);

        if (i % 8 == 0) {
            out += row + '\n';
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
    pos.enPassant = 64;
    pos.castles = 0;
    int stage = 0;
    int skip_offset = 0;
    int ep_file = -1;
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
            } else if (stage == 2) {
                if (c == 'k') {
                    pos.castles |= BLACK_KING_CASTLE;
                } else if (c == 'K') {
                    pos.castles |= WHITE_KING_CASTLE;
                } else if (c == 'q') {
                    pos.castles |= BLACK_QUEEN_CASTLE;
                } else if (c == 'Q') {
                    pos.castles |= WHITE_QUEEN_CASTLE;
                }
            } else if (stage == 3) {
                if (c == '-') continue;

                if (isalpha(c) && ep_file == -1) {
                    ep_file = tolower(c) - 'a';
                } else if (isdigit(c)) {
                    pos.enPassant = (c - '1') * 8 + ep_file;
                }
            }

        }
    }

    return pos;
}

unsigned int alg_to_index(const std::string alg) {
    if (alg.size() != 2) {
        return 64;
    }

    int file = tolower(alg.at(0)) - 'a';
    int rank = alg.at(1) - '1';

    return  rank * 8 + file;
}

CHEDDAR_END
