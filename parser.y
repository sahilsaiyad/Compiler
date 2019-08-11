%{
	#include <stdio.h>
	#include <string>
	#include <list>
	extern "C" void yyerror(const char *s);
	extern int yylex(void);
	extern "C" int yylineno;
	Symbol_Table l_symbol_table;
	Symbol_Table g_symbol_table;
%}

%union {
	int integer_value;
	std::string *string_value;
	double double_value;
	list<Ast *> *ast_list;
	Ast *ast;
	Symbol_Table *symbol_table;
	Symbol_Table_Entry *symbol_entry;
	Basic_Block *basic_block;
	Procedure *procedure;
	list<Symbol_Table_Entry *> *symbol_table_entry_list;
}

%token AND
%token OR
%token NOT
%token NOT_EQUAL
%token GREATER_THAN
%token LESS_THAN
%token GREATER_THAN_EQUAL
%token LESS_THAN_EQUAL
%token EQUAL 
%token WHILE
%token IF
%token ELSE
%token DO
%token INTEGER_NUMBER
%token RETURN
%token DOUBLE_NUMBER
%token ASSIGN
%token VOID
%token INTEGER
%token FLOAT
%token NAME
%token PRINT

%left '?' ':'
%left OR
%left AND
%left EQUAL NOT_EQUAL
%left GREATER_THAN_EQUAL LESS_THAN_EQUAL GREATER_THAN LESS_THAN
%left '+' '-' 
%left '*' '/'
%left NOT
%type<string_value> NAME
%type<ast> variable constant assignment_statement E B R stmt matched_stmt unmatched_stmt other_stmt while_loop  do_while print_stmt
%type<ast_list> statement_list
%type<integer_value> INTEGER_NUMBER
%type<double_value> DOUBLE_NUMBER
%type<procedure> procedure_definition
%type<symbol_table> global_optional_variable_declaration_list global_declaration global_variable_declaration global_variable_declaration_list local_optional_variable_declaration_list local_declaration local_variable_declaration local_variable_declaration_list declaration_list
%type<symbol_table_entry_list> variable_list
%%

program : declaration_list 
		  procedure_definition
		  {
		  		program_object.set_global_table(*$1);
		  		program_object.set_procedure($2, yylineno);
		  }
		;

declaration_list : global_optional_variable_declaration_list
				   {
				   		$1->set_table_scope(global);
				   		$$ = $1;
				   }

procedure_definition : VOID NAME '(' ')'
                  	   '{'
					   		local_optional_variable_declaration_list
	                        statement_list
        	           	'}'
        	           	{
        	           		$$ = new Procedure(void_data_type, *$2, yylineno);
        	           		$6->set_table_scope(local); 
        	           		$$->set_local_list(*$6);
        	           		$$->set_ast_list(*$7);
        	           	}


global_optional_variable_declaration_list : %empty
									{
										$$ = new Symbol_Table();
									}
								    | global_variable_declaration_list
								    {
								    	$$ = $1;
								    }
								   ;

local_optional_variable_declaration_list : %empty
									{
										$$ = new Symbol_Table();
									}
								   | local_variable_declaration_list
								    {
								    	$$ = $1;
								    }
								   ;

global_variable_declaration_list :	global_variable_declaration
							{
								$$ = $1;
							}
						  |	global_variable_declaration_list 
							global_variable_declaration
							{
								$1->append_list(*$2,yylineno);
								$$ = $1;
							}
                          ;

local_variable_declaration_list :	local_variable_declaration
							{
								$$ = $1;
							}
						  |	local_variable_declaration_list 
							local_variable_declaration
							{
								$1->append_list(*$2,yylineno);
								$$ = $1;
							}
                          ;
                          
global_variable_declaration : global_declaration ';'
					{
						$$ = $1;
					}
					;

local_variable_declaration : local_declaration ';'
					{
						$$ = $1;
					}
					;

global_declaration : INTEGER variable_list
			  {
			  		$$ = new Symbol_Table();
			  		list<Symbol_Table_Entry *>::iterator it;
					for (it = $2->begin(); it != $2->end(); it++) {
    					(*it)->set_data_type(int_data_type);
    					$$->push_symbol(*it);
    					g_symbol_table.push_symbol(*it);
					}
			  }
			| FLOAT variable_list
			  {
			  		$$ = new Symbol_Table();
			  		list<Symbol_Table_Entry *>::iterator it;
					for (it = $2->begin(); it != $2->end(); it++) {
    					(*it)->set_data_type(double_data_type);
    					$$->push_symbol(*it);
    					g_symbol_table.push_symbol(*it);
					}
			  }
			;

local_declaration : INTEGER variable_list
			  {
			  		$$ = new Symbol_Table();
			  		list<Symbol_Table_Entry *>::iterator it;
					for (it = $2->begin(); it != $2->end(); it++) {
    					(*it)->set_data_type(int_data_type);
    					$$->push_symbol(*it);
    					l_symbol_table.push_symbol(*it);
					}
			  }
			| FLOAT variable_list
			  {
			  		$$ = new Symbol_Table();
			  		list<Symbol_Table_Entry *>::iterator it;
					for (it = $2->begin(); it != $2->end(); it++) {
    					(*it)->set_data_type(double_data_type);
    					$$->push_symbol(*it);
    					l_symbol_table.push_symbol(*it);
					}
			  }
			;

variable_list : NAME
				{
					$$ = new list<Symbol_Table_Entry *>();
					Symbol_Table_Entry *var_entry = new Symbol_Table_Entry(*$1, int_data_type,yylineno);
					$$->push_back(var_entry);

				}
			  | variable_list ',' NAME
			    {
			  		Symbol_Table_Entry *var_entry = new Symbol_Table_Entry(*$3, int_data_type, yylineno);
			  		$$->push_back(var_entry);
			    }		
			  ;

statement_list : %empty
				 {
				 	$$ = new list<Ast *>;
				 }
				 | statement_list
				   stmt
				   {
				   		$1->push_back($2);
				   		$$ = $1;
				   }
			   ;

assignment_statement : variable ASSIGN E ';'
				{
			   		Assignment_Ast *e_ast = new Assignment_Ast($1, $3, yylineno);
			   		e_ast->set_data_type($1->get_data_type());
			   		e_ast->check_ast();
			   		$$ = e_ast;
				}
		    	;

E : E '+' E
	{
		$$ = new Plus_Ast($1, $3, yylineno);
		$$->set_data_type($1->get_data_type());
		$$->check_ast();

	}
  | E '-' E
  {
  		$$ = new Minus_Ast($1, $3, yylineno);
  		$$->set_data_type($1->get_data_type());
  		$$->check_ast();
  }
  | E '*' E
  {
  		$$ = new Mult_Ast($1, $3, yylineno);
  		$$->set_data_type($1->get_data_type());
  		$$->check_ast();
  }
  | E '/' E
  {
  		$$ = new Divide_Ast($1, $3, yylineno);
  		$$->set_data_type($1->get_data_type());
  		$$->check_ast();
  }
  | variable
  {
  		$$ = $1;
  }
  | constant
  {
  		$$ = $1;
  }
  | '(' E ')'
  {
  		$$ = $2;
  }
  | '-' variable
  {
  		$$ = new UMinus_Ast($2, NULL, yylineno);
  		$$->set_data_type($2->get_data_type());
  }
  | '-' '(' E ')'
  {
  		$$ = new UMinus_Ast($3, NULL, yylineno);
  		$$->set_data_type($3->get_data_type());
  }
  | '-' constant
  {
  		$$ = new UMinus_Ast($2, NULL, yylineno);
  		$$->set_data_type($2->get_data_type());
  }
  | B '?' E ':' E
	{
		$$ = new Conditional_Expression_Ast($1, $3, $5, yylineno);
		if ($$->check_ast()) {
			$$->set_data_type($3->get_data_type());
		} else {
			printf("cs316: Error\n");
			exit(0);
		}
	}
  ;

R : E LESS_THAN E
{
	$$ = new Relational_Expr_Ast($1, less_than, $3, yylineno);
	$$->set_data_type($1->get_data_type());
	$$->check_ast();
}
| E GREATER_THAN E
{
	$$ = new Relational_Expr_Ast($1, greater_than, $3, yylineno);
	$$->set_data_type($1->get_data_type());
	$$->check_ast();  		
}
| E LESS_THAN_EQUAL E
{
	$$ = new Relational_Expr_Ast($1, less_equalto, $3, yylineno);
	$$->set_data_type($1->get_data_type());
	$$->check_ast();  		
}
| E GREATER_THAN_EQUAL E
{
	$$ = new Relational_Expr_Ast($1, greater_equalto, $3, yylineno);
	$$->set_data_type($1->get_data_type());
	$$->check_ast();  		
}
| E EQUAL E
{
	$$ = new Relational_Expr_Ast($1, equalto, $3, yylineno);
	$$->set_data_type($1->get_data_type());
	$$->check_ast();  		
}
| E NOT_EQUAL E
{
	$$ = new Relational_Expr_Ast($1, not_equalto, $3, yylineno);
	$$->set_data_type($1->get_data_type());
	$$->check_ast();  		
}


B : B AND B
{
  	$$ = new Logical_Expr_Ast($1, _logical_and, $3, yylineno);
 	$$->set_data_type($1->get_data_type());
	$$->check_ast(); 		
}
| B OR B
{
	$$ = new Logical_Expr_Ast($1, _logical_or, $3, yylineno);
 	$$->set_data_type($1->get_data_type());
	$$->check_ast();
}
| R
{
	$$ = $1;
}
| NOT B
{
	$$ = new Logical_Expr_Ast(NULL, _logical_not, $2, yylineno);
	$$->set_data_type($2->get_data_type());
}
| '(' B ')'
{
  	$$ = $2;
} 
;

variable : NAME
		{
		   	Name_Ast *n_ast;
			if(!g_symbol_table.variable_in_symbol_list_check(*$1) && !l_symbol_table.variable_in_symbol_list_check(*$1))	
			{
				fprintf(stderr,"No variable was declared with this name \n");
			}
			else
			{
				if(g_symbol_table.variable_in_symbol_list_check(*$1))
				{
					n_ast = new Name_Ast(*$1,g_symbol_table.get_symbol_table_entry(*$1) ,yylineno);
                	n_ast->set_data_type((g_symbol_table.get_symbol_table_entry(*$1)).get_data_type());
				}
				if(l_symbol_table.variable_in_symbol_list_check(*$1))
				{ 
                	n_ast = new Name_Ast(*$1,l_symbol_table.get_symbol_table_entry(*$1) ,yylineno);
                	n_ast->set_data_type((l_symbol_table.get_symbol_table_entry(*$1)).get_data_type());
                }
                $$ = n_ast;
			}
		}
	;

constant : INTEGER_NUMBER
		   {
		   		$$ = new Number_Ast<int>($1, int_data_type, yylineno);
		   		$$->set_data_type(int_data_type); 
		   }
		 | DOUBLE_NUMBER
		   {
		   		$$ = new Number_Ast<double>($1, double_data_type, yylineno);
		   		$$->set_data_type(double_data_type);
		   }
		 ;

stmt : matched_stmt
	{
		$$ = $1;
	}
	| unmatched_stmt
	{
		$$ = $1;
	}
	| while_loop
	{
		$$ = $1;
	}
	| do_while
	{
		$$ = $1;
	};

matched_stmt : IF B matched_stmt ELSE matched_stmt
		{
			$$ = new Selection_Statement_Ast($2, $3, $5, yylineno);
			$$->set_data_type(void_data_type);
		}
		| other_stmt
		{
			$$ = $1;
		};

unmatched_stmt : IF B stmt
			{
				$$ = new Selection_Statement_Ast($2, $3, NULL, yylineno);
				$$->set_data_type(void_data_type);
			}
			|
			IF B matched_stmt ELSE unmatched_stmt
			{
				$$ = new Selection_Statement_Ast($2, $3, $5, yylineno);
				$$->set_data_type(void_data_type);
			};

other_stmt : '{' statement_list '}'
		{
			Sequence_Ast * temp = new Sequence_Ast(yylineno);
			for(list<Ast *>::iterator it=$2->begin();it!=$2->end();it++){
				temp->ast_push_back(*it);
			}
			$$=temp;
		}
		| assignment_statement
		{
			$$ = $1;
		}
		| print_stmt
		{
			$$ = $1;
		};

print_stmt : PRINT NAME ';'
		{
			Name_Ast *n_ast;
			if(!g_symbol_table.variable_in_symbol_list_check(*$2) && !l_symbol_table.variable_in_symbol_list_check(*$2))	
			{
				fprintf(stderr,"No variable was declared with this name \n");
			}
			else
			{
				if(g_symbol_table.variable_in_symbol_list_check(*$2))
				{
					n_ast = new Name_Ast(*$2,g_symbol_table.get_symbol_table_entry(*$2) ,yylineno);
                	n_ast->set_data_type((g_symbol_table.get_symbol_table_entry(*$2)).get_data_type());
				}
				if(l_symbol_table.variable_in_symbol_list_check(*$2))
				{ 
                	n_ast = new Name_Ast(*$2,l_symbol_table.get_symbol_table_entry(*$2) ,yylineno);
                	n_ast->set_data_type((l_symbol_table.get_symbol_table_entry(*$2)).get_data_type());
                }
                $$ = new Print_Ast(n_ast, yylineno);
			}
		};

do_while : DO stmt WHILE B ';'
	{
		$$ = new Iteration_Statement_Ast($4, $2, yylineno, 1);
		$$->set_data_type(void_data_type);
	};

while_loop : WHILE B stmt
		{
			$$ = new Iteration_Statement_Ast($2, $3, yylineno, 0);
			$$->set_data_type(void_data_type);
		};

%%
void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
}