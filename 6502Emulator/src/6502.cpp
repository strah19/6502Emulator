#include "6502.h"
#include "bus.h"
#include <stdio.h>

Sixty502::Sixty502() {
	using s = Sixty502;
}

void Sixty502::write(uint16_t address, uint8_t data){
	bus->write(address, data);
}

bool Sixty502::clock() {
	bool executed = false;

	if (cycles == 0) {
		opcode = read(pc++);
		set_flag(FLAGS6502::U, true);
		cycles = instructions[opcode].cycles;
		printf("%s\n", instructions[opcode].name.c_str());

		uint8_t additional_cycle1 = (this->*instructions[opcode].address_mode)();
		uint8_t additional_cycle2 = (this->*instructions[opcode].opcode)();

		cycles += (additional_cycle1 & additional_cycle2);

		set_flag(FLAGS6502::U, true);

		executed = true;
	}

	cycles--;
	clock_count++;

	return executed;
}

void Sixty502::reset() {
	uint16_t lo = read(0xFFFC);
	uint16_t hi = read(0xFFFD);

	pc = (hi << 8) | lo;

	x = 0x00;
	y = 0x00;
	a = 0x00;
	f = 0x00 | U;

	addr_mode_bytes = 0x00;

	clock_count = 0;
	cycles += 8;
}

uint8_t Sixty502::read(uint16_t address) {
	return bus->read(address);
}

void Sixty502::set_flag(Sixty502::FLAGS6502 flag, bool status) {
	if (status) 
		f |= flag;
	else
		f &= ~flag;
}

uint8_t Sixty502::get_flag(Sixty502::FLAGS6502 flag) {
	return (((f & flag) > 0) ? 1 : 0);
}

// 6502 ADDRESSING MODES!

/**
* Accumulator:
* No extra data is needed, the instruction works off the a register.
*/
uint8_t Sixty502::MODE_ACC() {
	return 0;
}

/**
* Absoulte:
* The next two bytes are a 16 bit address that could be used by the instruction. 6502 is little endian
* so the first byte is the low and the second is the high.
*/
uint8_t Sixty502::MODE_ABS() {
	uint16_t low = read(pc++);
	uint16_t high = read(pc++);

	addr_mode_bytes = (high << 8) | low;

	return 0;
}

/**
* Absoulte X:
* Same as Absoulte from above but it also will add the x register to the 16 bit address read in.
*/
uint8_t Sixty502::MODE_ABSX() {
	uint16_t low = read(pc++);
	uint16_t high = read(pc++);

	addr_mode_bytes = ((high << 8) | low) + x;

	if ((addr_mode_bytes & 0xFF00) != (high << 8))	//This means that adding the x register resulted in a carry (crossing page boundries) and requires an extra clock cycle.
		return 1;
	return 0;
}

/**
* Absoulte Y:
* Same as Absoulte X but works with the y register.
*/
uint8_t Sixty502::MODE_ABSY() {
	uint16_t low = read(pc++);
	uint16_t high = read(pc++);

	addr_mode_bytes = ((high << 8) | low) + y;

	if ((addr_mode_bytes & 0xFF00) != (high << 8))	//This means that adding the y register resulted in a carry (crossing page boundries) and requires an extra clock cycle.
		return 1;
	return 0;
}

/**
* Immediate:
* The instruction needs the following byte.
*/
uint8_t Sixty502::MODE_IMM() {
	addr_mode_bytes = read(pc++);
	return 0;
}

/**
* Implied:
* The instruction requires no extra data because the instruction 'implies' what it will do.
*/
uint8_t Sixty502::MODE_IMP() {
	return 0;
}

/**
* Indirect:
* Only the JMP instruction uses this address mode. It takes the 2nd and 3rd bytes of the instruction
* and forms a pointer. 
*/
uint8_t Sixty502::MODE_IND() {
	uint16_t low = read(pc++);
	uint16_t high = read(pc++);

	uint16_t ptr = (high << 8) | low;
	addr_mode_bytes = (read(ptr + 1) << 8) | read(ptr);	//Reading from the specified ptr to get the actual address.

	return 0;
}

/**
* Indirect X:
* Reads the 2nd byte of the instruction then adds the x register to it and goes to the zero page to read the real
* address. The ptr points to the low bytes and the next address points to the high bytes.
*/
uint8_t Sixty502::MODE_INDX() {
	uint8_t ptr = read(pc++) + x;
	addr_mode_bytes = (read(ptr + 1) << 8) | read(ptr);

	return 0;
}

/**
* Indirect Y:
* Same as Indirect X but with te y register.
*/
uint8_t Sixty502::MODE_INDY() {
	uint8_t ptr = read(pc++) + y;
	addr_mode_bytes = (read(ptr + 1) << 8) | read(ptr);

	return 0;
}

/**
* Relative:
* Used with branch instructions. Takes the 2nd byte of the instruction and adds the pc to get the address.
* This has to be a signed byte so (-128 to +127).
*/
uint8_t Sixty502::MODE_REL() {
	addr_mode_bytes = read(pc++);
	addr_mode_bytes = pc + addr_mode_bytes;
	return 0;
}

/**
* Zero Page:
* It read the 2nd byte and gets the address from the zero page.
*/
uint8_t Sixty502::MODE_ZP() {
	addr_mode_bytes = read(pc++);
	addr_mode_bytes &= 0x00FF;
	return 0;
}

/**
* Zero Page X:
* It read the 2nd byte but also adds the x register and gets the address from the zero page.
*/
uint8_t Sixty502::MODE_ZPX() {
	addr_mode_bytes = read(pc++) + x;
	addr_mode_bytes &= 0x00FF;
	return 0;
}

/**
* Zero Page Y:
* Same as Zero Page X but with the y register.
*/
uint8_t Sixty502::MODE_ZPY() {
	addr_mode_bytes = read(pc++) + y;
	addr_mode_bytes &= 0x00FF;
	return 0;
}

/**
* There is no instruction for the specified opcode.
*/
uint8_t Sixty502::ILL() {
	return 0;
}