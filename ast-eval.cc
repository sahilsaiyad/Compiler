
void Ast::print_value(Local_Environment & eval_env, ostream & file_buffer){}
Eval_Result & Ast::get_value_of_evaluation(Local_Environment & eval_env){}
void Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result){}

Eval_Result & Assignment_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{	
	if(this->get_data_type() == int_data_type)
	{

		Eval_Result *temp = new Eval_Result_Value_Int;
		// *temp=rhs->evaluate(eval_env, file_buffer);
		temp->set_variable_status(true);
		temp->set_value(rhs->evaluate(eval_env, file_buffer).get_int_value());
		lhs->set_value_of_evaluation(eval_env, *temp);
		this->print(file_buffer);
		lhs->print_value(eval_env, file_buffer);
		file_buffer<<"\n\n";
		return lhs->get_value_of_evaluation(eval_env);
	}
	else
	{
		Eval_Result *temp = new Eval_Result_Value_Double;
		temp->set_variable_status(true);		
		temp->set_value(rhs->evaluate(eval_env, file_buffer).get_double_value());
		lhs->set_value_of_evaluation(eval_env, *temp);
		this->print(file_buffer);
		lhs->print_value(eval_env, file_buffer);
		file_buffer<<"\n\n";
		return lhs->get_value_of_evaluation(eval_env);	
	}
}

void Name_Ast::print_value(Local_Environment & eval_env, ostream & file_buffer)
{
	if(this->get_data_type() == int_data_type)
	{
		file_buffer<<"\n";
		file_buffer<<AST_SPACE<<this->get_symbol_entry().get_variable_name()<<" : "<<this->get_value_of_evaluation(eval_env).get_int_value();
	}
	else
	{
		file_buffer<<"\n";
		file_buffer<<AST_SPACE<<this->get_symbol_entry().get_variable_name()<<" : "<<this->get_value_of_evaluation(eval_env).get_double_value();
	}
}

Eval_Result & Name_Ast::get_value_of_evaluation(Local_Environment & eval_env)
{
	if(eval_env.is_variable_defined(this->get_symbol_entry().get_variable_name()))
		return *eval_env.get_variable_value(this->get_symbol_entry().get_variable_name());
	else if(interpreter_global_table.is_variable_defined(this->get_symbol_entry().get_variable_name()))
		return *interpreter_global_table.get_variable_value(this->get_symbol_entry().get_variable_name());
	else
	{
		printf("CS316: Error: Variable should be defined before it's use\n");
		exit(0);
	}
}

void Name_Ast::set_value_of_evaluation(Local_Environment & eval_env, Eval_Result & result)
{
	
	if(eval_env.does_variable_exist(this->get_symbol_entry().get_variable_name()))
		eval_env.put_variable_value(result, this->get_symbol_entry().get_variable_name());
	else if(interpreter_global_table.does_variable_exist(this->get_symbol_entry().get_variable_name()))
		interpreter_global_table.put_variable_value(result, this->get_symbol_entry().get_variable_name());
	else
	{
		printf("CS316: Error: Variable does not exist\n");
		exit(0);
	}
}

Eval_Result & Name_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(eval_env.is_variable_defined(this->get_symbol_entry().get_variable_name()))
		return *eval_env.get_variable_value(this->get_symbol_entry().get_variable_name());
	else if(interpreter_global_table.does_variable_exist(this->get_symbol_entry().get_variable_name()))
	{
		if(interpreter_global_table.is_variable_defined(this->get_symbol_entry().get_variable_name()))
			return *interpreter_global_table.get_variable_value(this->get_symbol_entry().get_variable_name());
	}
	else
	{
		printf("CS316: Error: Variable not defined");
		exit(0);
	}	
}

template<>
Eval_Result & Number_Ast<int>::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
	temp->set_variable_status(true);
	temp->set_value(constant);
	return *temp;
}

template<>
Eval_Result & Number_Ast<double>::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	Eval_Result_Value_Double *temp = new Eval_Result_Value_Double;
	temp->set_variable_status(true);
	temp->set_value(constant);
	return *temp;
}

Eval_Result & Plus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(lhs->get_data_type() == int_data_type)
	{
		Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_int_value() + rhs->evaluate(eval_env, file_buffer).get_int_value());
		return *temp;
	}
	else
	{
		Eval_Result_Value_Double *temp = new Eval_Result_Value_Double;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_double_value() + rhs->evaluate(eval_env, file_buffer).get_double_value());
		return *temp;
	}	
}

Eval_Result & Minus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(lhs->get_data_type() == int_data_type)
	{
		Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_int_value() - rhs->evaluate(eval_env, file_buffer).get_int_value());
		return *temp;
	}
	else
	{
		Eval_Result_Value_Double *temp = new Eval_Result_Value_Double;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_double_value() - rhs->evaluate(eval_env, file_buffer).get_double_value());
		return *temp;
	}
}

Eval_Result & Divide_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(lhs->get_data_type() == int_data_type)
	{
		Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_int_value() / rhs->evaluate(eval_env, file_buffer).get_int_value());
		return *temp;
	}
	else
	{
		Eval_Result_Value_Double *temp = new Eval_Result_Value_Double;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_double_value() / rhs->evaluate(eval_env, file_buffer).get_double_value());
		return *temp;
	}
}

Eval_Result & Mult_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(lhs->get_data_type() == int_data_type)
	{
		Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_int_value() * rhs->evaluate(eval_env, file_buffer).get_int_value());
		return *temp;
	}
	else
	{
		Eval_Result_Value_Double *temp = new Eval_Result_Value_Double;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_double_value() * rhs->evaluate(eval_env, file_buffer).get_double_value());
		return *temp;
	}
}

Eval_Result & UMinus_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(lhs->get_data_type() == int_data_type)
	{
		Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_int_value() * -1);
		return *temp;
	}
	else
	{
		Eval_Result_Value_Double *temp = new Eval_Result_Value_Double;
		temp->set_variable_status(true);
		temp->set_value(lhs->evaluate(eval_env, file_buffer).get_double_value() * -1);
		return *temp;
	}
}

Eval_Result & Conditional_Expression_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(cond->evaluate(eval_env, file_buffer).get_int_value())
		lhs->evaluate(eval_env, file_buffer);
	else
		rhs->evaluate(eval_env, file_buffer);
}

Eval_Result & 	::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{}

Eval_Result & Relational_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(rel_op==0)
	{
		if(lhs_condition->get_data_type() == int_data_type)
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_int_value() <= rhs_condition->evaluate(eval_env, file_buffer).get_int_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}

		else
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_double_value() <= rhs_condition->evaluate(eval_env, file_buffer).get_double_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}
	}

	if(rel_op==1)
	{
		if(lhs_condition->get_data_type() == int_data_type)
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_int_value() < rhs_condition->evaluate(eval_env, file_buffer).get_int_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}

		else
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_double_value() < rhs_condition->evaluate(eval_env, file_buffer).get_double_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}
	}

	if(rel_op==2)
	{
		if(lhs_condition->get_data_type() == int_data_type)
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_int_value() > rhs_condition->evaluate(eval_env, file_buffer).get_int_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}

		else
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_double_value() > rhs_condition->evaluate(eval_env, file_buffer).get_double_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}
	}

	if(rel_op==3)
	{
		if(lhs_condition->get_data_type() == int_data_type)
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_int_value() >= rhs_condition->evaluate(eval_env, file_buffer).get_int_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}

		else
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_double_value() >= rhs_condition->evaluate(eval_env, file_buffer).get_double_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}
	}

	if(rel_op==4)
	{
		if(lhs_condition->get_data_type() == int_data_type)
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_int_value() == rhs_condition->evaluate(eval_env, file_buffer).get_int_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}

		else
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_double_value() == rhs_condition->evaluate(eval_env, file_buffer).get_double_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}
	}

	if(rel_op==5)
	{
		if(lhs_condition->get_data_type() == int_data_type)
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_int_value() != rhs_condition->evaluate(eval_env, file_buffer).get_int_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}

		else
		{
			Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
			temp->set_variable_status(true);
			if (lhs_condition->evaluate(eval_env, file_buffer).get_double_value() != rhs_condition->evaluate(eval_env, file_buffer).get_double_value())
				temp->set_value(1);
			else
				temp->set_value(0);
			return *temp;
		}
	}		
}

Eval_Result & Logical_Expr_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(bool_op == 0)
	{
		Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
		temp->set_variable_status(true);
		if(rhs_op->evaluate(eval_env, file_buffer).get_int_value())
			temp->set_value(0);
		else
			temp->set_value(1);
		return *temp;
	}

	if(bool_op == 1)
	{
		Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
		temp->set_variable_status(true);
		if(lhs_op->evaluate(eval_env, file_buffer).get_int_value() || rhs_op->evaluate(eval_env, file_buffer).get_int_value())
			temp->set_value(1);
		else
			temp->set_value(0);
		return *temp;
	}

	if(bool_op == 2)
	{
		Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
		temp->set_variable_status(true);
		if(lhs_op->evaluate(eval_env, file_buffer).get_int_value() && rhs_op->evaluate(eval_env, file_buffer).get_int_value())
			temp->set_value(1);
		else
			temp->set_value(0);
		return *temp;
	}
}

Eval_Result & Selection_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(cond->evaluate(eval_env, file_buffer).get_int_value())
		then_part->evaluate(eval_env, file_buffer);
	else
		else_part->evaluate(eval_env, file_buffer);
}

Eval_Result & Iteration_Statement_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	if(is_do_form)
	{
		do{body->evaluate(eval_env, file_buffer);}
		while(cond->evaluate(eval_env, file_buffer).get_int_value());
	}
	else
		while(cond->evaluate(eval_env, file_buffer).get_int_value())
			body->evaluate(eval_env, file_buffer);
}

Eval_Result & Sequence_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	list <Ast *>::iterator it;
	for(it = statement_list.begin(); it != statement_list.end(); it++)
		(*it)->evaluate(eval_env, file_buffer);
}

Eval_Result & Return_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	return return_value->compile(eval_env, file_buffer);
}

Eval_Result & Call_Ast::evaluate(Local_Environment & eval_env, ostream & file_buffer)
{
	list <Ast *>::iterator it;
	for(it = actual_param_list.begin(); it != actual_param_list.end(); it++)
		(*it)->evaluate(eval_env, file_buffer);
}