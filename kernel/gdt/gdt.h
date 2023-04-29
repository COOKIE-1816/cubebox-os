#pragma once

#define SEG_DESCTYPE(x)  ((x) << 0x04)
#define SEG_PRES(x)      ((x) << 0x07)
#define SEG_SAVL(x)      ((x) << 0x0C)
#define SEG_LONG(x)      ((x) << 0x0D)
#define SEG_SIZE(x)      ((x) << 0x0E)
#define SEG_GRAN(x)      ((x) << 0x0F
#define SEG_PRIV(x)     (((x) &  0x03) << 0x05)

#define SEG_DATA_RD        0x00
#define SEG_DATA_RDA       0x01
#define SEG_DATA_RDWR      0x02
#define SEG_DATA_RDWRA     0x03
#define SEG_DATA_RDEXPD    0x04
#define SEG_DATA_RDEXPDA   0x05
#define SEG_DATA_RDWREXPD  0x06
#define SEG_DATA_RDWREXPDA 0x07
#define SEG_CODE_EX        0x08
#define SEG_CODE_EXA       0x09
#define SEG_CODE_EXRD      0x0A
#define SEG_CODE_EXRDA     0x0B
#define SEG_CODE_EXC       0x0C
#define SEG_CODE_EXCA      0x0D
#define SEG_CODE_EXRDC     0x0E
#define SEG_CODE_EXRDCA    0x0F

#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_CODE_EXRD
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_DATA_RDWR
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_CODE_EXRD
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_DATA_RDWR
#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_CODE_EXRD
#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(0) | SEG_DATA_RDWR
#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_CODE_EXRD
#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | SEG_LONG(0) | SEG_SIZE(1) | SEG_GRAN(1) | SEG_PRIV(3) | SEG_DATA_RDWR

/*struct gdt_entry {
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));*/

struct gdt_entry {
	unsigned int limit_low = 16;
	unsigned int base_low = 24;
	unsigned int accessed = 1;
	unsigned int read_write = 1;
	unsigned int conforming_expand_down = 1;
	unsigned int code = 1;
	unsigned int code_data_segment = 1;
	unsigned int DPL = 2;
	unsigned int present = 1;
	unsigned int limit_high = 4;
	unsigned int available = 1;
	unsigned int long_mode = 1;
	unsigned int big = 1;
	unsigned int gran = 1;
	unsigned int base_high = 8;
} __packed;

void gdt_encode(uint8_t* target, struct GlobalDescriptorTable source);
void gdt_createDescriptor(uint32_t base, uint32_t limit, uint16_t flag);
void gdt_init(void);