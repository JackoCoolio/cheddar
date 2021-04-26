#include <gtest/gtest.h>

#include "board.h"
#include "fill.h"

using namespace Cheddar;

TEST(Fill, north) {
    Position pos = from_fen("8/8/8/8/8/8/8/RRRRRRRR w - - 0 1");

    BitBoard occl = north_occl(pos.whiteRooks, ~get_all_pieces(pos));

    // test that filling on empty board will fill the entire board
    ASSERT_EQ(occl | pos.whiteRooks, ~0ULL);

    pos = from_fen("8/8/pppppppp/8/8/8/8/RRRRRRRR w - - 0 1");

    occl = north_occl(pos.whiteRooks, ~get_all_pieces(pos));

    // test that a row of pawns blocks the occl fill
    ASSERT_EQ(occl | pos.whiteRooks, 0x000000ffffffffff);
}

TEST(Fill, east) {
    Position pos = from_fen("R7/R7/R7/R7/R7/R7/R7/R7 w - - 0 1");

    BitBoard occl = east_occl(pos.whiteRooks, ~get_all_pieces(pos));

    // test that filling on empty board will fill the entire board
    ASSERT_EQ(occl | pos.whiteRooks, ~0ULL);

    pos = from_fen("R4p2/R4p2/R4p2/R4p2/R4p2/R4p2/R4p2/R4p2 w - - 0 1");

    occl = east_occl(pos.whiteRooks, ~get_all_pieces(pos));

    // test that a row of pawns blocks the occl fill
    ASSERT_EQ(occl | pos.whiteRooks, 0x1f1f1f1f1f1f1f1f);
}

TEST(Fill, south) {
    Position pos = from_fen("RRRRRRRR/8/8/8/8/8/8/8 w - - 0 1");

    BitBoard occl = south_occl(pos.whiteRooks, ~get_all_pieces(pos));

    // test that filling on empty board will fill the entire board
    ASSERT_EQ(occl | pos.whiteRooks, ~0ULL);

    pos = from_fen("RRRRRRRR/8/8/8/8/pppppppp/8/8 w - - 0 1");

    occl = south_occl(pos.whiteRooks, ~get_all_pieces(pos));

    // test that a row of pawns blocks the occl fill
    ASSERT_EQ(occl | pos.whiteRooks, 0xffffffffff000000);
}

TEST(Fill, west) {
    Position pos = from_fen("7R/7R/7R/7R/7R/7R/7R/7R w - - 0 1");

    BitBoard occl = west_occl(pos.whiteRooks, ~get_all_pieces(pos));

    // test that filling on empty board will fill the entire board
    ASSERT_EQ(occl | pos.whiteRooks, ~0ULL);

    pos = from_fen("2p4R/2p4R/2p4R/2p4R/2p4R/2p4R/2p4R/2p4R w - - 0 1");

    occl = west_occl(pos.whiteRooks, ~get_all_pieces(pos));

    // test that a row of pawns blocks the occl fill
    ASSERT_EQ(occl | pos.whiteRooks, 0xf8f8f8f8f8f8f8f8);
}

TEST(Fill, ne) {
    Position pos = from_fen("Q7/Q7/Q7/Q7/Q7/Q7/Q7/QQQQQQQQ w - - 0 1");

    BitBoard occl = ne_occl(pos.whiteQueens, ~get_all_pieces(pos));

    // test that filling on an empty board will fill the entire board
    ASSERT_EQ(occl | pos.whiteQueens, ~0ULL);

    pos = from_fen("Qpp5/Q1pp4/Q2pp3/Q3pp2/Q4pp1/Q5pp/Q6p/QQQQQQQQ w - - 0 1");

    occl = ne_occl(pos.whiteQueens, ~get_all_pieces(pos));

    ASSERT_EQ(occl | pos.whiteQueens, 0x0103070f1f3f7fff);
}

TEST(Fill, se) {
    Position pos = from_fen("QQQQQQQQ/Q7/Q7/Q7/Q7/Q7/Q7/Q7 w - - 0 1");

    BitBoard occl = se_occl(pos.whiteQueens, ~get_all_pieces(pos));

    ASSERT_EQ(occl | pos.whiteQueens, ~0ULL);

    pos = from_fen("QQQQQQQQ/Q6p/Q5pp/Q4pp1/Q3pp2/Q2pp3/Q1pp4/Qpp5 w - - 0 1");

    occl = se_occl(pos.whiteQueens, ~get_all_pieces(pos));

    ASSERT_EQ(occl | pos.whiteQueens, 0xff7f3f1f0f070301);
}

TEST(Fill, sw) {
    Position pos = from_fen("QQQQQQQQ/7Q/7Q/7Q/7Q/7Q/7Q/7Q w - - 0 1");

    BitBoard occl = sw_occl(pos.whiteQueens, ~get_all_pieces(pos));

    ASSERT_EQ(occl | pos.whiteQueens, ~0ULL);

    pos = from_fen("QQQQQQQQ/p6Q/pp5Q/1pp4Q/2pp3Q/3pp2Q/4pp1Q/5ppQ w - - 0 1");

    occl = sw_occl(pos.whiteQueens, ~get_all_pieces(pos));

    ASSERT_EQ(occl | pos.whiteQueens, 0xfffefcf8f0e0c080);
}

TEST(Fill, nw) {
    Position pos = from_fen("7Q/7Q/7Q/7Q/7Q/7Q/7Q/QQQQQQQQ w - - 0 1");

    BitBoard occl = nw_occl(pos.whiteQueens, ~get_all_pieces(pos));

    ASSERT_EQ(occl | pos.whiteQueens, ~0ULL);

    pos = from_fen("5ppQ/4pp1Q/3pp2Q/2pp3Q/1pp4Q/pp5Q/p6Q/QQQQQQQQ w - - 0 1");

    occl = nw_occl(pos.whiteQueens, ~get_all_pieces(pos));

    ASSERT_EQ(occl | pos.whiteQueens, 0x80c0e0f0f8fcfeff);
}

TEST(Fill, knight) {
    Position pos = from_fen("8/8/1N4N1/8/4N3/8/N6N/8 w - - 0 1");

    BitBoard fill = knight_fill(pos.whiteKnights);

    ASSERT_EQ(fill, 0xa518285ce7642824);
}

TEST(Fill, king) {
    Position pos = from_fen("K6K/8/8/8/3K4/8/8/K6K w - - 0 1");

    BitBoard fill = king_fill(pos.whiteKing);

    ASSERT_EQ(fill, 0x42c3001c141cc342);
}
