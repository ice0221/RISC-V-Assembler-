#include <stdlib.h> 
#include <math.h>
#include <iostream>
#include <string>
#include <bitset>
#include <cstdlib>
using namespace std;
//--------R type-------------
string dec2bit(int dec);
string add(string inst);
string sub(string inst);
string sll(string inst);
string slt(string inst);
string sltu(string inst);
string xor(string inst);
string srl(string inst);
string sra(string inst);
string or(string inst);
string and(string inst);
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


//-----------------------------
//Instrction Kind
//--------R type-------------
string ADD("add");
string SUB("sub");
string SLL("sll");
string SLT("slt");
string SLTU("sltu");
string XOR("xor");
string SRL("srl");
string SRA("sra");
string OR("or");
string AND("and");
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

void main()
{
	string inst;
	string code;
	string machine_code_reg;
	string machine_code;
	int i;//counter
	/*
	add x2,x21,x23
	add x2, x2, x23
	*/
	//INPUT
	cout<<"Input:\n";
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
	while (code != "\n")
	{
		i = 0;
		//GET inst
		while (1)
		{
			inst.append(1, code[i]);
			if (code[i + 1] == '\n')
			{
				break;
			}
			i = i + 1;
		}
		//DISTINGUISH inst
		i = 0;
		while (1)
		{
			kind.append(1, inst[i]);
			if (inst[i + 1] == ' ')
			{
				break;
			}
			i = i + 1;
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
		else if (kind == XOR)
		{
			machine_code_reg = xor (inst);
		}
		else if (kind == SRL)
		{
			machine_code_reg = srl(inst);
		}
		else if (kind == SRA)
		{
			machine_code_reg = sra(inst);
		}
		else if (kind == OR)
		{
			machine_code_reg = or (inst);
		}
		else if (kind == AND)
		{
			machine_code_reg = and (inst);
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
		machine_code= machine_code+ machine_code_reg;
		code.erase(0,inst.size()+1);
		kind.clear();
		inst.clear();
	}
	cout << "Machine_Code:\n";
	cout << machine_code;
	system("pause");
}
//--------R type-------------
string dec2bit(int dec)
{
	string bit,bit_reg;
	int i;
	while (dec!= 0)
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
	//inverse
	for (i = bit_reg.size()-1; i >= 0; i--)
	{
		bit.append(1, bit_reg[i]);
	}
	return bit;
}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start+1; i < rs2_char_start-1; i++)
	{
		rs1_char.append(1,inst[i]);
	}
	rs1_num=atoi(rs1_char.c_str());
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string xor(string inst)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string or(string inst)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
	}
	machine_code = func5 + func2 + rs2 + rs1 + func3 + rd + opcode;

	return machine_code;
}
string and(string inst)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	for (i = rs2_char_start + 1; i < end - 1; i++)
	{
		rs2_char.append(1, inst[i]);
	}
	rs2_num = atoi(rs2_char.c_str());
	rs2 = dec2bit(rs2_num);
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	simm_7 = simm_7.assign(simm, 0, 7);
	simm_5 = simm_5.assign(simm, 7, 5);
	for (i = rs1_char_start + 1; i < end - 1; i++)
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
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs1.size() != 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs2.size() != 5)
	{
		shift = 5 - rs2.size();
		while (shift > 0)
		{
			rs2.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs1.size() != 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs1.size() != 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs1.size() != 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs1.size() != 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs1.size() != 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rs1.size() != 5)
	{
		shift = 5 - rs1.size();
		while (shift > 0)
		{
			rs1.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	for (i = simm_char_start + 1; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() != 5)
	{
		shift = 5 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	for (i = simm_char_start + 1; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() != 5)
	{
		shift = 5 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
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
	if (rd.size() != 5)
	{
		shift = 5 - rd.size();
		while (shift > 0)
		{
			rd.insert(0, "0");
			shift = shift - 1;
		}
	}
	for (i = rs1_char_start + 1; i < simm_char_start - 1; i++)
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
	for (i = simm_char_start + 1; i < end - 1; i++)
	{
		simm_char.append(1, inst[i]);
	}
	simm_num = atoi(simm_char.c_str());
	simm = dec2bit(simm_num);
	if (simm.size() != 5)
	{
		shift = 5 - simm.size();
		while (shift > 0)
		{
			simm.insert(0, "0");
			shift = shift - 1;
		}
	}
	machine_code = func5 + func2 + simm + rs1 + func3 + rd + opcode; //前兩項需為string
																	 //machine_code = strcat_s("00000",32,"00");
	return machine_code;

}
/*
add x2,x21,x23
sb x2,10(x21)
lb x2,10(x21)
addi x2,x21,23
slli x2,x21,23
*/