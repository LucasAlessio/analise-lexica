#define TKId 1
#define TKVoid 2
#define TKInt 3
#define TKFloat 4
#define TKVirgula 5
#define TKDoisPontos 6
#define TKAbreParenteses 7
#define TKFechaParenteses 8
#define TKAtrib 9
#define TKPontoEVirgula 10
#define TKAbreChaves 11
#define TKFechaChaves 12
#define TKSoma 13
#define TKDuploMais 14
#define TKProd 15
#define TKChar 16
#define TKSub 17
#define TKVolatile 18
#define TKDouble 19
#define TKFimArquivo 20
#define TKAndBit 21
#define TKAndLogico 22
#define TKShort 23
#define TKLong 24
#define TKIf 25
#define TKElse 26
#define TKWhile 27
#define TKDo 28
#define TKFor 29
#define TKContinue 30
#define TKSwitch 31
#define TKCase 32
#define TKBreak 33
#define TKDefault 34
#define TKGoto 35
#define TKReturn 36
#define TKStruct 37
#define TKTypedef 38
#define TKMaiorQue 39
#define TKMenorQue 40
#define TKMaiorIgual 41
#define TKMenorIgual 42
#define TKDeslocamentoEsq 43
#define TKDeslocamentoDir 44
#define TKDuploMenos 45
#define TKDuploIgual 46

#define false 0
#define true 1

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
int pos = 0;

int tk;
char lex[20];
FILE *arqin;
char c; // �ltimo caracter lido do arquivo

struct pal_res {
	char palavra[20];
	int tk;
};

struct pal_res lista_pal[] = {
	{"void", TKVoid},
	{"short", TKShort},
	{"int", TKInt},
	{"long", TKLong},
	{"float", TKFloat},
	{"double", TKDouble},
	{"if", TKIf},
	{"else", TKElse},
	{"while", TKWhile},
	{"do", TKDo},
	{"for", TKFor},
	{"continue", TKContinue},
	{"switch", TKSwitch},
	{"case", TKCase},
	{"break", TKBreak},
	{"default", TKDefault},
	{"goto", TKGoto},
	{"return", TKReturn},
	{"struct", TKStruct},
	{"typedef", TKTypedef},
	{"fimtabela", TKId}
};

int palavra_reservada(char lex[]) {
	int postab=0;
	
	while (strcmp("fimtabela", lista_pal[postab].palavra) != 0) {
		if (strcmp(lex,lista_pal[postab].palavra) == 0)
			return lista_pal[postab].tk;
		
		postab++;
	}
	
	return TKId;
}


void getToken(); // prot�tipos
void proxC();

// vari�veis globais para retrocesso

long int posglobal;
int linha = 0, coluna = 0;

void proxC() {
	if (feof(arqin)) {
		c = -1;
		//printf("Chegou no fim de arquivo\n");
		return;
   }
	fread(&c, 1, 1, arqin);
	
	if (c == '\t') {
		coluna += 4;
	}
	else {
		coluna++;
	}

	if (c == '\n') {
		coluna = 0;
		linha++;		
	}
	//printf("Leu caracter %c\n",c);
}

void getToken() {
	int estado=0,
    fim=0,
    posl=0;
	
	while (!fim) {
		/* printf("%s\n",exp1);
		printf("char=%c pos=%d\n", c, pos);*/
		lex[posl++] = c;
		
		switch(estado) {
			case 0:
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_') {
					proxC();
					estado = 1;
					break;
				}
             	if (c == '=') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKDuploIgual; /*printf("Reconheceu token TKDuploIgual\n");*/
						return;
					}
					else {
						lex[posl] = '\0';
						proxC();
						tk = TKAtrib; /*printf("Reconheceu token TKAtrib\n");*/
						return;
					}
				}
				if (c == '+') {
			    	proxC();
					if (c == '+') {
						lex[posl++] = '+';
						lex[posl] = '\0';
						proxC();
						tk = TKDuploMais; /*printf("Reconheceu token TKDuploMais\n");*/
						return;
					} else {
						lex[posl] = '\0';
						tk = TKSoma; /*printf("Reconheceu token TKSoma\n");*/
						return;
					}
				}
				if (c == '-') {
			    	proxC();
					if (c == '-') {
						lex[posl++] = '-';
						lex[posl] = '\0';
						proxC();
						tk = TKDuploMenos; /*printf("Reconheceu token TKDuploMenos\n");*/
						return;
					} else {
						lex[posl] = '\0';
						tk = TKSub; /*printf("Reconheceu token TKSub\n");*/
						return;
					}
				}
				if (c == '&') {
			    	proxC();
					if (c == '&') {
						lex[posl++] = '&';
						lex[posl] = '\0';
						proxC();
						tk = TKAndLogico; /*printf("Reconheceu token TKDuploMais\n");*/
						return;
					} else {
						lex[posl] = '\0';
						tk = TKAndBit; /*printf("Reconheceu token TKSoma\n");*/
						return;
					}
				}
				if (c == '>') {
			    	proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKMaiorIgual; /*printf("Reconheceu token TKMaiorIgual\n");*/
						return;
					} else {
						if (c == '>') {
							lex[posl++] = '>';
							lex[posl] = '\0';
							proxC();
							tk = TKDeslocamentoDir; /*printf("Reconheceu token TKDeslocamentoDir\n");*/
							return;
						}
						else {
							lex[posl] = '\0';
							tk = TKMaiorQue; /*printf("Reconheceu token TKMaiorQue\n");*/
							return;
						}
					}
				}
				if (c == '<') {
			    	proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKMaiorIgual; /*printf("Reconheceu token TKMenorIgual\n");*/
						return;
					} else {
						if (c == '<') {
							lex[posl++] = '<';
							lex[posl] = '\0';
							proxC();
							tk = TKDeslocamentoDir; /*printf("Reconheceu token TKDeslocamentoEsq\n");*/
							return;
						}
						else {
							lex[posl] = '\0';
							tk = TKMaiorQue; /*printf("Reconheceu token TKMenorQue\n");*/
							return;
						}
					}
				}
				if (c == '*') { lex[posl]='\0'; proxC(); tk = TKProd; /*printf("Reconheceu token TKProd\n");*/ return; }
				if (c == '(') { lex[posl]='\0'; proxC(); tk = TKAbreParenteses; /*printf("Reconheceu token TKAbrePar\n");*/ return; }
				if (c == ')') { lex[posl]='\0'; proxC(); tk = TKFechaParenteses; /*printf("Reconheceu token FechaPar\n");*/ return; }
				if (c == '&') { lex[posl]='\0'; proxC(); tk = TKAndBit; /*printf("Reconheceu token TKAndBit\n");*/ return; }
				if (c == '{') { lex[posl]='\0'; proxC(); tk = TKAbreChaves; /*printf("Reconheceu token TKAbreChaves\n");*/ return; }
				if (c == '}') { lex[posl]='\0'; proxC(); tk = TKFechaChaves; /*printf("Reconheceu token TKFechaChaves\n");*/ return; }
				if (c == ',') { lex[posl]='\0'; proxC(); tk = TKVirgula; /*printf("Reconheceu token TKVirgula\n");*/ return; }
				if (c == ';') { lex[posl]='\0'; proxC(); tk = TKPontoEVirgula; /*printf("Reconheceu token TKPontoEVirgula\n");*/ return; }
				if (c == ':') { lex[posl]='\0'; proxC(); tk = TKDoisPontos; /*printf("Reconheceu token TKDoisPontos\n");*/ return; }
				if (c == -1) { lex[posl]='\0'; proxC(); tk = TKFimArquivo; /*printf("Reconheceu token TKFimArquivo\n");*/ return; }
				if (c == ' ' || c == '\n' || c == '\t' || c == '\r') { proxC(); posl--; break; }
				if (c == '\0') { tk = -1; return; }
				printf("\nErro lexico: caractere inesperado %c (%d) na linha %d e coluna %d\n", c, c, linha + 1, coluna);
				tk = TKFimArquivo;
				return;

			case 1:
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_' || c >= '0' && c <= '9') {
					proxC();
					break;
				}
				lex[--posl] = '\0';
				tk = palavra_reservada(lex);
				//printf("reconheceu token %s\n",lex);
				return;
		} //switch
	} // while
} // fun��o

int strlenInt(int n) {
	int len = 1;
	
	while(n > 9){
		len++;
		n /= 10;
	}

	return len;
}

int main() {
	arqin = fopen("prog.c", "rb");
	
	if (!arqin) {
		printf("Erro na abertura do fonte.\n");
		return 0;
	}

	proxC(); // l� primeiro caracter do arquivo
	getToken(); // l� primeiro token
	
	if (tk != TKFimArquivo) {	
		printf("%s%*.*s", "Token", 20 - strlen("Token"), 20 - strlen("Token"), " ");
		printf("%s%*.*s", "Lexema", 10 - strlen("Lexema"), 10 - strlen("Lexema"), " ");
		printf("%s%*.*s", "Linha", 9 - strlen("Linha"), 9 - strlen("Linha"), " ");
		printf("%s%*.*s\n", "Coluna", 10 - strlen("Coluna"), 10 - strlen("Coluna"), " ");
		
		int i;
		for (i = 0; i < 45; i++) {
			printf("%c", 205);
		}
		
		printf("\n", 205);
	}
	
	while (tk != TKFimArquivo) {		
		printf("%s%*.*s", lex, 20 - strlen(lex), 20 - strlen(lex), " ");
		printf("%*.*s%d", 6 - strlenInt(tk), 6 - strlenInt(tk), " ", tk);
		printf("%*.*s%d", 9 - strlenInt(linha + 1), 9 - strlenInt(linha + 1), " ", linha + 1);
		printf("%*.*s%d\n", 10 - strlenInt(coluna - strlen(lex)), 10 - strlenInt(coluna - strlen(lex)), " ", coluna - strlen(lex));
		
		getToken();
	}
	
	printf("\n");
	
	fclose(arqin);
	system("pause");
}
