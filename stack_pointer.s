    .text
    .align 2
    .type stack_pointer, %function
    .global stack_pointer
stack_pointer:
    li r3, 12
    stw r3, 24(SP)
    lfs f1, 24(SP)
