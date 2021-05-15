#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include "ui.h"

using namespace Cheddar;
using namespace std;

void UI::unknown_error(string command) {
    cout << "Unknown command: " << command << std::endl;
}

bool UI::command(string input) {
    // split input into tokens
    vector<string> tokens;
    boost::algorithm::split(tokens, input, boost::is_any_of("\t "), boost::token_compress_on);

    string &command = tokens[0];

    if (command == "isready") {
        while (!m_isready);

        cout << "readyok" << endl;
    } else if (command == "uci") {
        cout << "id name Cheddar ALPHA" << endl;
        cout << "id author Jackson Wambolt" << endl;

        cout << "uciok" << endl;
    } else if (command == "quit") {
        return 1; // just quit
    } else if (command == "position") {
        if (tokens.size() > 1) {
            if (tokens[1] == "startpos") {
                m_position = from_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
            } else if (tokens[1] == "fen" && tokens.size() > 2) {
                string fen;
                for_each(tokens.begin() + 2, tokens.end(), [&](const string token) { fen += token; });

                fen.erase(remove(fen.begin(), fen.end(), '"'), fen.end());
                m_position = from_fen(fen);
            }
        }
    } else {
        unknown_error(input);
    }

    return 0;
}

