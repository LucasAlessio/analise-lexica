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
#define TKDiv 47
#define TKMaisIgual 48
#define TKMenosIgual 49
#define TKProdIgual 50
#define TKDivIgual 51
#define TKAbreColchetes 52
#define TKFechaColchetes 53
#define TKRestoDiv 54
#define TKRestoDivIgual 55
#define TKOrBit 56
#define TKXorBit 57
#define TKNotBit 58
#define TKAndBitIgual 59
#define TKOrBitIgual 60
#define TKXorBitIgual 61
#define TKNotBitIgual 62
#define TKNegacaoLogica 63
#define TKDiferenteLogico 64
#define TKConstInt 65
#define TKPonto 66
#define TKSeta 67
#define TKOrLogico 68

#define false 0
#define true 1

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
int pos = 0;

int tk;
char tkD[20];
char lex[20];
FILE *arqin;
FILE *arqout;
char c; // último caracter lido do arquivo

struct pal_res {
	char palavra[20];
	int tk;
	char tkD[20];
};

struct pal_res lista_pal[] = {
	{"void", TKVoid, "TKVoid"},
	{"short", TKShort, "TKShort"},
	{"char", TKChar, "TKChar"},
	{"int", TKInt, "TKInt"},
	{"long", TKLong, "TKLong"},
	{"float", TKFloat, "TKFloat"},
	{"double", TKDouble, "TKDouble"},
	{"if", TKIf, "TKIf"},
	{"else", TKElse, "TKElse"},
	{"while", TKWhile, "TKWhile"},
	{"do", TKDo, "TKDo"},
	{"for", TKFor, "TKFor"},
	{"continue", TKContinue, "TKContinue"},
	{"switch", TKSwitch, "TKSwitch"},
	{"case", TKCase, "TKCase"},
	{"break", TKBreak, "TKBreak"},
	{"default", TKDefault, "TKDefault"},
	{"goto", TKGoto, "TKGoto"},
	{"return", TKReturn, "TKReturn"},
	{"struct", TKStruct, "TKStruct"},
	{"typedef", TKTypedef, "TKTypedef"},
	{"fimtabela", TKId, "TKId"}
};

int palavra_reservada(char lex[]) {
	int postab=0;
	
	while (strcmp("fimtabela", lista_pal[postab].palavra) != 0) {
		if (strcmp(lex, lista_pal[postab].palavra) == 0) {
			strcpy(tkD, lista_pal[postab].tkD);
			return lista_pal[postab].tk;
		}
		
		postab++;
	}
	
	strcpy(tkD, "TKId");
	return TKId;
}


void getToken(); // protótipos
void proxC();

// variáveis globais para retrocesso

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
	// printf("Leu caracter %c\n",c);
}

void getToken() {
	int estado=0,
	fim=0,
	posl=0;
	
	while (!fim) {
		/* printf("%s\n",exp1);
		printf("char=%c pos=%d\n", c, pos); */
		lex[posl++] = c;
		
		switch(estado) {
			case 0:
				if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '_') {
					proxC();
					estado = 1;
					break;
				}
				if (c >= '0' && c <= '9') {
					proxC();
                    estado = 2;
					break;
                }
				if (c == '=') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKDuploIgual; /* printf("Reconheceu token TKDuploIgual\n"); */
						strcpy(tkD, "TKDuploIgual");
						return;
					} else {
						lex[posl] = '\0';
						proxC();
						tk = TKAtrib; /* printf("Reconheceu token TKAtrib\n"); */
						strcpy(tkD, "TKAtrib");
						return;
					}
				}
				if (c == '&') {
					proxC();
					if (c == '&') {
						lex[posl++] = '&';
						lex[posl] = '\0';
						proxC();
						tk = TKAndLogico; /* printf("Reconheceu token TKAndLogico\n"); */
						strcpy(tkD, "TKAndLogico");
						return;
					} else {
						if (c == '=') {
							lex[posl++] = '=';
							lex[posl] = '\0';
							proxC();
							tk = TKAndLogico; /* printf("Reconheceu token TKAndLogico\n"); */
							strcpy(tkD, "TKAndLogico");
							return;
						} else {
							lex[posl] = '\0';
							tk = TKAndBit; /* printf("Reconheceu token TKAndBit\n"); */
							strcpy(tkD, "TKAndBit");
							return;	
						}
					}
				}
				if (c == '>') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKMaiorIgual; /* printf("Reconheceu token TKMaiorIgual\n"); */
						strcpy(tkD, "TKMaiorIgual");
						return;
					} else {
						if (c == '>') {
							lex[posl++] = '>';
							lex[posl] = '\0';
							proxC();
							tk = TKDeslocamentoDir; /* printf("Reconheceu token TKDeslocamentoDir\n"); */
							strcpy(tkD, "TKDeslocamentoDir");
							return;
						}
						else {
							lex[posl] = '\0';
							tk = TKMaiorQue; /* printf("Reconheceu token TKMaiorQue\n"); */
							strcpy(tkD, "TKMaiorQue");
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
						tk = TKMenorIgual; /* printf("Reconheceu token TKMenorIgual\n"); */
						strcpy(tkD, "TKMenorIgual");
						return;
					} else {
						if (c == '<') {
							lex[posl++] = '<';
							lex[posl] = '\0';
							proxC();
							tk = TKDeslocamentoEsq; /* printf("Reconheceu token TKDeslocamentoEsq\n"); */
							strcpy(tkD, "TKDeslocamentoEsq");
							return;
						}
						else {
							lex[posl] = '\0';
							tk = TKMenorQue; /* printf("Reconheceu token TKMenorQue\n"); */
							strcpy(tkD, "TKMaiorQue");
							return;
						}
					}
				}
				if (c == '!') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKDiferenteLogico; /* printf("Reconheceu token TKDiferenteLogico\n"); */
						strcpy(tkD, "TKDiferenteLogico");
						return;
					} else {
						lex[posl] = '\0';
						tk = TKNegacaoLogica; /* printf("Reconheceu token TKNegacaoLogica\n"); */
						strcpy(tkD, "TKNegacaoLogica");
						return;
					}
				}
				if (c == '+') {
					proxC();
					if (c == '+') {
						lex[posl++] = '+';
						lex[posl] = '\0';
						proxC();
						tk = TKDuploMais; /* printf("Reconheceu token TKDuploMais\n"); */
						strcpy(tkD, "TKDuploMais");
						return;
					} else {
						if (c == '=') {
							lex[posl++] = '=';
							lex[posl] = '\0';
							proxC();
							tk = TKMaisIgual; /* printf("Reconheceu token TKMaisIgual\n"); */
							strcpy(tkD, "TKMaisIgual");
							return;
						} else {
							lex[posl] = '\0';
							tk = TKSoma; /* printf("Reconheceu token TKSoma\n"); */
							strcpy(tkD, "TKSoma");
							return;
						}
					}
				}
				if (c == '-') {
					proxC();
					if (c == '-') {
						lex[posl++] = '-';
						lex[posl] = '\0';
						proxC();
						tk = TKDuploMenos; /* printf("Reconheceu token TKDuploMenos\n"); */
						strcpy(tkD, "TKDuploMenos");
						return;
					} else {
						if (c == '=') {
							lex[posl++] = '=';
							lex[posl] = '\0';
							proxC();
							tk = TKMenosIgual; /* printf("Reconheceu token TKMenosIgual\n"); */
							strcpy(tkD, "TKMenosIgual");
							return;
						} else {
							if (c == '>') {
								lex[posl++] = '>';
								lex[posl] = '\0';
								proxC();
								tk = TKSeta; /* printf("Reconheceu token TKMenosIgual\n"); */
								strcpy(tkD, "TKSeta");
								return;
							} else {
								lex[posl] = '\0';
								tk = TKSub; /* printf("Reconheceu token TKSub\n"); */
								strcpy(tkD, "TKSub");
								return;
							}
						}
					}
				}
				if (c == '*') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKProdIgual; /* printf("Reconheceu token TKProdIgual\n"); */
						strcpy(tkD, "TKProdIgual");
						return;
					} else {
						lex[posl] = '\0';
						tk = TKProd; /* printf("Reconheceu token TKProd\n"); */
						strcpy(tkD, "TKProd");
						return;
					}
				}
				if (c == '/') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKDivIgual; /* printf("Reconheceu token TKProdIgual\n"); */
						strcpy(tkD, "TKDivIgual");
						return;
					} else {
						lex[posl] = '\0';
						tk = TKDiv; /* printf("Reconheceu token TKProd\n"); */
						strcpy(tkD, "TKDiv");
						return;
					}
				}
				if (c == '%') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKRestoDivIgual; /* printf("Reconheceu token TKRestoDivIgual\n"); */
						strcpy(tkD, "TKRestoDivIgual");
						return;
					} else {
						lex[posl] = '\0';
						tk = TKRestoDiv; /* printf("Reconheceu token TKRestoDiv\n"); */
						strcpy(tkD, "TKRestoDiv");
						return;
					}
				}
				if (c == '|') {
					proxC();
					if (c == '|') {
						lex[posl++] = '|';
						lex[posl] = '\0';
						proxC();
						tk = TKOrLogico; /* printf("Reconheceu token TKOrBitIgual\n"); */
						strcpy(tkD, "TKOrLogico");
						return;
					} else {
						if (c == '=') {
							lex[posl++] = '=';
							lex[posl] = '\0';
							proxC();
							tk = TKOrBitIgual; /* printf("Reconheceu token TKOrBitIgual\n"); */
							strcpy(tkD, "TKOrBitIgual");
							return;
						} else {
							lex[posl] = '\0';
							tk = TKOrBit; /* printf("Reconheceu token TKOrBit\n"); */
							strcpy(tkD, "TKOrBit");
							return;
						}
					}
				}
				if (c == '^') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKXorBitIgual; /* printf("Reconheceu token TKXorBitIgual\n"); */
						strcpy(tkD, "TKXorBitIgual");
						return;
					} else {
						lex[posl] = '\0';
						tk = TKXorBit; /* printf("Reconheceu token TKXorBit\n"); */
						strcpy(tkD, "TKXorBit");
						return;
					}
				}
				if (c == '~') {
					proxC();
					if (c == '=') {
						lex[posl++] = '=';
						lex[posl] = '\0';
						proxC();
						tk = TKNotBitIgual; /* printf("Reconheceu token TKNotBitIgual\n"); */
						strcpy(tkD, "TKNotBitIgual");
						return;
					} else {
						lex[posl] = '\0';
						tk = TKNotBit; /* printf("Reconheceu token TKNotBit\n"); */
						strcpy(tkD, "TKNotBit");
						return;
					}
				}
				if (c == '(') { lex[posl]='\0'; proxC(); tk = TKAbreParenteses; strcpy(tkD, "TKAbreParenteses"); /* printf("Reconheceu token TKAbrePar\n"); */ return; }
				if (c == ')') { lex[posl]='\0'; proxC(); tk = TKFechaParenteses; strcpy(tkD, "TKFechaParenteses"); /* printf("Reconheceu token FechaPar\n"); */ return; }
				if (c == '[') { lex[posl]='\0'; proxC(); tk = TKAbreColchetes; strcpy(tkD, "TKAbreColchetes"); /* printf("Reconheceu token TKAbreColchetes\n"); */ return; }
				if (c == ']') { lex[posl]='\0'; proxC(); tk = TKFechaColchetes; strcpy(tkD, "TKFechaColchetes"); /* printf("Reconheceu token TKFechaColchetes\n"); */ return; }
				if (c == '{') { lex[posl]='\0'; proxC(); tk = TKAbreChaves; strcpy(tkD, "TKAbreChaves"); /* printf("Reconheceu token TKAbreChaves\n"); */ return; }
				if (c == '}') { lex[posl]='\0'; proxC(); tk = TKFechaChaves; strcpy(tkD, "TKFechaChaves"); /* printf("Reconheceu token TKFechaChaves\n"); */ return; }
				if (c == ',') { lex[posl]='\0'; proxC(); tk = TKVirgula; strcpy(tkD, "TKVirgula"); /* printf("Reconheceu token TKVirgula\n"); */ return; }
				if (c == ';') { lex[posl]='\0'; proxC(); tk = TKPontoEVirgula; strcpy(tkD, "TKPontoEVirgula"); /* printf("Reconheceu token TKPontoEVirgula\n"); */ return; }
				if (c == ':') { lex[posl]='\0'; proxC(); tk = TKDoisPontos; strcpy(tkD, "TKDoisPontos"); /* printf("Reconheceu token TKDoisPontos\n"); */ return; }
				if (c == '.') { lex[posl]='\0'; proxC(); tk = TKPonto; strcpy(tkD, "TKPonto"); /* printf("Reconheceu token TKPonto\n"); */ return; }
				if (c == -1) { lex[posl]='\0'; proxC(); tk = TKFimArquivo; /* printf("Reconheceu token TKFimArquivo\n"); */ return; }
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
				// printf("reconheceu token %s\n",lex);
				return;

			case 2:
				if (c >= '0' && c <= '9') {
					proxC();
					break;
				}
				lex[--posl] = '\0';
				tk = TKConstInt;
				strcpy(tkD, "TKConstInt");
				return;

		} // switch
	} // while
} // função

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
	arqout = fopen("output.txt","wb");
	
	if (!arqin) {
		printf("Erro na abertura do fonte.\n");
		return 0;
	}

	proxC(); // lê primeiro caracter do arquivo
	getToken(); // lê primeiro token
	
	if (tk != TKFimArquivo) {	
		printf("%s%*.*s", "Token", 28 - strlen("Token"), 28 - strlen("Token"), " ");
		printf("%s%*.*s", "Lexema", 20 - strlen("Lexema"), 20 - strlen("Lexema"), " ");
		printf("%s%*.*s", "Linha", 9 - strlen("Linha"), 9 - strlen("Linha"), " ");
		printf("%s%*.*s\n", "Coluna", 10 - strlen("Coluna"), 10 - strlen("Coluna"), " ");
		
		fprintf(arqout, "%s%*.*s", "Token", 28 - strlen("Token"), 28 - strlen("Token"), " ");
		fprintf(arqout, "%s%*.*s", "Lexema", 20 - strlen("Lexema"), 20 - strlen("Lexema"), " ");
		fprintf(arqout, "%s%*.*s", "Linha", 9 - strlen("Linha"), 9 - strlen("Linha"), " ");
		fprintf(arqout, "%s%*.*s\n", "Coluna", 10 - strlen("Coluna"), 10 - strlen("Coluna"), " ");
		
		int i;
		for (i = 0; i < 63; i++) {
			printf("%c", 205);
			fprintf(arqout, "%c", '=');
		}
		
		printf("\n");
		fprintf(arqout, "\n");
	}
	
	while (tk != TKFimArquivo) {		
		printf("%*.*s%d -", 3 - strlenInt(tk), 3 - strlenInt(tk), " ", tk);
		printf(" %s%*.*s", tkD, 20 - strlen(tkD), 20 - strlen(tkD), " ");
		printf("  %s%*.*s", lex, 16 - strlen(lex), 16 - strlen(lex), " ");
		printf("%*.*s%d", 9 - strlenInt(linha + 1), 9 - strlenInt(linha + 1), " ", linha + 1);
		printf("%*.*s%d\n", 10 - strlenInt(coluna - strlen(lex)), 10 - strlenInt(coluna - strlen(lex)), " ", coluna - strlen(lex));
		
		fprintf(arqout, "%*.*s%d -", 3 - strlenInt(tk), 3 - strlenInt(tk), " ", tk);
		fprintf(arqout, " %s%*.*s", tkD, 20 - strlen(tkD), 20 - strlen(tkD), " ");
		fprintf(arqout, "  %s%*.*s", lex, 16 - strlen(lex), 16 - strlen(lex), " ");
		fprintf(arqout, "%*.*s%d", 9 - strlenInt(linha + 1), 9 - strlenInt(linha + 1), " ", linha + 1);
		fprintf(arqout, "%*.*s%d\n", 10 - strlenInt(coluna - strlen(lex)), 10 - strlenInt(coluna - strlen(lex)), " ", coluna - strlen(lex));
		
		getToken();
	}
	
	printf("\n");
	
	fclose(arqout);
	fclose(arqin);
	system("pause");
}
