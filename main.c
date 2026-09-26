#include <stdio.h>
#include <stdint.h>

#define FLAG_Z (1 << 0)
#define FLAG_C (1 << 1)

typedef struct {
    uint8_t regA;     
    uint8_t regB;    
    uint8_t status;   
} SimpleCPU;

void cpu_reset(SimpleCPU *cpu) {
    cpu->regA = 0;
    cpu->regB = 0;
    cpu->status = 0;
}

void alu_add(SimpleCPU *cpu) {
    uint16_t result = (uint16_t)cpu->regA + (uint16_t)cpu->regB;
    cpu->regA = (uint8_t)(result & 0xFF);

    if (result > 0xFF) {
        cpu->status |= FLAG_C;   
    } else {
        cpu->status &= ~FLAG_C;  
    }

    if (cpu->regA == 0) {
        cpu->status |= FLAG_Z; 
    } else {
        cpu->status &= ~FLAG_Z; 
    }
}

void alu_and(SimpleCPU *cpu) {
    cpu->regA = cpu->regA & cpu->regB;
    cpu->status &= ~FLAG_C; 

    if (cpu->regA == 0) {
        cpu->status |= FLAG_Z;
    } else {
        cpu->status &= ~FLAG_Z;
    }
}

void print_cpu_state(const char *test_name, SimpleCPU *cpu) {
    printf("=== %s ===\n", test_name);
    printf("RegA   : 0x%02X (%d)\n", cpu->regA, cpu->regA);
    printf("RegB   : 0x%02X (%d)\n", cpu->regB, cpu->regB);
    printf("Status : 0x%02X [Carry: %d | Zero: %d]\n\n",
           cpu->status,
           (cpu->status & FLAG_C) ? 1 : 0,
           (cpu->status & FLAG_Z) ? 1 : 0);
}

int main() {
    SimpleCPU cpu;
    cpu_reset(&cpu);

    cpu.regA = 15;
    cpu.regB = 10;
    alu_add(&cpu);
    print_cpu_state("Test 1: ADD (15 + 10)", &cpu);

    cpu.regA = 200;
    cpu.regB = 100;
    alu_add(&cpu);
    print_cpu_state("Test 2: ADD Overflow (200 + 100)", &cpu);

    cpu.regA = 0b10100000;
    cpu.regB = 0b01010000;
    alu_and(&cpu);
    print_cpu_state("Test 3: AND Zero Result", &cpu);

    return 0;
}