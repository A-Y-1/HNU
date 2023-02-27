%option noyywrap
%{
/*****************声明和选项设置  begin*****************/
#include <stdio.h>
#include <stdlib.h>

#include "lexical_analyzer.h"

int lines;
int pos_start;
int pos_end;

/*****************声明和选项设置  end*****************/

%}
 

%%

 /******************TODO*********************/
 /****请在此补全所有flex的模式与动作  start******/
 //STUDENT TO DO
\+   {pos_start = pos_end; pos_end++; return ADD;}
\-   {pos_start = pos_end; pos_end++; return SUB;}
\*   {pos_start = pos_end; pos_end++; return MUL;}
\/   {pos_start = pos_end; pos_end++; return DIV;}
\<   {pos_start = pos_end; pos_end++; return LT;}
"<=" {pos_start = pos_end; pos_end+=2; return LTE;}
\>   {pos_start = pos_end; pos_end++; return GT;}
">=" {pos_start = pos_end; pos_end+=2; return GTE;}
"==" {pos_start = pos_end; pos_end+=2; return EQ;}	
"!=" {pos_start = pos_end; pos_end+=2; return NEQ;}
\=   {pos_start = pos_end; pos_end++; return ASSIN;}
\;   {pos_start = pos_end; pos_end++; return SEMICOLON;}
\,   {pos_start = pos_end; pos_end++; return COMMA;}
\(  {pos_start = pos_end; pos_end++; return LPARENTHESE;}
\)  {pos_start = pos_end; pos_end++; return RPARENTHESE;}
\[  {pos_start = pos_end; pos_end++; return LBRACKET;}
\]  {pos_start = pos_end; pos_end++; return RBRACKET;}
\{  {pos_start = pos_end; pos_end++; return LBRACE;}
\}  {pos_start = pos_end; pos_end++; return RBRACE;}
else {pos_start = pos_end; pos_end+=4; return ELSE;}
if   {pos_start = pos_end; pos_end+=2; return IF;}
int  {pos_start = pos_end; pos_end+=3; return INT;}
float {pos_start = pos_end; pos_end+=5; return FLOAT;}
return {pos_start = pos_end; pos_end+=6; return RETURN;}
void   {pos_start = pos_end; pos_end+=4; return VOID;}
while  {pos_start = pos_end; pos_end+=5; return WHILE;}
[a-zA-Z]+ {pos_start = pos_end; pos_end+=strlen(yytext); return IDENTIFIER;}
[a-zA-Z]  {pos_start = pos_end; pos_end++; return LETTER;}  
[0-9]+    {pos_start = pos_end; pos_end+=strlen(yytext); return INTEGER;}
[0-9]+\.|[0-9]*\.[0-9]+ {pos_start = pos_end; pos_end+=strlen(yytext); return FLOATPOINT;}
"[]" {pos_start = pos_end; pos_end+=2; return ARRAY;}
\n  {return EOL;} 
"/*"([^*]|\*+[^*/])*\*+"/"  {return COMMENT;}
[" "|\t] {pos_start = pos_end; pos_end+=strlen(yytext);return BLANK;}
. {pos_start = pos_end; pos_end+=strlen(yytext); return ERROR;}




 /****请在此补全所有flex的模式与动作  end******/
%%
/****************C代码 start*************/

/// \brief analysize a *.cminus file
///
/// \param input_file, 需要分析的文件路径
/// \param token stream, Token_Node结构体数组，用于存储分析结果，具体定义参考lexical_analyer.h

void analyzer(char* input_file, Token_Node* token_stream){
    lines = 1;
    pos_start = 1;
    pos_end = 1;
    if(!(yyin = fopen(input_file,"r"))){
        printf("[ERR] No input file\n");
        exit(1);
    }
    printf("[START]: Read from: %s\n", input_file);

    int token;
    int index = 0;
    int len;
    while(token = yylex()){
        switch(token){
            case COMMENT:
                len = strlen(yytext);
                for(int i=0;i<len;i++){
                    if(yytext[i]=='\n') {
                        lines++;
                        pos_end = 1;	//pos_start由pos_end得到，这里就不需要置1了
                    }
                    else pos_end++;
                }
                break;
            case BLANK:
                break;
            case EOL:
                lines++;
                pos_end = 1;
                break;
            case ERROR:
                printf("[ERR]: unable to analysize %s at %d line, from %d to %d\n", yytext, lines, pos_start, pos_end);
            default :
                if (token == ERROR){
                    sprintf(token_stream[index].text, "[ERR]: unable to analysize %s at %d line, from %d to %d", yytext, lines, pos_start, pos_end);
                } else {
                    strcpy(token_stream[index].text, yytext);
                }
                token_stream[index].token = token;
                token_stream[index].lines = lines;
                token_stream[index].pos_start = pos_start;
                token_stream[index].pos_end = pos_end;
                index++;
                if (index >= MAX_NUM_TOKEN_NODE){
                    printf("%s has too many tokens (> %d)", input_file, MAX_NUM_TOKEN_NODE);
                    exit(1);
                }
        }
    }
    printf("[END]: Analysis completed.\n");
    return;
}



/****************C代码 end*************/
