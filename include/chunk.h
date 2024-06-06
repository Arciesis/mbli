#ifndef chunk_h
#define chunk_h

/**
 *  includes lib
 */
#include <stdint.h>
#include "common.h"
#include "value.h"

/**
 * Type definition
 */

typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    int count;
    int capacity;
    uint8_t* code;
    ValueArray constants;
} Chunk;


/**
 * functions declarations
 */

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);
int addConstant(Chunk* chunk, Value value);

#endif
