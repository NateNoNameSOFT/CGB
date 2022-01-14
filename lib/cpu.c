#include <cpu.h>
#include <bus.h>
#include <emu.h>

cpu_context ctx = {0};

void cpu_init() {
    ctx.regs.pc = 0x100;    //send to entry point
    ctx.regs.a = 0x01;      //set a to default value
}

static void fetch_instruction(){
    ctx.cur_opcode = bus_read(ctx.regs.pc++);               //set the current opcode to the current instruction from the rom
    ctx.cur_inst = instruction_by_opcode(ctx.cur_opcode);   //set the current instruction to the address on instructions[ctx.cur_opcode]
}

static void execute(){
    IN_PROC proc = inst_get_processor(ctx.cur_inst->type);

    if(!proc){
        NO_IMPL
    }

    proc(&ctx);
}

bool cpu_step() {
    
    if(!ctx.halted){
        u16 pc = ctx.regs.pc;   //Get program counter and set pc to the program counter

        fetch_instruction();
        fetch_data();

        printf("%04X: %7s (%02X %02X %02X) A: %02X B: %02X C: %02X\tBC: %X%X DE: %X%X HL: %X%X\n", 
            pc, inst_name(ctx.cur_inst->type), 
            ctx.cur_opcode, bus_read(pc+1), bus_read(pc+2),
            ctx.regs.a, ctx.regs.b, ctx.regs.c,
            ctx.regs.b, ctx.regs.c, ctx.regs.d, ctx.regs.e, ctx.regs.h, ctx.regs.l);

        if(ctx.cur_inst == NULL){                               //check if the current instruction is known    
            printf("Unknown instruction! | %X |\n", ctx.cur_opcode);
            exit(-7);
        }

        execute();
    }

    return true;
}

u8 cpu_get_ie_register(){
    return ctx.ie_register;
}

u8 cpu_set_ie_register(u8 n){
    ctx.ie_register = n;
}
