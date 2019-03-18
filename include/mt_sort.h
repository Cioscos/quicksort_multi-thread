#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <string.h>

struct Params
{
    uint32_t *start;
    size_t len;
    uint32_t depth;
};



//Functions
void *merge_sort_thread(void *pv);
void merge(uint32_t *start, uint32_t *mid, uint32_t *end);
void merge_sort(uint32_t *start, unsigned int len);
void merge_sort_mt(uint32_t *start, unsigned int len, uint32_t depth);
