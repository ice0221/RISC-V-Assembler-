# RISC-V-Assembler
Use C++ language finish simple algorithm about RISC-V to machine code.

## Input rule
1. 只能夠使用I,R,S type的指令
2. I type指令只能使用正數
3. 空格只會出現在指令與暫存器中間
4. 若全部指令都執行完成時，則會顯示machine code
## input
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

## output
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
