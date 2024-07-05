/**
 * @file cheri_sdrad_api.c
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#include "cheri_sdrad_api.h"

global_manager_s cheri_sdrad_manager = { .active_domain = 0, .domain_info[0].parent_udi = 0 }; // init of the main domain

int cheri_domain_enter(uint32_t udi){
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    

    if(udi > (NUMBER_MAX_DOMAIN) || udi < 1){
        printf("invalid uid, you should choose one between 1 and %d\n",NUMBER_MAX_DOMAIN);
        return UDI_OUT_OF_BOUNDS;
    }

    domain_info_s *di_ptr = &(gm_ptr->domain_info[udi]);

    if(di_ptr->domain_init != INIT){
        printf("This domain is not initialised\n");
        return NOT_INITIALIZE;
    }

    gm_ptr->active_domain = udi;
    return 0;
}

int cheri_domain_exit(){
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[gm_ptr->active_domain]);


    gm_ptr->active_domain = di_ptr->parent_udi;
    return 0;
}