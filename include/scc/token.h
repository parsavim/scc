#ifndef __SCC_TOKEN_H__
#define __SCC_TOKEN_H__

#include <scc/pos.h>

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* TODO: Add all tokens. */
enum token_kind {
    /* Internal (Used only by the lexer). */
    /* 
     * No new token was generated, keep going.
     * (Preprocessor directives are not tokens but are
     * parsed and dealt with by the lexer.
     */
    TOKEN_FORWARD,

    /* Special. */
    TOKEN_EOF,
    TOKEN_UNKNOWN,

    /* Literals. */
    TOKEN_CHR, /* 'f' */
    TOKEN_STR, /* "foo" */
    TOKEN_INT, /* -12345 */
    TOKEN_FLT, /* -123.45 */

    /* Identifier. */
    TOKEN_IDENT, /* foo */

    /* Keywords. */
    TOKEN_CONST,
    TOKEN_IF,
    TOKEN_WHILE,

    /* Operators. */
    /* Arithmetic. */
    TOKEN_ADD, /* + */
    TOKEN_SUB, /* - */
    TOKEN_MUL, /* * */
    TOKEN_DIV, /* / */
    TOKEN_REM, /* % */

    /* Assignment. */
    TOKEN_ASSIGN, /* = */

    /* Equality. */
    TOKEN_EQ,  /* == */
    TOKEN_NEQ, /* != */

    /* Comparison. */
    TOKEN_LT,   /* < */
    TOKEN_LTEQ, /* <= */
    TOKEN_GT,   /* > */
    TOKEN_GTEQ, /* >= */

    /* Logical. */
    TOKEN_LAND, /* && */
    TOKEN_LOR,  /* || */
    TOKEN_NOT,  /* ! */

    /* Bitwise. */
    TOKEN_AND,    /* & */
    TOKEN_OR,     /* | */
    TOKEN_XOR,    /* ^ */
    TOKEN_CMPL,   /* ~ */
    TOKEN_LSHIFT, /* << */
    TOKEN_RSHIFT, /* >> */
};
typedef enum token_kind token_kind_t;

/*
 * The equivalent string representation for each token. 
 * Tokens whose string representation is an empty string
 * have multiple string representations.
 */
char const* tokens[] = {
    [TOKEN_FORWARD] = "forward",

    [TOKEN_EOF] = "EOF",
    [TOKEN_UNKNOWN] = "",

    [TOKEN_CHR] = "",
    [TOKEN_STR] = "",
    [TOKEN_INT] = "",
    [TOKEN_FLT] = "",

    [TOKEN_IDENT] = "",

    [TOKEN_CONST] = "const",
    [TOKEN_IF] = "if",
    [TOKEN_WHILE] = "while",

    [TOKEN_ADD] = "+",
    [TOKEN_SUB] = "-",
    [TOKEN_MUL] = "*",
    [TOKEN_DIV] = "/",
    [TOKEN_REM] = "%",

    [TOKEN_ASSIGN] = "=",

    [TOKEN_EQ] = "==",
    [TOKEN_NEQ] = "!=",

    [TOKEN_LT] = "<",
    [TOKEN_LTEQ] = "<=",
    [TOKEN_GT] = ">",
    [TOKEN_GTEQ] = ">=",

    [TOKEN_LAND] = "&&",
    [TOKEN_LOR] = "||",
    [TOKEN_NOT] = "!",

    [TOKEN_AND] = "&",
    [TOKEN_OR] = "|",
    [TOKEN_XOR] = "^",
    [TOKEN_CMPL] = "~",
    [TOKEN_LSHIFT] = "<<",
    [TOKEN_RSHIFT] = ">>",
};

struct token {
    pos_t pos;
    token_kind_t kind;

    /* true if it is the token's responsibility to free the value string.  */
    bool free;

    /* Exactly what the lexer matched. */
    char* value;
};
typedef struct token token_t;

/* Frees the value string if the free field is true. */
static inline
void token_free(token_t* tok) {
    if (tok->free) {
        free(tok->value);
    }
}

#endif
