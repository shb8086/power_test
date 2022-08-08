    .text
    .type gemm_asm_power_8_4_1, %function
    .global gemm_asm_power_8_4_1
    /*
    * Performs the matrix-multiplication C+=A*B
    * with the shapes (8x4) = (8x1) * (1x4).
    * The input-data is of type float.
    *
    * @param r3 pointer to A.
    * @param r4 pointer to B.
    * @param r5 pointer to C.
    */
gemm_asm_power_8_4_1:

    # loading A
    lxvw4x vs0,0,r3
    addi r3, r3, 4*4 # 4 block of single precision
    lxvw4x vs1,0,r3
    # subi r3, r3, (4*4)

    # loading C
    lxvw4x vs2,0,r5
    addi r5, r5, (4*4)
    lxvw4x vs3,0,r5
    addi r5, r5, (4*4)
    lxvw4x vs4,0,r5
    addi r5, r5, (4*4)
    lxvw4x vs5,0,r5
    addi r5, r5, (4*4)
    lxvw4x vs6,0,r5
    addi r5, r5, (4*4)
    lxvw4x vs7,0,r5
    addi r5, r5, (4*4)
    lxvw4x vs8,0,r5
    addi r5, r5, (4*4)
    lxvw4x vs9,0,r5
    subi r5, r5, (4*4*7)

    # loading B
    lxvw4x vs10,0,r4
    xxspltw vs11, vs10, 0
    xxspltw vs12, vs10, 1
    xxspltw vs13, vs10, 2
    xxspltw vs14, vs10, 3

    # mul-add
    xvmaddasp vs2, vs0, vs11 # vs2 = vs2 + vs0 * vs11
    xvmaddasp vs3, vs1, vs11 
    xvmaddasp vs4, vs0, vs12
    xvmaddasp vs5, vs1, vs12
    xvmaddasp vs6, vs0, vs13
    xvmaddasp vs7, vs1, vs13
    xvmaddasp vs8, vs0, vs14
    xvmaddasp vs9, vs1, vs14

    # storing C 
    stxvw4x vs2,0,r5
    addi r5, r5, (4*4)
    stxvw4x vs3,0,r5
    addi r5, r5, (4*4)
    stxvw4x vs4,0,r5
    addi r5, r5, (4*4)
    stxvw4x vs5,0,r5
    addi r5, r5, (4*4)
    stxvw4x vs6,0,r5
    addi r5, r5, (4*4)
    stxvw4x vs7,0,r5
    addi r5, r5, (4*4)
    stxvw4x vs8,0,r5
    addi r5, r5, (4*4)
    stxvw4x vs9,0,r5
    # subi r5, r5, (4*4*7)
