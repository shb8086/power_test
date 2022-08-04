    .text
    .type gemm_asm_power_16_6_1, %function
    .global gemm_asm_power_16_6_1
    /*
    * Performs the matrix-multiplication C+=A*B
    * with the shapes (16x6) = (16x1) * (1x6).
    * The input-data is of type float.
    *
    * @param x0 pointer to A.
    * @param x1 pointer to B.
    * @param x2 pointer to C.
    */ 
gemm_asm_power_16_6_1:
