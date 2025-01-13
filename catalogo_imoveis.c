#include "catalogo_imoveis.h"

int salva_imoveis_a_venda(int t){
	FILE *fp = fopen("imoveis_a_venda.bin", "wb+");
	if(!fp){
		perror("Falha ao abiri \"nosAVenda.bin\"");
		exit(1);
	}
	char*noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	if(!noEsq){
		perror("Falha ao procurar no mais a esqierda");
		free(noEsq);
		fclose(fp);
		exit(1);
	}
	salva_imoveis_a_venda0(noEsq, t, fp);
	fwrite("\0", sizeof(char*), 1, fp);
	fclose(fp);
	return 1;
}

void salva_imoveis_a_venda0(char *raiz, int t, FILE *fp){
	TARVBM *x = TARVBM_carrega(raiz, t);
	if(!x)
		 return;
	int i;
	free(raiz);
	for(i = 0; i < x->nchaves; i++){
		if(status_imovel(x->imovel[i]) == 1){
			TIM_salva(x->imovel[i], fp);
			printf("IMOVEL\n\n");
			mostra_imovel(x->imovel[i]);
			printf("\n\n");
		}
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	salva_imoveis_a_venda0(proxNo, t, fp);
}

TIM* imovelAVendaMaisBarato(int t){
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	TIM *resp = NULL;
	 imovelAVendaMaisBarato0(noEsq, &resp, t);
	 return resp;
}

void imovelAVendaMaisBarato0(char *raiz, TIM **imo, int t){
	TARVBM *x = TARVBM_carrega(raiz, t);
	if(!x)
		 return;
	free(raiz);
	int i;
	for(i = 0; i < x->nchaves; i++){
		if(status_imovel(x->imovel[i]) == 1){
			float precoImoX = x->imovel[i]->precoTotal + x->imovel[i]->centPrecT/100;
			float precoImoZ = *imo ? (*imo)->precoTotal + (*imo)->centPrecT/100 : FLT_MIN;
			if((!*imo) || (precoImoX < precoImoZ)){
				if(*imo)
					free(*imo);
				*imo = TIM_copia(x->imovel[i]);
			}
		}
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	 imovelAVendaMaisBarato0(proxNo, imo, t);
}

TIM* imovelAVendaMaisCaro(int t){
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	TIM *resp = NULL;
	 imovelAVendaMaisCaro0(noEsq, &resp, t);
	 printf("\n\nresp\n\n");
	 mostra_imovel(resp);
	 return resp;
}

void imovelAVendaMaisCaro0(char *raiz, TIM **imo, int t){
	TARVBM *x = TARVBM_carrega(raiz, t);
	if(!x)
		 return;
	free(raiz);
	int i;
	for(i = 0; i < x->nchaves; i++){
		if(status_imovel(x->imovel[i]) == 1){
			float precoImoX = x->imovel[i]->precoTotal + x->imovel[i]->centPrecT/100;
			float precoImoZ = *imo ? (*imo)->precoTotal + (*imo)->centPrecT/100.0 : 0;
			if((!*imo) || (precoImoX > precoImoZ)){
				if(*imo)
					free(*imo);
				*imo = TIM_copia(x->imovel[i]);
			}
		}
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	printf("-> %s", proxNo);
	TARVBM_libera_no(x, t);
	 imovelAVendaMaisCaro0(proxNo, imo, t);
}

TIM* imovelAlugadoMaisBarato(int t){
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	TIM *resp = NULL;
	 imovelAlugadoMaisBarato0(noEsq, &resp, t);
	 return resp;
}

void imovelAlugadoMaisBarato0(char *raiz, TIM **imo, int t){
	TARVBM *x = TARVBM_carrega(raiz, t);
	if(!x)
		 return;
	int i;
	free(raiz);
	for(i = 0; i < x->nchaves; i++){
		if(status_imovel(x->imovel[i]) == 2){
			float precoImoX = x->imovel[i]->precoTotal + x->imovel[i]->centPrecT/100;
			float precoImoZ = *imo ? (*imo)->precoTotal + (*imo)->centPrecT/100 : FLT_MAX;
			if((!*imo) || (precoImoX < precoImoZ)){
				if(*imo)
					free(*imo);
				*imo = TIM_copia(x->imovel[i]);
			}
		}
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	 imovelAlugadoMaisBarato0(proxNo, imo, t);
}

TIM* imovelAlugadoMaisCaro(int t){
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	TIM *resp = NULL;
	 imovelAlugadoMaisCaro0(noEsq, &resp, t);
	 return resp;
}
void imovelAlugadoMaisCaro0(char *raiz, TIM **imo, int t){
	TARVBM *x = TARVBM_carrega(raiz, t);
	if(!x)
		 return;
	int i;
	free(raiz);
	for(i = 0; i < x->nchaves; i++){
		if(status_imovel(x->imovel[i]) == 2){
			float precoImoX = x->imovel[i]->precoTotal + x->imovel[i]->centPrecT/100;
			float precoImoZ = *imo ? (*imo)->precoTotal + (*imo)->centPrecT/100 : FLT_MIN;
			if((!*imo) || (precoImoX > precoImoZ)){
				if(*imo)
					free(*imo);
				*imo = TIM_copia(x->imovel[i]);
			}
		}
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	 imovelAlugadoMaisCaro0(proxNo, imo, t);
}

void imoveis_do_cep(int cep, int t){
	FILE *fp = fopen("imoveis_cep.bin", "wb+");
	if(!fp){
		perror("Falha ao abir \"imoveis_cep.bin\"");
		exit(1);
	}
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	imoveis_do_cep0(noEsq, cep, t, fp);
	fwrite("\0", sizeof(char), 1, fp);
	fclose(fp);
}

void imoveis_do_cep0(char *raiz, int cep, int t, FILE *fp){
	TARVBM *x = TARVBM_carrega(raiz, t);
	int i;
	free(raiz);
	if(!x){
		TARVBM_libera_no(x, t);
		return;
	}
	for(i = 0; i < x->nchaves; i++){
		if(x->imovel[i]->cep == cep)
			TIM_salva(x->imovel[i], fp);
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	imoveis_do_cep0(proxNo, cep, t, fp);
}

void imoveis_da_lat(float lat, int t){
		FILE *fp = fopen("imoveis_lat.bin", "wb+");
	if(!fp){
		perror("Falha ao abir \"imoveis_lat.bin\"");
		exit(1);
	}
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	imoveis_da_lat0(noEsq, lat, t, fp);
	fwrite("\0", sizeof(char), 1, fp);
	fclose(fp);
}

void imoveis_da_lat0(char *raiz, float lat, int t, FILE *fp){
	TARVBM *x = TARVBM_carrega(raiz, t);
	int i;
	free(raiz);
	if(!x){
		TARVBM_libera_no(x, t);
		return;
	}
	for(i = 0; i < x->nchaves; i++){
		float latitude = x->imovel[i]->lat - x->imovel[i]->decLat/divisor_casas_decimais(x->imovel[i]->decLat);
		if(latitude == lat)
			TIM_salva(x->imovel[i], fp);
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	imoveis_da_lat0(proxNo, lat, t, fp);
}

void imoveis_da_long(float lon, int t){
	FILE *fp = fopen("imoveis_long.bin", "wb+");
	if(!fp){
		perror("Falha ao abir \"imoveis_long.bin\"");
		exit(1);
	}
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	imoveis_da_long0(noEsq, lon, t, fp);
	fwrite("\0", sizeof(char), 1, fp);
	fclose(fp);
}

void imoveis_da_long0(char *raiz, float lon, int t, FILE *fp){
	TARVBM *x = TARVBM_carrega(raiz, t);
	int i;
	free(raiz);
	if(!x){
		TARVBM_libera_no(x, t);
		return;
	}
	for(i = 0; i < x->nchaves; i++){
		double longitude = x->imovel[i]->lon - x->imovel[i]->decLong/divisor_casas_decimais(x->imovel[i]->decLong);
		if(longitude == lon)
			TIM_salva(x->imovel[i], fp);
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	imoveis_da_long0(proxNo, lon, t, fp);
}

void imoveis_da_rua(char *rua, int t){
		FILE *fp = fopen("imoveis_rua.bin", "wb+");
	if(!fp){
		perror("Falha ao abir \"imoveis_rua.bin\"");
		exit(1);
	}
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	imoveis_da_rua0(noEsq, rua, t, fp);
	fwrite("\0", sizeof(char), 1, fp);
	fclose(fp);
}

void imoveis_da_rua0(char *raiz, char *rua, int t, FILE *fp){
		TARVBM *x = TARVBM_carrega(raiz, t);
	int i;
	free(raiz);
	if(!x){
		TARVBM_libera_no(x, t);
		return;
	}
	for(i = 0; i < x->nchaves; i++){
		if(strcmp(x->imovel[i]->rua, rua) == 0)
			TIM_salva(x->imovel[i], fp);
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	imoveis_da_rua0(proxNo, rua, t, fp);
}