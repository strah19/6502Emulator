#include "6502.h"
#include "bus.h"
#include <stdio.h>

Sixty502::Sixty502() {
	using s = Sixty502;
	lookup = {
{ "BRK", &s::IMP, &s::BRK, 7 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "BPL", &s::REL, &s::BPL, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "JSR", &s::ABS, &s::JSR, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "BMI", &s::REL, &s::BMI, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "RTI", &s::IMP, &s::RTI, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "BVC", &s::REL, &s::BVC, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "RTS", &s::IMP, &s::RTS, 5 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "BVS", &s::REL, &s::BVS, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "BCC", &s::REL, &s::BCC, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "LDY", &s::IMM, &s::LDY, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "LDA", &s::ZP, &s::LDA,  3 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "LDA", &s::IMM, &s::LDA, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "BCS", &s::REL, &s::BCS, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "LDA", &s::ZPX, &s::LDA, 4 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "LDA", &s::ABY, &s::LDA, 4 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "CPY", &s::IMM, &s::CPY, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "BNE", &s::REL, &s::BNE, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "CPX", &s::IMM, &s::CPX, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "NOP", &s::IMP, &s::NOP, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
{ "BEQ", &s::REL, &s::BEQ, 2 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 }, { "???", &s::IMM, &s::ILL, 6 },
};
}

void Sixty502::write(uint16_t address, uint8_t data){
	bus->write(address, data);
}

bool Sixty502::clock() {
	bool executed = false;

	if (cycles == 0) {
		opcode = read(pc++);
		set_flag(FLAGS6502::U, true);
		cycles = lookup[opcode].cycles;
		printf("%s\n", lookup[opcode].name.c_str());

		uint8_t additional_cycle1 = (this->*lookup[opcode].address_mode)();
		uint8_t additional_cycle2 = (this->*lookup[opcode].opcode)();

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

	addr_abs = 0x00;
	addr_rel = 0x00;
	fetched = 0x00;

	clock_count = 0;
	cycles += 8;
}

void Sixty502::fetch() {
	if (!(lookup[opcode].address_mode == &Sixty502::IMP))
		fetched = read(addr_abs);
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

uint8_t Sixty502::IMP() {
	fetched = a;
	return 0x00;
}

uint8_t Sixty502::IMM() {
	addr_abs = pc++;
	return 0x00;
}

uint8_t Sixty502::ZP() {
	addr_abs = read(pc++);
	addr_abs &= 0x00FF;
	return 0x00;
}

uint8_t Sixty502::ZPX() {
	addr_abs = read(pc + x);
	pc++;
	addr_abs &= 0x00FF;
	return 0x00;
}

uint8_t Sixty502::ZPY() {
	addr_abs = read(pc + y);
	pc++;
	addr_abs &= 0x00FF;
	return 0x00;
}

uint8_t Sixty502::REL() {
	addr_rel = read(pc);
	pc++;

	if (addr_rel & 0x80)
		addr_rel |= 0xFF00;

	return 0x00;
}

uint8_t Sixty502::ABS() {
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;

	return 0x00;
}

uint8_t Sixty502::ABX() {
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += x;

	if ((addr_abs & 0xFF00) != (hi << 8))	//If the page is crossed it takes 1 extra cycle
		return 0x01;
	else
		return 0x00;
}

uint8_t Sixty502::ABY() {
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 0x01;
	else
		return 0x00;
}

uint8_t Sixty502::IND() {
	uint16_t lo = read(pc);
	pc++;
	uint16_t hi = read(pc);
	pc++;

	uint16_t ptr = (hi << 8) | lo;

	if (lo == 0x00FF)
		addr_abs = (read(ptr & 0xFF00) << 8) | read(ptr + 0);
	else
		addr_abs = (read(ptr + 1) << 8) | read(ptr + 0);

	return 0x00;
}

uint8_t Sixty502::INX() {
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read((uint16_t)(t + (uint16_t)x) & 0x00FF);
	uint16_t hi = read((uint16_t)(t + (uint16_t)x + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;

	return 0x00;
}

uint8_t Sixty502::CLD()
{
	return uint8_t();
}

uint8_t Sixty502::CLI()
{
	return uint8_t();
}

uint8_t Sixty502::CLV()
{
	return uint8_t();
}

uint8_t Sixty502::CMP()
{
	return uint8_t();
}

uint8_t Sixty502::CPX()
{
	return uint8_t();
}

uint8_t Sixty502::CPY()
{
	return uint8_t();
}

uint8_t Sixty502::DEC()
{
	return uint8_t();
}

uint8_t Sixty502::DEX()
{
	return uint8_t();
}

uint8_t Sixty502::DEY()
{
	return uint8_t();
}

uint8_t Sixty502::EOR()
{
	return uint8_t();
}

uint8_t Sixty502::INC()
{
	return uint8_t();
}

uint8_t Sixty502::INY() {
	uint16_t t = read(pc);
	pc++;

	uint16_t lo = read(t & 0x00FF);
	uint16_t hi = read((t + 1) & 0x00FF);

	addr_abs = (hi << 8) | lo;
	addr_abs += y;

	if ((addr_abs & 0xFF00) != (hi << 8))
		return 1;
	else
		return 0;
}

uint8_t Sixty502::JMP()
{
	return uint8_t();
}

uint8_t Sixty502::NOP() {
	return 0;
}

uint8_t Sixty502::LDA() {
	fetch();
	a = fetched;

	set_flag(Sixty502::Z, a == 0);
	set_flag(Sixty502::N, a & 0x80);

	return 0;
}

uint8_t Sixty502::ILL() {
	return 0;
}

uint8_t Sixty502::ADC()
{
	return uint8_t();
}

uint8_t Sixty502::AND()
{
	return uint8_t();
}

uint8_t Sixty502::ASL()
{
	return uint8_t();
}

uint8_t Sixty502::BCC()
{
	return uint8_t();
}

uint8_t Sixty502::BCS()
{
	return uint8_t();
}

uint8_t Sixty502::BEQ()
{
	return uint8_t();
}

uint8_t Sixty502::BIT()
{
	return uint8_t();
}

uint8_t Sixty502::BMI()
{
	return uint8_t();
}

uint8_t Sixty502::BNE()
{
	return uint8_t();
}

uint8_t Sixty502::BPL()
{
	return uint8_t();
}

uint8_t Sixty502::BRK()
{
	return uint8_t();
}

uint8_t Sixty502::BVC()
{
	return uint8_t();
}

uint8_t Sixty502::BVS()
{
	return uint8_t();
}

uint8_t Sixty502::CLC()
{
	return uint8_t();
}

uint8_t Sixty502::JSR()
{
	return uint8_t();
}

uint8_t Sixty502::LDX()
{
	return uint8_t();
}

uint8_t Sixty502::LDY()
{
	return uint8_t();
}

uint8_t Sixty502::LSR()
{
	return uint8_t();
}

uint8_t Sixty502::ORA()
{
	return uint8_t();
}

uint8_t Sixty502::PHA()
{
	return uint8_t();
}

uint8_t Sixty502::PHP()
{
	return uint8_t();
}

uint8_t Sixty502::PLA()
{
	return uint8_t();
}

uint8_t Sixty502::PLP()
{
	return uint8_t();
}

uint8_t Sixty502::ROL()
{
	return uint8_t();
}

uint8_t Sixty502::ROR()
{
	return uint8_t();
}

uint8_t Sixty502::RTI()
{
	return uint8_t();
}

uint8_t Sixty502::RTS()
{
	return uint8_t();
}

uint8_t Sixty502::SBC()
{
	return uint8_t();
}

uint8_t Sixty502::SEC()
{
	return uint8_t();
}

uint8_t Sixty502::SED()
{
	return uint8_t();
}

uint8_t Sixty502::SEI()
{
	return uint8_t();
}

uint8_t Sixty502::STA()
{
	return uint8_t();
}

uint8_t Sixty502::STX()
{
	return uint8_t();
}

uint8_t Sixty502::STY()
{
	return uint8_t();
}

uint8_t Sixty502::TAX()
{
	return uint8_t();
}

uint8_t Sixty502::TAY()
{
	return uint8_t();
}

uint8_t Sixty502::TSX()
{
	return uint8_t();
}

uint8_t Sixty502::TXA()
{
	return uint8_t();
}

uint8_t Sixty502::TXS()
{
	return uint8_t();
}

uint8_t Sixty502::TYA()
{
	return uint8_t();
}
