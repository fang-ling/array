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
#include <stdio.h>

/* Require arc4random() by array_random_element() */
/* TO-DO: Add Windows OS support */
#ifdef linux
#include <bsd/stdlib.h>
#endif

#include "types.h"
#include "util.h"

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
 * - Return Value:
 *     A pointer to the generated array.
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
 * - Return Value:
 *     A pointer to the generated array.
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
 * - Return Value:
 *     A pointer to the generated array.
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

/** Begin: Accessing Elements **/
/* Reads the element at the specified position.
 * - Parameters:
 *     array: The array to access.
 *     index: The position of the element to access. index must be greater than
 *            or equal to 0 and less than array -> count.
 *            TO-DO: add boundary check.
 * - Return Value:
 *     A pointer to the requested element. If the collection is empty, the
 *     function returns nil.
 * - Complexity:
 *     O(1)
 * - Discussion:
 *     See discussion of array_set(array:index:).
 */
void* array_get(struct Array* array, Int index);

/* Write to the element at the specified position.
 * - Parameters:
 *     array: The array to access.
 *     index: The position of the element to access. index must be greater than
 *            or equal to 0 and less than array -> count.
 *            TO-DO: add boundary check.
 * - Complexity:
 *     O(1)
 * - Discussion:
 *     The following example uses array_get(array:index) and
 *     array_get(array:index:) to update an array’sthird element. After
 *     assigning the new value (12333) at a specific position, that value is
 *     immediately available at that same position.
 *     ```c
 *     var repeated_value = 19358;
 *     var array = array_init3(sizeof(Int), &repeated_value, 5);
 *     repeated_value = 12333;
 *     array_set(array, 2, &repeated_value);
 *     printf("%lld\n", *(Int*)array_get(array, 2));
 *     // Prints "12333"
 *     ```
 */
void array_set(struct Array* array, Int index, void* element);

/* Returns the first element of the collection.
 * - Parameters:
 *     array: The array to access.
 * - Complexity:
 *     O(1)
 * - Return Value:
 *     The first element of the collection. If the collection is empty, the
 *     return value of this function is NULL.
 */
void* array_first(struct Array* array);

/* Returns the last element of the collection.
 * - Parameters:
 *     array: The array to access.
 * - Complexity:
 *     O(1)
 * - Return Value:
 *     The last element of the collection. If the collection is empty, the
 *     return value of this function is NULL.
 */
void* array_last(struct Array* array);

/* Returns a random element of the collection.
 *  - Parameters:
 *     array: The array to access.
 * - Complexity:
 *     O(1)
 * - Return Value:
 *     A random element from the collection. If the collection is empty, the
 *     function returns NULL.
 */
void* array_random_element(struct Array* array);
/** End: Accessing Elements **/

/** Begin: Adding Elements **/
void array_append(struct Array* array, void* new_element);
void array_insert(struct Array* array, void* new_element, Int at_i);
/** End: Adding Elements **/

/** Begin: Combining Arrays **/
void array_append2(struct Array* lhs, struct Array* rhs);
/** End: Combining Arrays **/

/** Begin: Describing an Array (Experimental) **/
void array_to_string(struct Array* array);
/** End: Describing an Array **/

/** Begin: Removing Elements **/
void* array_remove(struct Array* array, Int index);
void* array_remove_last(struct Array* array);
void* array_remove_first(struct Array* array);
/** End: Removing Elements **/

#endif /* array_h */
