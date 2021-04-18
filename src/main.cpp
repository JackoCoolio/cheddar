#include <iostream>

#include <move.h>
#include <util.h>

using namespace Cheddar;

int main() {
    // quiet move
    Move move(coords_to_int(0, 0), coords_to_int(7, 7), 0);

    std::cout << move.get_to() << std::endl;
    std::cout << move.get_from() << std::endl;
    std::cout << move.is_capture() << std::endl;

    return 0;
}
