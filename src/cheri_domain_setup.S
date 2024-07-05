/**
 * @file cheri_domain_setup.S
 * @author Sacha Ruchlejmer
 * @date 2022-07-02
 * 
 * @copyright © Ericsson AB 2024
 * 
 * SPDX-License-Identifier: BSD 3-Clause
 */

.global    cheri_domain_setup
.type      cheri_domain_setup, "function"
.extern    setjmp@PLT


cheri_domain_setup:
    stp     c29, c30, [csp, #-32]!                  // store the return address on the stack
    str     c0, [csp, #-16]!                        // store the udi on the stack
    sub     csp, csp, #512                          // store some space for the environnement variable on the stack

    mov     c0, csp                                 // give the environnement variable to setjmp
    bl      setjmp@PLT
    cbnz    w0,.ljmp                                // if non 0 go to .ljmp
    mov     c0, csp
    bl      cheri_domain_init@PLT

    add     csp, csp, #528                          // restore the stack pointer
    ldp     c29, c30, [csp], #32                    // restore the return address and the stack pointer
    ret


.ljmp:
    bl      cheri_domain_destroy@PLT
    ldp     c29, c30, [c0]                           // load the return address
    add     csp, csp, #0x230                         // restore the stack pointer
    ret     c30