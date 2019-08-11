%{
    #include "parser.tab.h"
    #include "storetokens.hh"
%}

float ([0-9]*\.[0-9]+|[0-9]+\.)
integer [0-9]+
name [a-zA-Z_]+[a-zA-Z0-9_]*
symbols [;:,\(\)\{\}?]
operator [-+*/]
greater >
less <
lte <=
gte >=
ee ==
ne !=
and &&
or "||"
not !
void void
int_id int
float_id float
return_id return
assign =
endl \n
ws [ \t]+
comment \/\/.*
while while
do do
if if
else else
print print
main main

%%
{endl} {
    yylineno++;
}
{ws} {

}
{comment} {

}
{symbols} {
    store_token_name("META CHAR", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return yytext[0];
}
{greater} {
    store_token_name("GREATER_THAN", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return GREATER_THAN;
}
{less} {
    store_token_name("LESS_THAN", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return LESS_THAN;
}
{lte} {
    store_token_name("LESS_THAN_EQUAL", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return LESS_THAN_EQUAL;
}
{gte} {
    store_token_name("GREATER_THAN_EQUAL", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return GREATER_THAN_EQUAL;
}
{ee} {
    store_token_name("EQUAL", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return EQUAL;
}
{ne} {
    store_token_name("NOT_EQUAL", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return NOT_EQUAL;
}
{and} {
    store_token_name("AND", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return AND;
}
{or} {
    store_token_name("OR", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return OR;
}
{not} {
    store_token_name("NOT", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return NOT;
}
{integer} {
    store_token_name("NUM", yytext, yylineno);
    yylval.integer_value=atoi(yytext);
    return INTEGER_NUMBER;
}
{float} {
    store_token_name("FNUM", yytext, yylineno);
    yylval.double_value=atof(yytext);
    return DOUBLE_NUMBER;
}
{operator} {
    store_token_name("ARITHOP", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return yytext[0];
}
{assign} {
    store_token_name("ASSIGN_OP", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return ASSIGN;
}
{void} {
    store_token_name("VOID", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return VOID;
}
{main} {
    store_token_name("NAME", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return NAME;
}
{int_id} {
    store_token_name("INTEGER", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return INTEGER;
}
{float_id} {
    store_token_name("FLOAT", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return FLOAT;
}
{return_id} {
    store_token_name("RETURN", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return RETURN;
}
{while} {
    store_token_name("WHILE", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return WHILE;
}
{if} {
    store_token_name("IF", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return IF;
}
{else} {
    store_token_name("ELSE", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return ELSE;
}
{do} {
    store_token_name("DO", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return DO;
}
{print} {
    store_token_name("PRINT", yytext, yylineno);
    yylval.string_value=new std::string(yytext);
    return PRINT;
}
{name} {
    store_token_name("NAME", yytext, yylineno);
    yylval.string_value=new std::string(strcat(yytext, "_"));
    return NAME;
}
.	{
	printf("CS316: Error: Scanning error\n");
    exit(0);

}
%%