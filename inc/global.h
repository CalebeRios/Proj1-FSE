#ifndef GLOBAL_H
#define GLOBAL_H

struct Temperatures {
    float temp_ext, temp_int, temp_ref;
};

extern struct Temperatures temp;

#endif
