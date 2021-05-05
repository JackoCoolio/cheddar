#include "fill.h"

CHEDDAR_START

// using a macro here because it makes it much easier to understand in my opinion
// we get "occludedFill()" as defined in the Kogge-Stone page on CPW without the lookups
#define KS_DIR_FILL(gen, pro, dir)\
    gen |= pro & (gen << dir);\
    pro &= pro << dir;\
    gen |= pro & (gen << (dir * 2));\
    pro &= pro << (dir * 2);\
    gen |= pro & (gen << (dir * 4))

#define KS_DIR_FILL_NEG(gen, pro, dir)\
    gen |= pro & (gen >> dir);\
    pro &= pro >> dir;\
    gen |= pro & (gen >> (dir * 2));\
    pro &= pro >> (dir * 2);\
    gen |= pro & (gen >> (dir * 4))

BitBoard north_occl(const BitBoard board, const BitBoard open) {
    BitBoard gen = board;
    BitBoard pro = open;

    KS_DIR_FILL(gen, pro, 8);
    return gen;
}

BitBoard north_one(const BitBoard board) {
    return (board << 8);
}

BitBoard north_blocker(const BitBoard board, const BitBoard open) {
    return ~open & north_attacks(board, open);
}

BitBoard south_occl(const BitBoard board, const BitBoard open) {
    BitBoard gen = board;
    BitBoard pro = open;

    KS_DIR_FILL_NEG(gen, pro, 8);
    return gen;
}

BitBoard south_one(const BitBoard board) {
    return (board >> 8);
}

BitBoard south_blocker(const BitBoard board, const BitBoard open) {
    return ~open & south_attacks(board, open);
}

BitBoard east_occl(const BitBoard board, const BitBoard open) {
    BitBoard gen = board;
    BitBoard pro = open & ~A_FILE;

    KS_DIR_FILL(gen, pro, 1);
    return gen;
}

BitBoard east_one(const BitBoard board) {
    return ~A_FILE & (board << 1);
}

BitBoard east_blocker(const BitBoard board, const BitBoard open) {
    return ~open & east_attacks(board, open);
}

BitBoard west_occl(const BitBoard board, const BitBoard open) {
    BitBoard gen = board;
    BitBoard pro = open & ~H_FILE;

    KS_DIR_FILL_NEG(gen, pro, 1);
    return gen;
}

BitBoard west_one(const BitBoard board) {
    return ~H_FILE & (board >> 1);
}

BitBoard west_blocker(const BitBoard board, const BitBoard open) {
    return ~open & west_attacks(board, open);
}

BitBoard ne_occl(const BitBoard board, const BitBoard open) {
    BitBoard gen = board;
    BitBoard pro = open & ~A_FILE;

    KS_DIR_FILL(gen, pro, 9);
    return gen;
}

BitBoard ne_one(const BitBoard board) {
    return ~A_FILE & (board << 9);
}

BitBoard ne_blocker(const BitBoard board, const BitBoard open) {
    return ~open & ne_attacks(board, open);
}

BitBoard se_occl(const BitBoard board, const BitBoard open) {
    BitBoard gen = board;
    BitBoard pro = open & ~A_FILE;

    KS_DIR_FILL_NEG(gen, pro, 7);
    return gen;
}

BitBoard se_one(const BitBoard board) {
    return ~A_FILE & (board >> 7);
}

BitBoard se_blocker(const BitBoard board, const BitBoard open) {
    return ~open & se_attacks(board, open);
}

BitBoard sw_occl(const BitBoard board, const BitBoard open) {
    BitBoard gen = board;
    BitBoard pro = open & ~H_FILE;

    KS_DIR_FILL_NEG(gen, pro, 9);
    return gen;
}

BitBoard sw_one(const BitBoard board) {
    return ~H_FILE & (board >> 9);
}

BitBoard sw_blocker(const BitBoard board, const BitBoard open) {
    return ~open & sw_attacks(board, open);
}

BitBoard nw_occl(const BitBoard board, const BitBoard open) {
    BitBoard gen = board;
    BitBoard pro = open & ~H_FILE;

    KS_DIR_FILL(gen, pro, 7);
    return gen;
}

BitBoard nw_one(const BitBoard board) {
    return ~H_FILE & (board << 7);
}

BitBoard nw_blocker(const BitBoard board, const BitBoard open) {
    return ~open & nw_attacks(board, open);
}

BitBoard king_fill(const BitBoard king) {
    BitBoard out = king | east_one(king) | west_one(king);
    out |= north_one(out) | south_one(out);

    // Note: kings defending each other won't be included in this fill,
    // but that's impossible, so...
    return out ^ king;
}

CHEDDAR_END
