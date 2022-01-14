#pragma once

#include <common.h>
#include <instructions.h>

typedef struct{
    u8 a;
    u8 f;
    u8 b;
    u8 c;
    u8 d;
    u8 e;
    u8 h;
    u8 l;
    u16 sp;     //Stack Pointer
    u16 pc;     //Program Counter/Pointer
} cpu_registers;

typedef struct{
    cpu_registers regs;

    //current fetch
    u16 fetched_data;
    u16 mem_dest;
    bool dest_is_mem;
    u8 cur_opcode;
    instruction *cur_inst;

    bool halted;
    bool stepping;

    bool int_master_enabled;
    u8 ie_register;
} cpu_context;

void cpu_init();
bool cpu_step();

void fetch_data();

typedef void (*IN_PROC)(cpu_context *);

IN_PROC inst_get_processor(in_type type);

#define CPU_FLAG_Z BIT(ctx->regs.f, 7)
#define CPU_FLAG_C BIT(ctx->regs.f, 4)

u16 cpu_read_reg(reg_type rt);
u16 cpu_set_reg(reg_type rt, u16 val);

u8 cpu_get_ie_register();
u8 cpu_set_ie_register(u8 n);