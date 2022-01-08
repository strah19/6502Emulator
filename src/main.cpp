#include <stdio.h>
#include "../include/bus.h"

int main() {
	Bus b;

	b.ram[0xFFFC] = 0x00;
	b.ram[0xFFFD] = 0x80;

	b.ram[0x8000] = 0x12;
	b.ram[0x0087] = 0x42;

	b.cpu.reset();

	b.cpu.y = 0x75;
	b.cpu.MODE_INDY();
	printf("%x\n", b.cpu.addr_abs);

	return 0;
}