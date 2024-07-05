/**
 * @file cheri_sdrad_signal.h
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#ifndef _CHERI_SDRAD_SIGNAL_H
#define _CHERI_SDRAD_SIGNAL_H

#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <assert.h>
#include "cheri_sdrad.h"


void cheri_signal_handler(int signum);
void cheri_setup_signal_handler();

#endif