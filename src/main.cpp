#include <string>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include "ui/ui.h"

using namespace Cheddar;

int main() {
    UI ui;

    std::string input;
    bool should_exit = 0;
    do {
        // get console input
        std::getline(std::cin, input);

        // trim any whitespace
        boost::algorithm::trim(input);

        should_exit = ui.command(input);
    } while (!should_exit);

    return 0;
}
