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

    // loading A 
    /* lxvwsx vs0,0,r3
       addi r3, r3, 4*4 //4 block of single precision
       lxvwsx vs0,0,r3
       subi r3, r3, 4*4 */

    lxvwsx vs0,0,r3
    lxvwsx vs1,(4*4),r3
    
    // loading B
    lxvwsx vs2,0,r4

    // loading C
    lxvwsx vs2,0,r5
    lxvwsx vs3,(4*4),r5
    lxvwsx vs4,(4*4*2),r5
    lxvwsx vs5,(4*4*3),r5
    lxvwsx vs6,(4*4*4),r5
    lxvwsx vs7,(4*4*5),r5
    lxvwsx vs8,(4*4*6),r5
    lxvwsx vs9,(4*4*7),r5
    lxvwsx vs10,(4*4*8),r5
    lxvwsx vs11,(4*4*9),r5

    // mul-add