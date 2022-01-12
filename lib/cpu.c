#include <cpu.h>
#include <bus.h>
#include <emu.h>

cpu_context ctx = {0};

void cpu_init() {
    ctx.regs.pc = 0x100;    //send to entry point
}

static void fetch_instruction(){
    ctx.cur_opcode = bus_read(ctx.regs.pc++);               //set the current opcode to the current instruction from the rom
    ctx.cur_inst = instruction_by_opcode(ctx.cur_opcode);   //set the current instruction to the address on instructions[ctx.cur_opcode]

    if(ctx.cur_inst == NULL){                               //check if the current instruction is known    
        printf("Unknown Instruction! |%X|\n", ctx.cur_opcode);
        exit(-7);
    }
}

static void fetch_data(){
    ctx.mem_dest = 0;
    ctx.dest_is_mem = false;

    switch(ctx.cur_inst->mode){
        case AM_IMP: return;

        case AM_R:
            ctx.fetched_data = cpu_read_reg(ctx.cur_inst->reg_1);   //Set fetched_data to a register
            return;
        
        case AM_R_D8:
            ctx.fetched_data = bus_read(ctx.regs.pc);               //Set fetched_data to the address 'ctx.regs.pc' of the rom
            emu_cycles(1);                                             
            ctx.regs.pc++;                                          //Increment program counter by 1 since it took 1 cycle
            return;

        case AM_D16: {
            u16 lo = bus_read(ctx.regs.pc);
            emu_cycles(1);

            u16 hi = bus_read(ctx.regs.pc + 1);
            emu_cycles(1);

            ctx.fetched_data = lo | (hi << 8);

            ctx.regs.pc += 2;                                       //Increment program counter by 2 since it took 2 cycles

            return;
        }

        default:
            printf("Unknown Addressing Mode! |%d|\n", ctx.cur_inst->mode);
            exit(-7);
    }
}

static void execute(){
    printf("\tNot Executing Yet...\n");
}

bool cpu_step() {
    
    if(!ctx.halted){
        u16 pc = ctx.regs.pc;   //Get program counter and set pc to the program counter

        fetch_instruction();
        fetch_data();

        printf("Executing Intruction: %02X\tPC: %04x\n", ctx.cur_opcode, pc);
        
        execute();
    }

    return true;
}
