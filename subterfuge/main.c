//
//  main.c
//  subterfuge - A tiny Scheme-like interpreter.r
//
//  Created by Dakota Schneider on 12/2/16.
//  Copyright © 2016 Dakota Schneider. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <limits.h>
#include <float.h>
#include <inttypes.h>

#include <math.h>

#include "stack.h"
#include "types.h"
#include "tokens.h"
#include "symboltables.h"

#include "methods.h"

const char seps[] = " \t\n";

SymbolTable * user = NULL;


typedef struct Input_State {
    FILE * infile;
    char * line;
    size_t len;
    ssize_t read;
    char * token;
    char * saveptr; // used by strtok_r, see http://stackoverflow.com/a/15961298/362042
} Input_State;


TypeVal * evaluate(Stack * args) {
    // no arguments? nothing to do...
    if (args->size < 1) { return NULL; }
    
//    for (int i = 0; i < args->size; i++) {
//        printf("%s\n", String_get(Stack_get(args, i)));
//    }
    
    // Some kinda big stack of conditions? For now...
    // TODO: replace this with a hash map of function pointers?
    char * method = String_get(Stack_pop(args));
    
    TypeVal * val = NULL;
    
    if (strcmp(method, "add") == 0 ||
        strcmp(method, "+") == 0
    ) {
        val = method_add(args);
    } else if (
        strcmp(method, "sub") == 0 ||
        strcmp(method, "-") == 0
    ) {
        val = method_sub(args);
    } else if (
        strcmp(method, "mul") == 0 ||
        strcmp(method, "*") == 0
    ) {
        val = method_mul(args);
    } else if (
        strcmp(method, "div") == 0 ||
        strcmp(method, "/") == 0
    ) {
        val = method_div(args);
    } else if (strcmp(method, "sqrt") == 0) {
        val = method_sqrt(args);
    } else if (strcmp(method, "expt") == 0) {
        val = method_expt(args);
    } else if (strcmp(method, "square") == 0) {
        val = method_square(args);
    } else if (strcmp(method, "sin") == 0) {
        val = method_sin(args);
    } else if (strcmp(method, "cos") == 0) {
        val = method_cos(args);
    } else if (strcmp(method, "tan") == 0) {
        val = method_tan(args);
    } else if (strcmp(method, "define") == 0) {
        val = method_define(args, user);
    } else {
        // wot
        fprintf(stderr, "Unknown operation: %s, aborting...\n", method);
        exit(1);
    }
    
    return val;
}


char * next_token(Input_State * is) {
    
    // is->saveptr indicates current token read point, so when it gets to the end
    // we need to get a new line
    if (is->read == 0 || is->saveptr[0] == '\0') {
        // prompt
        fputs("SF>", stdout);
        // get input
        is->read = getline(&is->line, &is->len, is->infile);
        // reset token read position
        is->saveptr = is->line;
    }

    // read NULL means ^D, so send NULL token to trigger exit()
    if (is->read == -1) {
        return NULL;
    }

    for (
        is->token = strtokenize(&is->saveptr, seps);
        is->token != NULL;
        is->token = strtokenize(&is->saveptr, seps)
    ) {
        // read until we get a token with actual content
        if (strlen(is->token) > 0) {
            break;
        }
    }
    
    // end of line or hit a comment
    if (is->token == NULL || is->token[0] == ';') {
        // read next line
        is->read = 0;
        return next_token(is);
    }

    // Check Token
    
    // Check for stuff before parens

    // find first special token char
    char * cut = strpbrk(is->token, "()");
    
    if (cut != NULL) {
        // Uh'oh, we have a special separator in our token!
        // How big is the first chunk before the separator?
        size_t len = cut - is->token;
        char * newtok;
        
        // if we found a special token at the start, just take it off
        if (len == 0) {
            is->saveptr -= strlen(is->token);
            newtok = malloc(sizeof(char[2]));
            newtok[0] = is->token[0];
            newtok[1] = '\0';
        // otherwise take everything before the special token
        } else {
            // assign a new token
            newtok = malloc(len + 1);
            // step backwards for tokenization
            is->saveptr -= strlen(cut) + 1;
            // copy new token contents
            strncpy(newtok, is->token, len);
            // make sure to null terminate
            newtok[len] = '\0';
        }
        
        // clean up
//        free(is->token);
        is->token = newtok;
    }

//    fputs("Token: ", stderr);
//    fputs(is->token, stderr);
//    fputs("\n", stderr);
    
    // now we have a single "token" to return
    return is->token;
}


TypeVal * parse_expr(Input_State * is) {
    // Get first char
    // If "(", it's an expression, recurse!
    // Get arguments
    // if ")", end of arguments so break;
//    double res = 0;
    
    TypeVal * val = NULL;
    
    char * token = next_token(is);
    
    // TODO check for NULL
    if (!token) return NULL;
    
    // check for expression
    if (strcmp(token, "(") == 0) {
        // expression!
        Stack * args = Stack_new();

        for (TypeVal * result = parse_expr(is);
             result != NULL;
             result = parse_expr(is)
        ) {
            if (strcmp(String_get(result), ")") == 0) {
                break;
            }
            
//            printf("args->push %s\n", String_get(result));
            
            Stack_push(args, result);
//            TypeVal_free(result);
        }
        
        args = Stack_reverse(args);
        
        // now evaluate!
        // TODO NULL CHECK THIS VALUE, DERP!
        val = evaluate(args);
        
//        res = 0;
    } else {
        // otherwise, attempt to parse value
        // we can take symbol literal strings and float types
        TypeVal * result = TypeVal_new(String);
        String_set(result, token);
        long double res = Double_get(result);
        
        // check if valid
        if (res != res) {
            // res is NaN, so assume string token
//            val = result;
            // look up in user-defined symbols
            char * symbol = String_get(result);
            
            if (SymbolTable_contains(user, symbol)) {
                val = SymbolTable_get(user, symbol);
            } else {
                val = result;
            }
        } else {
            // just fine
//            TypeVal_free(result);

            val = Double_new();
            Double_set(val, res);
        }
        
    }
    
//    printf("parse_expr: %s\n", String_get(val));

//    return res;
    return val;
}


int main(int argc, char const *argv[]) {
    Types_init();
    
    // init input state
    Input_State * is = malloc(sizeof(Input_State));

    // input file
    if (argc == 2) {
        is->infile = fopen(argv[1], "r");
        if (is->infile == NULL) {
            printf("can't open file %s", argv[1]); exit(1);
        }
    } else {
        is->infile = stdin;
    }
    
    is->line = NULL;
    is->len = 0;
    is->read = 0;
    
    is->token = NULL;
    is->saveptr = NULL;
    
    // init user defined symbol storage
    user = SymbolTable_new();
    
    while (is->read != -1) {
        printf("%s\n", String_get(parse_expr(is)));
    }
    
    // clean up
    free(is->line);
    free(is->token);
    free(is);
    return 0;
}
