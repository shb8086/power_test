BUILD_DIR = ./build

gemm_asm_power: driver.cpp kernels/gemm_ref.cpp kernels/gemm_asm_power_8_4_1.s kernels/gemm_asm_power_8_4_1.s
				g++ -g -pedantic -Wall -Wextra -Werror -O2 -c kernels/gemm_ref.cpp -o ${BUILD_DIR}/gemm_ref.o
				gcc -g -mregnames -pedantic -Wall -Wextra -Werror -c kernels/gemm_asm_power_8_4_1.s -o ${BUILD_DIR}/gemm_asm_power_8_4_1.o
				g++ -g -pedantic -Wall -Wextra -Werror driver.cpp ${BUILD_DIR}/gemm_ref.o ${BUILD_DIR}/gemm_asm_power_8_4_1.o -o ${BUILD_DIR}/gemm_asm_power
$(shell mkdir -p build)
