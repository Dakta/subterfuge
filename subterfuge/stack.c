//
//  stack.c
//  tinycalc
//
//  Created by Dakota Schneider on 12/2/16.
//  Copyright © 2016 Code From Above. All rights reserved.
//

#include "stack.h"


#include <stdlib.h>


Stack * Stack_new() {
    Stack * stack= malloc(sizeof(StackNode));
    if (!stack) return NULL;
    
    stack->size = 0;
    stack->top = NULL;
    
    return stack;
}


void Stack_free(Stack * stack) {
    while (stack->size > 0) {
        TypeVal_free(Stack_pop(stack));
    }
    free(stack);
}


Stack * Stack_reverse(Stack * old) {
    Stack * rev = Stack_new();
    
    for (; old->size > 0; Stack_push(rev, Stack_pop(old))) {}
    
    // free old?
    Stack_free(old);
    
    return rev;
}


StackNode * Stack_push(Stack * stack, TypeVal * val) {
    StackNode * node = malloc(sizeof(StackNode));
    if (!node) return NULL;
    
    node->val = TypeVal_copy(val);
    node->prev = stack->top;
    
    stack->top = node;
    
    stack->size++;
    
    return node;
}

TypeVal * Stack_pop(Stack * stack) {
    if (stack->top != NULL) {
        TypeVal * val = stack->top->val;
        StackNode * prev = stack->top->prev;
        free(stack->top);
        stack->top = prev;
        
        stack->size--;
        return val;
        
    } else {
        // error condition, empty stack
    }
    return 0;
}

TypeVal * Stack_get(Stack * stack, intmax_t idx) {
    // stack overflow?
    if (idx >= stack->size) { return NULL; }
    
    // otherwise
    StackNode * node = stack->top;
    for (int i = 0; i < idx; i++) {
        node = node->prev;
    }
    return TypeVal_copy(node->val);
}


TypeVal * Stack_set(Stack * stack, intmax_t idx, TypeVal * val) {
    // stack overflow?
    if (idx >= stack->size) { return NULL; }
    
    // otherwise
    StackNode * node = stack->top;
    for (int i = 0; i < idx; i++) {
        node = node->prev;
    }
    
    return node->val = TypeVal_copy(val);
}

