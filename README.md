# Disassembler

This is one of the three projects in the course BU MET CS472, which requires us to obtain a solid understanding of disassembler in computer architecture and how it works.

### **Goal:**

The project is to write a partial disassembler for MIPS instructions. That is, the input will be the 32-bit machine instructions that a compiler or assembler produces.  The program then figures out what the original source instructions were that created those 32-bit machine instructions and outputs them.  The possible source instructions that you must be able to disassemble are: add, sub, and, or, slt, lw, sw, beq, bne. 

The specific machine instructions that will be disassembled (one after another in this exact order) are: 0x032BA020, 0x8CE90014, 0x12A90003, 0x022DA822, 0xADB30020, 0x02697824, 0xAE8FFFF4, 0x018C6020, 0x02A4A825, 0x158FFFF7, 0x8ECDFFF0 

That is, the above 32-bit instructions will be the input to the program.  (Eight hex digits are 32 binary bits.)   The program will then analyze a 32-bit instruction and figure out what the opcode, register operands and other fields in the instruction are and then print out the assembly language instruction that produced it.  Assume that the first instruction begins at address hex 9A040 and the rest follow right after that one.

For example, if the program determines that the first 32-bit machine instruction above is the instruction lw $10, 12 ($20) (it isn't, but if it were) then your output for that instruction would be: 

**9A040 lw $10, 12 ($20)** 

The "shamt" field in R-type instructions can always be assumed to be all zeroes.  



Steps:

Due to the simple structure of the project, I implemented it in just one C++ file which only contains the main method.

1. We set up arrays to store the opcode, src1, src2, dest, func and offset.
2. We initialize the first address, which is 0x9A040.
3. Put all instructions into an array.
4. Set up a 'for' loop, in which we  decode opcode, src1, src2, dest, func and offset for each instruction and we output each instructions in MIPS language every time it got decoded.
5. At the end of each loop, the address will add 4 (in hex).



Problems and Solutions:

1.P:

At first I found it quite hard to get the opcode, src1, etc., since I had no idea about 'Bitwise And'.

S: Bitwise And

Basically, 'Bitwise And' is an mathematical algorithms that is used to get particular bits within a number while ignoring other bits. Take a look at the following instruction: 

**opcode[i] = (intr[i] & 0xFC000000) >> 26;**

We implement '&' operation to each instruction and 0xFC000000 (which stands for six '1' in the most significant bits while '0' for others) and we will get the six most significant bits in each instruction while other bits will get into all zeros. Because 1 & 1 = 1 while 1 & 0 = 0. 

Then, we use '>>' operation to shift each instruction 26 bits in order to get the first six most significant bits. This is how we decode each instruction.



2.P: 

For branch instructions, we also need to calculate target address for each instruction, which I initially found quite complex.

S:

For simplicity, we use the following statement:

**int targetadd1 = (offset[i]<<2)+4+init;** 

When an offset is shifted two bits to the left, it is multiplied by 4 and when the result is added another 4, we will get the exact distance between the current address and the target address (could be positive or negative). The target address will be easy to find if we then add the distance to current address.



**Conclusion:**

This project is quite easy to implement for the very first project in this class. To get a full mark, it still requires a complete understanding of disassembler in computer architecture. What I really learned is 'Bitwise And' and the way to figure out target address for branch instruction, which I had misunderstood during class. The next two projects, which are about cache and pipeline, are much harder and complex in both logical understanding and skills of using data structure during coding.