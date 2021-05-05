#ifndef GEN_H
#define GEN_H

#include <array>

#include "movelist.h"
#include "board.h"
#include "core.h"

CHEDDAR_START

/**
 * Generate a list of legal moves for the player whose pawns move UP the board.
 *
 * @param pos the Position to determine moves for
 *
 * @return a MoveList of maximum capacity 256
 */
MoveList generate_legal_moves(const Position pos);

CHEDDAR_END

#endif
