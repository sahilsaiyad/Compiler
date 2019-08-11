int Eval_Result::get_int_value(){}
void Eval_Result::set_value(int value){}
double Eval_Result::get_double_value(){}
void Eval_Result::set_value(double value){}
bool Eval_Result::is_variable_defined(){}
void Eval_Result::set_variable_status(bool def){}
void Eval_Result_Value::set_value(int value){}
void Eval_Result_Value::set_value(double value){}
int Eval_Result_Value::get_int_value(){}
double Eval_Result_Value::get_double_value(){}

Eval_Result_Value_Int::Eval_Result_Value_Int(){
	defined = false;
	result_type = int_result;
};
Eval_Result_Value_Int::~Eval_Result_Value_Int(){};
Eval_Result_Value_Double::Eval_Result_Value_Double(){
	defined = false;
	result_type = double_result;
};
Eval_Result_Value_Double::~Eval_Result_Value_Double(){};


void Eval_Result_Value_Int::set_value(int n)
{
	// printf("%i",n);
	value = n;
}

void Eval_Result_Value_Int::set_value(double n)
{
	value = (int) n;
}

int Eval_Result_Value_Int::get_int_value()
{
	return value;
}

void Eval_Result_Value_Int::set_variable_status(bool def)
{
	defined = def;
}

bool Eval_Result_Value_Int::is_variable_defined()
{
	return defined;
}

void Eval_Result_Value_Int::set_result_enum(Result_Enum res)
{
	result_type = res;
}

Result_Enum Eval_Result_Value_Int::get_result_enum()
{
	return result_type;
}

void Eval_Result_Value_Double::set_value(double n)
{
	value = n;
}

void Eval_Result_Value_Double::set_value(int n)
{
	value = (double) n;
}

double Eval_Result_Value_Double::get_double_value()
{
	return value;
}

void Eval_Result_Value_Double::set_variable_status(bool def)
{
	defined = def;
}

bool Eval_Result_Value_Double::is_variable_defined()
{
	return defined;
}

void Eval_Result_Value_Double::set_result_enum(Result_Enum res)
{
	result_type = res;
}

Result_Enum Eval_Result_Value_Double::get_result_enum()
{
	return result_type;
}

void Local_Environment::print(ostream & file_buffer)
{
	map<string, Eval_Result *>::iterator it;
	for(it = variable_table.begin(); it != variable_table.end(); it++)
	{
		if(it->second->get_result_enum() == int_result)
		{
			if(it->second->is_variable_defined())
			{
				file_buffer<<AST_SPACE<<it->first<<" : "<<it->second->get_int_value()<<"\n";
			}
			else
			{
				file_buffer<<AST_SPACE<<it->first<<" : "<<"undefined"<<"\n";
			}
		}
		else
		{
			if(it->second->is_variable_defined())
			{
				file_buffer<<AST_SPACE<<it->first<<" : "<<it->second->get_double_value()<<"\n";
			}
			else
			{
				file_buffer<<AST_SPACE<<it->first<<" : "<<"undefined"<<"\n";
			}
		}
	}
}

bool Local_Environment::is_variable_defined(string name)
{
	if(does_variable_exist(name))
	{
		map<string, Eval_Result *>::iterator it;
		for(it = variable_table.begin(); it != variable_table.end(); it++)
		{
			if(it->first == name)
			{
				if(it->second->is_variable_defined())
					return true;
				else
					return false;
			}
		}
	}
	else
		return false;
}

Eval_Result * Local_Environment::get_variable_value(string name)
{
	map<string, Eval_Result *>::iterator it;
	for(it = variable_table.begin(); it != variable_table.end(); it++)
	{
		if(it->first == name)
			return it->second;
	}
}

void Local_Environment::put_variable_value(Eval_Result & value, string name)
{
	variable_table[name] = &value;
}

bool Local_Environment::does_variable_exist(string name)
{
	map<string, Eval_Result *>::iterator it;
	bool temp = false;
	for(it = variable_table.begin(); it != variable_table.end(); it++)
	{
		if(it->first == name)
			temp = true;
	}
	return temp;
}

Local_Environment::Local_Environment(){}
Local_Environment::~Local_Environment(){}

void Symbol_Table::create(Local_Environment & local_global_variables_table)
{
	list<Symbol_Table_Entry *>::iterator it;
	for(it = variable_table.begin(); it != variable_table.end(); it++)
	{
		if(get_table_scope() == local)
		{
			if((*it)->get_data_type() == int_data_type)
			{
				Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
				temp->set_variable_status(false);
				// local_global_variables_table.variable_table[(*it)->get_variable_name()] = temp;
				local_global_variables_table.put_variable_value(*temp, (*it)->get_variable_name());
			}
			else
			{
				Eval_Result_Value_Double *temp = new Eval_Result_Value_Double;
				temp->set_variable_status(false);
				// local_global_variables_table.variable_table[(*it)->get_variable_name()] = temp;
				local_global_variables_table.put_variable_value(*temp, (*it)->get_variable_name());
			}
		}
		else if(get_table_scope() == global)
		{
			if((*it)->get_data_type() == int_data_type)
			{
				Eval_Result_Value_Int *temp = new Eval_Result_Value_Int;
				temp->set_variable_status(true);
				temp->set_value(0);
				// local_global_variables_table.variable_table[(*it)->get_variable_name()] = temp;
				local_global_variables_table.put_variable_value(*temp, (*it)->get_variable_name());
			}
			else
			{
				Eval_Result_Value_Double *temp = new Eval_Result_Value_Double;
				temp->set_variable_status(true);
				temp->set_value(0);
				// local_global_variables_table.variable_table[(*it)->get_variable_name()] = temp;
				local_global_variables_table.put_variable_value(*temp, (*it)->get_variable_name());
			}
		}
	}
}
