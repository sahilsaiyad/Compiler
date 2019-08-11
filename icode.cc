Instruction_Descriptor::Instruction_Descriptor (Tgt_Op op, string nam, string mnn, string ics, Icode_Format icf, Assembly_Format af){
	inst_op = op;
	mnemonic = mnn;
	ic_symbol = ics;       /* symbol for printing in intermediate code */
	name = nam;
	ic_format = icf; /* format for printing in intemediate code */
	assem_format = af;
}

Instruction_Descriptor::Instruction_Descriptor (){}

Tgt_Op Instruction_Descriptor::get_op(){
	return inst_op;
}

string Instruction_Descriptor::get_name(){
	return name;
}

string Instruction_Descriptor::get_mnemonic(){
	return mnemonic;
}

string Instruction_Descriptor::get_ic_symbol(){
	return ic_symbol;
}

Icode_Format Instruction_Descriptor::get_ic_format(){
	return ic_format;
}

Assembly_Format Instruction_Descriptor::get_assembly_format(){
	return assem_format;
}

void Instruction_Descriptor::print_instruction_descriptor(ostream & file_buffer){

}

Register_Descriptor* Ics_Opd::get_reg(){}

Mem_Addr_Opd::Mem_Addr_Opd(Symbol_Table_Entry & se){
	symbol_entry = &se;
}

Mem_Addr_Opd & Mem_Addr_Opd::operator = (const Mem_Addr_Opd & rhs){
	symbol_entry = rhs.symbol_entry;
	return *this;
}

void Mem_Addr_Opd::print_ics_opd(ostream & file_buffer){
	file_buffer<<symbol_entry->get_variable_name();
}

void Mem_Addr_Opd::print_asm_opd(ostream & file_buffer){
	Table_Scope symbol_scope = symbol_entry->get_symbol_scope();
	if (symbol_scope == local)
	{
		int offset = symbol_entry->get_start_offset();
		file_buffer << offset << "($fp)";
	}
	else
		file_buffer << symbol_entry->get_variable_name();
}

Register_Addr_Opd::Register_Addr_Opd(Register_Descriptor * rd){
	register_description = rd;
}

Register_Descriptor * Register_Addr_Opd::get_reg(){
	return register_description;
}

Register_Addr_Opd& Register_Addr_Opd::operator = (const Register_Addr_Opd& rhs){
	register_description = rhs.register_description;
	return *this;
}

void Register_Addr_Opd::print_ics_opd(ostream & file_buffer){
	file_buffer << register_description->get_name();
}

void Register_Addr_Opd::print_asm_opd(ostream & file_buffer){
	file_buffer << "$" << register_description->get_name();
}

template<>
Const_Opd<int>::Const_Opd (int n){
	num = n;
}

template<>
Const_Opd<double>::Const_Opd (double n){
	num = n;
}

template<>
Const_Opd<int> & Const_Opd<int>::operator = (const Const_Opd<int> &rhs)
{
	num = rhs.num;
	return *this;
}

template<>
Const_Opd<float> & Const_Opd<float>::operator = (const Const_Opd<float> &rhs)
{
	num = rhs.num;
	return *this;
}

template<>
void Const_Opd<int>::print_ics_opd(ostream & file_buffer){
	file_buffer << num;
}

template<>
void Const_Opd<double>::print_ics_opd(ostream & file_buffer){
	file_buffer << num;
}

template<>
void Const_Opd<int>::print_asm_opd(ostream & file_buffer){
	file_buffer << num;
}

template<>
void Const_Opd<double>::print_asm_opd(ostream & file_buffer){
	file_buffer << num;
}

Instruction_Descriptor & Icode_Stmt::get_op(){
	return op_desc;
}

Ics_Opd * Icode_Stmt::get_opd1(){}
Ics_Opd * Icode_Stmt::get_opd2(){}
Ics_Opd * Icode_Stmt::get_result(){}
void Icode_Stmt::set_opd1(Ics_Opd * io){}
void Icode_Stmt::set_opd2(Ics_Opd * io){}
void Icode_Stmt::set_result(Ics_Opd * io){}

Print_IC_Stmt::Print_IC_Stmt(){
	op_desc = *(machine_desc_object.spim_instruction_table[print]);
}
Print_IC_Stmt::~Print_IC_Stmt(){}

void Print_IC_Stmt::print_icode(ostream & file_buffer){
	file_buffer<<"\t"<<op_desc.get_name()<<endl;
}

void Print_IC_Stmt::print_assembly(ostream & file_buffer){
	file_buffer<<"\t"<<op_desc.get_mnemonic()<<endl;
}

Move_IC_Stmt::Move_IC_Stmt(Tgt_Op inst_op, Ics_Opd * o, Ics_Opd * r){
	opd1 = o;
	result = r;
	op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
}

Instruction_Descriptor & Move_IC_Stmt::get_inst_op_of_ics(){
	return op_desc;
}

Ics_Opd * Move_IC_Stmt::get_opd1(){
	return opd1;
}

void Move_IC_Stmt::set_opd1(Ics_Opd * io){
	opd1 = io;
}

Ics_Opd * Move_IC_Stmt::get_result(){
	return result;
}

void Move_IC_Stmt::set_result(Ics_Opd * io){
	result = io;
}

Move_IC_Stmt& Move_IC_Stmt::operator = (const Move_IC_Stmt & rhs)
{
	op_desc = rhs.op_desc;
	opd1 = rhs.opd1;
	result = rhs.result; 
	return *this;
}


void Move_IC_Stmt::print_icode(ostream & file_buffer){
	string opname = op_desc.get_name();
	Icode_Format icf = op_desc.get_ic_format();
	if (icf == i_r_op_o1)
	{
		file_buffer << "\t" << opname << ":    \t";
		result->print_ics_opd(file_buffer);
		file_buffer << " <- ";
		opd1->print_ics_opd(file_buffer);
		file_buffer << "\n";
	}
	else
	{
		printf("CS316 error\n");
		exit(0);
	}
}

void Move_IC_Stmt::print_assembly(ostream & file_buffer){
	string opmne = op_desc.get_mnemonic();
	Assembly_Format asf = op_desc.get_assembly_format();
	if (asf == a_op_r_o1)
	{
		file_buffer << "\t" << opmne << " ";
		result->print_asm_opd(file_buffer);
		file_buffer << ", ";
		opd1->print_asm_opd(file_buffer);
		file_buffer << "\n";
	}
	else if (asf == a_op_o1_r)
	{
		file_buffer << "\t" << opmne << " ";
		opd1->print_asm_opd(file_buffer);
		file_buffer << ", ";
		result->print_asm_opd(file_buffer);
		file_buffer << "\n";
	}
	else
	{
		printf("CS316 error\n");
		exit(0);
	}
}

Compute_IC_Stmt::Compute_IC_Stmt(Tgt_Op inst_op, Ics_Opd * o1, Ics_Opd * o2, Ics_Opd * r){
	opd1 = o1;
	opd2 = o2;
	result = r;
	op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
}

Instruction_Descriptor & Compute_IC_Stmt::get_inst_op_of_ics(){
	return op_desc;
}

Ics_Opd * Compute_IC_Stmt::get_opd1(){
	return opd1;
}

void Compute_IC_Stmt::set_opd1(Ics_Opd * io){
	opd1 = io;
}

Ics_Opd * Compute_IC_Stmt::get_opd2(){
	return opd2;
}

void Compute_IC_Stmt::set_opd2(Ics_Opd * io){
	opd2 = io;
}

Ics_Opd * Compute_IC_Stmt::get_result(){
	return result;
}

void Compute_IC_Stmt::set_result(Ics_Opd * io){
	result = io;
}

void Compute_IC_Stmt::print_icode(ostream & file_buffer){
	string opname = op_desc.get_name();
	Icode_Format icf = op_desc.get_ic_format();
	if (icf == i_r_o1_op_o2)
	{
		file_buffer << "\t" << opname << ":    \t";
		result->print_ics_opd(file_buffer);
		file_buffer << " <- ";
		opd1->print_ics_opd(file_buffer);
		file_buffer << " , ";
		opd2->print_ics_opd(file_buffer);
		file_buffer << "\n";
	}
	else if (icf == i_r_op_o1)
	{
		file_buffer << "\t" << opname << ":    \t";
		result->print_ics_opd(file_buffer);
		file_buffer << " <- ";
		opd1->print_ics_opd(file_buffer);
		file_buffer << "\n";
	}
	else
	{
		printf("CS316 error\n");
		exit(0);
	}
}

void Compute_IC_Stmt::print_assembly(ostream & file_buffer){
	string opmne = op_desc.get_mnemonic();
	Assembly_Format asf = op_desc.get_assembly_format();
	if (asf == a_op_r_o1_o2)
	{
		file_buffer << "\t" << opmne << " ";
		result->print_asm_opd(file_buffer);
		file_buffer << ", ";
		opd1->print_asm_opd(file_buffer);
		file_buffer << ", ";
		opd2->print_asm_opd(file_buffer);
		file_buffer << "\n";
	}
	else if (asf == a_op_o1_o2_r)
	{
		file_buffer << "\t" << opmne << " ";
		opd1->print_asm_opd(file_buffer);
		file_buffer << ", ";
		opd2->print_asm_opd(file_buffer);
		file_buffer << ", ";
		result->print_asm_opd(file_buffer);
		file_buffer << "\n";
	}
	else if (asf == a_op_r_o1)
	{
		file_buffer << "\t" << opmne << " ";
		result->print_asm_opd(file_buffer);
		file_buffer << ", ";
		opd1->print_asm_opd(file_buffer);
		file_buffer << "\n";
	}
	else if (asf == a_op_o1_r)
	{
		file_buffer << "\t" << opmne << " ";
		opd1->print_asm_opd(file_buffer);
		file_buffer << ", ";
		result->print_asm_opd(file_buffer);
		file_buffer << "\n";
	}
	else
	{
		printf("CS316 error\n");
		exit(0);
	}
}

Control_Flow_IC_Stmt::Control_Flow_IC_Stmt(Tgt_Op inst_op, Ics_Opd * o1, string l){
	opd1 = o1;
	label = l;
	op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
}

Instruction_Descriptor & Control_Flow_IC_Stmt::get_inst_op_of_ics(){
	return op_desc;
}

Ics_Opd * Control_Flow_IC_Stmt::get_opd1(){
	return opd1;
}

void Control_Flow_IC_Stmt::set_opd1(Ics_Opd * io){
	opd1 = io;
}

string Control_Flow_IC_Stmt::get_label(){
	return label;
}

void Control_Flow_IC_Stmt::set_label(string l){
	label = l;
}

Control_Flow_IC_Stmt& Control_Flow_IC_Stmt::operator=(const Control_Flow_IC_Stmt& rhs)
{
	opd1 = rhs.opd1;
	label = rhs.label;
	op_desc = rhs.op_desc;
	return *this;
}

void Control_Flow_IC_Stmt::print_icode(ostream & file_buffer){
	string op = op_desc.get_name();
	Icode_Format icf = op_desc.get_ic_format();
	if (icf == i_op_o1_o2_st)
	{
		file_buffer << "\t" << op << ":    \t";
		opd1->print_ics_opd(file_buffer);
		file_buffer << " , zero";
		file_buffer << " : goto " << label << "\n";
	}
	else if (icf == i_op_st)
		file_buffer << "\tgoto " << label << "\n";
	else
	{
		printf("CS316 error\n");
		exit(0);
	}

}

void Control_Flow_IC_Stmt::print_assembly(ostream & file_buffer){
	string op = op_desc.get_mnemonic();
	Assembly_Format af = op_desc.get_assembly_format();
	if(af == a_op_o1_o2_st)
	{
		file_buffer << "\t" << op << " ";
		opd1->print_asm_opd(file_buffer);
		file_buffer << ", ";
		file_buffer << "$zero, ";
		file_buffer << label << "\n";
	}
	else if (af == a_op_st)
		file_buffer << "\tj " << label << "\n";
}

Label_IC_Stmt::Label_IC_Stmt(Tgt_Op inst_op, string l){
	label = l;
	this->op_desc = *(machine_desc_object.spim_instruction_table[inst_op]);
}

Instruction_Descriptor & Label_IC_Stmt::get_inst_op_of_ics(){
	return op_desc;
}

string Label_IC_Stmt::get_label(){
	return label;
}

void Label_IC_Stmt::set_label(string l){
	label = l;
}

void Label_IC_Stmt::print_icode(ostream & file_buffer){
	string opname = op_desc.get_name();
	Icode_Format icf = op_desc.get_ic_format();
	if (icf == i_op_st)
		file_buffer << "\n" << label << ":     \t\n";
	else
		printf("CS316 error\n");
}

void Label_IC_Stmt::print_assembly(ostream & file_buffer){
	string opmne = op_desc.get_mnemonic();
	Assembly_Format asf = op_desc.get_assembly_format();
	if (asf == a_op_st)
		file_buffer << "\n" << label << ":      \t\n";
	else
		printf("CS316 error\n");
}

Code_For_Ast::Code_For_Ast(){}

Code_For_Ast::Code_For_Ast(list<Icode_Stmt *> & ic_l, Register_Descriptor * reg){
	ics_list = ic_l;
	result_register = reg;
}

void Code_For_Ast::append_ics(Icode_Stmt & ics){
	ics_list.push_back(&ics);
}

list<Icode_Stmt *> & Code_For_Ast::get_icode_list()  
{ 
	return ics_list;
}

Register_Descriptor * Code_For_Ast::get_reg()
{
	return result_register;
}

void Code_For_Ast::set_reg(Register_Descriptor * reg){
	result_register = reg;
}

Code_For_Ast& Code_For_Ast::operator=(const Code_For_Ast& rhs)
{
	ics_list = rhs.ics_list;
	result_register = rhs.result_register;
	return *this;
}





