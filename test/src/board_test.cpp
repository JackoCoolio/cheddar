#include <gtest/gtest.h>
#include <iostream>

#include "test_util.h"
#include "board.h"
#include "util.h"

using namespace Cheddar;

TEST(Board, standard_fen) {
    Position pos = from_fen(STANDARD_FEN);

    // test white
    ASSERT_EQ(pos.whitePawns,   0x000000000000ff00);
    ASSERT_EQ(pos.whiteKnights, 0x0000000000000042);
    ASSERT_EQ(pos.whiteBishops, 0x0000000000000024);
    ASSERT_EQ(pos.whiteRooks,   0x0000000000000081);
    ASSERT_EQ(pos.whiteQueens,  0x0000000000000008);
    ASSERT_EQ(pos.whiteKing,    0x0000000000000010);

    ASSERT_EQ(pos.blackPawns,   0x00ff000000000000);
    ASSERT_EQ(pos.blackKnights, 0x4200000000000000);
    ASSERT_EQ(pos.blackBishops, 0x2400000000000000);
    ASSERT_EQ(pos.blackRooks,   0x8100000000000000);
    ASSERT_EQ(pos.blackQueens,  0x0800000000000000);
    ASSERT_EQ(pos.blackKing,    0x1000000000000000);

    ASSERT_EQ(pos.enPassant, 64);

    pos = from_fen("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");
    ASSERT_EQ(pos.enPassant, 20);
}

TEST(Board, alg_to_index) {
    ASSERT_EQ(alg_to_index("a1"), 0);
    ASSERT_EQ(alg_to_index("a8"), 56);
    ASSERT_EQ(alg_to_index("h8"), 63);
    ASSERT_EQ(alg_to_index("h1"), 7);
    ASSERT_EQ(alg_to_index("-"), 64); // invalid index
}

TEST(Board, index_to_alg) {
    ASSERT_STREQ(index_to_alg(0).c_str(), "a1");
    ASSERT_STREQ(index_to_alg(56).c_str(), "a8");
    ASSERT_STREQ(index_to_alg(63).c_str(), "h8");
    ASSERT_STREQ(index_to_alg(7).c_str(), "h1");
}

TEST(Board, castles) {
    // all castles
    Position pos = from_fen("rnb1kb1r/pp3p1p/2p1pnp1/q2p4/2PP4/2N1PN2/PP2BPPP/R1BQK2R w KQkq - 0 1");
    ASSERT_EQ(pos.castles, WHITE_KING_CASTLE | WHITE_QUEEN_CASTLE | BLACK_KING_CASTLE | BLACK_QUEEN_CASTLE);

    // one castle missing
    pos = from_fen("rnb1kb1r/pp3p1p/2p1pnp1/q2p4/2PP4/2N1PN2/PP2BPPP/R1BQK2R w Kkq - 0 1");
    ASSERT_EQ(pos.castles, WHITE_KING_CASTLE | BLACK_KING_CASTLE | BLACK_QUEEN_CASTLE);

    // no castles
    pos = from_fen("rnb1kb1r/pp3p1p/2p1pnp1/q2p4/2PP4/2N1PN2/PP2BPPP/R1BQK2R w - - 0 1");
    ASSERT_EQ(pos.castles, 0);

    // a bunch of junk characters
    pos = from_fen("rnb1kb1r/pp3p1p/2p1pnp1/q2p4/2PP4/2N1PN2/PP2BPPP/R1BQK2R w asdfhfdieERTYTREB - 0 1");
    ASSERT_EQ(pos.castles, 0);
}

TEST(Board, mirror_bitboard) {
    BitBoard board = 0x00000000000000ff;
    ASSERT_EQ(mirror_bitboard(board), 0xff00000000000000);
}

TEST(Board, to_fen) {
    FenMap fens = get_test_fens();

    for (std::pair<std::string, unsigned int> pair : fens) {
        Position pos = from_fen(pair.first);
        std::string output_fen = to_fen(pos);

        ASSERT_STREQ(pair.first.c_str(), output_fen.c_str());
    }
}