//
//  array.c
//  array
//
//  Created by Fang Ling on 2023/1/16.
//

#include "array.h"
#include "util.h"
#include <i386/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (array -> is_empty) {
        return NULL;
    } else {
        return array_get(array, 0);
    }
}

/* Returns the last element of the collection. */
void* array_last(struct Array* array) {
    if (array -> is_empty) {
        return NULL;
    } else {
        return array_get(array, array -> count - 1);
    }
}

/* Returns a random element of the collection. */
void* array_random_element(struct Array* array) {
    if (array -> is_empty) {
        return NULL;
    } else {
        /* arc4random only works with 32-bits, it shouldn't have problems here.
         * Since it may unrealistic to put 2**64 items in a single array. ;-)
         */
        return array_get(array, arc4random_uniform(array -> count));
    }
}
/** End: Accessing Elements **/

/** Begin: sbrk **/
/* Internal use function that double or halve the current data size.
 * Note that the caller does not need to scale the parameter `new_size `by
 * `element_size`.
 */
static void array_sbrk(struct Array* array, Int new_size) {
    array -> capacity = new_size;
    new_size *= array -> element_size;
    if ((array -> data = realloc(array -> data, new_size)) == NULL) {
        fprintf(stderr, "array_sbrk(array:new_size): realloc error\n");
    }
}
/** End: sbrk **/

/** Begin: Adding Elements **/
/* Adds a new element at the end of the array. */
void array_append(struct Array* array, void* new_element) {
    /* Special case when array is empty. Because 0 * 2 = 0. */
    if (array -> is_empty) {
        array_sbrk(array, 1);
        array -> is_empty = false;
    } else if (array -> count >= array -> capacity) {
        array_sbrk(array, array -> capacity * 2);
    }
    memcpy(array -> data + array -> element_size * array -> count,
           new_element,
           array -> element_size);
    array -> count += 1;
}

/* Inserts a new element at the specified position. */
void array_insert(struct Array* array, void* new_element, Int at_i) {
    /* Insert to an empty array at position 0 is like append(array:new_element)
     */
    if (array -> is_empty) {
        if (at_i != 0) {
            fprintf(stderr, "Fatal error: Array index is out of range\n");
        }
        array_append(array, new_element);
    } else if (at_i == array -> count) {
        array_append(array, new_element);
    } else {
        array -> count += 1;
        if (array -> count >= array -> capacity) {
            array_sbrk(array, array -> capacity * 2);
        }
        /* Create a buffer to hold elements behind the insert position. */
        var num_moves = array -> count - at_i;
        var buf = malloc(num_moves * array -> element_size);
        /* Copy the rest to buffer */
        memcpy(buf,
               array -> data + array -> element_size * at_i,
               num_moves * array -> element_size);
        /* Insert the new element */
        memcpy(array -> data + array -> element_size * at_i,
               new_element,
               array -> element_size);
        /* Move back */
        memcpy(array -> data + array -> element_size * (at_i + 1),
               buf,
               num_moves * array -> element_size);
        /* Free buffer */
        free(buf);
    }
}
/** End: Adding Elements **/

/** Begin: Combining Arrays **/
/* Adds the elements of an array to the end of this array */
void array_append2(struct Array* lhs, struct Array* rhs) {
    if (lhs -> element_size != rhs -> element_size) {
        return;
    }
    /* Maybe copy the whole range will faster than call append n times */
    //TO-DO
    for (var i = 0; i < rhs -> count; i += 1) {
        array_append(lhs, array_get(rhs, i));
    }
}
/** End: Combining Arrays **/

/** Begin: Removing Elements **/
/* Removes and returns the last element of the array.
 * It's caller's responsibility to free the return value.
 */
void* array_remove_last(struct Array* array) {
    if (array -> is_empty) {
        fatal_error("Can't remove last element from an empty array.");
    }
    var ret = malloc(array -> element_size);
    memcpy(ret, array_last(array), array -> element_size);
    array -> count -= 1;
    if (array -> count == 0) {
        array -> is_empty = true;
        array -> capacity = 0;
        array_sbrk(array, 0);
    } else if (array -> count <= array -> capacity / 4) {
        array_sbrk(array, array -> capacity / 2);
    }
    return ret;
}
/** End: Removing Elements **/

/** Begin: Describing an Array **/
//TO-DO: using String instead of print, currently only works with integer type
void array_to_string(struct Array* array) {
    printf("[%lld", *(Int*)array_get(array, 0));
    for (var i = 1; i < array -> count; i += 1) {
        printf(", %lld", *(Int*)array_get(array, i));
    }
    printf("]\n");
}
/** End: Describing an Array **/
