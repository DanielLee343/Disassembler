//created by Li Yuze on 09/20

#include <iostream>

using namespace std;

int main()
{
    int opcode[11], src1[11], src2[11], dest[11], func[11];
    signed short offset[11];
    int address[11];
    int init = 0x9A040;

    unsigned int intr[11] = {0x032BA020,
    0x8CE90014,
    0x12A90003,
    0x022DA822,
    0xADB30020,
    0x02697824,
    0xAE8FFFF4,
    0x018C6020,
    0x02A4A825,
    0x158FFFF7,
    0x8ECDFFF0};

    for(int i = 0; i<11; i++){
        address[i] = init;
        opcode[i] = (intr[i] & 0xFC000000) >> 26;
        src1[i] = (intr[i] & 0x03E00000) >> 21;
        src2[i] = (intr[i] & 0x001F0000) >> 16;
        if (opcode[i] == 0){//R type
            dest[i] = (intr[i] & 0x0000F800) >> 11;
            func[i] = (intr[i] & 0x0000003F);

            if(func[i] == 32){
                cout<<hex<<init<<dec<<" add $"<<dest[i]<<", $"<<src1[i]<<", $"<<src2[i]<<endl;
            }else if(func[i] == 34){
                cout<<hex<<init<<dec<<" sub $"<<dest[i]<<", $"<<src1[i]<<", $"<<src2[i]<<endl;
            }else if(func[i] == 36){
                cout<<hex<<init<<dec<<" and $"<<dest[i]<<", $"<<src1[i]<<", $"<<src2[i]<<endl;
            }else if(func[i] == 37){
                cout<<hex<<init<<dec<<" or $"<<dest[i]<<", $"<<src1[i]<<", $"<<src2[i]<<endl;
            }else if(func[i] == 42){
                cout<<hex<<init<<dec<<" slt $"<<dest[i]<<", $"<<src1[i]<<", $"<<src2[i]<<endl;
            }
        }else {//I type
            offset[i] = (intr[i] & 0x0000FFFF);
            if(opcode[i] == 35){
                cout<<hex<<init<<dec<<" lw $"<<src2[i]<<", "<<offset[i]<<"($"<<src1[i]<<")"<<endl;
            }else if(opcode[i] == 43){
                cout<<hex<<init<<dec<<" sw $"<<src2[i]<<", "<<offset[i]<<"($"<<src1[i]<<")"<<endl;
            }else if(opcode[i] == 4){//branch beq
                int targetadd1 = (offset[i]<<2)+4+init;
                cout<<hex<<init;
                cout<<dec<<" beq $"<<src1[i]<<", $"<<src2[i];
                cout<< "     "<<offset[i]<<"        ";
                cout<<", address "<<hex<<targetadd1<<endl;
            }else if (opcode[i] == 5){//branch bne
                int targetadd2 = (offset[i]<<2)+4+init;
                cout<<hex<<init;
                cout<<dec<<" bne $"<<src1[i]<<", $"<<src2[i];
                cout<<", address "<<hex<<targetadd2<<endl;
            }
        }//end else
        init+=4;//add 4 to current address each time
    }//end loop

    return 0;
}
