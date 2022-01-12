#include <bus.h>

// 0x0000 - 0x3FFF : ROM Bank 0
// 0x4000 - 0x7FFF : ROM Bank 1 - Switchable
// 0x8000 - 0x97FF : CHR RAM
// 0x9800 - 0x9BFF : BG Map 1
// 0x9C00 - 0x9FFF : BG Map 2
// 0xA000 - 0xBFFF : Cartridge RAM
// 0xC000 - 0xCFFF : RAM Bank 0
// 0xD000 - 0xDFFF : RAM Bank 1-7 - switchable - Color only
// 0xE000 - 0xFDFF : Reserved - Echo RAM
// 0xFE00 - 0xFE9F : Object Attribute Memory
// 0xFEA0 - 0xFEFF : Reserved - Unusable
// 0xFF00 - 0xFF7F : I/O Registers
// 0xFF80 - 0xFFFE : Zero Page

// 0x0000 - 0x3FFF : 16 KiB ROM bank 00	From cartridge, usually a fixed bank
// 0x4000 - 0x7FFF : 16 KiB ROM Bank 01~NN	From cartridge, switchable bank via mapper (if any)
// 0x8000 - 0x9FFF : 8 KiB Video RAM (VRAM)	In CGB mode, switchable bank 0/1
// 0xA000 - 0xBFFF : 8 KiB External RAM	From cartridge, switchable bank if any
// 0xC000 - 0xCFFF : 4 KiB Work RAM (WRAM)	
// 0xD000 - 0xDFFF : 4 KiB Work RAM (WRAM)	In CGB mode, switchable bank 1~7
// 0xE000 - 0xFDFF : Mirror of C000~DDFF (ECHO RAM)	Nintendo says use of this area is prohibited.
// 0xFE00 - 0xFE9F : Sprite attribute table (OAM)	
// 0xFEA0 - 0xFEFF : Not Usable	Nintendo says use of this area is prohibited
// 0xFF00 - 0xFF7F : I/O Registers	
// 0xFF80 - 0xFFFE : High RAM (HRAM)	
// 0xFFFF - 0xFFFF : Interrupt Enable register (IE)	

u8 bus_read(u16 address){
    if(address < 0x8000){
        //ROM Data
        return cart_read(address);
    }

    NO_IMPL
}

void bus_write(u16 address, u8 value){
    if(address < 0x8000){
        //ROM Data
        cart_write(address, value);
    }

    NO_IMPL
}