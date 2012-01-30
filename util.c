#include <stdio.h>
#include "util.h"

void format_millis(const double ms, char *result)
{
    if (ms > 60000) {
        int minutes = ms / 60000;
        int seconds = (ms - (minutes * 60000)) / 1000;
        sprintf(result, "%d minutes, %d seconds", minutes, seconds);
    } else if (ms >= 1000) {
        int seconds = ms / 1000;
        sprintf(result, "%d seconds", seconds);
    } else {
        sprintf(result, "%.2f milliseconds", ms);
    }
}
