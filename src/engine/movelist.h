#ifndef MOVELIST_H
#define MOVELIST_H

#include <array>
#include "move.h"
#include "../core.h"

CHEDDAR_START

// As far as I can tell, the maximum possible number of moves is 218.
constexpr size_t MAX_MOVES = 256;

/**
 * A container of Moves with a maximum capacity of 256.
 */
typedef struct MoveList {

    /**
     * The list of Moves.
     */
    std::array<Move, MAX_MOVES> moves;

    /**
     * The number of Moves in the list.
     */
    unsigned int count;

    /**
     * Appends a Move to the MoveList.
     *
     * @param Move the Move to append
     */
    inline void append(Move move) {
        moves[count++] = move;

        #ifdef DEBUG_MOVE_APPENDS
        std::cout << "Append: " << index_to_alg(move.get_from()) << index_to_alg(move.get_to()) << std::endl;
        #endif
    }

    /**
     * Appends a Move to the MoveList.
     *
     * @param to the to index of the Move
     * @param from the from index of the Move
     * @param flags the flags for the Move
     */
    inline void append(unsigned int to, unsigned int from, unsigned int flags) {
        append(Move(to, from, flags));
    }

    /**
     * Flips all Moves across the 4th and 5th rank axis.
     */
    inline void flip() {
        for (Move move : moves) {
            move.flip();
        }
    }

    typedef std::array<Move, MAX_MOVES>::iterator iterator;
    typedef std::array<Move, MAX_MOVES>::const_iterator const_iterator;
    iterator begin() { return &moves[0]; }
    iterator end() { return &moves[count]; }

} MoveList;

CHEDDAR_END

#endif
