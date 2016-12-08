//
//  methods.h
//  subterfuge
//
//  Created by Dakota Schneider on 12/6/16.
//  Copyright © 2016 Dakota Schneider. All rights reserved.
//

#ifndef methods_h
#define methods_h

#include <stdio.h>

#include <math.h>

#include "stack.h"
#include "types.h"
#include "symboltables.h"


TypeVal * method_add(Stack * args);

TypeVal * method_sub(Stack * args);

TypeVal * method_mul(Stack * args);

TypeVal * method_div(Stack * args);

TypeVal * method_sqrt(Stack * args);

TypeVal * method_expt(Stack * args);

TypeVal * method_square(Stack * args);

TypeVal * method_sin(Stack * args);

TypeVal * method_cos(Stack * args);

TypeVal * method_tan(Stack * args);

TypeVal * method_define(Stack * args, SymbolTable * defs);


#endif /* methods_h */
