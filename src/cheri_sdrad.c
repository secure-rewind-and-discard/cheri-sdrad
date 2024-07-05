/**
 * @file cheri_sdrad.c
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#include "cheri_sdrad.h"

int cheri_domain_init(void *base_address){
    struct cheri_init_stack_s *cis_ptr; 
    cis_ptr = (struct cheri_init_stack_s *)base_address; 
    long udi = cis_ptr->udi;
    global_manager_s *gm_ptr = &cheri_sdrad_manager;


    if(udi > (NUMBER_MAX_DOMAIN) || udi < 1){

        printf("invalid udi, you should choose one between 1 and %d\n",NUMBER_MAX_DOMAIN);
        return UDI_OUT_OF_BOUNDS;
    }

    domain_info_s *di_ptr = &(gm_ptr->domain_info[udi]);

    if(di_ptr->domain_init == INIT){
        printf("This domain is already initialised\n");
        return ALREADY_INITIALIZE;
    }
    

    di_ptr->domain_init = INIT;
    di_ptr->parent_udi = gm_ptr->active_domain;
    di_ptr->return_address = cis_ptr->return_address;
    memcpy(di_ptr->env, cis_ptr->env, sizeof(jmp_buf)); 

    return SUCCESSFUL_INITIALIZE;
}

void *cheri_domain_destroy(){
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[gm_ptr->active_domain]);


    if(di_ptr->heap_init == INIT){
        tlsf_destroy(di_ptr->tlsf);
    }

    int temp = gm_ptr->active_domain;
    gm_ptr->active_domain = di_ptr->parent_udi;

    return &gm_ptr->domain_info[temp].return_address;
}