#ifndef THREAD_H
#define THREAD_H

#include "../core.h"

CHEDDAR_START

class Thread {
    void operator(bool &is_done);
}

CHEDDAR_END

#endif
