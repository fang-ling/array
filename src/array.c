//
//  array.c
//  array
//
//  Created by Fang Ling on 2023/1/16.
//

#include "array.h"

/* Implemented in GCC 4.9, __auto_type is similar to C++11 auto but works in C.
 * So GCC 4.9+ or Clang (newer than 2016's version) is required to compile this
 * code.
 */
#define var __auto_type

/* Notice that it's caller's responsibility to distinguish between different
 * element type arrays.
 */

/** Begin: Creating an array **/
/* Creates a new array containing the specified number of empty slots. */
struct Array* array_init2(Int element_size, Int count) {
    var array = (struct Array*)malloc(sizeof(struct Array));
    array -> data = malloc(count * element_size);
    array -> element_size = element_size;
    array -> capacity = count;
    array -> count = count;
    array -> is_empty = count == 0 ? true : false;

    return array;
}

/* Creates a new, empty array. */
struct Array* array_init(Int element_size) {
    return array_init2(element_size, 0);
}

/* Creates a new array containing the specified number of a single, repeated
 * value. */
struct Array* array_init3(Int element_size, void* repeated_value, Int count) {
    var array = array_init2(element_size, count);
    for (var i = 0; i < count; i += 1) {
        memcpy(array -> data + element_size * i, repeated_value, element_size);
    }
    return array;
}
/** End: Creating an array **/

/** Begin: Accessing Elements **/
/* Notice that there is no operator override in C. Accessing elements is
 * something like Java ArrayList's get() & set().
 */
/* Reads the element at the specified position. */
void* array_get(struct Array* array, Int index) {
    return array -> data + array -> element_size * index;
}

/* Write to the element at the specified position. */
void array_set(struct Array* array, Int index, void* element) {
    memcpy(array -> data + array -> element_size * index,
           element,
           array -> element_size);
}

/* Returns the first element of the collection. */
void* array_first(struct Array* array) {
    if (array -> count < 1) {
        return NULL;
    } else {
        return array_get(array, 0);
    }
}

/* Returns the last element of the collection. */
void* array_last(struct Array* array) {
    if (array -> count < 1) {
        return NULL;
    } else {
        return array_get(array, array -> count - 1);
    }
}
/** End: Accessing Elements **/
