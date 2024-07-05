/**
 * @file cheri_sdrad_api.h
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

#ifndef _CHERI_SDRAD_API_H
#define _CHERI_SDRAD_API_H

#include "tlsf.h"
#include "cheri_sdrad.h"
#include "cheri_sdrad_signal.h"
#include "cheri_sdrad_heap_mng.h"

#include <string.h>

/**
 * @brief Initialize Domain with a unique udi
 * 
 * @param udi 
 * @return int32_t UDI_OUT_OF_BOUNDS (-2)
 *                 ALREADY_INITIALIZE (1)
 *                 SUCCESSFUL_INITIALIZE (0)
 */
extern int cheri_domain_setup(int udi);

/**
 * @brief entering already initialized domain
 * 
 * @param udi 
 * @return int32_t UDI_OUT_OF_BOUNDS (-2)
 *                 NOT_INITIALIZE (2)
 */
int cheri_domain_enter(uint32_t udi);

/**
 * @brief exiting from the current domain to the parent one
 *
 */
int cheri_domain_exit();

#endif