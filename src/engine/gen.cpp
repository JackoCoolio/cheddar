#include <array>
#include "fill.h"
#include "gen.h"

CHEDDAR_START

/**
 * Isolates the least set 1 bit in a specified BitBoard.
 * 
 * @param board the BitBoard whose 
 *
 * @return a power of two
 */
inline BitBoard ls1b(const BitBoard &board) {
    return board & -board;
}

std::array<BitBoard, 16> generate_legal_target_bitboards(const Position pos) {
    BitBoard occupancy = ~get_all_pieces(pos);

    // generate black attacks

    // west
    BitBoard _attacks = west_attacks(pos.blackRooks | pos.blackQueens, occupancy ^ pos.whiteKing);
    BitBoard attacks = _attacks;
    BitBoard _super_attacks = east_attacks(pos.whiteKing, occupancy);
    BitBoard super_attacks_orth = _super_attacks;
    BitBoard horizontal_between = _attacks & _super_attacks;

    // east
    _attacks = east_attacks(pos.blackRooks | pos.blackQueens, occupancy ^ pos.whiteKing);
    attacks |= _attacks;
    _super_attacks = west_attacks(pos.whiteKing, occupancy);
    super_attacks_orth |= _super_attacks;
    horizontal_between |= _attacks & _super_attacks;

    // north
    _attacks = north_attacks(pos.blackRooks | pos.blackQueens, occupancy ^ pos.whiteKing);
    attacks |= _attacks;
    _super_attacks = south_attacks(pos.whiteKing, occupancy);
    super_attacks_orth |= _super_attacks;
    BitBoard vertical_between = _attacks & _super_attacks;

    // south
    _attacks = south_attacks(pos.blackRooks | pos.blackQueens, occupancy ^ pos.whiteKing);
    attacks |= _attacks;
    _super_attacks = north_attacks(pos.whiteKing, occupancy);
    super_attacks_orth |= _super_attacks;
    vertical_between |= _attacks & _super_attacks;

    // north east
    _attacks = ne_attacks(pos.blackQueens | pos.blackBishops, occupancy ^ pos.whiteKing);
    attacks |= _attacks;
    _super_attacks = sw_attacks(pos.whiteKing, occupancy);
    BitBoard super_attacks_diag = _super_attacks;
    BitBoard pdiag_between = _attacks & _super_attacks;

    // south west
    _attacks = sw_attacks(pos.blackQueens | pos.blackBishops, occupancy ^ pos.whiteKing);
    attacks |= _attacks;
    _super_attacks = ne_attacks(pos.whiteKing, occupancy);
    super_attacks_diag |= _super_attacks;
    pdiag_between |= _attacks & _super_attacks;

    // north west
    _attacks = nw_attacks(pos.blackQueens | pos.blackBishops, occupancy ^ pos.whiteKing);
    attacks |= _attacks;
    _super_attacks = se_attacks(pos.whiteKing, occupancy);
    super_attacks_diag |= _super_attacks;
    BitBoard ndiag_between = _attacks & _super_attacks;

    // south east
    _attacks = se_attacks(pos.blackQueens | pos.blackBishops, occupancy ^ pos.whiteKing);
    attacks |= _attacks;
    _super_attacks = nw_attacks(pos.whiteKing, occupancy);
    super_attacks_diag |= _super_attacks;
    ndiag_between |= _attacks & _super_attacks;

    // knight moves
    attacks |= knight_fill(pos.blackKnights);

    // pawn moves
    attacks |= south_pawn_attacks(pos.blackPawns);

    attacks |= king_fill(pos.blackKing);

    // white move gen

    BitBoard between = horizontal_between | vertical_between | pdiag_between | ndiag_between;
    BitBoard _blocks = between & occupancy;
    BitBoard _check_from =  (super_attacks_orth & (pos.blackRooks | pos.blackQueens)) |
                            (super_attacks_diag & (pos.blackBishops | pos.blackQueens)) |
                            (knight_fill(pos.whiteKing) & pos.blackKnights) |
                            (north_pawn_attacks(pos.whiteKing) & pos.blackPawns);

    long long _null_if_check = ((long long) (attacks & pos.whiteKing) - 1) >> 63;
    long long _null_if_double_check = ((long long) (_check_from & (_check_from - 1)) - 1) >> 63;

    BitBoard _check_to = _check_from | _blocks | _null_if_check;
    BitBoard target_mask = ~get_white_pieces(pos) & _check_to & _null_if_double_check;

    // sliders

    BitBoard _sliders = (pos.whiteRooks | pos.whiteQueens) & ~(between ^ horizontal_between);
    BitBoard west_move_targets = west_attacks(_sliders, occupancy) & target_mask;
    BitBoard east_move_targets = east_attacks(_sliders, occupancy) & target_mask;

    _sliders = (pos.whiteRooks | pos.whiteQueens) & ~(between ^ vertical_between);
    BitBoard north_move_targets = north_attacks(_sliders, occupancy) & target_mask;
    BitBoard south_move_targets = south_attacks(_sliders, occupancy) & target_mask;

    _sliders = (pos.whiteBishops | pos.whiteQueens) & ~(between ^ pdiag_between);
    BitBoard ne_move_targets = ne_attacks(_sliders, occupancy) & target_mask;
    BitBoard sw_move_targets = sw_attacks(_sliders, occupancy) & target_mask;

    _sliders = (pos.whiteBishops | pos.whiteQueens) & ~(between ^ ndiag_between);
    BitBoard nw_move_targets = nw_attacks(_sliders, occupancy) & target_mask;
    BitBoard se_move_targets = se_attacks(_sliders, occupancy) & target_mask;

    // knights
    BitBoard available_knights = pos.whiteKnights & ~between;
    BitBoard nne_move_targets = nne_fill(available_knights) & target_mask;
    BitBoard ene_move_targets = ene_fill(available_knights) & target_mask;
    BitBoard ese_move_targets = ese_fill(available_knights) & target_mask;
    BitBoard sse_move_targets = sse_fill(available_knights) & target_mask;
    BitBoard ssw_move_targets = ssw_fill(available_knights) & target_mask;
    BitBoard wsw_move_targets = wsw_fill(available_knights) & target_mask;
    BitBoard wnw_move_targets = wnw_fill(available_knights) & target_mask;
    BitBoard nnw_move_targets = nnw_fill(available_knights) & target_mask;

    // pawn captures
    BitBoard pawn_targets = (get_black_pieces(pos) & target_mask) | ((1ULL << pos.enPassant) & -(pos.enPassant < 64));
    BitBoard available_pawns = pos.whitePawns & ~(between ^ pdiag_between);
    ne_move_targets |= ne_one(available_pawns) & pawn_targets;

    available_pawns = pos.whitePawns & ~(between ^ ndiag_between);
    nw_move_targets |= nw_one(available_pawns) & pawn_targets;

    // pawn pushes
    available_pawns = pos.whitePawns & ~(between ^ vertical_between);
    BitBoard pawn_pushes = north_one(pos.whitePawns) & occupancy;
    north_move_targets |= pawn_pushes & target_mask;

    // double pawn pushes
    BitBoard double_pawn_pushes = north_one(pawn_pushes) & occupancy & target_mask & 0x00000000ff000000;
    north_move_targets |= double_pawn_pushes;

    // king moves
    target_mask = ~(get_white_pieces(pos) | attacks); // target mask is now a mask of safe squares for king

    north_move_targets  |= north_one(pos.whiteKing) & target_mask;
    ne_move_targets     |= ne_one(pos.whiteKing) & target_mask;
    se_move_targets     |= se_one(pos.whiteKing) & target_mask;
    south_move_targets  |= south_one(pos.whiteKing) & target_mask;
    sw_move_targets     |= sw_one(pos.whiteKing) & target_mask;
    nw_move_targets     |= nw_one(pos.whiteKing) & target_mask;

    // my solution to king-side castling
    BitBoard east_king_moves = east_one(pos.whiteKing) & target_mask;
    east_king_moves |= east_one(east_king_moves) & (pos.castles & ~attacks & _null_if_check & ~get_all_pieces(pos));
    BitBoard west_king_moves = west_one(pos.whiteKing) & target_mask; // make sure that there isn't a piece on b1 or c1
    BitBoard west_castle_mask = ~get_all_pieces(pos) & ~(get_all_pieces(pos) << 1);
    west_king_moves |= west_one(west_king_moves) & (pos.castles & ~attacks & _null_if_check) & west_castle_mask;

    east_move_targets |= east_king_moves;
    west_move_targets |= west_king_moves;

    return {
        north_move_targets,
        nne_move_targets,
        ne_move_targets,
        ene_move_targets,
        east_move_targets,
        ese_move_targets,
        se_move_targets,
        sse_move_targets,
        south_move_targets,
        ssw_move_targets,
        sw_move_targets,
        wsw_move_targets,
        west_move_targets,
        wnw_move_targets,
        nw_move_targets,
        nnw_move_targets,
    };
}

// magic array!
constexpr unsigned int magic[64] = {
     0,  1, 48,  2, 57, 49, 28,  3,
    61, 58, 50, 42, 38, 29, 17,  4,
    62, 55, 59, 36, 53, 51, 43, 22,
    45, 39, 33, 30, 24, 18, 12,  5,
    63, 47, 56, 27, 60, 41, 37, 16,
    54, 35, 52, 21, 44, 32, 23, 11,
    46, 26, 40, 15, 34, 20, 31, 10,
    25, 14, 19,  9, 13,  8,  7,  6
};

// magic number!
constexpr unsigned long long de_bruijn_seq = 0x03f79d71b4cb0a89;

/**
 * Returns the index of the first set bit in a 64-bit word.
 */
inline int bitscan(BitBoard board) {
    return magic[(ls1b(board) * de_bruijn_seq) >> 58];
}

MoveList generate_legal_moves(const Position _pos) {
    Position pos = (_pos.turn == White) ? _pos : mirror_position(_pos);
    MoveList move_list = { std::array<Move, MAX_MOVES>(), 0 };

    // generate move target bitboards
    std::array<BitBoard, 16> move_target_bitboards = generate_legal_target_bitboards(pos);
    BitBoard all_pieces = get_all_pieces(pos);

    // make en passant board
    BitBoard en_passant = 0ULL;
    set_bit(en_passant, pos.enPassant);

    // north
    BitBoard north_move_targets = move_target_bitboards[0];
    while (north_move_targets) {
        BitBoard target = ls1b(north_move_targets); // bitboard of move target
        BitBoard piece = south_blocker(target, ~all_pieces); // bitboard of moving piece

        unsigned int from = bitscan(piece);
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        if ((pos.whitePawns & piece) != 0) {
            int diff = to - from;

            if (to >= 56) {

                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::KNIGHT_PROMOTION | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::BISHOP_PROMOTION | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::ROOK_PROMOTION   | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::QUEEN_PROMOTION  | capture_flag);
            } else if (target && diff == 16) {
                move_list.append(to, from, Move::Flags::DOUBLE_PAWN_PUSH);
            } else {
                move_list.append(to, from, capture_flag);
            }
        } else {
            move_list.append(to, from, capture_flag);
        }

        north_move_targets &= north_move_targets - 1;
    }

    // north north east
    BitBoard nne_move_targets = move_target_bitboards[1];
    while (nne_move_targets) {
        BitBoard target = ls1b(nne_move_targets);

        unsigned int from = bitscan(ssw_fill(target)); // don't need an ssw_blocker func
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        nne_move_targets &= nne_move_targets - 1;
    }

    // north east
    BitBoard ne_move_targets = move_target_bitboards[2];
    while (ne_move_targets) {
        BitBoard target = ls1b(ne_move_targets); // bitboard of move target
        BitBoard piece = sw_blocker(target, ~all_pieces); // bitboard of moving piece

        unsigned int from = bitscan(piece);
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        if ((pos.whitePawns & piece) != 0) { // if the moving piece is a pawn
            if (to >= 56) { // promotion

                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::KNIGHT_PROMOTION | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::BISHOP_PROMOTION | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::ROOK_PROMOTION   | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::QUEEN_PROMOTION  | capture_flag);
            } else if (target & pos.enPassant != 0) { // en passant
                // we know it's a capture, so ignore capture_flag
                move_list.append(to, from, Move::Flags::EN_PASSANT | Move::Flags::CAPTURE);
            } else {
                move_list.append(to, from, capture_flag);
            }
        } else {
            move_list.append(to, from, capture_flag);
        }

        ne_move_targets &= ne_move_targets - 1;
    }

    // east north east
    BitBoard ene_move_targets = move_target_bitboards[3];
    while (ene_move_targets) {
        BitBoard target = ls1b(ene_move_targets);

        unsigned int from = bitscan(wsw_fill(target));
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        ene_move_targets &= ene_move_targets - 1;
    }

    // east
    BitBoard east_move_targets = move_target_bitboards[4];
    while (east_move_targets) {
        BitBoard target = ls1b(east_move_targets);
        BitBoard piece = west_blocker(target, ~all_pieces);

        unsigned int from = bitscan(piece);
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        if (pos.whiteKing == piece) { // if moving piece is a king
            int diff = to - from;

            if (diff == 2) {
                move_list.append(to, from, Move::Flags::KING_CASTLE);
            } else {
                move_list.append(to, from, capture_flag);
            }
        } else {
            move_list.append(to, from, capture_flag);
        }

        east_move_targets &= east_move_targets - 1;
    }

    // east south east
    BitBoard ese_move_targets = move_target_bitboards[5];
    while (ese_move_targets) {
        BitBoard target = ls1b(ese_move_targets);

        unsigned int from = bitscan(wnw_fill(target));
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        ese_move_targets &= ese_move_targets - 1;
    }

    // south east
    BitBoard se_move_targets = move_target_bitboards[6];
    while (se_move_targets) {
        BitBoard target = se_move_targets & -se_move_targets;
        BitBoard piece = nw_blocker(target, ~all_pieces);

        unsigned int from = bitscan(piece);
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        se_move_targets &= se_move_targets - 1;
    }

    // south south east
    BitBoard sse_move_targets = move_target_bitboards[7];
    while (sse_move_targets) {
        BitBoard target = ls1b(sse_move_targets);

        unsigned int from = bitscan(nnw_fill(target));
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        sse_move_targets &= sse_move_targets - 1;
    }

    // south
    BitBoard south_move_targets = move_target_bitboards[8];
    while (south_move_targets) {
        BitBoard target = south_move_targets & -south_move_targets;
        BitBoard piece = north_blocker(target, ~all_pieces);

        unsigned int from = bitscan(piece);
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        south_move_targets &= south_move_targets - 1;
    }

    // south south west
    BitBoard ssw_move_targets = move_target_bitboards[9];
    while (ssw_move_targets) {
        BitBoard target = ls1b(ssw_move_targets);

        unsigned int from = bitscan(nne_fill(target));
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        ssw_move_targets &= ssw_move_targets - 1;
    }

    // south west
    BitBoard sw_move_targets = move_target_bitboards[10];
    while (sw_move_targets) {
        BitBoard target = sw_move_targets & -sw_move_targets;
        BitBoard piece = ne_blocker(target, ~all_pieces);

        unsigned int from = bitscan(piece);
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        sw_move_targets &= sw_move_targets - 1;
    }

    // west south west
    BitBoard wsw_move_targets = move_target_bitboards[11];
    while (wsw_move_targets) {
        BitBoard target = ls1b(wsw_move_targets);

        unsigned int from = bitscan(ene_fill(target));
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        wsw_move_targets &= wsw_move_targets - 1;
    }

    // west
    BitBoard west_move_targets = move_target_bitboards[12];
    while (west_move_targets) {
        BitBoard target = ls1b(west_move_targets);
        BitBoard piece = east_blocker(target, ~all_pieces);

        unsigned int from = bitscan(piece);
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        if (pos.whiteKing == piece) { // if moving piece is a king
            int diff = to - from;

            if (diff == -3) {
                move_list.append(to, from, Move::Flags::QUEEN_CASTLE);
            } else {
                move_list.append(to, from, capture_flag);
            }
        } else {
            move_list.append(to, from, capture_flag);
        }

        west_move_targets &= west_move_targets - 1;
    }

    // west north west
    BitBoard wnw_move_targets = move_target_bitboards[13];
    while (wnw_move_targets) {
        BitBoard target = ls1b(wnw_move_targets);

        unsigned int from = bitscan(ese_fill(target));
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        wnw_move_targets &= wnw_move_targets - 1;
    }

    // north west
    BitBoard nw_move_targets = move_target_bitboards[14];
    while (nw_move_targets) {
        BitBoard target = ls1b(nw_move_targets); // bitboard of move target
        BitBoard piece = se_blocker(target, ~all_pieces); // bitboard of moving piece

        unsigned int from = bitscan(piece);
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        if ((pos.whitePawns & piece) != 0) { // if the moving piece is a pawn
            if (to >= 56) { // promotion
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::KNIGHT_PROMOTION | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::BISHOP_PROMOTION | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::ROOK_PROMOTION   | capture_flag);
                move_list.append(to, from, Move::Flags::PROMOTION | Move::Flags::QUEEN_PROMOTION  | capture_flag);
            } else if ((target & en_passant) != 0) { // en passant
                // we know it's a capture, so ignore capture_flag
                move_list.append(to, from, Move::Flags::EN_PASSANT | Move::Flags::CAPTURE);
            } else {
                move_list.append(to, from, capture_flag);
            }
        } else {
            move_list.append(to, from, capture_flag);
        }

        nw_move_targets &= nw_move_targets - 1;
    }

    // north north west
    BitBoard nnw_move_targets = move_target_bitboards[15];
    while (nnw_move_targets) {
        BitBoard target = ls1b(nnw_move_targets);

        unsigned int from = bitscan(sse_fill(target));
        unsigned int to = bitscan(target);

        const unsigned int capture_flag = ((target & all_pieces) != 0) * 4;

        move_list.append(to, from, capture_flag);

        nnw_move_targets &= nnw_move_targets - 1;
    }

    if (pos.turn == Black) {
        move_list.flip();
    }
    return move_list;
}

CHEDDAR_END
