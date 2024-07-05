/**
 * @file cheri_sdrad_signal.c
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#include "cheri_sdrad_signal.h"

__attribute__((constructor))
void cheri_setup_signal_handler()
{
    struct sigaction sa;
    sa.sa_flags =  SA_SIGINFO;
    sa.sa_handler = cheri_signal_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGPROT, &sa, NULL) == -1) {
        printf("sigaction");
    }
}

void cheri_signal_handler(int signum)
{
    global_manager_s *gm_ptr = &cheri_sdrad_manager;
    domain_info_s *di_ptr = &(gm_ptr->domain_info[gm_ptr->active_domain]);
    int udi = gm_ptr->active_domain;

    
    printf("SIGPROT detected\n");

    if(udi != 0){
        sigset_t sigset;
        __int32_t ret;
        ret = sigemptyset(&sigset); assert(0 == ret);
        ret = sigaddset(&sigset, SIGPROT); assert(0 == ret);
        ret = sigprocmask(SIG_UNBLOCK, &sigset, NULL); assert(0 == ret);

        longjmp(di_ptr->env, ABNORMAL_EXIT);
    }
    else{
        exit(1);
    }
}