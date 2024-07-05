/**
 * @file cheri_sdrad_overflow.c
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#include "../src/cheri_sdrad_api.h"

void get_request(){
    char buff[5];
    printf("Waiting for the request:\n");
    scanf("%s",buff);
    printf("Handling the request\n");
}

int main(void){
    int i = 0;
    int err;
    int udi = 1
    ;
    for(i = 0; i < 5; i++){
        err = cheri_domain_setup(udi);
		if(err == SUCCESSFUL_INITIALIZE || err == ALREADY_INITIALIZE){
            cheri_domain_enter(udi);
			get_request();
            cheri_domain_exit();
		}
        else{
            printf("Bad input!\n");
        }
    }

    return 0;
}