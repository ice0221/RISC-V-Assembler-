//---------------------------------------------
//---------------------------------------------
//README
//
//The version_1 is finished in 2021/04/24
//The version_1 is updated  in 2021/04/27
//---------------------------------------------
//
//The rule of input:
//1. Use ":" after certain label
//2. Use "," between two register
//3. Use " " btween kind of instruction and register
//
//---------------------------------------------
//
//The kind of Error:
//1. Error : it don't have this instruction
//2. Error : it don't have this label
//3. Error : it don't have this register
//
//---------------------------------------------
//
//Input,Output Example:
/*
Input
label:add x2,x21,x23
beq x2,x21,label
label:add x2,x21,x23
jalr x1,x24,label
sb x2,10(x21)
lb x2,10(x21)
addi x2,x21,23
slli x2,x21,23
*/
//
//Output
//000000010111101010000001001100111111111101010
//001000011101110001100000001011110101000000100
//110011111111111110110000000000111001110000000
//000101010100001010010001100000000101000010101
//010000000011000000010111101010000001000100110
//0000000001110101001000100010011
//
//---------------------------------------------
//---------------------------------------------
#include <math.h>
#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
using namespace std;
//---------------------------
//Delcare
//---------------------------
//string *label[100];
string label[100];
string labelname;
//string *addr = new string;
//int pc=0;
//int record_pc[100];
int flag = 0;
int l = 0;
int error_flag = 0;
//--------R type-------------
string dec2bit(int dec);
string add(string inst);
string sub(string inst);
string sll(string inst);
string slt(string inst);
string sltu(string inst);
string _xor(string inst);
string srl(string inst);
string sra(string inst);
string _or(string inst);
string _and(string inst);
//--------S type-------------
string sb(string inst);
string sh(string inst);
string sw(string inst);
//--------I type-------------
string lb(string inst);
string lh(string inst);
string lw(string inst);
string lbu(string inst);
string lhu(string inst);
string addi(string inst);
string slti(string inst);
string sltiu(string inst);
string xori(string inst);
string ori(string inst);
string andi(string inst);
//--------------------------
string slli(string inst);
string srli(string inst);
string srai(string inst);
//--------UJ type------------
string lui(string inst);
string auipc(string inst);
string jal(string inst);
string jalr(string inst);
string beq(string inst);
string bne(string inst);
string blt(string inst);
string bge(string inst);
string bltu(string inst);
string bgeu(string inst);

//---------------------------
//Instrction Kind
//--------R type-------------
string ADD("add");
string SUB("sub");
string SLL("sll");
string SLT("slt");
string SLTU("sltu");
string _XOR("xor");
string SRL("srl");
string SRA("sra");
string _OR("or");
string _AND("and");
//--------S type-------------
string SB("sb");
string SH("sh");
string SW("sw");
//--------I type-------------
string LB("lb");
string LH("lh");
string LW("lw");
string LBU("lbu");
string LHU("lhu");
string ADDI("addi");
string SLTI("slti");
string SLTIU("sltiu");
string XORI("xori");
string ORI("ori");
string ANDI("andi");
//--------------------------
string SLLI("slli");
string SRLI("srli");
string SRAI("srai");
string LUI("lui");
string AUIPC("auipc");
string JAL("jal");
string JALR("jalr");
string BEQ("beq");
string BNE("bne");
string BLT("blt");
string BGE("bge");
string BLTU("bltu");
string BGEU("bgeu");

void main()
{
	string inst;
	string code;
	string machine_code_reg;
	string machine_code;
	int i, j, k=0;//counter
	int next_inst=0;
	int reg_colon = 0;
	/*
	add x2,x21,x23
	add x2, x2, x23
	*/
	//INPUT
	//ptr = malloc(32 * sizeof(int));
	cout<<"RISC-V Input:\n";
	while(1)
	{
		getline(cin, inst);
		code.append(inst);
		code.append("\n");
		if (inst == "\0")
		{
			inst.clear();
			break;
		}
		inst.clear();
	}
	//ASEMBLER
	string kind;
	i = 0;
	while (k < code.size() - 1)
	{
		//GET inst
		i = k;
		while (1)
		{
			inst.append(1, code[i]);
			//record_pc[] = pc;
			//pc = pc + 4;
			if (code[i + 1] == '\n')
			{
				break;
			}
			i = i + 1;
		}
		//DISTINGUISH INST
		i = 0;
		flag = 0;
		while (1)
		{
			kind.append(1, inst[i]);
			if (inst[i + 1] == ' ')
			{
				break;
			}
			if (inst[i] == ':')
			{
				flag = 1;
				reg_colon = i;
			}
			i = i + 1;
		}
		//DISTINGUISH LABEL IN INST
		i = 0;
		while (1)
		{
			if (kind[i] == ':')
			{
				//addr= (string *)malloc(sizeof(int));
				for (j = 0; j < i; j++)
				{
					labelname.append(1, kind[j]);
				}
				label[l] = labelname;
				//*addr = labelname;
				//label[k] = addr;
				//addr = new string;
				//k = k + 1;
			}
			if (kind[i] == '\0')
			{
				labelname.clear();
				break;
			}
			i = i + 1;
		}
		if (flag == 1)
		{
			kind.erase(0, reg_colon + 1);
		}
		//--------R type-------------
		if (kind == ADD)
		{
			machine_code_reg = add(inst);
		}
		else if (kind == SUB)
		{
			machine_code_reg = sub(inst);
		}
		else if (kind == SLL)
		{
			machine_code_reg = sll(inst);
		}
		else if (kind == SLT)
		{
			machine_code_reg = slt(inst);
		}
		else if (kind == SLTU)
		{
			machine_code_reg = sltu(inst);
		}
		else if (kind == _XOR)
		{
			machine_code_reg = _xor (inst);
		}
		else if (kind == SRL)
		{
			machine_code_reg = srl(inst);
		}
		else if (kind == SRA)
		{
			machine_code_reg = sra(inst);
		}
		else if (kind == _OR)
		{
			machine_code_reg = _or (inst);
		}
		else if (kind == _AND)
		{
			machine_code_reg = _and (inst);
		}
		//--------S type-------------
		else if (kind == SB)
		{
			machine_code_reg = sb(inst);
		}
		else if (kind == SH)
		{
			machine_code_reg = sh(inst);
		}
		else if (kind == SW)
		{
			machine_code_reg = sw(inst);
		}
		//--------I type-------------
		else if (kind == LB)
		{
			machine_code_reg = lb(inst);
		}
		else if (kind == LH)
		{
			machine_code_reg = lh(inst);
		}
		else if (kind == LW)
		{
			machine_code_reg = lw(inst);
		}
		else if (kind == LBU)
		{
			machine_code_reg = lbu(inst);
		}
		else if (kind == LHU)
		{
			machine_code_reg = lhu(inst);
		}
		else if (kind == ADDI)
		{
			machine_code_reg = addi(inst);
		}
		else if (kind == SLTI)
		{
			machine_code_reg = slti(inst);
		}
		else if (kind == SLTIU)
		{
			machine_code_reg = sltiu(inst);
		}
		else if (kind == XORI)
		{
			machine_code_reg = xori(inst);
		}
		else if (kind == ANDI)
		{
			machine_code_reg = andi(inst);
		}
		//-----------------------------
		else if (kind == SLLI)
		{
			machine_code_reg = slli(inst);
		}
		else if (kind == SRLI)
		{
			machine_code_reg = srli(inst);
		}
		else if (kind == SRAI)
		{
			machine_code_reg = srai(inst);
		}
		//--------UJ type------------
		else if (kind == LUI)
		{
			machine_code_reg = lui(inst);
		}
		else if (kind == AUIPC)
		{
			machine_code_reg = auipc(inst);
		}
		else if (kind == JAL)
		{
			machine_code_reg = jal(inst);
		}
		else if (kind == JALR)
		{
			machine_code_reg = jalr(inst);
		}
		else if (kind == BEQ)
		{
			machine_code_reg = beq(inst);
		}
		else if (kind == BNE)
		{
			machine_code_reg = bne(inst);
		}
		else if (kind == BLT)
		{
			machine_code_reg = blt(inst);
		}
		else if (kind == BGE)
		{
			machine_code_reg = bge(inst);
		}
		else if (kind == BLTU)
		{
			machine_code_reg = bltu(inst);
		}
		else if (kind == BGEU)
		{
			machine_code_reg = bgeu(inst);
		}
		else
		{
			cout << "Error : it don't have this instruction";
			error_flag = error_flag + 1;
		}
		if (error_flag == 1)
		{
			machine_code = "";
			machine_code_reg = "";
		}
		l = l + 4;
		machine_code= machine_code+ machine_code_reg;
		machine_code_reg.clear();
		next_inst = next_inst+inst.size() + 1;
		k = next_inst;
		//code.erase(0,inst.size()+1);
		kind.clear();
		inst.clear();
	}
	cout << "\nMachine_Code:\n";
	cout << machine_code;
	system("pause");
}
//---------------------------
//Function
//---------------------------
string dec2bit(int dec)
{
	string bit,bit_reg;
	int i;
	int sign;
	if (dec >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	dec = abs(dec);
	if (sign == 0)
	{
		while (dec != 0)
		{
			if (dec % 2 == 0)
			{
				bit_reg.append("0");
			}
			else
			{
				bit_reg.append("1");
			}
			dec = dec / 2;
		}
	}
	else
	{
		while (dec != 0)
		{
			if (dec % 2 == 0)
			{
				bit_reg.append("1");
			}
			else
			{
				bit_reg.append("0");
			}
			dec = dec / 2;
		}
	}
	//inverse
	for (i = bit_reg.size()-1; i >= 0; i--)
	{
		bit.append(1, bit_reg[i]);
	}
	// add one
	i = bit.size()-1;
	if (sign == 1)
	{
		while (1)
		{
			if (bit[i] == '1')
			{
				bit.replace(i,1,"0");// == '0';
			}
			else
			{
				bit.replace(i, 1, "1");
				//bit[i] == '1';
				break;
			}
			i = i - 1;
		}
	}

	return bit;
}
//--------R type-------------
string add(string inst)
{
	
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char,rs2_char,rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "00000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "000";
	int i;//counter
	//ANALYSIS
	i = 0;
	int first_flag=0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i+1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i+1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i+1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i+1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start+1; i < rs2_char_start-1; i++)
	{
		rs1_char.append(1,inst[i]);
	}
	rs1_num=atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2+ rs2 + rs1 + func3 + rd+opcode; //前兩項需為string
	//machine_code = strcat_s("00000",32,"00");
	return machine_code;
	
}
string sub(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "01000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "000";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}	
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode; 

	return machine_code;
}
string sll(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "00000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "001";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string slt(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "00000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "010";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string sltu(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "00000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "011";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string _xor(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "00000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "100";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string srl(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "00000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "101";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string sra(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "01000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "101";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string _or(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "00000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "110";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string _and(string inst)
{
	string machine_code;//local
	string rs1, rs2, rd;
	string rs1_char, rs2_char, rd_char;
	int rs1_num, rs2_num, rd_num;
	string func5 = "00000";
	string opcode = "0110011";
	string func2 = "00";
	string func3 = "111";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				rs2_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
//--------S type-------------
string sb (string inst)
{
	string machine_code;//local
	string rs1, rs2, simm,simm_7,simm_5;
	string rs1_char, rs2_char, simm_char;
	int rs1_num, rs2_num, simm_num;
	string opcode = "0100011";
	string func3 = "000";
	int i;//counter
    //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs2_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '(')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ')')
		{
			end = i + 2;
			break;
		}
		i = i + 1;
	}
	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start ; i < rs1_char_start - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm_7 = simm_7.assign(simm, 0, 7);
	simm_5 = simm_5.assign(simm, 7, 5);
	for (i = rs1_char_start + 1; i < end - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code =  simm_7+ rs2 + rs1 + func3 + simm_5+ opcode;

	return machine_code;
}
string sh(string inst)
{
	string machine_code;//local
	string rs1, rs2, simm, simm_7, simm_5;
	string rs1_char, rs2_char, simm_char;
	int rs1_num, rs2_num, simm_num;
	string opcode = "0100011";
	string func3 = "001";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs2_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '(')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ')')
		{
			end = i + 2;
			break;
		}
		i = i + 1;
	}
	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < rs1_char_start - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm_7 = simm_7.assign(simm, 0, 7);
	simm_5 = simm_5.assign(simm, 7, 5);
	for (i = rs1_char_start + 1; i < end - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = simm_7 + rs2 + rs1 + func3 + simm_5 + opcode;

	return machine_code;
}
string sw(string inst)
{
	string machine_code;//local
	string rs1, rs2, simm, simm_7, simm_5;
	string rs1_char, rs2_char, simm_char;
	int rs1_num, rs2_num, simm_num;
	string opcode = "0100011";
	string func3 = "010";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rs2_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs2_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '(')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ')')
		{
			end = i + 2;
			break;
		}
		i = i + 1;
	}
	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < rs1_char_start - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	simm_7 = simm_7.assign(simm, 0, 7);
	simm_5 = simm_5.assign(simm, 7, 5);
	for (i = rs1_char_start + 1; i < end - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = simm_7 + rs2 + rs1 + func3 + simm_5 + opcode;

	return machine_code;
}
//--------I type-------------
string lb(string inst)
{
	string machine_code;//local
	string rd,rs1, simm;
	string rd_char, rs1_char,simm_char;
	int rd_num, rs1_num,simm_num;
	string opcode = "0000011";
	string func3 = "000";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int rs1_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '(')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ')')
		{
			end = i + 2;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < rs1_char_start - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < end - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = simm + rd + rs1 + func3  + opcode;

	return machine_code;
}
string lh(string inst)
{
	string machine_code;//local
	string rd, rs1, simm;
	string rd_char, rs1_char, simm_char;
	int rd_num, rs1_num, simm_num;
	string opcode = "0000011";
	string func3 = "001";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int rs1_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '(')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ')')
		{
			end = i + 2;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < rs1_char_start - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < end - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = simm + rd + rs1 + func3 + opcode;

	return machine_code;
}
string lw(string inst)
{
	string machine_code;//local
	string rd, rs1, simm;
	string rd_char, rs1_char, simm_char;
	int rd_num, rs1_num, simm_num;
	string opcode = "0000011";
	string func3 = "010";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int rs1_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '(')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ')')
		{
			end = i + 2;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < rs1_char_start - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < end - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = simm + rd + rs1 + func3 + opcode;

	return machine_code;
}
string lbu(string inst)
{
	string machine_code;//local
	string rd, rs1, simm;
	string rd_char, rs1_char, simm_char;
	int rd_num, rs1_num, simm_num;
	string opcode = "0000011";
	string func3 = "100";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int rs1_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '(')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ')')
		{
			end = i + 2;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < rs1_char_start - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < end - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = simm + rd + rs1 + func3 + opcode;

	return machine_code;
}
string lhu(string inst)
{
	string machine_code;//local
	string rd, rs1, simm;
	string rd_char, rs1_char, simm_char;
	int rd_num, rs1_num, simm_num;
	string opcode = "0000011";
	string func3 = "101";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int rs1_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '(')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ')')
		{
			end = i + 2;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < rs1_char_start - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < end - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = simm + rd + rs1 + func3 + opcode;

	return machine_code;
}
string addi(string inst)
{
	string machine_code;//local
	string rs1, rd, simm;
	string rs1_char, rd_char, simm_char;
	int rs1_num, rd_num, simm_num;
	string opcode = "0010011";
	string func3 = "000";
	int i;//counter
	//ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rd_char_start;
	int end;
	int shift;
	int first_flag = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	machine_code = simm + rs1 + func3 + rd + opcode;
	return machine_code;
}
string slti(string inst)
{
	string machine_code;//local
	string rs1, rd, simm;
	string rs1_char, rd_char, simm_char;
	int rs1_num, rd_num, simm_num;
	string opcode = "0010011";
	string func3 = "010";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rd_char_start;
	int end;
	int shift;
	int first_flag = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	machine_code = simm + rs1 + func3 + rd + opcode;
	return machine_code;
}
string sltiu(string inst)
{
	string machine_code;//local
	string rs1, rd, simm;
	string rs1_char, rd_char, simm_char;
	int rs1_num, rd_num, simm_num;
	string opcode = "0010011";
	string func3 = "011";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rd_char_start;
	int end;
	int shift;
	int first_flag = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	machine_code = simm + rs1 + func3 + rd + opcode;
	return machine_code;
}
string xori(string inst)
{
	string machine_code;//local
	string rs1, rd, simm;
	string rs1_char, rd_char, simm_char;
	int rs1_num, rd_num, simm_num;
	string opcode = "0010011";
	string func3 = "100";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rd_char_start;
	int end;
	int shift;
	int first_flag = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	machine_code = simm + rs1 + func3 + rd + opcode;
	return machine_code;
}
string ori(string inst)
{
	string machine_code;//local
	string rs1, rd, simm;
	string rs1_char, rd_char, simm_char;
	int rs1_num, rd_num, simm_num;
	string opcode = "0010011";
	string func3 = "110";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rd_char_start;
	int end;
	int shift;
	int first_flag = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	machine_code = simm + rs1 + func3 + rd + opcode;
	return machine_code;
}
string andi(string inst)
{
	string machine_code;//local
	string rs1, rd, simm;
	string rs1_char, rd_char, simm_char;
	int rs1_num, rd_num, simm_num;
	string opcode = "0010011";
	string func3 = "111";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs1_char_start;
	int rd_char_start;
	int end;
	int shift;
	int first_flag = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 12)
	{
		shift = 12 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	machine_code = simm + rs1 + func3 + rd + opcode;
	return machine_code;
}
string slli(string inst)
{

	string machine_code;//local
	string rs1, simm, rd;
	string rs1_char, simm_char, rd_char;
	int rs1_num, simm_num, rd_num;
	string func5 = "00000";
	string opcode = "0010011";
	string func2 = "00";
	string func3 = "001";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int simm_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start + 1; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() <= 5)
	{
		shift = 5 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + simm + rs1 + func3 + rd + opcode; //前兩項需為string
																	//machine_code = strcat_s("00000",32,"00");
	return machine_code;

}
string srli(string inst)
{

	string machine_code;//local
	string rs1, simm, rd;
	string rs1_char, simm_char, rd_char;
	int rs1_num, simm_num, rd_num;
	string func5 = "00000";
	string opcode = "0010011";
	string func2 = "00";
	string func3 = "101";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int simm_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start + 1; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() <= 5)
	{
		shift = 5 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + simm + rs1 + func3 + rd + opcode; //前兩項需為string
																	 //machine_code = strcat_s("00000",32,"00");
	return machine_code;

}
string srai(string inst)
{
	string machine_code;//local
	string rs1, simm, rd;
	string rs1_char, simm_char, rd_char;
	int rs1_num, simm_num, rd_num;
	string func5 = "01000";
	string opcode = "0010011";
	string func2 = "00";
	string func3 = "101";
	int i;//counter
		  //ANALYSIS
	i = 0;
	int first_flag = 0; //first record rs start
	int rd_char_start;
	int rs1_char_start;
	int simm_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < rs1_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = simm_char_start + 1; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() <= 5)
	{
		shift = 5 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	machine_code = func5 + func2 + simm + rs1 + func3 + rd + opcode; //前兩項需為string
																	 //machine_code = strcat_s("00000",32,"00");
	return machine_code;

}
//--------UJ type------------
string lui(string inst)
{
	string machine_code;//local
	string rd, simm;
	string  rd_char, simm_char;
	int rd_num, simm_num;
	string opcode = "0110111";

	int i;//counter
	//ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int end;
	int shift;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() < 20)
	{
		shift = 20 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	machine_code = simm +rd+ opcode;
	return machine_code;
}
string auipc(string inst)
{
	string machine_code;//local
	string rd, simm;
	string  rd_char, simm_char;
	int rd_num, simm_num;
	string opcode = "0010111";
	int offset;
	int addr_search;
	int addr_diff;
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int end;
	int shift;
	int sign = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for(i=0;i<100;i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == 100)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag + 1;
		return 0;
	}

	offset = addr_search - l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	simm=dec2bit(offset);
	simm.erase(simm.size() - 1, simm.size() - 1);
	if (simm.size() < 20)
	{
		shift = 20 - simm.size();
		if (sign == 0)
		{
			while (shift > 0)
			{
				simm.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	machine_code =  simm +rd+ opcode;
	return machine_code;
}
string jal(string inst)
{
	string machine_code;//local
	string rd, simm;
	string  rd_char, simm_char;
	int rd_num, simm_num;
	string simm_reg;
	string opcode = "1101111";
	int offset;
	int addr_search;
	int addr_diff;
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int end;
	int shift;
	int sign = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			simm_char_start = i + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}
	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for (i = 0; i<100; i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == 100)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag + 1;
		return 0;
	}
	offset = addr_search - l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	simm_reg = dec2bit(offset);
	simm_reg.erase(simm_reg.size() - 1, simm_reg.size() - 1);
	if (simm_reg.size() < 20)
	{
		shift = 20 - simm_reg.size();
		if (sign == 0)
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	simm= simm_reg;
	simm[0] = simm_reg[0];
	int j = 10;
	for (i = 1; i <=10 ; i++)
	{
		simm[i] = simm_reg[j];
		j = j + 1;
	}
	simm[11] = simm_reg[9];
	j = 0;
	for (i = 12; i <= 19; i++)
	{
		simm[i] = simm_reg[j];
		j = j + 1;
	}
	machine_code = simm + rd + opcode;
	return machine_code;
}
string jalr(string inst)
{
	string machine_code;//local
	string rd, simm,rs1;
	string  rd_char, simm_char, rs1_char;
	int rd_num, simm_num,rs1_num;
	string simm_reg;
	string opcode = "1100111";
	string func3 = "000";
	int offset;
	int addr_search;
	int addr_diff;
	int i;//counter
	//ANALYSIS
	i = 0;
	int simm_char_start;
	int rd_char_start;
	int rs1_char_start;
	int end;
	int shift;
	int first_flag = 0;
	int sign = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rd_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs1_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}

	for (i = rd_char_start + 1; i < simm_char_start - 1; i++)
	{
		rd_char.append(1, inst[i]);
	}
	rd_num = atoi(rd_char.c_str());
	rd = dec2bit(rd_num);
	if (rd.size() <= 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for (i = 0; i<100; i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == 100)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag + 1;
		return 0;
	}
	offset = addr_search - l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	simm_reg = dec2bit(offset);
	simm_reg.erase(simm_reg.size() - 1, simm_reg.size() - 1);
	if (simm_reg.size() < 12)
	{
		shift = 12 - simm_reg.size();
		if (sign == 0) {
			while (shift > 0)
			{
				simm_reg.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm = simm_reg;

	machine_code = simm + rs1 + func3 + rd + opcode;
	return machine_code;
}
string beq(string inst)
{
	string machine_code;//local
	string rs2, simm, rs1,simm_front,simm_back;
	string  rs2_char, simm_char, rs1_char;
	int rs2_num, simm_num, rs1_num;
	string simm_reg;
	string opcode = "1100011";
	string func3 = "000";
	int offset;
	int addr_search=-1;
	int addr_diff;
	int i;//counter
	int sign=0;
	//ANALYSIS
	i = 0;
	int simm_char_start;
	int rs2_char_start;
	int rs1_char_start;
	int end;
	int shift;
	int first_flag = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs2_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}

	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for (i = 0; i<100; i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == -1)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag + 1;
		return 0;
	}
	offset = addr_search-l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	simm_reg = dec2bit(offset);
	simm_reg.erase(simm_reg.size() - 1, simm_reg.size()-1);
	if (simm_reg.size() < 12)
	{
		shift = 12 - simm_reg.size();
		if (sign == 0) {
			while (shift > 0)
			{
				simm_reg.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm = simm_reg;
	//int j = 6;
	int j = 2;
	simm_front = "0000000";
	simm_front[0] = simm[0];
	for (i=1;i<=6;i++)
	{
		simm_front[i] = simm[j];
		j = j + 1;
	}
	simm_back = "00000";
	j = 8;
	for (i = 0; i <= 3; i++)
	{
		simm_back[i] = simm[j];
		j = j + 1;
	}
	simm_back[4] = simm[1];
	machine_code = simm_front + rs2 + rs1 + func3 + simm_back + opcode;

	return machine_code;
}
string bne(string inst)
{
	string machine_code;//local
	string rs2, simm, rs1, simm_front, simm_back;
	string  rs2_char, simm_char, rs1_char;
	int rs2_num, simm_num, rs1_num;
	string simm_reg;
	string opcode = "1100011";
	string func3 = "001";
	int offset;
	int addr_search = -1;
	int addr_diff;
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs2_char_start;
	int rs1_char_start;
	int end;
	int shift;
	int first_flag = 0;
	int sign = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs2_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}

	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() != 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}

	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for (i = 0; i<100; i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == -1)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag + 1;
		return 0;
	}
	offset = addr_search-l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	simm_reg = dec2bit(offset);
	simm_reg.erase(simm_reg.size() - 1, simm_reg.size() - 1);
	if (simm_reg.size() < 12)
	{
		shift = 12 - simm_reg.size();
		if (sign == 0)
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm = simm_reg;
	int j = 2;
	simm_front = "0000000";
	simm_front[0] = simm[0];
	for (i = 1; i <= 6; i++)
	{
		simm_front[i] = simm[j];
		j = j + 1;
	}
	simm_back = "00000";
	j = 8;
	for (i = 0; i <= 3; i++)
	{
		simm_back[i] = simm[j];
		j = j + 1;
	}
	simm_back[4] = simm[1];
	machine_code = simm_front + rs2 + rs1 + func3 + simm_back + opcode;

	return machine_code;
}
string blt(string inst)
{
	string machine_code;//local
	string rs2, simm, rs1, simm_front, simm_back;
	string  rs2_char, simm_char, rs1_char;
	int rs2_num, simm_num, rs1_num;
	string simm_reg;
	string opcode = "1100011";
	string func3 = "100";
	int offset;
	int addr_search = -1;
	int addr_diff;
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs2_char_start;
	int rs1_char_start;
	int end;
	int shift;
	int first_flag = 0;
	int sign = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs2_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}

	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for (i = 0; i<100; i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == -1)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag + 1;
		return 0;
	}
	offset = addr_search - l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	while (shift > 0)
	{
		simm_reg.insert(0, "0");
		shift = shift - 1;
	}
	simm_reg = dec2bit(offset);
	simm_reg.erase(simm_reg.size() - 1, simm_reg.size() - 1);
	if (simm_reg.size() < 12)
	{
		shift = 12 - simm_reg.size();
		if (sign == 0)
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm = simm_reg;
	int j = 2;
	simm_front = "0000000";
	simm_front[0] = simm[0];
	for (i = 1; i <= 6; i++)
	{
		simm_front[i] = simm[j];
		j = j + 1;
	}
	simm_back = "00000";
	j = 8;
	for (i = 0; i <= 3; i++)
	{
		simm_back[i] = simm[j];
		j = j + 1;
	}
	simm_back[4] = simm[1];
	machine_code = simm_front + rs2 + rs1 + func3 + simm_back + opcode;

	return machine_code;
}
string bge(string inst)
{
	string machine_code;//local
	string rs2, simm, rs1, simm_front, simm_back;
	string  rs2_char, simm_char, rs1_char;
	int rs2_num, simm_num, rs1_num;
	string simm_reg;
	string opcode = "1100011";
	string func3 = "101";
	int offset;
	int addr_search = -1;
	int addr_diff;
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs2_char_start;
	int rs1_char_start;
	int end;
	int shift;
	int first_flag = 0;
	int sign = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs2_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}

	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for (i = 0; i<100; i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == -1)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag + 1;
		return 0;
	}
	offset = addr_search - l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	simm_reg = dec2bit(offset);
	simm_reg.erase(simm_reg.size() - 1, simm_reg.size() - 1);
	if (simm_reg.size() < 12)
	{
		shift = 12 - simm_reg.size();
		if (sign == 0) {
			while (shift > 0)
			{
				simm_reg.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm = simm_reg;
	int j = 2;
	simm_front = "0000000";
	simm_front[0] = simm[0];
	for (i = 1; i <= 6; i++)
	{
		simm_front[i] = simm[j];
		j = j + 1;
	}
	simm_back = "00000";
	j = 8;
	for (i = 0; i <= 3; i++)
	{
		simm_back[i] = simm[j];
		j = j + 1;
	}
	simm_back[4] = simm[1];
	machine_code = simm_front + rs2 + rs1 + func3 + simm_back + opcode;

	return machine_code;
}
string bltu(string inst)
{
	string machine_code;//local
	string rs2, simm, rs1, simm_front, simm_back;
	string  rs2_char, simm_char, rs1_char;
	int rs2_num, simm_num, rs1_num;
	string simm_reg;
	string opcode = "1100011";
	string func3 = "110";
	int offset;
	int addr_search = -1;
	int addr_diff;
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs2_char_start;
	int rs1_char_start;
	int end;
	int shift;
	int first_flag = 0;
	int sign = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs2_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}

	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for (i = 0; i<100; i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == -1)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag+1;
		return 0;
	}
	offset = addr_search - l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	simm_reg = dec2bit(offset);
	simm_reg.erase(simm_reg.size() - 1, simm_reg.size() - 1);
	if (simm_reg.size() < 12)
	{
		shift = 12 - simm_reg.size();
		if (sign == 0)
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm = simm_reg;
	int j = 2;
	simm_front = "0000000";
	simm_front[0] = simm[0];
	for (i = 1; i <= 6; i++)
	{
		simm_front[i] = simm[j];
		j = j + 1;
	}
	simm_back = "00000";
	j = 8;
	for (i = 0; i <= 3; i++)
	{
		simm_back[i] = simm[j];
		j = j + 1;
	}
	simm_back[4] = simm[1];
	machine_code = simm_front + rs2 + rs1 + func3 + simm_back + opcode;

	return machine_code;
}
string bgeu(string inst)
{
	string machine_code;//local
	string rs2, simm, rs1, simm_front, simm_back;
	string  rs2_char, simm_char, rs1_char;
	int rs2_num, simm_num, rs1_num;
	string simm_reg;
	string opcode = "1100011";
	string func3 = "111";
	int offset;
	int addr_search = -1;
	int addr_diff;
	int i;//counter
		  //ANALYSIS
	i = 0;
	int simm_char_start;
	int rs2_char_start;
	int rs1_char_start;
	int end;
	int shift;
	int first_flag = 0;
	int sign = 0;
	while (1)
	{
		if (inst[i] == ' ')
		{
			rs1_char_start = i + 1;
		}
		if (inst[i] == ',')
		{
			if (first_flag == 0)
			{
				rs2_char_start = i + 1;
			}
			else if (first_flag == 1)
			{
				simm_char_start = i + 1;
			}
			first_flag = first_flag + 1;
		}
		if (inst[i] == '\0')
		{
			end = i + 1;
			break;
		}
		i = i + 1;
	}

	for (i = rs1_char_start + 1; i < rs2_char_start - 1; i++)
	{
		rs1_char.append(1, inst[i]);
	}
	rs1_num = atoi(rs1_char.c_str());
	rs1 = dec2bit(rs1_num);
	if (rs1.size() <= 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = rs2_char_start + 1; i < simm_char_start - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() <= 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}

	for (i = simm_char_start; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	//simm_num = atoi(simm_char.c_str());
	for (i = 0; i<100; i++)
	{
		if (simm_char == label[i])
		{
			addr_search = i;
		}
	}
	if (addr_search == -1)
	{
		i = 0;
		cout << "Error : it don't have this label";
		error_flag = error_flag + 1;
		return 0;
	}
	offset = addr_search - l;
	if (offset >= 0)
	{
		sign = 0;
	}
	else
	{
		sign = 1;
	}
	simm_reg = dec2bit(offset);
	simm_reg.erase(simm_reg.size() - 1, simm_reg.size() - 1);
	if (simm_reg.size() < 12)
	{
		shift = 12 - simm_reg.size();
		if (sign == 0)
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "0");
				shift = shift - 1;
			}
		}
		else
		{
			while (shift > 0)
			{
				simm_reg.insert(0, "1");
				shift = shift - 1;
			}
		}
	}
	else
	{
		cout << "Error: it don't have this register";
		error_flag = error_flag + 1;
	}
	simm = simm_reg;
	int j = 2;
	simm_front = "0000000";
	simm_front[0] = simm[0];
	for (i = 1; i <= 6; i++)
	{
		simm_front[i] = simm[j];
		j = j + 1;
	}
	simm_back = "00000";
	j = 8;
	for (i = 0; i <= 3; i++)
	{
		simm_back[i] = simm[j];
		j = j + 1;
	}
	simm_back[4] = simm[1];
	machine_code = simm_front + rs2 + rs1 + func3 + simm_back + opcode;

	return machine_code;
}

