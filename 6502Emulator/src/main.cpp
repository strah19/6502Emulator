#include <stdio.h>
#include "bus.h"

int main() {
	Bus b;

	b.ram[0xFFFC] = 0x00;
	b.ram[0xFFFD] = 0x80;

	b.ram[0x8000] = 0xa9;
	b.ram[0x8001] = 0x12;
	b.ram[0x8002] = 0xea;

	b.cpu.reset();


	while (b.cpu.pc < 0x8003) {
		if (b.cpu.clock()) {
			printf("Reading 0x%x from 0x%x\n", b.read(b.cpu.pc), b.cpu.pc);
			printf("OPCODE: 0x%x\n", b.cpu.opcode);
			printf("A Register: 0x%x\n", b.cpu.a);
		}
	}

	return 0;
}