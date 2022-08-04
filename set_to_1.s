    .text
    .align 2
    .type set_to_1, %function
    .global set_to_1
set_to_1:
    li r3, 12
    stw r3, 24(SP)
    #addi sp, sp, #24
    lfs f1, 24(SP)
