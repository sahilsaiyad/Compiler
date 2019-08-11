#include<iostream>
#include<stdlib.h>
// #include "ast.hh"

using namespace std;

int Ast::labelCounter;

Ast::Ast()
{}

Ast::~Ast()
{}
void Ast::print(ostream & file_buffer)
{
	file_buffer << node_data_type;
}

Data_Type Ast::get_data_type()
{
	return node_data_type;
}

void Ast::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

bool Ast::is_value_zero()
{}

Symbol_Table_Entry & Ast::get_symbol_entry()
{}

bool Ast::check_ast()
{}

Assignment_Ast::Assignment_Ast(Ast * temp_lhs, Ast * temp_rhs, int line)
{
	lhs = temp_lhs;
	rhs = temp_rhs;
	lineno = line;
}

Assignment_Ast::~Assignment_Ast()
{}

bool Assignment_Ast::check_ast()
{
	if(lhs->get_data_type() == rhs->get_data_type())
		return 1;
	else
	{
		printf("cs316: Error\n");
		exit(0);
	}
}

void Assignment_Ast::print(ostream & file_buffer)
{
	file_buffer<<"\n"<<AST_SPACE<<"Asgn:"<<"\n"<<AST_NODE_SPACE<<"LHS (";
	lhs->print(file_buffer);
	file_buffer<<")"<<"\n"<<AST_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer<<")";
}

Name_Ast::Name_Ast(string & name, Symbol_Table_Entry & var_entry, int line)
{
	variable_symbol_entry = &var_entry;
	lineno = line;
}

Name_Ast::~Name_Ast()
{}

Data_Type Name_Ast::get_data_type()
{
	return variable_symbol_entry->get_data_type();
}

void Name_Ast::print(ostream & file_buffer)
{
	file_buffer<<"Name"<<" : "<<variable_symbol_entry->get_variable_name();
}

void Name_Ast::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

Symbol_Table_Entry & Name_Ast::get_symbol_entry()
{
	return *variable_symbol_entry;
}

template<>
Number_Ast<int>::Number_Ast(int number, Data_Type constant_data_type, int line)
{
	constant = number;
	node_data_type = constant_data_type;
	lineno = line;
}

template<>
Number_Ast<int>::~Number_Ast()
{}

template<>
void Number_Ast<int>::print(ostream & file_buffer)
{
	file_buffer<<"Num : "<<constant;
}

template<>
void Number_Ast<double>::print(ostream & file_buffer)
{
	file_buffer<<"Num : "<<constant;
}

template<>
bool Number_Ast<int>::is_value_zero()
{}

template<>
bool Number_Ast<double>::is_value_zero()
{}

template<>
Number_Ast<double>::Number_Ast(double number, Data_Type constant_data_type, int line)
{
	constant = number;
	node_data_type = constant_data_type;
	lineno = line;
}

template<>
Number_Ast<double>::~Number_Ast()
{}

template<>
Data_Type Number_Ast<int>::get_data_type()
{
	return node_data_type;
}

template<>
Data_Type Number_Ast<double>::get_data_type()
{
	return node_data_type;
}

template<>
void Number_Ast<int>::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

template<>
void Number_Ast<double>::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

Data_Type Arithmetic_Expr_Ast::get_data_type()
{
	return node_data_type;
}

void Arithmetic_Expr_Ast::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

// void Arithmetic_Expr_Ast::print(ostream &file_buffer)
// {
// 	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"Arith: "
// }

bool Arithmetic_Expr_Ast::check_ast()
{
	if(rhs == NULL || (lhs->get_data_type() == rhs->get_data_type()))
		return 1;
	else
		return 0; 
}

Plus_Ast::Plus_Ast(Ast * l, Ast * r, int line)
{
	lhs = l;
	rhs = r;
	lineno = line;
}

void Plus_Ast::print(ostream & file_buffer)
{
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: PLUS"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	lhs->print(file_buffer);
	file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer<<")";
}

Minus_Ast::Minus_Ast(Ast * l, Ast * r, int line)
{
	lhs = l;
	rhs = r;
	lineno = line;
}

void Minus_Ast::print(ostream & file_buffer)
{
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: MINUS"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	lhs->print(file_buffer);
	file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer<<")";
}

Divide_Ast::Divide_Ast(Ast * l, Ast * r, int line)
{
	lhs = l;
	rhs = r;
	lineno = line;
}

void Divide_Ast::print(ostream & file_buffer)
{
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: DIV"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	lhs->print(file_buffer);
	file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer<<")";
}

Mult_Ast::Mult_Ast(Ast * l, Ast * r, int line)
{
	lhs = l;
	rhs = r;
	lineno = line;
}

void Mult_Ast::print(ostream & file_buffer)
{
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: MULT"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	lhs->print(file_buffer);
	file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer<<")";
}

UMinus_Ast::UMinus_Ast(Ast * l, Ast * r, int line)
{
	lhs = l;
	rhs = r;
	lineno = line;
}

void UMinus_Ast::print(ostream & file_buffer)
{
	file_buffer<<"\n"<<AST_NODE_SPACE<<"Arith: UMINUS"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
	lhs->print(file_buffer);
	file_buffer<<")";
}

Return_Ast::Return_Ast(int line)
{
	lineno = line;
}

void Return_Ast::print(ostream & file_buffer)
{}

Conditional_Expression_Ast::Conditional_Expression_Ast(Ast* c, Ast* l, Ast* r, int line)
{
	cond = c;
	lhs = l;
	rhs = r;
	lineno = line;
}

void Conditional_Expression_Ast::print(ostream & file_buffer)
{
	file_buffer<<"\n"<<AST_SPACE<<"Cond:"<<"\n"<<AST_NODE_SPACE<<"IF_ELSE";
	cond->print(file_buffer);
	file_buffer<<"\n"<<AST_NODE_SPACE<<"LHS (";
	lhs->print(file_buffer);
	file_buffer<<")";
	file_buffer<<"\n"<<AST_NODE_SPACE<<"RHS (";
	rhs->print(file_buffer);
	file_buffer<<")";
}

Relational_Expr_Ast::Relational_Expr_Ast(Ast * lhs, Relational_Op rop, Ast * rhs, int line)
{
	lhs_condition = lhs;
	rhs_condition = rhs;
	rel_op = rop;
	lineno = line;
}

Data_Type Relational_Expr_Ast::get_data_type()
{
	return node_data_type;
}

void Relational_Expr_Ast::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

bool Relational_Expr_Ast::check_ast()
{
	if (lhs_condition->get_data_type() == rhs_condition->get_data_type())
	{
		return 1;
	}
	else
		return 0;
}

void Relational_Expr_Ast::print(ostream & file_buffer)
{
	if(rel_op==0)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: LE"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		lhs_condition->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer<<")";
	}
	if(rel_op==1)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: LT"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		lhs_condition->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer<<")";
	}
	if(rel_op==2)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: GT"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		lhs_condition->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer<<")";
	}
	if(rel_op==3)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: GE"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		lhs_condition->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer<<")";
	}
	if(rel_op==4)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: EQ"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		lhs_condition->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer<<")";
	}
	if(rel_op==5)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: NE"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		lhs_condition->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_condition->print(file_buffer);
		file_buffer<<")";
	}
}

Logical_Expr_Ast::Logical_Expr_Ast(Ast * lhs, Logical_Op bop, Ast * rhs, int line)
{
	lhs_op = lhs;
	rhs_op = rhs;
	bool_op = bop;
	lineno = line;
}

Data_Type Logical_Expr_Ast::get_data_type()
{
	return node_data_type;
}

void Logical_Expr_Ast::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

bool Logical_Expr_Ast::check_ast()
{
	if (lhs_op->get_data_type() == rhs_op->get_data_type())
	{
		return 1;
	}
	else
		return 0;
}

void Logical_Expr_Ast::print(ostream & file_buffer)
{
	if(bool_op==0)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: NOT"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_op->print(file_buffer);
		file_buffer<<")";
	}
	if(bool_op==1)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: OR"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		lhs_op->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_op->print(file_buffer);
		file_buffer<<")";
	}
	if(bool_op==2)
	{
		file_buffer<<"\n"<<AST_NODE_SPACE<<"Condition: AND"<<"\n"<<AST_SUB_NODE_SPACE<<"LHS (";
		lhs_op->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SUB_NODE_SPACE<<"RHS (";
		rhs_op->print(file_buffer);
		file_buffer<<")";
	}
}

Selection_Statement_Ast::Selection_Statement_Ast(Ast * c,Ast* t, Ast* e, int line)
{
	cond = c;
	then_part = t;
	else_part = e;
	lineno = line;
}

Data_Type Selection_Statement_Ast::get_data_type()
{
	return node_data_type;
}

void Selection_Statement_Ast::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

bool Selection_Statement_Ast::check_ast()
{}

void Selection_Statement_Ast::print(ostream & file_buffer)
{
	file_buffer<<"\n"<<AST_SPACE<<"IF : "<<"\n"<<AST_SPACE<<"CONDITION (";
	cond->print(file_buffer);
	file_buffer<<")"<<"\n"<<AST_SPACE<<"THEN (";
	then_part->print(file_buffer);
	file_buffer<<")";
	if(else_part!=NULL)
	{
		file_buffer<<"\n"<<AST_SPACE<<"ELSE (";
		else_part->print(file_buffer);
		file_buffer<<")";
	}	
}

Iteration_Statement_Ast::Iteration_Statement_Ast(Ast * c, Ast* b, int line, bool do_form)
{
	cond = c;
	body = b;
	is_do_form = do_form;
	lineno = line;
}

Data_Type Iteration_Statement_Ast::get_data_type()
{
	return node_data_type;
}

void Iteration_Statement_Ast::set_data_type(Data_Type dt)
{
	node_data_type = dt;
}

void Iteration_Statement_Ast::print(ostream & file_buffer)
{
	if(is_do_form==0)
	{
		file_buffer<<"\n"<<AST_SPACE<<"WHILE : "<<"\n"<<AST_SPACE<<"CONDITION (";
		cond->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SPACE<<"BODY (";
		body->print(file_buffer);
		file_buffer<<")";
	}
	else
	{
		file_buffer<<"\n"<<AST_SPACE<<"DO (";
		body->print(file_buffer);
		file_buffer<<")"<<"\n"<<AST_SPACE<<"WHILE CONDITION (";
		cond->print(file_buffer);
		file_buffer<<")";
	}
}

bool Iteration_Statement_Ast::check_ast()
{}

Sequence_Ast::Sequence_Ast(int line)
{
	lineno = line;
}

void Sequence_Ast::ast_push_back(Ast *ast)
{
	statement_list.push_back(ast);
}

void Sequence_Ast::print(ostream & file_buffer)
{
	list<Ast *>::iterator it;
	for (it = statement_list.begin(); it != statement_list.end(); it++) {
		file_buffer<<"\n"<<AST_NODE_SPACE;
    	(*it)->print(file_buffer);
	}
}

Print_Ast::Print_Ast(Ast *v, int line)
{
	var = v;
	lineno = line;
}

Print_Ast::~Print_Ast(){}

void Print_Ast::print(ostream & file_buffer){
	file_buffer<<"\n"<<AST_SPACE<<"Print :";
	file_buffer<<"\n"<<AST_SUB_NODE_SPACE<<"(";
	var->print(file_buffer);
	file_buffer<<")";
}

Return_Ast::Return_Ast(Ast* ret_val, string name, int line)
{
	this->ret_val = ret_val;
	this->ast_num_child = unary_arity;
	this->func_name = name;
	if(return_value == NULL)
		this->node_data_type = void_data_type;
	else 
		this->node_data_type = return_value->get_data_type();
	this->lineno = line;
	this->check_ast();
}

Data_Type Return_Ast::get_data_type()
{
	return this->node_data_type;
}

bool Return_Ast::check_ast()
{
	return true;
}

string Return_Ast::get_func_name()
{
	return this->func_name;
}

void Return_Ast::print(ostream & file_buffer)
{
	file_buffer << endl
				<< AST_SPACE << "RETURN ";
	if(this->ret_val == NULL) {
		file_buffer << "<NOTHING>";
	} else {
		ret_val->print(file_buffer);
	}
	file_buffer << endl;
}

Call_Ast::Call_Ast(string name, int line)
{
	this->procedure_name = name;
	this->node_data_type = int_data_type;
	this->lineno = line;
}

Data_Type Call_Ast::get_data_type()
{
	return this->node_data_type;
}

void Call_Ast::set_register(Register_Descriptor * reg)
{
	return_value_reg = reg;
}

void Call_Ast::check_actual_formal_param(Symbol_Table & formal_param_list)
{
	
}
	
void set_actual_param_list(list<Ast *> & param_list)
{
	this->actual_param_list = param_list;
}

void Call_Ast::print(ostream & file_buffer)
{
	file_buffer << "\n"
				<< AST_SPACE << "FN CALL: " << this->func_name << "(";
	for(auto it: arguments) {
		file_buffer << endl;
		file_buffer << AST_NODE_SPACE;
		it->print(file_buffer);
	}
	file_buffer << ")";
}