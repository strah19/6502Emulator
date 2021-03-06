#ifndef SIXTY502_H
#define SIXTY502_H

#include <cstdint>
#include <vector>
#include <string>

#define NMI_LOW 0xFFFE
#define NMI_HIGH 0xFFFF

class Bus;

class Sixty502 {
public:
	Sixty502();

	uint8_t a = 0x00;
	uint8_t x = 0x00;
	uint8_t y = 0x00;
	uint16_t pc = 0x00;
	uint8_t status = 0x00;

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
	uint8_t fetch();
	bool check_page_crossing(uint16_t address, uint16_t off);
	void update_z_and_n_flag(uint8_t check);

	//Address modes
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

	//Illegal instruction
	uint8_t ILL();

	//Instructions
	uint8_t BRK(); uint8_t ORA();
	uint8_t BPL(); uint8_t AND();
	uint8_t LDA(); uint8_t STX();
	uint8_t STA(); uint8_t STY();
	uint8_t TAX(); uint8_t TXA();
	uint8_t DEX(); uint8_t INX();
	uint8_t TAY(); uint8_t TYA();
	uint8_t DEY(); uint8_t INY();
	uint8_t ROL(); uint8_t ROR();
	uint8_t NOP();

	struct Instruction {
		std::string name;

		uint8_t(Sixty502::* address_mode)(void) = nullptr;
		uint8_t(Sixty502::* opcode)(void) = nullptr;

		uint8_t cycles = 0;
	};

	std::vector<Instruction> instructions;

	Bus* bus = nullptr;

	uint8_t fetched_data = 0x00;
	uint16_t addr_abs = 0x0000;

	uint8_t stkptr = 0x00;
	uint32_t clock_count = 0;
	uint8_t  opcode = 0x00;
	uint8_t  cycles = 0;
};

#endif // !SIXTY502_H
