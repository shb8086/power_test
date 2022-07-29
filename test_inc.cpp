#include <cstdint>
#include <cstdlib>
#include <iostream>
using namespace std;

extern "C"{
	void one_asm (float *a);
  void load_asm_2 (float *a);
  void load_asm (float *a);
}

int main(){
	float l_a10[4] = { 1, 2, 3, 4 };
  load_asm_2( l_a10 );
  std::cout << "example_10: " << l_a10[0] << " / " << l_a10[1] << " / " << l_a10[2] << " / " << l_a10[3] << std::endl;
  return 0;
}
