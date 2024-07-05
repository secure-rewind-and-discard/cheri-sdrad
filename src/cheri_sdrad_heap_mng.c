/**
 * @file cheri_sdrad_heap_mng.c
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#include "cheri_sdrad_heap_mng.h"
#include "cheri_sdrad_signal.h"
#include <stdio.h>
#include <assert.h>

pthread_mutex_t application_mutex = PTHREAD_MUTEX_INITIALIZER;

/*Multithreaded application support*/
#ifdef TLSF_MULTITHREAD
#define TLSF_MUTEX_LOCK(...)  pthread_mutex_lock(&application_mutex);
#define TLSF_MUTEX_UNLOCK(...)  pthread_mutex_unlock(&application_mutex);
#else
#define TLSF_MUTEX_LOCK(...)
#define TLSF_MUTEX_UNLOCK(...)
#endif


void cheri_heap_init(){

    size_t  app_heap_size; 
    uintptr_t  app_heap_address;
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[gm_ptr->active_domain]);


    char *pTmp;

    pTmp = getenv( "APP_HEAP_SIZE");

    if(pTmp != NULL){
        app_heap_size = atoi(pTmp);
    }else{
        app_heap_size = APP_DEFAULT_HEAP_SIZE;
    }


    app_heap_address = (uintptr_t)mmap(NULL, APP_DEFAULT_HEAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);



    if(app_heap_size <= TLSF_MAX_POOL_SIZE){
        di_ptr->tlsf = tlsf_create_with_pool((void *)app_heap_address, app_heap_size);
    }else{
        di_ptr->tlsf = tlsf_create_with_pool((void *)app_heap_address, TLSF_MAX_POOL_SIZE);
        app_heap_size = app_heap_size - TLSF_MAX_POOL_SIZE;
        app_heap_address =  app_heap_address + TLSF_MAX_POOL_SIZE;
        while (app_heap_size  > TLSF_MAX_POOL_SIZE)
        {
            tlsf_add_pool(di_ptr->tlsf, (void *)app_heap_address, TLSF_MAX_POOL_SIZE);
            app_heap_size = app_heap_size - TLSF_MAX_POOL_SIZE;
            app_heap_address = app_heap_address + TLSF_MAX_POOL_SIZE;
        }
        tlsf_add_pool(di_ptr->tlsf, (void *)app_heap_address, app_heap_size);
    }

}


/* That's avoiding to calloc directly call libcmalloc*/
void *__malloc(size_t size);
void *__malloc(size_t size)
{
    void *ptr;
    ptr = malloc(size);
    return ptr;
}


void *malloc(size_t size);
void *malloc(size_t size){
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[gm_ptr->active_domain]);


    if (di_ptr->heap_init != INIT) {
        cheri_heap_init();
        di_ptr->heap_init = INIT;
    }

    void *ptr;
    size_t rounded_len = __builtin_cheri_round_representable_length(size);


    TLSF_MUTEX_LOCK();
    ptr = tlsf_malloc(di_ptr->tlsf, rounded_len);
    ptr = __builtin_cheri_bounds_set(ptr, rounded_len);
    TLSF_MUTEX_UNLOCK();

    return ptr;
}


char *strdup (const char *s);
char *strdup (const char *s)
{
    size_t len = strlen (s) + 1;
    len = __builtin_cheri_round_representable_length(len);
    void *new = malloc (len);
    if (new == NULL)
        return NULL;
    return (char *) memcpy (new, s, len);
}


int posix_memalign(void **memptr, size_t alignment, size_t size)
{
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[gm_ptr->active_domain]);
    void *ptr;


    TLSF_MUTEX_LOCK();
    ptr = tlsf_memalign(di_ptr->tlsf, alignment, size); 
    ptr = __builtin_cheri_bounds_set(ptr, __builtin_cheri_round_representable_length(size));
    TLSF_MUTEX_UNLOCK();
    *memptr = ptr; 
    return 0; //tlsf_memalign doesn't have any zero code
}



void *realloc(void *ptr, size_t size);
void *realloc(void *ptr, size_t size)
{
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[gm_ptr->active_domain]);


    if (di_ptr->heap_init != INIT) {
        cheri_heap_init();
        di_ptr->heap_init = INIT;
    }

    TLSF_MUTEX_LOCK();
    ptr = tlsf_realloc(di_ptr->tlsf, ptr, size);
    ptr = __builtin_cheri_bounds_set(ptr, __builtin_cheri_round_representable_length(size));
    TLSF_MUTEX_UNLOCK();

    return ptr;
}


void *calloc(size_t nelem, size_t elsize);
void *calloc (size_t nelem, size_t elsize)
{
    register void *ptr;  
    if (nelem == 0 || elsize == 0)
        nelem = elsize = 1;
    
    ptr = __malloc (nelem * elsize); 
    if (ptr) bzero (ptr, nelem * elsize);
    
    return ptr;
}


void free(void *ptr);
void free(void *ptr)
{
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[gm_ptr->active_domain]);


    TLSF_MUTEX_LOCK();
    ptr = __builtin_cheri_address_set(di_ptr->tlsf, __builtin_cheri_address_get(ptr));
    tlsf_free(di_ptr->tlsf, ptr);
    TLSF_MUTEX_UNLOCK();
}





void cheri_heap_init_udi(int udi);
void cheri_heap_init_udi(int udi){

    size_t  app_heap_size; 
    uintptr_t  app_heap_address;
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[udi]);


    char *pTmp;

    pTmp = getenv( "APP_HEAP_SIZE");

    if(pTmp != NULL){
        app_heap_size = atoi(pTmp);
    }else{
        app_heap_size = APP_DEFAULT_HEAP_SIZE;
    }


    app_heap_address = (uintptr_t)mmap(NULL, APP_DEFAULT_HEAP_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    

    
    if(app_heap_size <= TLSF_MAX_POOL_SIZE){
        di_ptr->tlsf = tlsf_create_with_pool((void *)app_heap_address, app_heap_size);
    }else{
        di_ptr->tlsf = tlsf_create_with_pool((void *)app_heap_address, TLSF_MAX_POOL_SIZE);
        app_heap_size = app_heap_size - TLSF_MAX_POOL_SIZE;
        app_heap_address =  app_heap_address + TLSF_MAX_POOL_SIZE;
        while (app_heap_size  > TLSF_MAX_POOL_SIZE)
        {
            tlsf_add_pool(di_ptr->tlsf, (void *)app_heap_address, TLSF_MAX_POOL_SIZE);
            app_heap_size = app_heap_size - TLSF_MAX_POOL_SIZE;
            app_heap_address = app_heap_address + TLSF_MAX_POOL_SIZE;
        }
        tlsf_add_pool(di_ptr->tlsf, (void *)app_heap_address, app_heap_size);
    }

}

int sdrad_memalign(int udi, void **memptr, size_t alignment, size_t size)
{
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[udi]);
    void *ptr;


    if(di_ptr->heap_init != INIT){
        cheri_heap_init_udi(udi);
        di_ptr->heap_init = INIT;
    }

    ptr = tlsf_memalign(di_ptr->tlsf, alignment, size);
    ptr = __builtin_cheri_bounds_set(ptr, __builtin_cheri_round_representable_length(size));
    *memptr = ptr; 
    // return to old pkru value
    return 0; //tlsf_memalign doesn't have any zero code
}

void *sdrad_malloc(int udi, size_t size)
{
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[udi]);


    if(di_ptr->heap_init != INIT){
        cheri_heap_init_udi(udi);
        di_ptr->heap_init = INIT;
    }

    void *ptr;
    size_t rounded_len = __builtin_cheri_round_representable_length(size);

    ptr = tlsf_malloc(di_ptr->tlsf, rounded_len);
    ptr = __builtin_cheri_bounds_set(ptr, rounded_len);
    return ptr;
}
void sdrad_free(int udi, void *ptr)
{
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[udi]);


    TLSF_MUTEX_LOCK();
    ptr = __builtin_cheri_address_set(di_ptr->tlsf, __builtin_cheri_address_get(ptr));
    tlsf_free(di_ptr->tlsf, ptr);
    TLSF_MUTEX_UNLOCK();
}