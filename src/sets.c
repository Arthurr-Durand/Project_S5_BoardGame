#include <stdio.h>
#include <stdlib.h>

#include "geometry.h"
#include "sets.h"

struct sets_t {
    struct places_t* l[WORLD_SIZE];
};
