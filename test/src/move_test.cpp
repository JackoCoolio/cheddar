#include <gtest/gtest.h>

#include <move.h>
#include <util.h>

using namespace Cheddar;

TEST(Move, is_capture) {
    Move move(coords_to_int(0, 0), coords_to_int(0, 0), Move::Flags::CAPTURE);

    ASSERT_TRUE(move.is_capture());
}

TEST(Move, get) {
    Move move(coords_to_int(0, 0), coords_to_int(7, 7), Move::Flags::QUIET);

    ASSERT_EQ(move.get_to(), 0x00);
    ASSERT_EQ(move.get_from(), 0x3f);
    ASSERT_EQ(move.get_butterfly_index(), (63 << 6) | 0); // 1111 1100 0000
    ASSERT_EQ(move.get_flags(), Move::Flags::QUIET);
}

TEST(Move, set) {
    Move move(0, 0, 0);

    for (int i = 0; i < 64; i++) {
        move.set_from(i);
        ASSERT_EQ(move.get_from(), i);

        move.set_to(i);
        ASSERT_EQ(move.get_to(), i);
    }
}
