#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include <array>

#include "6502.h"

#define RAM_SIZE 64 * 1024

class Bus {
public:
	Bus();

	uint8_t* ram;
	Sixty502 cpu;

	void write(uint16_t address, uint8_t data);
	uint8_t read(uint16_t address);
};

#endif // !BUS_H
