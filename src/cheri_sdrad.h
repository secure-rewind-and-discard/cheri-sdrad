/**
 * @file cheri_sdrad.h
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#ifndef _CHERI_SDRAD_H
#define _CHERI_SDRAD_H

#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tlsf.h"


#define UDI_OUT_OF_BOUNDS -2
#define ABNORMAL_EXIT -1
#define SUCCESSFUL_INITIALIZE 0
#define ALREADY_INITIALIZE 1
#define NOT_INITIALIZE 2


#define NUMBER_MAX_DOMAIN 15
enum State{UNINIT, INIT};

typedef struct _return_reg_type_s {
    void *c29;
    void *c30;
}return_reg_type_s;


typedef struct _domain_info_s {
    jmp_buf env;
    return_reg_type_s return_address;
    tlsf_t tlsf;
    uint32_t parent_udi;
    enum State domain_init;
    enum State heap_init;
} domain_info_s;


typedef struct _global_manager_s{
    uint32_t active_domain;
    domain_info_s domain_info[NUMBER_MAX_DOMAIN+1];
} global_manager_s;


struct cheri_init_stack_s{
    jmp_buf env;
    uint64_t udi; 
    return_reg_type_s return_address;
};



extern global_manager_s cheri_sdrad_manager;

int cheri_domain_init(void *base_address);
void *cheri_domain_destroy();

#endif