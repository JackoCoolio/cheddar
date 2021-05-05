#include "move.h"

using namespace Cheddar;

// returns the last 16 bits, because those are the only bits that are relevant
#define MASK_IMPORTANT_BITS(move) (move & 0xffff)

Move::Move() {
    m_move = 0;
}

Move::Move(unsigned int to, unsigned int from) {
    m_move = ((from & 0x3f) << 6) | (to & 0x3f);
}

Move::Move(unsigned int to, unsigned int from, unsigned int flags) {
    m_move = ((flags & 0xf) << 12) | ((from & 0x3f) << 6) | (to & 0x3f);
}

void Move::operator=(Move other) {
    m_move = other.m_move;
}

bool Move::operator==(Move other) const {
    return MASK_IMPORTANT_BITS(m_move) == MASK_IMPORTANT_BITS(other.m_move);
}

bool Move::operator!=(Move other) const {
    return MASK_IMPORTANT_BITS(m_move) != MASK_IMPORTANT_BITS(other.m_move);
}

unsigned int Move::get_to() const {
    return m_move & 0x3f; // return last 6 bits
}

unsigned int Move::get_from() const {
    return (m_move >> 6) & 0x3f; // return 6 bits before the last 6
}

unsigned int Move::get_flags() const {
    return (m_move >> 12) & 0xf; // return 4 bits before the last 12
}

void Move::set_to(unsigned int to) {
    m_move &= ~0x3f; // clear TO bits
    m_move |= (to & 0x3f); // set TO bits
}

void Move::set_from(unsigned int from) {
    m_move &= ~(0x3f << 6); // clear FROM bits. note: cpw calculates this instead of bitshifting
    m_move |= ((from & 0x3f) << 6); // set FROM bits
}

bool Move::is_capture() const {
    return (0x4000 & m_move) != 0;
}

unsigned int Move::get_butterfly_index() const {
    return m_move & 0xfff; // return last 12 bits
}

void Move::flip() {
    m_move = ((63 - get_to()) & 0x3f) | ((63 - get_from()) & 0x3f) << 6 | get_flags() << 12;
}
