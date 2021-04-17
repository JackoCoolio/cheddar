typedef unsigned long long U64;

typedef struct Position {
    U64 whitePawns;
    U64 whiteKnights;
    U64 whiteBishops;
    U64 whiteRooks;
    U64 whiteQueens;
    U64 whiteKing;

    U64 blackPawns;
    U64 blackKnights;
    U64 blackBishops;
    U64 blackRooks;
    U64 blackQueens;
    U64 blackKing;
} Position;

/**
 * Returns a bitboard of white pieces in the given position.
 */
inline U64 get_white_pieces(Position &pos) {
    return pos.whitePawns | pos.whiteKnights | pos.whiteBishops | pos.whiteRooks | pos.whiteQueens | pos.whiteKing;
}

/**
 * Returns a bitboard of black pieces in the given position.
 */
inline U64 get_black_pieces(Position &pos) {
    return pos.blackPawns | pos.blackKnights | pos.blackBishops | pos.blackRooks | pos.blackQueens | pos.blackKing;
}
