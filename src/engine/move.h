/**
 * Adapted from https://www.chessprogramming.org/Encoding_Moves
 */

#include <core.h>

CHEDDAR_START

class Move {

public:

    /**
     * Constructs a move from the specified TO square to the specified FROM square with flags.
     *
     * @param to a 6-bit integer index
     * @param from a 6-bit integer index
     * @param flags 4 bits: promotion, capture, and two bits for special moves
     */
    Move(unsigned int to, unsigned int from, unsigned int flags);

    void operator=(Move other);
    bool operator==(Move other) const;
    bool operator!=(Move other) const;

    /**
     * Returns the board-index of the TO square of this move.
     *
     * @return a 6-bit integer index
     */
    unsigned int get_to() const;

    /**
     * Returns the board-index of the FROM square of this move.
     *
     * @return a 6-bit integer index
     */
    unsigned int get_from() const;

    /**
     * Returns the flags for this move.
     *
     * @return 4 bits: promotion, capture, and two bits for special moves
     */
    unsigned int get_flags() const;

    /**
     * Sets the board-index of the TO square for this move.
     *
     * @param to a 6-bit integer index
     */
    void set_to(unsigned int to);

    /**
     * Sets the board-index of the FROM square for this move.
     *
     * @param from a 6-bit integer index
     */
    void set_from(unsigned int from);

    /**
     * Returns true if this move is a capture.
     *
     * @return true if this move is a capture
     */
    bool is_capture() const;

    /**
     * Returns the butterfly index for this move.
     *
     * @return a 12 bit unsigned integer: the FROM square and the TO square
     */
    unsigned int get_butterfly_index() const;

protected:

    // m_move is interpreted like so:
    // XXXX XXXXXX XXXXXX
    // flgs  from    to
    unsigned int m_move;

};

CHEDDAR_END