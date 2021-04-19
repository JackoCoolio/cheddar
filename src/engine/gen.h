#ifndef GEN_H
#define GEN_H

#include "util.h"
#include "board.h"
#include "core.h"

CHEDDAR_START

BitBoard generate_pawn_moves(const Position pos, Color color);

BitBoard generate_knight_moves(const Position pos, Color color);

CHEDDAR_END

#endif
