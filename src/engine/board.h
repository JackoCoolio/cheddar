#ifndef BOARD_H
#define BOARD_H

#include "../core.h"
#include "util.h"
#include <string>
#include <bitset>

CHEDDAR_START

/**
 * A bitboard.
 */
typedef unsigned long long BitBoard;

constexpr BitBoard EMPTY_BOARD = 0ULL;
constexpr BitBoard WHITE_KING_CASTLE = 0x0000000000000040;
constexpr BitBoard WHITE_QUEEN_CASTLE = 0x0000000000000004;
constexpr BitBoard BLACK_KING_CASTLE = 0x4000000000000000;
constexpr BitBoard BLACK_QUEEN_CASTLE = 0x0400000000000000;

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

    unsigned int enPassant;
    BitBoard castles;
    Color turn;
} Position;

BitBoard mirror_bitboard(const BitBoard board);

Position mirror_position(const Position pos);

std::string to_fen(const Position pos);

inline void set_bit(BitBoard &board, unsigned int index) {
    board |= 0x1ULL << index;
}

inline void clear_bit(BitBoard &board, unsigned int index) {
    board &= ~(0x1ULL << index);
}

inline unsigned int get_bit(const BitBoard board, unsigned int index) {
    return (board >> index) & 1ULL;
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

/**
 * Returns a bitboard of all pieces in the given position.
 *
 * @param pos a Position of bitboards
 *
 * @return a bitboard
 */
inline BitBoard get_all_pieces(Position pos) {
    return get_white_pieces(pos) | get_black_pieces(pos);
}

Position from_fen(std::string fen);

unsigned int alg_to_index(const std::string alg);
std::string index_to_alg(const unsigned int index);

CHEDDAR_END

#endif
