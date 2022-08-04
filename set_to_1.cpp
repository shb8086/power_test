#include <cstdint>
#include <cstdlib>
#include <iostream>
using namespace std;

extern "C"{
	void set_to_1 (float *a);
}

int main(){
	float l_a10 = 5;
  set_to_1( &l_a10 );
  std::cout << "example_10: " << l_a10 << std::endl;
  return 0;
}
