#include <stdio.h>
#include <string.h>
#include "c-head.h"

player make_player(char *name, int type) 
{
    player result ;
    strcpy(result.name, name) ;
    result.type = type ;
    return result ;
}
