# RISC-V-Assembler
Use C++ language finish simple algorithm about RISC-V to machine code.

Refer to https://github.com/michaeljclark/rv8/blob/master/doc/pdf/riscv-instructions.pdf page1. 

## Input Rule
1. Use ":" after certain label
2. Use "," between two register
3. Use " " btween kind of instruction and register
## Kind of Error
1. Error : it don't have this instruction
2. Error : it don't have this label
3. Error : it don't have this register
## Input
```
    label:add x2,x21,x23
    beq x2,x21,label
    label:add x2,x21,x23
    jalr x1,x24,label
    sb x2,10(x21)
    lb x2,10(x21)
    addi x2,x21,23
    slli x2,x21,23
```

## Output
```
    00000001011110101000000100110011
    11111111010100010000111011100011
    00000001011110101000000100110011
    11111111111011000000000011100111
    00000000001010101000010100100011
    00000000101000010101010000000011
    00000001011110101000000100010011
    00000000001110101001000100010011
```
