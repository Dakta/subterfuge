//
//  symboltables.c
//  subterfuge
//
//  Created by Dakota Schneider on 12/6/16.
//  Copyright © 2016 Dakota Schneider. All rights reserved.
//

#include "symboltables.h"

#include <stdlib.h>
#include <string.h>


SymbolTable * SymbolTable_new() {
    SymbolTable * st = malloc(sizeof(SymbolTable));
    if (!st) return NULL;
    
    st->sz = 0;
    st->first = NULL;
    
    return st;
}

SymbolTableNode * SymbolTableNode_new(char * key, TypeVal * val, SymbolTableNode * next) {
    SymbolTableNode * node = malloc(sizeof(SymbolTableNode));
    if (!node) return NULL;

    node->next = next;
    node->key = strdup(key);
    node->val = TypeVal_copy(val);
    
    return node;
}

//SymbolTableNode * SymbolTableNode_new() {
//    return SymbolTableNode_new(NULL, NULL);
//}

/**
 * add key-value pair to the symbol table
 * @param st SymbolTable to operate on
 * @param key Key to put/update
 * @param val Value
 */
void SymbolTable_put(SymbolTable * st, char * key, TypeVal * val) {
    
    if (key == NULL) {
        // some kinda errpr
        exit(1);
    }
    
    if (val == NULL) {
        SymbolTable_delete(st, key);
        return;
    }
    
    SymbolTableNode * prev = NULL;
    for (SymbolTableNode * n = st->first; n != NULL; n = (prev = n)->next) {
        if (strcmp(key, n->key) == 0) {
            n->val = TypeVal_copy(val);
            SymbolTable_promote(st, prev, n);
            return;
        }
    }
    
    SymbolTableNode * newNode = SymbolTableNode_new(key, val, st->first);
    st->first = newNode;
    st->sz++;
}


/**
 * retrieve the value associated with the key
 * @param st SymbolTable to operate on
 * @param key The key to get
 * @return returns the value associated with the key, otherwise it returns null
 */
TypeVal * SymbolTable_get(SymbolTable * st, char * key) {
    
    SymbolTableNode * prev = NULL;
    for (SymbolTableNode * n = st->first; n != NULL; n = (prev = n)->next) {
        if (strcmp(key, n->key) == 0) {
            SymbolTable_promote(st, prev, n);
            return n->val;
        }
    }
    return NULL;
}

/**
 * deletes the key-value pair associated with the key from the symbol table
 * @param key The key to delete
 */
void SymbolTable_delete(SymbolTable * st, char * key) {
    if (key == NULL) return;
    
    SymbolTableNode * prev = NULL;
    for (SymbolTableNode * n = st->first; n != NULL; n = (prev = n)->next) {
        if (strcmp(key, n->key) == 0) {
            prev->next = n->next;
            st->sz--;
            return;
        }
    }		
}

/**
 * promotes a node to the head of the list
 * @param one node before the node to promote
 * @param two node to promote
 */
void SymbolTable_promote(SymbolTable * st, SymbolTableNode * one, SymbolTableNode * two) {
    if (one != NULL && two != NULL) one->next = two->next;
    if (two == st->first) return;
    two->next = st->first;
    st->first = two;
}

/**
 * is a key in the symbol table or not?
 * @param key Key to search for
 * @return returns true if the a key-value pair is associated with the key, otherwise false
 * @throws NullPointerException if the key is null
 */
bool SymbolTable_contains(SymbolTable * st, char * key) {
    return (SymbolTable_get(st, key) != NULL);
}

/**
 *
 * @return true if the table is empty, otherwise false
 */
bool SymbolTable_isEmpty(SymbolTable * st) {
    return (st->sz == 0);
}

/**
 *
 * @return the number of key-value pairs in the table
 */
size_t SymbolTable_size(SymbolTable * st) {
    return st->sz;
}


