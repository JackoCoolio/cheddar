#include <core.h>

CHEDDAR_START

/**
 * Converts a rank and file into a 6-bit integer.
 *
 * @param rank
 * @param file
 *
 * @return a 6-bit integer bitboard index
 */
inline unsigned int coords_to_int(unsigned int rank, unsigned int file) {
    return (rank * 8 + file) & 0x3f;
}

/**
 * Converts a 6-bit integer index to the corresponding board rank.
 *
 * @param index 6-bit integer index
 *
 * @return a board rank [0-7]
 */
inline unsigned int index_to_rank(unsigned int index) {
    return (index / 8) & 0x3f;
}

/**
 * Converts a 6-bit integer index to the corresponding board file.
 *
 * @param index 6-bit integer index
 *
 * @return a board file [0-7]
 */
inline unsigned int index_to_file(unsigned int index) {
    return (index % 8) & 0x3f;
}

CHEDDAR_END
