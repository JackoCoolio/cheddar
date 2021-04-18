#include <core.h>

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
} Position;

/**
 * Returns a bitboard of white pieces in the given position.
 *
 * @param pos a Position of bitboards
 *
 * @return a bitboard
 */
inline BitBoard get_white_pieces(Position &pos) {
    return pos.whitePawns | pos.whiteKnights | pos.whiteBishops | pos.whiteRooks | pos.whiteQueens | pos.whiteKing;
}

/**
 * Returns a bitboard of black pieces in the given position.
 *
 * @param pos a Position of bitboards
 *
 * @return a bitboard
 */
inline BitBoard get_black_pieces(Position &pos) {
    return pos.blackPawns | pos.blackKnights | pos.blackBishops | pos.blackRooks | pos.blackQueens | pos.blackKing;
}

CHEDDAR_END
