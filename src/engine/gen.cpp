#include "gen.h"

CHEDDAR_START

BitBoard generate_pawn_moves(const Position pos, bool color) {
    if (color) {
        BitBoard captures = (pos.whitePawns >> 7 | pos.whitePawns >> 9) & get_black_pieces(pos);
        BitBoard double_moves = (pos.whitePawns & get_white_pawn_starts()) >> 16;
        BitBoard single_moves = pos.whitePawns >> 8;

        return captures | double_moves | single_moves;
    } else {
        BitBoard captures = (pos.blackPawns << 7 | pos.blackPawns << 9) & get_black_pieces(pos);
        BitBoard double_moves = (pos.blackPawns & get_black_pawn_starts()) << 16;
        BitBoard single_moves = pos.blackPawns << 8;

        return captures | double_moves | single_moves;
    }
}

CHEDDAR_END
