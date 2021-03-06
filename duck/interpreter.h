/* interpreter.h */
#ifndef _INTERPRETER_H
#define _INTERPRETER_H

#include "lr_parser.h"
#include "duck.h"

/* constants */
#define VAL_NIL             0
#define VAL_PRIMITIVE       1
#define VAL_STRING          2
#define VAL_REFERENCE       3
#define VAL_FUNCTION        4
#define VAL_FLOATING_POINT  5
#define VAL_DICTIONARY      6

/* types */

struct CONTEXT;
struct PAIR;

typedef struct FUNCTION
{
    struct PAIR* parameters;
    SYNTAX_TREE* body;
    unsigned int built_in;
    int (*functor)(int);
	struct CONTEXT* closure;
    int ref_count;
    const char* fn_name;
} FUNCTION;

struct HASH_TABLE;
typedef struct VALUE
{
    int         type;
    union {
        int         primitive;
        double      floatp;
        const char* string;
        FUNCTION*   function;
        struct CONTEXT* reference;
        struct HASH_TABLE* dictionary;
    } data;
//  int const_string;
} VALUE;

typedef struct PAIR
{
    const char* identifier;
    VALUE       value;
    struct PAIR* next;
} PAIR;

typedef struct CONTEXT
{
    PAIR*       list;
    int         ref_count;
    struct CONTEXT* parent;
} CONTEXT;

typedef struct CALLSTACK
{
    const char* fn_name;
    struct CALLSTACK* next;
} CALLSTACK;

/* memory allocation */
void* ALLOCATE(size_t amount);
/* void  FREE(void* data_ptr); */
void CreateEnvironment();
void  FreeEnvironment();

/* library routines */
VALUE LinkNamespace(const char* identifier);
VALUE CreateFunction(int (*function)(int));
void  AddParameter(VALUE functor,
                   const char* argument_name);
void  LinkFunction(VALUE ref_namespace,
                   const char* identifier,
                   VALUE function);
void  LinkConstPrimitive(VALUE ref_namespace,
                         const char* identifier,
                         int value);
void  LinkConstFloatp(VALUE ref_namespace,
                      const char* identifier,
                      double value);
void  LinkConstString(VALUE ref_namespace,
                      const char* identifier,
                      const char* string);

/* execution context */
extern CONTEXT* gGlobalContext;
extern CONTEXT* gCurrentContext;
extern VALUE    gLastExpression;
extern PAIR*    gParameterListing;
//extern CONTEXT* gDictionaryInit;
extern struct HASH_TABLE* gDictionaryInit;
extern int      gArrayIndex;
extern PAIR*    gArgumentEvaluation;
extern CALLSTACK gStackTrace;

extern const char* gLValueIdentifier;
extern CONTEXT*    gLValueContext;
extern VALUE       gLValueIndex;
extern struct HASH_TABLE* gLValueDictionary;

extern int array_indexing;

extern int returning;
extern int breaking;
extern int continuing;
extern int halting;

extern int stack_depth;
extern int greatest_stack_depth;

extern int line_error;
extern SYNTAX_TREE* failed_production;

//extern int return_value_exists;

/* functions */
void PrintContext(CONTEXT* context);
VALUE GetRecord(const char* identifier, CONTEXT* context);
void  StoreRecord(const char* identifier, VALUE value, CONTEXT* context);

/* type-casting */
double TypeFloat(VALUE value);
int TypeInt(VALUE value);

/* interpreter */
int Interpret(SYNTAX_TREE*);
/* remove redundant abstract syntax tree branches */
void ReduceProgramAST(SYNTAX_TREE**);

/* stack trace */
void ClearCallStack(CALLSTACK*);
void PushCallStack(CALLSTACK*, const char*);
void PrintStackTrace();

#endif // _INTERPRETER_H

