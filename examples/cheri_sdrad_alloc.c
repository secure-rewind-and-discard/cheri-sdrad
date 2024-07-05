/**
 * @file cheri_sdrad_alloc.c
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#include "../src/cheri_sdrad_api.h"

void allocation(){
    int active_domain = cheri_sdrad_manager.active_domain;
    void* a = malloc(1);
    printf("Inside domain: %d\n",active_domain);
    printf("CHERI-SDRaD Heap: %#p\n",cheri_sdrad_manager.domain_info[active_domain].tlsf);
    printf("a: %#p\n\n",a);
    free(a);
}


int main(void){

    int udi = 1;
    int err;


    allocation();
    
    err = cheri_domain_setup(udi);
    if(err == SUCCESSFUL_INITIALIZE || err == ALREADY_INITIALIZE){
        cheri_domain_enter(udi);
        allocation();
        cheri_domain_exit();
    }

    return 0;
}