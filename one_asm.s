    .text
    .align 2
    .type one_asm, %function
    .global one_asm
one_asm:
    # all byte elements are set to 1
    vcmpequb v0, v0, v0
    # negate, i.e., ones complement + 1
    vnegw v0, v0
    # convert to floating point
    vcfsx v0, v0, 0

    stvx v0, 0, r3
    blr