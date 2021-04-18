/**
 * Adapted from https://www.chessprogramming.org/Encoding_Moves
 */

namespace Cheddar {

    constexpr unsigned int CAPTURE_FLAG = 0x4000;

    class Move {

    // unsigned int is interpreted like so:
    // XXXX XXXXXX XXXXXX
    // flgs  from    to
    // flags are:
    // promotion, capture, special 1 & 0

    public:

        /**
         * Constructs a move from the specified TO square to the specified FROM square with flags.
         */
        Move(unsigned int to, unsigned int from, unsigned int flags);

        void operator=(Move other);
        bool operator==(Move other) const;
        bool operator!=(Move other) const;

        /**
         * Returns the board-index of the TO square of this move.
         */
        unsigned int get_to() const;

        /**
         * Returns the board-index of the FROM square of this move.
         */
        unsigned int get_from() const;

        /**
         * Returns the flags for this move.
         */
        unsigned int get_flags() const;

        /**
         * Sets the board-index of the TO square for this move.
         */
        void set_to(unsigned int to);

        /**
         * Sets the board-index of the FROM square for this move.
         */
        void set_from(unsigned int from);

        /**
         * Returns true if this move is a capture.
         */
        bool is_capture() const;

        /**
         * Returns the butterfly index for this move.
         */
        unsigned int get_butterfly_index() const;

    protected:
        unsigned int m_move;


    };

}