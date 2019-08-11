Code_For_Ast & Ast::create_store_stmt(Register_Descriptor * store_register){}

Code_For_Ast & Assignment_Ast::compile() {
	Code_For_Ast & rs = rhs->compile();
	Register_Descriptor * lr = rs.get_reg();
	list<Icode_Stmt *> & ist = *new list<Icode_Stmt *>;
	ist = rs.get_icode_list();
	lr->reset_use_for_expr_result();
	Code_For_Ast st = lhs->create_store_stmt(lr);
	ist.splice(ist.end(), st.get_icode_list());
	Code_For_Ast *ans = new Code_For_Ast(ist, NULL);
	return *ans;
}

Code_For_Ast & Assignment_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Name_Ast::compile() {
	Mem_Addr_Opd * md = new Mem_Addr_Opd(*variable_symbol_entry);
	Register_Descriptor * nr;
	Register_Descriptor * temp;
	Icode_Stmt * ct;
	if(get_data_type() == int_data_type)
	{
		temp = machine_desc_object.get_new_register<int_reg>();
		Register_Addr_Opd * rd = new Register_Addr_Opd(temp);
		ct = new Move_IC_Stmt(load, md, rd);
	}
	else
	{
		temp = machine_desc_object.get_new_register<float_reg>();
		Register_Addr_Opd * rd = new Register_Addr_Opd(temp);
		ct = new Move_IC_Stmt(load_d, md, rd);
	}

	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist.push_back(ct);
	Code_For_Ast *ans = new Code_For_Ast(ist, temp);
	return *ans;
}

Code_For_Ast & Name_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Name_Ast::create_store_stmt(Register_Descriptor * store_register) {
	Mem_Addr_Opd * md = new Mem_Addr_Opd(*variable_symbol_entry);
	Register_Addr_Opd * rd = new Register_Addr_Opd(store_register);
	Icode_Stmt* ct;
	if(get_data_type() == int_data_type)
	{
		ct = new Move_IC_Stmt(store, rd, md);
	}
	else
	{
		ct = new Move_IC_Stmt(store_d, rd, md);
	}
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist.push_back(ct);
	Code_For_Ast *ans;
	ans = new Code_For_Ast(ist, store_register);
	return *ans;
}

template<>
Code_For_Ast & Number_Ast<int>::compile(){
	Const_Opd<int> *num = new Const_Opd<int>(constant);
	Icode_Stmt *ct;
	Register_Descriptor * temp = machine_desc_object.get_new_register<int_reg>();
	Register_Addr_Opd *rd = new Register_Addr_Opd(temp);
	ct = new Move_IC_Stmt(imm_load, num, rd);
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist.push_back(ct);
	Code_For_Ast *ans;
	ans = new Code_For_Ast(ist, temp);
	return *ans;
}

template<>
Code_For_Ast & Number_Ast<double>::compile(){
	Const_Opd<double> *num = new Const_Opd<double>(constant);
	Icode_Stmt *ct;
	Register_Descriptor * temp = machine_desc_object.get_new_register<float_reg>();
	Register_Addr_Opd *rd = new Register_Addr_Opd(temp);
	ct = new Move_IC_Stmt(imm_load_d, num, rd);
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist.push_back(ct);
	Code_For_Ast *ans;
	ans = new Code_For_Ast(ist, temp);
	return *ans;
}

template<>
Code_For_Ast & Number_Ast<int>::compile_and_optimize_ast(Lra_Outcome & lra){}

template<>
Code_For_Ast & Number_Ast<double>::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Plus_Ast::compile(){
	Code_For_Ast &l = lhs->compile();
	Code_For_Ast &r = rhs->compile();
	Register_Descriptor *lg = l.get_reg();
	Register_Descriptor *rg = r.get_reg();
	Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
	Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
	Register_Descriptor * temp;
	Icode_Stmt* ct;
	if (get_data_type() == int_data_type)
	{
		temp =  machine_desc_object.get_new_register<int_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(add, ld, rd, res);
	}
	else
	{
		temp =  machine_desc_object.get_new_register<float_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(add_d, ld, rd, res);
	}
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist = l.get_icode_list();
	ist.splice(ist.end(), r.get_icode_list());
	ist.push_back(ct);
	lg->reset_use_for_expr_result();
	rg->reset_use_for_expr_result();
	Code_For_Ast *ans = new Code_For_Ast(ist, temp);
	return *ans;
}

Code_For_Ast & Plus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Minus_Ast::compile(){
	Code_For_Ast &l = lhs->compile();
	Code_For_Ast &r = rhs->compile();
	Register_Descriptor *lg = l.get_reg();
	Register_Descriptor *rg = r.get_reg();
	Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
	Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
	Register_Descriptor * temp;
	Icode_Stmt* ct;
	if (get_data_type() == int_data_type)
	{
		temp =  machine_desc_object.get_new_register<int_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(sub, ld, rd, res);
	}
	else
	{
		temp =  machine_desc_object.get_new_register<float_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(sub_d, ld, rd, res);
	}
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist = l.get_icode_list();
	ist.splice(ist.end(), r.get_icode_list());
	ist.push_back(ct);
	lg->reset_use_for_expr_result();
	rg->reset_use_for_expr_result();
	Code_For_Ast *ans = new Code_For_Ast(ist, temp);
	return *ans;
}

Code_For_Ast & Minus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Divide_Ast::compile(){
	Code_For_Ast &l = lhs->compile();
	Code_For_Ast &r = rhs->compile();
	Register_Descriptor *lg = l.get_reg();
	Register_Descriptor *rg = r.get_reg();
	Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
	Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
	Register_Descriptor * temp;
	Icode_Stmt* ct;
	if (get_data_type() == int_data_type)
	{
		temp =  machine_desc_object.get_new_register<int_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(divd, ld, rd, res);
	}
	else
	{
		temp =  machine_desc_object.get_new_register<float_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(div_d, ld, rd, res);
	}
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist = l.get_icode_list();
	ist.splice(ist.end(), r.get_icode_list());
	ist.push_back(ct);
	lg->reset_use_for_expr_result();
	rg->reset_use_for_expr_result();
	Code_For_Ast *ans = new Code_For_Ast(ist, temp);
	return *ans;
}

Code_For_Ast & Divide_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Mult_Ast::compile(){
	Code_For_Ast &l = lhs->compile();
	Code_For_Ast &r = rhs->compile();
	Register_Descriptor *lg = l.get_reg();
	Register_Descriptor *rg = r.get_reg();
	Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
	Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
	Register_Descriptor * temp;
	Icode_Stmt* ct;
	if (get_data_type() == int_data_type)
	{
		temp =  machine_desc_object.get_new_register<int_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(mult, ld, rd, res);
	}
	else
	{
		temp =  machine_desc_object.get_new_register<float_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(mult_d, ld, rd, res);
	}
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist = l.get_icode_list();
	ist.splice(ist.end(), r.get_icode_list());
	ist.push_back(ct);
	lg->reset_use_for_expr_result();
	rg->reset_use_for_expr_result();
	Code_For_Ast *ans = new Code_For_Ast(ist, temp);
	return *ans;
}

Code_For_Ast & Mult_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & UMinus_Ast::compile(){
	Code_For_Ast &l = lhs->compile();
	Register_Descriptor *lg = l.get_reg();
	Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
	Icode_Stmt* ct;
	Register_Descriptor * temp;
	if(get_data_type() == int_data_type)
	{
		temp = machine_desc_object.get_new_register<int_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(uminus, ld, NULL, res);
	}
	else
	{
		temp = machine_desc_object.get_new_register<float_reg>();
		Register_Addr_Opd * res = new Register_Addr_Opd(temp);
		ct = new Compute_IC_Stmt(uminus_d, ld, NULL, res);
	}
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist = l.get_icode_list();
	ist.push_back(ct);
	lg->reset_use_for_expr_result();
	Code_For_Ast *ans = new Code_For_Ast(ist, temp);
	return *ans;
}

Code_For_Ast & UMinus_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Conditional_Expression_Ast::compile(){
	Code_For_Ast &con = cond->compile();
	Code_For_Ast &l = lhs->compile();
	Code_For_Ast &r = rhs->compile();
	Register_Descriptor *conr = con.get_reg();
	Register_Descriptor *lg = l.get_reg();
	Register_Descriptor *rg = r.get_reg();
	string s0 = get_new_label();
	string s1 = get_new_label();
	Register_Addr_Opd *temp1 = new Register_Addr_Opd(conr);
	Register_Addr_Opd *temp2 = new Register_Addr_Opd(machine_desc_object.spim_register_table[zero]);
	Control_Flow_IC_Stmt *ct = new Control_Flow_IC_Stmt(beq, temp1, s0);
	Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
	Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
	Register_Descriptor *res;
	if(get_data_type() == int_data_type)
	{
		res = machine_desc_object.get_new_register<int_reg>();
	}
	else
	{
		res = machine_desc_object.get_new_register<float_reg>();
	}
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	ist = con.get_icode_list();
	ist.push_back(ct);
	ist.splice(ist.end(), l.get_icode_list());
	Compute_IC_Stmt *sl = new Compute_IC_Stmt(or_t, ld, temp2, new Register_Addr_Opd(res));
	Compute_IC_Stmt *sr = new Compute_IC_Stmt(or_t, rd, temp2, new Register_Addr_Opd(res));

	ist.push_back(sl);
	Control_Flow_IC_Stmt *nct = new Control_Flow_IC_Stmt(j, NULL, s1);
	ist.push_back(nct);
	Label_IC_Stmt *s0t = new Label_IC_Stmt(label, s0);
	ist.push_back(s0t);
	ist.splice(ist.end(), r.get_icode_list());
	ist.push_back(sr);
	Label_IC_Stmt *s1t = new Label_IC_Stmt(label, s1);
	ist.push_back(s1t);
	conr->reset_use_for_expr_result();
	lg->reset_use_for_expr_result();
	rg->reset_use_for_expr_result();
	Code_For_Ast *ans = new Code_For_Ast(ist, res);
	return *ans;
}

Code_For_Ast & Return_Ast::compile(){}

Code_For_Ast & Return_Ast::compile_and_optimize_ast(Lra_Outcome & lra){}

Code_For_Ast & Relational_Expr_Ast::compile(){
	if(rel_op == 0)
	{
		Code_For_Ast &l = lhs_condition->compile();
		Code_For_Ast &r = rhs_condition->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(sle, ld, rd, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(sle, ld, rd, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
	else if(rel_op == 1)
	{
		Code_For_Ast &l = lhs_condition->compile();
		Code_For_Ast &r = rhs_condition->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(slt, ld, rd, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(slt, ld, rd, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
	else if(rel_op == 2)
	{
		Code_For_Ast &l = lhs_condition->compile();
		Code_For_Ast &r = rhs_condition->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(sgt, ld, rd, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(sgt, ld, rd, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
	else if(rel_op == 3)
	{
		Code_For_Ast &l = lhs_condition->compile();
		Code_For_Ast &r = rhs_condition->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(sge, ld, rd, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(sge, ld, rd, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
	else if(rel_op == 4)
	{
		Code_For_Ast &l = lhs_condition->compile();
		Code_For_Ast &r = rhs_condition->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(seq, ld, rd, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(seq, ld, rd, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
	else if(rel_op == 5)
	{
		Code_For_Ast &l = lhs_condition->compile();
		Code_For_Ast &r = rhs_condition->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(sne, ld, rd, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(sne, ld, rd, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
}

Code_For_Ast & Logical_Expr_Ast::compile(){
	if(bool_op == 0)
	{
		Ast *lhs_op = new Number_Ast<int>(1, int_data_type, 1);
		Code_For_Ast &l = lhs_op->compile();
		Code_For_Ast &r = rhs_op->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(not_t, rd, ld, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(not_t, rd, ld, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
	else if(bool_op == 1)
	{
		Code_For_Ast &l = lhs_op->compile();
		Code_For_Ast &r = rhs_op->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(or_t, ld, rd, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(or_t, ld, rd, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
	else if(bool_op == 2)
	{
		Code_For_Ast &l = lhs_op->compile();
		Code_For_Ast &r = rhs_op->compile();
		Register_Descriptor *lg = l.get_reg();
		Register_Descriptor *rg = r.get_reg();
		Register_Addr_Opd * ld = new Register_Addr_Opd(lg);
		Register_Addr_Opd * rd = new Register_Addr_Opd(rg);
		Register_Descriptor * temp;
		Icode_Stmt* ct;
		if (get_data_type() == int_data_type)
		{
			temp =  machine_desc_object.get_new_register<int_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(and_t, ld, rd, res);
		}
		else
		{
			temp =  machine_desc_object.get_new_register<float_reg>();
			Register_Addr_Opd * res = new Register_Addr_Opd(temp);
			ct = new Compute_IC_Stmt(and_t, ld, rd, res);
		}
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = l.get_icode_list();
		ist.splice(ist.end(), r.get_icode_list());
		ist.push_back(ct);
		lg->reset_use_for_expr_result();
		rg->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, temp);
		return *ans;
	}
}

Code_For_Ast & Selection_Statement_Ast::compile(){
	Code_For_Ast &con = cond->compile();
	Code_For_Ast &t = then_part->compile();
	if(else_part != NULL)
	{
		Code_For_Ast &e = else_part->compile();
		Register_Descriptor *conr = con.get_reg();
		string s0 = get_new_label();
		string s1 = get_new_label();
		Register_Addr_Opd *temp1 = new Register_Addr_Opd(conr);
		Control_Flow_IC_Stmt *ct = new Control_Flow_IC_Stmt(beq, temp1, s0);
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = con.get_icode_list();
		ist.push_back(ct);
		ist.splice(ist.end(), t.get_icode_list());
		Control_Flow_IC_Stmt *nct = new Control_Flow_IC_Stmt(j, NULL, s1);
		ist.push_back(nct);
		Label_IC_Stmt *s0t = new Label_IC_Stmt(label, s0);
		ist.push_back(s0t);
		ist.splice(ist.end(), e.get_icode_list());
		Label_IC_Stmt *s1t = new Label_IC_Stmt(label, s1);
		ist.push_back(s1t);
		conr->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, NULL);
		return *ans;
	}
	else
	{
		Register_Descriptor *conr = con.get_reg();
		string s0 = get_new_label();
		Register_Addr_Opd *temp1 = new Register_Addr_Opd(conr);
		Control_Flow_IC_Stmt *ct = new Control_Flow_IC_Stmt(beq, temp1, s0);
		list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
		ist = con.get_icode_list();
		ist.push_back(ct);
		ist.splice(ist.end(), t.get_icode_list());
		Label_IC_Stmt *s0t = new Label_IC_Stmt(label, s0);
		ist.push_back(s0t);
		conr->reset_use_for_expr_result();
		Code_For_Ast *ans = new Code_For_Ast(ist, NULL);
		return *ans;
	}
	// string s1 = get_new_label();
	// Control_Flow_IC_Stmt *nct = new Control_Flow_IC_Stmt(j, NULL, s1);
	// ist.push_back(nct);
	// ist.splice(ist.end(), e.get_icode_list());
	// Label_IC_Stmt *s1t = new Label_IC_Stmt(label, s1);
	// ist.push_back(s1t);
}

Code_For_Ast & Iteration_Statement_Ast::compile(){
	Code_For_Ast &con = cond->compile();
	Code_For_Ast &b = body->compile();
	string s0 = get_new_label();
	string s1 = get_new_label();
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	if(!is_do_form)
	{
		Control_Flow_IC_Stmt *ct = new Control_Flow_IC_Stmt(j, NULL, s1);
		ist.push_back(ct);
	}
	Label_IC_Stmt *s0t = new Label_IC_Stmt(label, s0);
	ist.push_back(s0t);
	ist.splice(ist.end(), b.get_icode_list());
	Label_IC_Stmt *s1t = new Label_IC_Stmt(label, s1);
	ist.push_back(s1t);
	ist.splice(ist.end(), con.get_icode_list());
	Register_Descriptor *conr = con.get_reg();
	Register_Addr_Opd *temp = new Register_Addr_Opd(conr);
	Control_Flow_IC_Stmt *nct = new Control_Flow_IC_Stmt(bne, temp, s0);
	ist.push_back(nct);
	conr->reset_use_for_expr_result();
	Code_For_Ast *ans = new Code_For_Ast(ist, NULL);
	return *ans;
}

Code_For_Ast & Sequence_Ast::compile(){
	sa_icode_list = list<Icode_Stmt*>();
	for(list<Ast *>::iterator it = statement_list.begin();it != statement_list.end();it++)
	{
		Code_For_Ast &temp = (*it)->compile();
		sa_icode_list.splice(sa_icode_list.end(), temp.get_icode_list());
	}
	Code_For_Ast *ans = new Code_For_Ast(sa_icode_list, NULL);
	return *ans;
}

Code_For_Ast & Print_Ast::compile(){
	Code_For_Ast *ans;
	list<Icode_Stmt*> &ist = *new list<Icode_Stmt *>;
	Register_Descriptor *temp = machine_desc_object.get_new_register<int_reg>();
	Print_IC_Stmt *pst = new Print_IC_Stmt();
	if(var->get_data_type() == int_data_type)
	{
		Register_Addr_Opd* temp2 = new Register_Addr_Opd(temp);
		Move_IC_Stmt *mt0 = new Move_IC_Stmt(imm_load, new Const_Opd<int>(1), temp2);
		Mem_Addr_Opd *temp3 = new Mem_Addr_Opd(var->get_symbol_entry());
		Register_Addr_Opd *temp4 = new Register_Addr_Opd(machine_desc_object.spim_register_table[a0]);
		Move_IC_Stmt *mt1 = new Move_IC_Stmt(load, temp3, temp4);
		ist.push_back(mt0);
		ist.push_back(mt1);
		ist.push_back(pst);
		temp->reset_use_for_expr_result();
		ans = new Code_For_Ast(ist, NULL);
	}
	else
	{
		Register_Addr_Opd* temp2 = new Register_Addr_Opd(temp);
		Move_IC_Stmt *mt0 = new Move_IC_Stmt(imm_load, new Const_Opd<int>(3), temp2);
		Mem_Addr_Opd *temp3 = new Mem_Addr_Opd(var->get_symbol_entry());
		Register_Addr_Opd *temp4 = new Register_Addr_Opd(machine_desc_object.spim_register_table[f12]);
		Move_IC_Stmt *mt1 = new Move_IC_Stmt(load_d, temp3, temp4);
		ist.push_back(mt0);
		ist.push_back(mt1);
		ist.push_back(pst);
		temp->reset_use_for_expr_result();
		ans = new Code_For_Ast(ist, NULL);
	}
	return *ans;
}

Code_For_Ast & Return_Ast::compile()
{
	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;
	string label = "epilogue_" + get_func_name();
	if(get_data_type() == void_data_type) {
		Control_Flow_IC_Stmt * control_stmt = new Control_Flow_IC_Stmt(j, NULL, NULL, label);
		ic_list.push_back(control_stmt);
		Code_For_Ast * ret_stmt = new Code_For_Ast(ic_list, NULL);
		return *ret_stmt;
	} 
	Code_For_Ast & expr_ast = ret_val->compile();
	Register_Descriptor * expr_reg = expr_ast.get_reg();
	Register_Addr_Opd * expr_opd = new Register_Addr_Opd(expr_reg);
	expr_reg->reset_use_for_expr_result();

	Icode_Stmt * curr_stmt;
	if(get_data_type() == int_data_type) {
		Register_Addr_Opd * v1_opd = new Register_Addr_Opd(machine_desc_object.spim_register_table[v1]);
		curr_stmt = new Move_IC_Stmt(mov, expr_opd, v1_opd);
	} else if(get_data_type() == double_data_type) {
		Register_Addr_Opd * f0_opd = new Register_Addr_Opd(machine_desc_object.spim_register_table[f0]);
		curr_stmt = new Move_IC_Stmt(move_d, expr_opd, f0_opd);
	}
	if (expr_ast.get_icode_list().empty() == false)
		ic_list = expr_ast.get_icode_list();
	ic_list.push_back(curr_stmt);
	Control_Flow_IC_Stmt * control_stmt = new Control_Flow_IC_Stmt(j, NULL, NULL, label);
	ic_list.push_back(control_stmt);
	Code_For_Ast * ret_stmt = new Code_For_Ast(ic_list, NULL);
	return *ret_stmt;
}

Code_For_Ast & Call_Ast::compile()
{
	list<Icode_Stmt *> & ic_list = *new list<Icode_Stmt *>;
	Register_Addr_Opd * sp_opd = new Register_Addr_Opd(machine_desc_object.spim_register_table[sp]);
	int offset = 0;
	for(auto it = arguments.end(); it != arguments.begin(); ) {
		--it;
		Code_For_Ast & expr_ast = (*it)->compile();
		if (expr_ast.get_icode_list().empty() == false)
			ic_list.splice(ic_list.end(), expr_ast.get_icode_list());
		Register_Descriptor * expr_reg = expr_ast.get_reg();
		CHECK_INVARIANT(expr_reg, "expr register cannot be null in return statement");
		Register_Addr_Opd * expr_opd = new Register_Addr_Opd(expr_reg);

		if((*it)->get_data_type() == int_data_type) {
			offset -= 4;
			Icode_Stmt * curr_stmt = new Parameter_Store_Stmt(store, expr_opd, sp_opd, offset);
			ic_list.push_back(curr_stmt);
		} else {
			offset -= 8;
			Icode_Stmt * curr_stmt = new Parameter_Store_Stmt(store_d, expr_opd, sp_opd, offset);
			ic_list.push_back(curr_stmt);
		}
		expr_reg->reset_use_for_expr_result();
	}
	Const_Opd<int> * offset_opd = new Const_Opd<int>(-1*offset);
	if(offset != 0) {
		Icode_Stmt* compute_stmt = new Compute_IC_Stmt(sub, sp_opd, sp_opd, offset_opd);
		ic_list.push_back(compute_stmt);
	}
	Control_Flow_IC_Stmt * control_stmt = new Control_Flow_IC_Stmt(jal, NULL, NULL, proc->get_proc_name());
	ic_list.push_back(control_stmt);
	if(offset != 0) {
		Icode_Stmt* compute_stmt = new Compute_IC_Stmt(add, sp_opd, sp_opd, offset_opd);
		ic_list.push_back(compute_stmt);
	}
	Register_Descriptor* reg;
	if(get_data_type() == void_data_type) {
	} else if(get_data_type() == int_data_type) {
		reg = machine_desc_object.get_new_register<gp_data>();
		Register_Addr_Opd * v1_opd = new Register_Addr_Opd(machine_desc_object.spim_register_table[v1]);
		Register_Addr_Opd * reg_opd = new Register_Addr_Opd(reg);
		Icode_Stmt * curr_stmt = new Move_IC_Stmt(mov, v1_opd, reg_opd);
		ic_list.push_back(curr_stmt);
	} else {
		reg = machine_desc_object.get_new_register<float_reg>();
		Register_Addr_Opd * f0_opd = new Register_Addr_Opd(machine_desc_object.spim_register_table[f0]);
		Register_Addr_Opd * reg_opd = new Register_Addr_Opd(reg);
		Icode_Stmt * curr_stmt = new Move_IC_Stmt(move_d, f0_opd, reg_opd);
		ic_list.push_back(curr_stmt);
	}
	Code_For_Ast * fn_stmt = new Code_For_Ast(ic_list, reg);
	machine_desc_object.clear_local_register_mappings();
	return *fn_stmt;
}