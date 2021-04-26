/**
 * Based on https://www.chessprogramming.org/Kogge-Stone_Algorithm
 */

#ifndef FILL_H
#define FILL_H

#include "board.h"

CHEDDAR_START

constexpr BitBoard A_FILE       = 0x0101010101010101;
constexpr BitBoard B_FILE       = 0x0202020202020202;
constexpr BitBoard G_FILE       = 0x4040404040404040;
constexpr BitBoard H_FILE       = 0x8080808080808080;
constexpr BitBoard FIRST_RANK   = 0x00000000000000ff;
constexpr BitBoard EIGHTH_RANK  = 0xff00000000000000;

#define north_attacks(board, open) Cheddar::north_one(Cheddar::north_occl(board, open), ~0ULL)
#define east_attacks(board, open) Cheddar::east_one(Cheddar::east_occl(board, open), ~0ULL)
#define south_attacks(board, open) Cheddar::south_one(Cheddar::south_occl(board, open), ~0ULL)
#define west_attacks(board, open) Cheddar::west_one(Cheddar::west_occl(board, open), ~0ULL)
#define ne_attacks(board, open) Cheddar::ne_one(Cheddar::ne_occl(board, open), ~0ULL)
#define se_attacks(board, open) Cheddar::se_one(Cheddar::se_occl(board, open), ~0ULL)
#define sw_attacks(board, open) Cheddar::sw_one(Cheddar::sw_occl(board, open), ~0ULL)
#define nw_attacks(board, open) Cheddar::nw_one(Cheddar::nw_occl(board, open), ~0ULL)
#define north_pawn_attacks(board) (Cheddar::nw_one(board, 0) | Cheddar::ne_one(board, 0))
#define south_pawn_attacks(board) (Cheddar::sw_one(board, 0) | Cheddar::se_one(board, 0))

// NORTH

BitBoard north_occl(const BitBoard board, const BitBoard open);
BitBoard north_one(const BitBoard board, const BitBoard open);

// SOUTH

BitBoard south_occl(const BitBoard board, const BitBoard open);
BitBoard south_one(const BitBoard board, const BitBoard open);

// EAST

BitBoard east_occl(const BitBoard board, const BitBoard open);
BitBoard east_one(const BitBoard board, const BitBoard open);

// WEST

BitBoard west_occl(const BitBoard board, const BitBoard open);
BitBoard west_one(const BitBoard board, const BitBoard open);

// NORTH EAST

BitBoard ne_occl(const BitBoard board, const BitBoard open);
BitBoard ne_one(const BitBoard board, const BitBoard open);

// SOUTH EAST

BitBoard se_occl(const BitBoard board, const BitBoard open);
BitBoard se_one(const BitBoard board, const BitBoard open);

// SOUTH WEST

BitBoard sw_occl(const BitBoard board, const BitBoard open);
BitBoard sw_one(const BitBoard board, const BitBoard open);

// NORTH WEST

BitBoard nw_occl(const BitBoard board, const BitBoard open);
BitBoard nw_one(const BitBoard board, const BitBoard open);

// KNIGHT MOVES

inline BitBoard nne_fill(const BitBoard knights) {
    return (knights << 17) & ~A_FILE; // good
}

inline BitBoard ene_fill(const BitBoard knights) {
    return (knights << 10) & ~A_FILE & ~B_FILE;
}

inline BitBoard ese_fill(const BitBoard knights) {
    return (knights >> 6) & ~A_FILE & ~B_FILE;
}

inline BitBoard sse_fill(const BitBoard knights) {
    return (knights >> 15) & ~A_FILE;
}

inline BitBoard ssw_fill(const BitBoard knights) {
    return (knights >> 17) & ~H_FILE;
}

inline BitBoard wsw_fill(const BitBoard knights) {
    return (knights >> 10) & ~G_FILE & ~H_FILE;
}

inline BitBoard wnw_fill(const BitBoard knights) {
    return (knights << 6) & ~G_FILE & ~H_FILE;
}

inline BitBoard nnw_fill(const BitBoard knights) {
    return (knights << 15) & ~H_FILE;
}

inline BitBoard knight_fill(const BitBoard knights) {
    return nne_fill(knights) |
        ene_fill(knights) |
        ese_fill(knights) |
        sse_fill(knights) |
        ssw_fill(knights) |
        wsw_fill(knights) |
        wnw_fill(knights) |
        nnw_fill(knights);
}

// KING MOVES

BitBoard king_fill(const BitBoard king);

CHEDDAR_END

#endif
