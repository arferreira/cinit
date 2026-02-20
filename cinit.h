#ifndef CINIT_H
#define CINIT_H

typedef enum {
    CINIT_COLOR_RESET = 0,
    CINIT_COLOR_RED,
    CINIT_COLOR_GREEN,
    CINIT_COLOR_YELLOW,
    CINIT_COLOR_BLUE,
    CINIT_COLOR_MAGENTA,
    CINIT_COLOR_CYAN,
    CINIT_COLOR_WHITE
} cinit_color_t;

void cinit_put_str_color(const char *str, cinit_color_t color);

#endif /* CINIT_H */