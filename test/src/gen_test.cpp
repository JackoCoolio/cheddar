#include <gtest/gtest.h>
#include "test_util.h"
#include "fill.h"
#include "gen.h"
#include "board.h"
#include <map>

using namespace Cheddar;
using namespace std;

void print_move_list(MoveList list) {
    for (int i = 0; i < list.count; i++) {
        Move &move = list.moves[i];
        std::cout << move.get_from() << "\t" << move.get_to() << "\t" << index_to_alg(move.get_from()) << index_to_alg(move.get_to()) << std::endl;
    }
}

TEST(Generation, move_gen) {
    FenMap fens = get_test_fens();

    for (FenMap::iterator iter = fens.begin(); iter != fens.end(); iter++) {
        Position pos = from_fen(iter->first);

        MoveList moves = generate_legal_moves(pos);

        if (moves.count != iter->second) {
            print_move_list(moves);
            FAIL() << "Found " << moves.count << " moves instead of " << iter->second << "!" << std::endl << iter->first << std::endl
            << "Moves:" << std::endl;
        }
    }
}
