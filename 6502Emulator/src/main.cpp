#include <stdio.h>
#include "bus.h"

int main() {
	Bus b;

	b.ram[0xFFFC] = 0x00;
	b.ram[0xFFFD] = 0x80;

	b.ram[0x8000] = 0xA9;
	b.ram[0x8001] = 0x81;

	b.cpu.reset();

	while (b.cpu.pc < 0x8002)
		b.cpu.clock();
	printf("%x\n", b.cpu.a);
	return 0;
}