#ifndef TARVBM_TIM_H_INCLUDED
#define TARVBM_TIM_H_INCLUDED
#include "tim.h"
#include <float.h>

typedef struct arvbm{
	int nchaves, folha;
	long int *chave;
	char **filho, *prox;
	TIM** imovel;
}TARVBM;

TARVBM* TARVBM_cria();
TARVBM* TARVBM_aloca(int t);
TARVBM* TARVBM_libera_no(TARVBM *a, int t);
TIM* TARVBM_busca_id(char* raiz, long int idAlvo, int t);
int TARVBM_insere(TIM *imo, int t);
int TARVBM_insere0(char *raiz, int t, TIM *imo);
TARVBM* TARVBM_insereNCompleto(TARVBM *a,char *raiz, TIM *imo, int t);
TARVBM* TARVBM_divisao(TARVBM *x, int i, TARVBM* y, char *noY, int t);
TARVBM* TARVBM_remover(TARVBM* a, char *nomeNo, TIM *imo, int t);
TARVBM* TARVBM_remove_3a(TARVBM *a, TIM * imo, int i, int t);
TARVBM *TARVBM_carrega(char *arquivo, int t);
int TARVBM_salva(TARVBM *a, char *arquivo, int t);
char* TARVBM_geraNomeNo();
char* TARVBM_alocaFilho();
TIM** TARVBM_alocaVetImo(int t);
void TARVBM_atualizaRaiz(char *no);
char* TARVBM_pegaRaiz();
char* TARVBM_noMaisAEsq(char *raiz, int t);
void TARVBM_salva_grau_no(int t);

//Funções auxiliares

void mostra_no(TARVBM *a);
void limpa_arquivos();
char* concat_nome_no(int num);
char* intToString3d(int num);
int pega_ultimo_no();
int status_imovel(TIM *imo);//retorna 1 se está a venda, 2 se for alugado e 0 se for indefinido
void mostra_arquivo_imoveis(char *arq);
void libera_nos_divisao(TARVBM *x, TARVBM *y, TARVBM *z, char *noY, char *noZ, int t);
#endif 