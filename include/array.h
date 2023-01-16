//
//  array.h
//  array
//
//  Created by Fang Ling on 2023/1/16.
//

#ifndef array_h
#define array_h

#include <stdlib.h>
#include <string.h>

#include "types.h"

struct Array {
    void* data;

    Int element_size;
    Int count;   /* The number of elements in the array. */
    /* (Internal use) The total number of elements that the array can contain
     * without allocating new storage.
     */
    Int capacity;
};

/** Begin: Creating an array **/
/* Creates a new array containing the specified number of empty slots.
 * - Parameters:
 *     element_size: size of the array element
 * - Complexity:
 *     O(1) if malloc(0) takes constant time.
 */
struct Array* array_init(Int element_size);
/** End: Creating an array **/

#endif /* array_h */
