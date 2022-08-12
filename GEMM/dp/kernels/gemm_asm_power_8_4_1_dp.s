    .text
    .type gemm_asm_power_8_4_1_dp, %function
    .global gemm_asm_power_8_4_1_dp
    /*
    * Performs the matrix-multiplication C+=A*B
    * with the shapes (8x4) = (8x1) * (1x4).
    * The input-data is of type double.
    *
    * @param r3 pointer to A.
    * @param r4 pointer to B.
    * @param r5 pointer to C.
    */
gemm_asm_power_8_4_1_dp:

    # loading A
    lxvd2x vs0,0,r3
    addi r3, r3, 2*8 # 2 block of double precision
    lxvd2x vs1,0,r3
    # subi r3, r3, (2*8)

    # loading C
    lxvd2x vs2,0,r5
    addi r5, r5, (2*8)
    lxvd2x vs3,0,r5
    addi r5, r5, (2*8)
    lxvd2x vs4,0,r5
    addi r5, r5, (2*8)
    lxvd2x vs5,0,r5
    addi r5, r5, (2*8)
    lxvd2x vs6,0,r5
    addi r5, r5, (2*8)
    lxvd2x vs7,0,r5
    addi r5, r5, (2*8)
    lxvd2x vs8,0,r5
    addi r5, r5, (2*8)
    lxvd2x vs9,0,r5
    subi r5, r5, (2*8*7)

    # loading B
    /*lxvd2x vs10,0,r4
    xxspltw vs11, vs10, 0
    xxspltw vs12, vs10, 1
    xxspltw vs13, vs10, 2
    xxspltw vs14, vs10, 3*/
    lxvdsx vs11, 0, r4
    addi r4, r4, 8
    lxvdsx vs12, 0, r4
    addi r4, r4, 8
    lxvdsx vs13, 0, r4
    addi r4, r4, 8
    lxvdsx vs14, 0, r4
    #subi r4, r4, (8*3)

    # mul-add
    xvmaddadp vs2, vs0, vs11 # vs2 = vs2 + vs0 * vs11
    xvmaddadp vs3, vs1, vs11 
    xvmaddadp vs4, vs0, vs12
    xvmaddadp vs5, vs1, vs12
    xvmaddadp vs6, vs0, vs13
    xvmaddadp vs7, vs1, vs13
    xvmaddadp vs8, vs0, vs14
    xvmaddadp vs9, vs1, vs14

    # storing C 
    stxvd2x vs2,0,r5
    addi r5, r5, (2*8)
    stxvd2x vs3,0,r5
    addi r5, r5, (2*8)
    stxvd2x vs4,0,r5
    addi r5, r5, (2*8)
    stxvd2x vs5,0,r5
    addi r5, r5, (2*8)
    stxvd2x vs6,0,r5
    addi r5, r5, (2*8)
    stxvd2x vs7,0,r5
    addi r5, r5, (2*8)
    stxvd2x vs8,0,r5
    addi r5, r5, (2*8)
    stxvd2x vs9,0,r5
    # subi r5, r5, (2*8*7)
