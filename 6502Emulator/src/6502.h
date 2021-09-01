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
	void fetch();

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

	uint8_t IMP();
	uint8_t IMM();
	uint8_t ZP();
	uint8_t ZPX();
	uint8_t ZPY();
	uint8_t REL();
	uint8_t ABS();
	uint8_t ABX();
	uint8_t ABY();
	uint8_t IND();
	uint8_t INX();
	uint8_t INY();

	uint8_t ADC(); uint8_t AND(); uint8_t ASL(); uint8_t BCC(); uint8_t BCS(); uint8_t BEQ(); uint8_t BIT(); uint8_t BMI(); uint8_t BNE(); uint8_t BPL(); uint8_t BRK(); uint8_t BVC(); uint8_t BVS(); uint8_t CLC();
	uint8_t CLD(); uint8_t CLI(); uint8_t CLV(); uint8_t CMP(); uint8_t CPX(); uint8_t CPY(); uint8_t DEC(); uint8_t DEX(); uint8_t DEY(); uint8_t EOR(); uint8_t INC(); uint8_t INX(); uint8_t INY(); uint8_t JMP();
	uint8_t JSR(); uint8_t LDA(); uint8_t LDX(); uint8_t LDY(); uint8_t LSR(); uint8_t NOP(); uint8_t ORA(); uint8_t PHA(); uint8_t PHP(); uint8_t PLA(); uint8_t PLP(); uint8_t ROL(); uint8_t ROR(); uint8_t RTI();
	uint8_t RTS(); uint8_t SBC(); uint8_t SEC(); uint8_t SED(); uint8_t SEI(); uint8_t STA(); uint8_t STX(); uint8_t STY(); uint8_t TAX(); uint8_t TAY(); uint8_t TSX(); uint8_t TXA(); uint8_t TXS(); uint8_t TYA();

	uint8_t ILL();

	struct Instruction {
		std::string name;

		uint8_t(Sixty502::*address_mode)(void) = nullptr;
		uint8_t(Sixty502::*opcode)(void) = nullptr;

		uint8_t cycles = 0;
	};

	std::vector<Instruction> lookup;

	Bus* bus = nullptr;

	uint8_t  fetched = 0x00;
	uint16_t addr_abs = 0x0000;
	uint16_t addr_rel = 0x0000;
	uint32_t clock_count = 0;
	uint8_t  opcode = 0x00;
	uint8_t  cycles = 0;
};

#endif // !SIXTY502_H
