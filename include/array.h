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

/* Require arc4random() by array_random_element() */
/* TO-DO: Add Windows OS support */
#ifdef linux
#include <bsd/stdlib.h>
#endif

#include "types.h"

struct Array {
    void* data;

    Int element_size;
    /* A Boolean value indicating whether the collection is empty. */
    Bool is_empty;
    Int count; /* The number of elements in the array. */
    /* (Internal use) The total number of elements that the array can contain
     * without allocating new storage.
     */
    Int capacity;
};

/** Begin: Creating an array **/
/* Creates a new, empty array.
 * - Parameters:
 *     element_size: The size of the array element.
 * - Complexity:
 *     O(1) if malloc(0) takes constant time.
 * - Discussion:
 *     When initialize an empty array, `is_empty` should be true. For example:
 *     ```c
 *     var array = array_init(sizeof(Int));
 *     printf(array -> is_empty ? "true" : "false");
 *     // Prints "true"
 *     ```
 */
struct Array* array_init(Int element_size);

/* Creates a new array containing the specified number of empty slots.
 * - Parameters:
 *     element_size: The size of the array element.
 *     count: The number of empty slots. count must be zero or greater.
 *            TO-DO: add negative value check.
 * - Complexity:
 *     O(1) if malloc(n) takes constant time. or
 *     O(n) if malloc(n) takes O(n) time. Where n = count.
 * - Discussion:
 *     The array created by array_init2(element_size:count:) contains
 *     nothing but `count` empty slots. `is_empty` is false unless `count`
 *     has value zero.
 *     ```c
 *     var array = array_init2(sizeof(Int), 100);
 *     printf(array -> is_empty ? "true" : "false");
 *     // Prints "false"
 *     ```
 */
struct Array* array_init2(Int element_size, Int count);

/* Creates a new array containing the specified number of a single, repeated
 * value.
 * - Parameters:
 *     element_size: The size of the array element.
 *     repeated_value: The pointer of the element to repeat.
 *     count: The number of times to repeat the value passed in the
 *            repeated_value parameter. count must be zero or greater.
 *            TO-DO: add negative value check.
 * - Complexity:
 *     O(n) since we need to copy n items. Where n = count.
 * - Discussion:
 *     Here's an example of creating an array initialized with five integers
 *     containing the digit 9.
 *     ```c
 *     var repeated_value = 9;
 *     var array = array_init3(sizeof(Int), &repeated_value, 5);
 *     ```
 */
struct Array* array_init3(Int element_size, void* repeated_value, Int count);
/** End: Creating an array **/

#endif /* array_h */
