#include "../include/6502.h"
#include "../include/bus.h"
#include <stdio.h>

using s = Sixty502;

Sixty502::Sixty502() {
	instructions =  {
		{ "BRK", &s::MODE_IMP, &s::BRK, 7 }, { "ORA", &s::MODE_INDX, &s::ORA, 6 }
	};
}

/**
* Writes data to the bus.
*/
void Sixty502::write(uint16_t address, uint8_t data){
	bus->write(address, data);
}

/**
* Executes the actual instructions.
*/
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

uint8_t Sixty502::fetch() {
	if (!(instructions[opcode].address_mode == &s::MODE_IMP) || !(instructions[opcode].address_mode == &s::MODE_ACC))
		fetched_data = read(addr_abs);
	return fetched_data;
}

/**
* Resets the MPU.
*/
void Sixty502::reset() {
	uint16_t lo = read(0xFFFC);
	uint16_t hi = read(0xFFFD);

	pc = (hi << 8) | lo;

	x = 0x00;
	y = 0x00;
	a = 0x00;
	status = 0x00 | U;
	fetched_data = 0x00;

	addr_abs = 0x00;

	clock_count = 0;
	cycles += 8;
}

/**
* Reads data from the bus.
*/
uint8_t Sixty502::read(uint16_t address) {
	return bus->read(address);
}

/**
* Sets flag from the status register.
*/
void Sixty502::set_flag(Sixty502::FLAGS6502 flag, bool status) {
	if (status) 
		status |= flag;
	else
		status &= ~flag;
}

bool Sixty502::check_page_crossing(uint16_t address, uint16_t off) {
	return ((address & 0xFF00) != (off << 8));	//This means that adding the x register resulted in a carry (crossing page boundries) and requires an extra clock cycle.
}

/**
* Gets specific flag from status register.
*/
uint8_t Sixty502::get_flag(Sixty502::FLAGS6502 flag) {
	return (((status & flag) > 0) ? 1 : 0);
}

// 6502 ADDRESSING MODES!
/**
* The return of the address modes is any extra clock cycles needed. Example
* would be a carry operation occuring.
*/

/**
* Accumulator:
* No extra data is needed, the instruction works off the 'a' register.
*/
uint8_t Sixty502::MODE_ACC() {
	fetched_data = a;
	return 0;
}

/**
* Absoulte:
* The next two bytes are a 16 bits that could be used by the instruction. 6502 is little endian
* so the first byte is the low and the second is the high.
*/
uint8_t Sixty502::MODE_ABS() {
	uint16_t low = read(pc++);
	uint16_t high = read(pc++);

	addr_abs = (high << 8) | low;

	return 0;
}

/**
* Absoulte X:
* Same as Absoulte from above but it also will add the x register to the 16 bit address read in.
*/
uint8_t Sixty502::MODE_ABSX() {
	uint16_t low = read(pc++);
	uint16_t high = read(pc++);

	addr_abs = ((high << 8) | low) + x;

	if ((addr_abs & 0xFF00) != (high << 8))	//This means that adding the x register resulted in a carry (crossing page boundries) and requires an extra clock cycle.
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

	addr_abs = ((high << 8) | low) + y;

	return (uint8_t)check_page_crossing(addr_abs, high);
}

/**
* Immediate:
* The instruction needs the following byte.
*/
uint8_t Sixty502::MODE_IMM() {
	addr_abs = read(pc++);
	return 0;
}

/**
* Implied:
* The instruction requires no extra data because the instruction 'implies' what it will do.
*/
uint8_t Sixty502::MODE_IMP() {
	fetched_data = a; //expect that the a register will be useful.
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
	addr_abs = (read(ptr + 1) << 8) | read(ptr);	//Reading from the specified ptr to get the actual address.

	return 0;
}

/**
* Indirect X:
* Reads the 2nd byte of the instruction then adds the x register to it and goes to the zero page to read the real
* address. The ptr points to the low bytes and the next address points to the high bytes. There is no need to check for page 
* crossing because the ptr wraps within the 0 page.
*/
uint8_t Sixty502::MODE_INDX() {
	uint8_t ptr = read(pc++) + x;
	addr_abs = (read(ptr + 1) << 8) | read(ptr);

	return 0;
}

/**
* Indirect Y:
* Same as Indirect X but with te y register.
*/
uint8_t Sixty502::MODE_INDY() {
	uint8_t ptr = read(pc++) + y;
	addr_abs = (read(ptr + 1) << 8) | read(ptr);

	return 0;
}

/**
* Relative:
* Used with branch instructions. Takes the 2nd byte of the instruction and adds the pc to get the address.
* This has to be a signed byte so (-128 to +127).
*/
uint8_t Sixty502::MODE_REL() {
	addr_abs = read(pc++);
	addr_abs &= 0x00FF;
	addr_abs = pc + addr_abs;
	return 0;
}

/**
* Zero Page:
* It read the 2nd byte and gets the address from the zero page.
*/
uint8_t Sixty502::MODE_ZP() {
	addr_abs = read(pc++);
	addr_abs &= 0x00FF;
	return 0;
}

/**
* Zero Page X:
* It read the 2nd byte but also adds the x register and gets the address from the zero page.
*/
uint8_t Sixty502::MODE_ZPX() {
	addr_abs = read(pc++) + x;
	addr_abs &= 0x00FF;
	return 0;
}

/**
* Zero Page Y:
* Same as Zero Page X but with the y register.
*/
uint8_t Sixty502::MODE_ZPY() {
	addr_abs = read(pc++) + y;
	addr_abs &= 0x00FF;
	return 0;
}

/**
* There is no instruction for the specified opcode making it 'illegal'.
*/
uint8_t Sixty502::ILL() {
	return 0;
}

//6502 INSTRUCTIONS!

/**
* BRK - Force Break
* Initiates a software interrupt similar to an IRQ. 
*/
uint8_t Sixty502::BRK() {
	pc++;

	//Set interrupt flag
	set_flag(FLAGS6502::I, true);
	write(0x0100 + stkptr, (pc >> 8) & 0x00FF);
	stkptr--;
	write(0x0100 + stkptr, pc & 0x00FF);
	stkptr--;

	//Set break flag
	set_flag(FLAGS6502::B, true);
	write(0x0100 + stkptr, status);
	stkptr--;
	set_flag(FLAGS6502::B, false);

	pc = (uint16_t)read(0xFFFE) | ((uint16_t)read(0xFFFF) << 8);	//Go to interrupt (NMI)
	return 0;
}

/**
* ORA - OR memory
* Or's the contents in the a register.
*/
uint8_t Sixty502::ORA() {
	a |= fetch();

	set_flag(FLAGS6502::Z, a == 0x00);
	set_flag(FLAGS6502::N, a == 0x80);
	return 1;
}

/**
* BPL - Branch on Result Plus
*/
uint8_t Sixty502::BPL() {
	uint8_t extra_cycles = 0;
	if (get_flag(FLAGS6502::N) == 0) {
		extra_cycles++;
	
		uint16_t new_addr = pc + addr_abs;

		if ((new_addr & 0xFF00) != (pc & 0xFF00))
			extra_cycles++;

		pc = new_addr;
	}


	return extra_cycles;
}