/**
 * @file cheri_sdrad_heap_mng.h
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#ifndef _CHERI_SDRAD_HEAP_MNG_H
#define _CHERI_SDRAD_HEAP_MNG_H

#include "tlsf.h"
#include "cheri_sdrad.h"
#include <sys/mman.h>
#include <pthread.h> 
#include <stdlib.h>
#include <string.h>


#define APP_DEFAULT_HEAP_SIZE               0x500000000
#define TLSF_MAX_POOL_SIZE                  0x100000000


void cheri_heap_init();
void *__malloc(size_t size);
void *malloc(size_t size);
char *strdup (const char *s);
int posix_memalign(void **memptr, size_t alignment, size_t size);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nelem, size_t elsize);
void free(void *ptr);

void *sdrad_malloc(int udi, size_t size);
int sdrad_memalign(int udi, void **memptr, size_t alignment, size_t size);
void sdrad_free(int udi, void *ptr);

#endif