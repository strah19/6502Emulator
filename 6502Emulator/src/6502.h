#ifndef SIXTY502_H
#define SIXTY502_H

#include <cstdint>
#include <vector>
#include <string>

class Bus;

class Sixty502 {
public:
	Sixty502();

	uint8_t a = 0x00;
	uint8_t x = 0x00;
	uint8_t y = 0x00;
	uint16_t pc = 0x00;
	uint8_t f = 0x00;
	uint8_t sp = 0x00;

	void connect_bus(Bus* bus) { this->bus = bus; }
	bool clock();
	void reset();

	enum FLAGS6502
	{
		C = 0x01,	// Carry Bit
		Z = 0x02,	// Zero
		I = 0x04,	// Disable Interrupts
		D = 0x08,	// Decimal Mode (unused in this implementation)
		B = 0x10,	// Break
		U = 0x20,	// Unused
		V = 0x40,	// Overflow
		N = 0x80,	// Negative
	};

	void write(uint16_t address, uint8_t data);
	uint8_t read(uint16_t address);

	void set_flag(FLAGS6502 flag, bool status);
	uint8_t get_flag(FLAGS6502 flag);

	uint8_t MODE_ACC();
	uint8_t MODE_ABS();
	uint8_t MODE_ABSX();
	uint8_t MODE_ABSY();
	uint8_t MODE_IMM();
	uint8_t MODE_IMP();
	uint8_t MODE_IND();
	uint8_t MODE_INDX();
	uint8_t MODE_INDY();
	uint8_t MODE_REL();
	uint8_t MODE_ZP();
	uint8_t MODE_ZPX();
	uint8_t MODE_ZPY();

	uint8_t ILL();

	struct Instruction {
		std::string name;

		uint8_t(Sixty502::*address_mode)(void) = nullptr;
		uint8_t(Sixty502::*opcode)(void) = nullptr;

		uint8_t cycles = 0;
	};

	std::vector<Instruction> instructions;

	Bus* bus = nullptr;

	uint16_t addr_mode_bytes = 0x0000;
	uint32_t clock_count = 0;
	uint8_t  opcode = 0x00;
	uint8_t  cycles = 0;
};

#endif // !SIXTY502_H
