/* aho_corasick.h - declarations for Aho Corasick implementations
   Copyright (C) 2007 Tideway Systems Limited.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef AHO_CORASICK_H
#define AHO_CORASICK_H

typedef enum {
    AC_SUCCESS = 0,
    AC_FAILURE = 1
} ac_error_code;

/**
 * Type for function pointers used for freeing complex item types.
 */
typedef ac_error_code (*ac_free_function)(void* item, void* data);

/**
 * Type for symbols used to build strings such as keywords and query phrases.
 * All symbols satisfy AC_MIN_SYMBOL <= symbol <= AC_MAX_SYMBOL.
 */
typedef char ac_symbol;

#define AC_MIN_SYMBOL 0     // Smallest ordinal for an ac_symbol.
#define AC_MAX_SYMBOL 255   // Greatest ordinal for an ac_symbol.


/**
 * Type for the index into a string of symbols or the length of a string of
 * symbols. We use 0-based indexing.
 */
typedef int ac_offset;


/**
 * Structure for a single query match, containing the span of the query phrase
 * that matched the keyword and a pointer associated with the keyword.
 */
typedef struct ac_result {
    /**
     * The offset of the first symbol in the matching substring of the query
     * phrase.
     */
    ac_offset   start;

    /** The offset of the symbol after the last symbol in the matching
     * substring of the query phrase.
     */
    ac_offset   end;
    
    /** Pointer associated with the keyword. */
    void*       object;
} ac_result;

/**
 * Interface states for an index objects.
 */
typedef enum ac_index_state {
    
    /**
     * The index is 'unfixed'. New keywords can be entered but the index
     * cannot be queried.
     */
    AC_INDEX_UNFIXED,
    
    /**
     * The index in 'fixed'. The index can be queried but new keywords cannot
     * be entered.
     */
    AC_INDEX_FIXED
    
} ac_index_state;


/**
 * Structure for index objects.
 */
typedef struct ac_index {
    
    /** The interface state of the index. */
    ac_index_state      index_state;
    
    /** The top state node of the index's patten matching machine. */
    struct ac_state*    state_0;
    
} ac_index;

/**
 * Type for result callback function.
 */
typedef ac_error_code (*ac_result_callback)(void*, ac_result*);

// Operations for index objects.
ac_index* ac_index_new(void);
ac_error_code ac_index_free(ac_index*, ac_free_function);
ac_error_code ac_index_enter(ac_index*, ac_symbol*, ac_offset, void*);
ac_error_code ac_index_fix(ac_index*);
ac_error_code ac_index_query_cb(ac_index*, ac_symbol*, ac_offset,
                                ac_result_callback, void*);

#endif // AHO_CORASICK_H

