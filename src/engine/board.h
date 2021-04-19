#ifndef BOARD_H
#define BOARD_H

#include "core.h"
#include "util.h"
#include <string>
#include <bitset>

CHEDDAR_START

/**
 * A bitboard.
 */
typedef unsigned long long BitBoard;

/**
 * A set of 12 bitboards that represent a chess position.
 */
typedef struct Position {
    BitBoard whitePawns;
    BitBoard whiteKnights;
    BitBoard whiteBishops;
    BitBoard whiteRooks;
    BitBoard whiteQueens;
    BitBoard whiteKing;

    BitBoard blackPawns;
    BitBoard blackKnights;
    BitBoard blackBishops;
    BitBoard blackRooks;
    BitBoard blackQueens;
    BitBoard blackKing;

    BitBoard enPassantSquare;
    unsigned int castles;
    Color turn;
} Position;

inline void set_bit(BitBoard &board, unsigned int index) {
    board |= 0x8000000000000000 >> index;
}

inline void clear_bit(BitBoard &board, unsigned int index) {
    board &= ~(0x8000000000000000 >> index);
}

inline unsigned int get_bit(const BitBoard board, unsigned int index) {
    return (0x8000000000000000 >> index) & board != 0;
}

std::bitset<64> get_bits(const BitBoard board);

std::string bb_to_string(const BitBoard board);

/**
 * Returns a bitboard of white pieces in the given position.
 *
 * @param pos a Position of bitboards
 *
 * @return a bitboard
 */
inline BitBoard get_white_pieces(const Position pos) {
    return pos.whitePawns | pos.whiteKnights | pos.whiteBishops | pos.whiteRooks | pos.whiteQueens | pos.whiteKing;
}

/**
 * Returns a bitboard of black pieces in the given position.
 *
 * @param pos a Position of bitboards
 *
 * @return a bitboard
 */
inline BitBoard get_black_pieces(const Position pos) {
    return pos.blackPawns | pos.blackKnights | pos.blackBishops | pos.blackRooks | pos.blackQueens | pos.blackKing;
}

inline BitBoard get_white_pawn_starts() {
    return 0xffffULL << 48;
}

inline BitBoard get_black_pawn_starts() {
    return 0xffffULL << 8;
}

Position from_fen(std::string fen);

CHEDDAR_END

#endif
