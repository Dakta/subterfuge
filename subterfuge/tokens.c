//
//  tokens.c
//  subterfuge
//
//  Created by Dakota Schneider on 12/5/16.
//  Copyright © 2016 Dakota Schneider. All rights reserved.
//

#include "tokens.h"

#include <string.h>

/**
 * String tokenization method; basically strtok_r() without input mangling
 *
 * @param start Start of string for checking token
 * @param seps String of characters to be used as separators
 * @return The extracted token
 */
char * strtokenize(char ** start, const char * seps) {
    
    // sanity check: abort on empty string or NULL pointer
    if (*start == NULL || *start[0] == '\0') { return NULL; }
    
    char * token = NULL;
    char * pos = NULL;
    
    // read characters from str
    for (
        pos = *start;
        strchr(seps, *pos) == NULL;
        pos++
    ) {
        // until we hit a char from seps
    }
    // Collect up chars since str (strndup adds \0 for us)
    token = strndup(*start, pos - *start);
    // step over found token
    *start = pos + 1;
    
    return token;
}



