#ifndef TIM_H
#define TIM_H

#define MAX_TAM_BAIRRO 31
#define MAX_TAM_INFO 49
#define MAX_TAM_RUA 51
#define MAX_TAM_DESC 2561
#define MAX_TAM_LINHA 2601
#define MAX_TAM_ARQ 15
#define MAX_TAM_NUM 15 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct imovel{
	long int id;
	int cep, precoTotal, precoM2, centPrecT, centPrecM2, num, lat, lon, decLat, decLong;
	char bairro[MAX_TAM_BAIRRO], tipo[MAX_TAM_INFO], rua[MAX_TAM_RUA], desc[MAX_TAM_DESC];
}TIM;

typedef  struct lista{
	TIM *info;
	struct lista *prox;
}TLSE_TIM;

// Funções Tipo Imóvel

TIM* TIM_aloca();
TIM* TIM_lineToTIM(char *s);
TIM* TIM_copia(TIM *imo);
int TIM_carrega(TIM **imovel, int t, FILE *fp);
TIM* TIM_carrega0(FILE *fp);
int TIM_salva(TIM* imovel, FILE* fp);

//Funções lista

TLSE_TIM* TLSE_TIM_cria(TIM *imo);
TLSE_TIM* TLSE_TIM_inicializa();
TLSE_TIM* TLSE_TIM_insereNoInicio(TLSE_TIM *l, TIM *imo);
TLSE_TIM* TLSE_TIM_remove(TLSE_TIM *l, TIM *imo);
TLSE_TIM* TLSE_TIM_libera(TLSE_TIM *l);
void TLSE_TIM_mostra(TLSE_TIM *l);

//Funções auxiliares

void mostra_imovel(TIM *imo);
long int stringToInt(char *s);
int pegaPreco(char *s);
double stringToDouble(char *s);
float divisor_casas_decimais(int num);

#endif // TIM_H_INCLUDED