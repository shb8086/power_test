BUILD_DIR = ./build

gemm_asm_power: driver.cpp kernels/gemm_ref.cpp kernels/gemm_asm_power_8_4_1_sp.s kernels/gemm_asm_power_8_4_1_sp.s
				g++ -g -pedantic -Wall -Wextra -Werror -O2 -c kernels/gemm_ref.cpp -o ${BUILD_DIR}/gemm_ref.o
				gcc -g -mregnames -pedantic -Wall -Wextra -Werror -c kernels/gemm_asm_power_8_4_1_sp.s -o ${BUILD_DIR}/gemm_asm_power_8_4_1_sp.o
				g++ -g -pedantic -Wall -Wextra -Werror driver.cpp ${BUILD_DIR}/gemm_ref.o ${BUILD_DIR}/gemm_asm_power_8_4_1_sp.o -o ${BUILD_DIR}/gemm_asm_power
$(shell mkdir -p build)
