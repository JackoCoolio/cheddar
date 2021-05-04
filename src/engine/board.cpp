#include <cctype>
#include "board.h"

CHEDDAR_START

BitBoard mirror_bitboard(const BitBoard board) {
    const BitBoard k1 = 0x00ff00ff00ff00ff;
    const BitBoard k2 = 0x0000ffff0000ffff;
    BitBoard out = board;

    out = ((out >>  8) & k1) | ((out & k1) <<  8);
    out = ((out >> 16) & k2) | ((out & k2) << 16);
    out = ( out >> 32)       | ( out       << 32);
    return out;
}

Position mirror_position(const Position pos) {
    return {
        mirror_bitboard(pos.blackPawns),
        mirror_bitboard(pos.blackKnights),
        mirror_bitboard(pos.blackBishops),
        mirror_bitboard(pos.blackRooks),
        mirror_bitboard(pos.blackQueens),
        mirror_bitboard(pos.blackKing),
        mirror_bitboard(pos.whitePawns),
        mirror_bitboard(pos.whiteKnights),
        mirror_bitboard(pos.whiteBishops),
        mirror_bitboard(pos.whiteRooks),
        mirror_bitboard(pos.whiteQueens),
        mirror_bitboard(pos.whiteKing),
        pos.enPassant ^ 56,
        mirror_bitboard(pos.castles),
        1 - pos.turn
    };
}

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

std::string to_fen(const Position pos) {
    std::string out = "";

    // piece section
    unsigned int blanks = 0;
    for (int i = 0; i < 64; i++) {
        int index = fen_to_bb_index(i, 0);

        // check if the blanks count needs to be printed
        if (blanks != 0) {
            if (get_bit(get_all_pieces(pos), index) || i % 8 == 0) {
                out += '0' + blanks;
                blanks = 0;
            }
        }

        if (i % 8 == 0 && i != 0) {
            out += '/';
        }

        // print the piece char or increment blanks count
        if (get_bit(pos.whitePawns, index)) {
            out += 'P';
        } else if (get_bit(pos.whiteKnights, index)) {
            out += 'N';
        } else if (get_bit(pos.whiteBishops, index)) {
            out += 'B';
        } else if (get_bit(pos.whiteRooks, index)) {
            out += 'R';
        } else if (get_bit(pos.whiteQueens, index)) {
            out += 'Q';
        } else if (get_bit(pos.whiteKing, index)) {
            out += 'K';
        } else if (get_bit(pos.blackPawns, index)) {
            out += 'p';
        } else if (get_bit(pos.blackKnights, index)) {
            out += 'n';
        } else if (get_bit(pos.blackBishops, index)) {
            out += 'b';
        } else if (get_bit(pos.blackRooks, index)) {
            out += 'r';
        } else if (get_bit(pos.blackQueens, index)) {
            out += 'q';
        } else if (get_bit(pos.blackKing, index)) {
            out += 'k';
        } else {
            blanks++;
        }
    }

    if (blanks > 0) {
        out += '0' + blanks;
    }

    out += ' ';

    // turn section
    if (pos.turn == White) {
        out += 'w';
    } else {
        out += 'b';
    }

    out += ' ';

    // castles section
    if (!pos.castles) {
        out += '-';
    } else {
        if (WHITE_KING_CASTLE & pos.castles) {
            out += 'K';
        }
        if (WHITE_QUEEN_CASTLE & pos.castles) {
            out += 'Q';
        }
        if (BLACK_KING_CASTLE & pos.castles) {
            out += 'k';
        }
        if (BLACK_QUEEN_CASTLE & pos.castles) {
            out += 'q';
        }
    }

    out += ' ';

    // en passant
    if (pos.enPassant > 63) { // unsigned, so don't need to check for < 0
        out += '-';
    } else {
        out += index_to_alg(pos.enPassant);
    }

    // TODO: implement turn counts
    out += " 0 0";

    return out;
}

unsigned int alg_to_index(const std::string alg) {
    if (alg.size() != 2) {
        return 64;
    }

    int file = tolower(alg.at(0)) - 'a';
    int rank = alg.at(1) - '1';

    return  rank * 8 + file;
}

std::string index_to_alg(const unsigned int index) {
    int rank = index / 8;
    int file = index % 8;

    char rank_char = '1' + rank;
    char file_char = 'a' + file;

    std::string out = "";
    out += file_char;
    out += rank_char;

    return out;
}

CHEDDAR_END
