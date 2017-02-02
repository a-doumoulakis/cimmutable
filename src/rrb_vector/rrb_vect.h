/*******************************************************************************
  MIT License

  Copyright (c) 2016 gral-master

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*******************************************************************************/

/**
 * @file rrb_vect.h
 * @version 0.1
 * @author Anastasios DOUMOULAKIS
 * @author Tanguy RETAIL
 * @date 9 december 2016
 * @brief Immutable Relaxed Radix Balanced Vectors C implementation
 * @copyright MIT Licence
 *
 * This file defines the structures and functions needed to manipulate immutable
 * RRB vectors. The implementation is made from scratch but the strucutre itself
 * comes from Nicolas Tucki's thesis.
 * @see https://github.com/nicolasstucki/scala-rrb-vector
 */

#ifndef _IMC_RRB_VECT_H
#define _IMC_RRB_VECT_H

#include "../../include/vector.h"
//-I -L à la compile pour faire #include <vector.h>
#include <stdio.h>

/* ARRAY_SIZE should be a power of 2 */
#define ARRAY_SIZE 32
#define MAX_DEPTH 7

//TODO define imc_data_t in a data.h file

typedef struct imc_rrb {
    int floor;
    int refs;
    int length;
    int* meta;
    union {
      struct imc_rrb** next; //children
      imc_data_t** data;
    } node; //to
} imc_rrb_t;

imc_rrb_t* imc_rrb_create();

int imc_rrb_size(imc_rrb_t* vec);

imc_rrb_t* imc_rrb_update(imc_rrb_t* vec, int index, imc_data_t* data);

imc_data_t* imc_rrb_lookup(imc_rrb_t* vec, int index);

imc_rrb_t* imc_rrb_push(imc_rrb_t* vec, imc_data_t* data);

imc_rrb_t* imc_rrb_push_full(imc_rrb_t* vec, imc_data_t* data);

imc_rrb_t* imc_rrb_push_not_full(imc_rrb_t* vec, imc_data_t* data);

void imc_rrb_emit(imc_rrb_t* vec, const char* path, char* (*print)(imc_data_t*));

void emit_node(imc_rrb_t* vec, char* from, char* prefix, FILE* f, char* (*print)(imc_data_t*), int refs);

char* concatc(char* str, char c);

int imc_rrb_is_full(imc_rrb_t* vec);

imc_rrb_t* imc_rrb_new_root(imc_rrb_t* vec);

int imc_rrb_is_balanced(imc_rrb_t* vec);

int imc_rrb_subindex(imc_rrb_t* vec, int index);

imc_rrb_t* imc_rrb_copy_leaf(imc_rrb_t* vec);

imc_rrb_t* imc_rrb_copy(imc_rrb_t* vec);

imc_rrb_t* imc_rrb_create_leaf();

imc_rrb_t* imc_rrb_pop(imc_rrb_t* vec, imc_data_t** data);

void imc_rrb_increase_length(imc_rrb_t* vec, int index);

void imc_rrb_decrease_length(imc_rrb_t* vec, int index);

int imc_rrb_split(imc_rrb_t* vec_in, int index,
                  imc_rrb_t** vec_out1, imc_rrb_t** vec_out2);

void imc_rrb_build_left(imc_rrb_t* vec_in, imc_rrb_t* left, int index);

void imc_rrb_build_right(imc_rrb_t* vec_in, imc_rrb_t* right, int index);

int imc_rrb_unref(imc_rrb_t* vec);

imc_rrb_t* copy_and_add_on_new_root(imc_rrb_t* body, imc_rrb_t* root);

imc_rrb_t* compress(imc_rrb_t* left, imc_rrb_t* mid, imc_rrb_t* right, int ignore1, int ignore2, int last_step);

int imc_rrb_is_leaf(imc_rrb_t* vec);

imc_rrb_t* imc_rrb_tail(imc_rrb_t* vec, int* res_index);

imc_rrb_t* imc_rrb_head(imc_rrb_t* vec, int* res_index);

int imc_rrb_init(imc_rrb_t* vec);

imc_rrb_t* imc_rrb_merge(imc_rrb_t* vec_front, imc_rrb_t* vec_tail);

imc_rrb_t* imc_rrb_merge_nodes(imc_rrb_t* left, imc_rrb_t* middle,
                               imc_rrb_t* right, int ignore1, int ignore2, int last_step);

imc_rrb_t* imc_rrb_merge_leaves(imc_rrb_t* vec1, imc_rrb_t* vec2);

#endif
