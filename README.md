# RISC-V-Assembler
Use C++ language finish simple algorithm about RISC-V to machine code.

## Input rule
1. 只能夠使用I,R,S type的指令
2. I type指令只能使用正數
3. 空格只會出現在指令與暫存器中間
4. 若全部指令都執行完成時，則會顯示machine code
## input
```
    add x2,x2,x23
    addi x24,x24,2
    sw x27,0(x10)
```

## output
```
000000010111000100000001001100110000000000101100000011000001001100000001101101010010000000100011
```
