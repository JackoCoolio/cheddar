namespace Cheddar {

    typedef struct Square {
        unsigned int rank;
        unsigned int file;
    } Square;

    inline unsigned int coords_to_int(unsigned int rank, unsigned int file) {
        return rank * 8 + file;
    }

    inline unsigned int index_to_rank(unsigned int index) {
        return index / 8;
    }

    inline unsigned int index_to_file(unsigned int index) {
        return index % 8;
    }

}