#ifndef TEST_UTIL
#define TEST_UTIL

#include <map>

constexpr const char *STANDARD_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 0";

typedef std::map<std::string, unsigned int> FenMap;
/**
 * Returns a map with FEN strings as keys and their move counts as values.
 *
 * Generated using Bernd's Random-FEN-Generator:
 * http://bernd.bplaced.net/fengenerator/fengenerator.html
 */
inline FenMap get_test_fens() {
    static std::map<std::string, unsigned int> fens;
    fens["rnb1kb1r/pp3p1p/2p1pnp1/q2p4/2PP4/2N1PN2/PP2BPPP/R1BQK2R w KQkq - 0 0"] = 30;
    fens["rnb1kb1r/pp3p1p/2p1pnp1/q2p4/2PP4/2N1PN2/PP2BPPP/R1BQK2R b KQkq - 0 0"] = 39;
    fens["8/B7/4P1P1/3N1p1p/1p4R1/1B1p4/1r3pP1/1k3K1b w - - 0 0"] = 30;
    fens["8/B7/4P1P1/3N1p1p/1p4R1/1B1p4/1r3pP1/1k3K1b b - - 0 0"] = 13;
    fens["6Kb/3rpP1B/pP1p1P1P/PnNp1p1P/1PrPRp1B/R1n2p2/2b2q1k/3QN3 w - - 0 0"] = 43;
    fens["6Kb/3rpP1B/pP1p1P1P/PnNp1p1P/1PrPRp1B/R1n2p2/2b2q1k/3QN3 b - - 0 0"] = 44;
    fens["8/P3N1k1/1p6/R2pP3/2Q1p2p/6P1/2pn3K/2B2r2 w - - 0 0"] = 44;
    fens["8/P3N1k1/1p6/R2pP3/2Q1p2p/6P1/2pn3K/2B2r2 b - - 0 0"] = 28;
    fens["1K6/5pn1/1p6/4r1P1/p3P1n1/3P2r1/bPp2k2/2b5 w - - 0 0"] = 9;
    fens["1K6/5pn1/1p6/4r1P1/p3P1n1/3P2r1/bPp2k2/2b5 b - - 0 0"] = 45;
    fens["rnbqk2r/ppp1ppbp/5np1/3p4/5P2/5NP1/PPPPP1BP/RNBQK2R w KQkq - 0 0"] = 28;
    fens["rnbqk2r/ppp1ppbp/5np1/3p4/5P2/5NP1/PPPPP1BP/RNBQK2R b KQkq - 0 0"] = 34;
    return fens;
}

#endif