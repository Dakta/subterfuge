//
//  methods.c
//  subterfuge
//
//  Created by Dakota Schneider on 12/6/16.
//  Copyright © 2016 Dakota Schneider. All rights reserved.
//

#include "methods.h"

#include "symboltables.h"

TypeVal * method_add(Stack * args) {
    // TODO minimu args count
    
    long double sum = 0;
    for (TypeVal * val = Stack_pop(args); val != NULL; val = Stack_pop(args)) {
        sum += Double_get(val);
    }
    TypeVal * ret = Double_new();
    Double_set(ret, sum);
    return ret;
}

TypeVal * method_sub(Stack * args) {
    // TODO minimum args count
    
    long double dif = Double_get(Stack_pop(args));
    for (TypeVal * val = Stack_pop(args); val != NULL; val = Stack_pop(args)) {
        dif -= Double_get(val);
    }
    
    TypeVal * ret = Double_new();
    Double_set(ret, dif);
    return ret;
}

TypeVal * method_mul(Stack * args) {
    long double prod = 1;
    for (TypeVal * val = Stack_pop(args); val != NULL; val = Stack_pop(args)) {
        prod *= Double_get(val);
    }
    TypeVal * ret = Double_new();
    Double_set(ret, prod);
    return ret;
}

TypeVal * method_div(Stack * args) {
    long double dividend = Double_get(Stack_pop(args));
    long double divisor = Double_get(Stack_pop(args));
    
    
    TypeVal * ret = Double_new();
    Double_set(ret, dividend / divisor);
    return ret;
}

TypeVal * method_sqrt(Stack * args) {
    TypeVal * ret = NULL;
    
    if (args->size > 0) {
        long double res;
        res = sqrtl(Double_get(Stack_pop(args)));
        
//        for (TypeVal * val = Stack_pop(args); val != NULL; val = Stack_pop(args)) {
//            res = powl(res, Double_get(val));
//        }
        
        ret = Double_new();
        Double_set(ret, res);
    }
    
    return ret;
}

TypeVal * method_expt(Stack * args) {
    TypeVal * ret = NULL;
    
    if (args->size > 0) {
        long double res;
        res = Double_get(Stack_pop(args));
        
        for (TypeVal * val = Stack_pop(args); val != NULL; val = Stack_pop(args)) {
            res = powl(res, Double_get(val));
        }
        
        ret = Double_new();
        Double_set(ret, res);
    }
    
    return ret;
}

TypeVal * method_square(Stack * args) {
    TypeVal * ret = NULL;
    
    if (args->size == 1) {
        ret = Double_new();
        Double_set(ret, powl(Double_get(Stack_pop(args)), 2));
    } else {
        // err procedure requires exactly 1 arg
    }
    
    return ret;
}

TypeVal * method_sin(Stack * args) {
    TypeVal * ret = NULL;
    
    if (args->size == 1) {
        ret = Double_new();
        Double_set(ret, sin(Double_get(Stack_pop(args))));
    } else {
        // err procedure requires exactly 1 arg
    }
    
    return ret;
}

TypeVal * method_cos(Stack * args) {
    TypeVal * ret = NULL;
    
    if (args->size == 1) {
        ret = Double_new();
        Double_set(ret, cos(Double_get(Stack_pop(args))));
    } else {
        // err procedure requires exactly 1 arg
    }
    
    return ret;
}

TypeVal * method_tan(Stack * args) {
    TypeVal * ret = NULL;
    
    if (args->size == 1) {
        ret = Double_new();
        Double_set(ret, tan(Double_get(Stack_pop(args))));
    } else {
        // err procedure requires exactly 1 arg
    }
    
    return ret;
}

TypeVal * method_define(Stack * args, SymbolTable * defs) {
    TypeVal * symbol = NULL;
    TypeVal * value = NULL;
    
    if (args->size == 2) {
        symbol = Stack_pop(args);
        value = Stack_pop(args);
        SymbolTable_put(defs, String_get(symbol), value);
    } else {
        // err procedure requires exactly 1 arg
    }
    
    return symbol;
}
