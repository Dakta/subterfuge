//
//  symboltables.h
//  subterfuge
//
//  Created by Dakota Schneider on 12/6/16.
//  Copyright © 2016 Dakota Schneider. All rights reserved.
//

#ifndef symboltables_h
#define symboltables_h

#include <stdio.h>
#include <stdbool.h>

#include "types.h"

typedef struct SymbolTable {
    size_t sz;
    struct SymbolTableNode * first;
} SymbolTable;

typedef struct SymbolTableNode {
    char * key;
    TypeVal * val;
    struct SymbolTableNode * next;
} SymbolTableNode;


SymbolTable * SymbolTable_new();

//SymbolTableNode * SymbolTableNode_new();

SymbolTableNode * SymbolTableNode_new(char * key, TypeVal * val, SymbolTableNode * next);

void SymbolTable_put(SymbolTable * st, char * key, TypeVal * val);

TypeVal * SymbolTable_get(SymbolTable * st, char * key);

void SymbolTable_delete(SymbolTable * st, char * key);

void SymbolTable_promote(SymbolTable * st, SymbolTableNode * one, SymbolTableNode * two);

bool SymbolTable_contains(SymbolTable * st, char * key);

bool SymbolTable_isEmpty(SymbolTable * st);

size_t SymbolTable_size(SymbolTable * st);


#endif /* symboltables_h */
