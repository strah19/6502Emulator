#include "bus.h"

Bus::Bus() {
	cpu.connect_bus(this);

	ram = new uint8_t[RAM_SIZE];

	for (int i = 0; i < RAM_SIZE; i++)
		ram[i] = 0x00;
}

void Bus::write(uint16_t address, uint8_t data) {
	if (address >= 0x00 && address <= 0xFFFF)
		ram[address] = data;
}

uint8_t Bus::read(uint16_t address) {
	if (address >= 0x00 && address <= 0xFFFF)
		return ram[address];
	return 0x00;
}
