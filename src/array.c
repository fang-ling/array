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
    var array = malloc(sizeof(struct Array));
    array -> data = malloc(count * element_size);
    array -> element_size = element_size;
    array -> capacity = count;
    array -> count = count;

    return array;
}

/* Creates a new, empty array. */
struct Array* array_init(Int element_size) {
    return array_init2(element_size, 0);
}

/* Creates a new array containing the specified number of a single, repeated
 * value. */
struct Array* array_init3(Int element_size, void* repeatedValue, Int count) {
    var array = array_init2(element_size, count);
    for (var i = 0; i < count; i += 1) {
        memcpy(array -> data + element_size * i, repeatedValue, element_size);
    }
}
/** End: Creating an array **/
