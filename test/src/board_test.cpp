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
}