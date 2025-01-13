#include "TARVBM_TIM.h"

TARVBM* TARVBM_cria(){
	return NULL;
}

/*Essa função não aloca o vetor de imoveis(precisei fazer isso para resolver um bug na função TARVBM_carrega), lembre-se de alocar manualmente, se for nó folha*/

TARVBM* TARVBM_aloca(int t){
	TARVBM *novo = (TARVBM*)malloc(sizeof(TARVBM));
	if(!novo){
		perror("Falha ao alocar TARVBM!");
		exit(1);
	}
	novo->chave = (long int*)calloc(2*t-1, sizeof(long int));
	if(!novo->chave){
		perror("Falha ao alocar TARVBM!");
		exit(1);
	}
	novo->filho = (char**)calloc(2*t, sizeof(char*));
	if(!novo->filho){
		perror("Falha ao alocar TARVBM!");
		exit(1);
	}
	novo->nchaves = 0;
	novo->folha = 1;
	novo->imovel = NULL;
	novo->prox = NULL;
	return novo;
}

TARVBM* TARVBM_libera_no(TARVBM *a, int t){
	if(!a) return NULL;
	int i = 0;
	free(a->chave);
	if(a->filho){
		for(i = 0; i < 2*t; i++)
			if(a->filho[i])		
				free(a->filho[i]);
			free(a->filho);
	}
	if(a->imovel){
		for(i = 0; i < a->nchaves; i++)
			if(a->imovel[i])
				free(a->imovel[i]);
		free(a->imovel);
	}
	a->prox = NULL;
	free(a);
	return NULL;
}

TIM* TARVBM_busca_id(char* raiz, long int idAlvo, int t){
	TARVBM *a = TARVBM_carrega(raiz, 4);
	printf("-> Buscando no no: %s", raiz);
	if(!a) return NULL;
	if(a->nchaves < 1){
		TARVBM_libera_no(a, 4);
		return NULL;
	}
	char *aux = TARVBM_alocaFilho();
	int i = 0;
	while((a->chave[i] < idAlvo) && (i < a->nchaves))
		i++;
	if(a->folha){
		if(i >= a->nchaves){
			a = TARVBM_libera_no(a, t);
			return NULL;
		}
		TIM *temp = TIM_copia(a->imovel[i]);
		a = TARVBM_libera_no(a, t);
		if(temp->id == idAlvo)
			return temp;
		return NULL;
	}
	if(a->chave[i] == idAlvo) i++;
	strcpy(aux, a->filho[i]);
	a = TARVBM_libera_no(a, t);
	return TARVBM_busca_id(aux, idAlvo, t);
}

int TARVBM_salva(TARVBM *a, char *arquivo, int t){
    FILE* fp = fopen(arquivo, "wb+");
    if(!fp){
    	perror("Falha ao abrir arquivo");
    	TARVBM_libera_no(a, t);
    	free(arquivo);
    	exit(1);
    }
    int i, controle;
    fwrite(&a->nchaves, sizeof(int), 1, fp);
    fwrite(a->chave, sizeof(long int),  a->nchaves, fp);
    fwrite(&a->folha, sizeof(int), 1, fp);
    if(a->folha){
       if(a->prox)
      	 fwrite(a->prox, sizeof(char) * MAX_TAM_ARQ, 1, fp);
       else{
       	char null_marker = 'N';
       	fwrite(&null_marker, sizeof(char), 1, fp);
       }
    }
    else{
       for(i = 0; i < a->nchaves + 1; i++){
       	int tam = sizeof(a->filho[i]);
       	int completar = MAX_TAM_ARQ - tam;
      	 fwrite(a->filho[i], sizeof(char) * tam, 1, fp);
      	 char aux = '\0';
      	 for(int j = 0; j < completar; j++)
      	 	fwrite(&aux, sizeof(char), 1, fp);
       }
    }
	if(a->folha){
		for(i = 0; i < a->nchaves; i++){
			controle = TIM_salva(a->imovel[i], fp);
			if(controle < 0) break;
		}
   }
    fclose(fp);
    return 1;
}

TARVBM* TARVBM_carrega(char *arquivo, int t) {
    FILE* fp = fopen(arquivo, "rb+");
    int i, controle;
    char aux;
    if (!fp) {
        if (!fp) {
            return NULL;
        }
    }
    TARVBM *a = TARVBM_aloca(t);
    controle = fread(&a->nchaves, sizeof(int), 1, fp);
    if(controle < 1){
    	TARVBM_libera_no(a, t);
    	return NULL;
    }
    fread(a->chave, sizeof(long int), a->nchaves, fp);
    fread(&(a->folha), sizeof(int), 1, fp);
    if (a->folha) {
        fread(&aux, sizeof(char), 1, fp);
        if(aux == 'N')
        	a->prox = NULL;
        else{
        	fseek(fp, -sizeof(char), SEEK_CUR);
        	a->prox = TARVBM_alocaFilho();
        	if(!a->prox){
        		TARVBM_libera_no(a, t);
        		exit(1);
        	}
        	fread(a->prox, sizeof(char) * MAX_TAM_ARQ, 1, fp);
        }
        a->filho = NULL;
    } 
    else{
    	for(i = 0; i < a->nchaves + 1; i++){
    		a->filho[i] = TARVBM_alocaFilho();
    		if(!a->filho[i]){
				TARVBM_libera_no(a, t);
    			exit(1);
    		}
			fread(a->filho[i], sizeof(char) * MAX_TAM_ARQ, 1, fp);
    	}
        a->prox = NULL;
    }
    if(a->folha){
    	a->imovel = TARVBM_alocaVetImo(t);
    	if(!a->imovel){
    		TARVBM_libera_no(a, t);
    		exit(1);
    	}
    	if(TIM_carrega(a->imovel, a->nchaves, fp) == -1){
	    	perror("Falha ao carregar no!");
	    	TARVBM_libera_no(a, t);
	    	exit(1);
	    }
    }
    fclose(fp);
    return a;
}

int TARVBM_insere(TIM *imo, int t){
	return TARVBM_insere0(TARVBM_pegaRaiz(), t, imo);
}

int TARVBM_insere0(char *raiz, int t, TIM *imo){
	if(TARVBM_busca_id(raiz, imo->id, t)) return 0;
	TARVBM *a = TARVBM_carrega(raiz, t);
	if(!a){
		a = TARVBM_aloca(t);
		a->chave[0] = imo->id;
		a->imovel = (TIM**)calloc(2*t-1, sizeof(TIM*));
		a->imovel[0] = imo;
		a->nchaves++;
		TARVBM_salva(a, raiz, t);
		TARVBM_atualizaRaiz(raiz);
		return 1;
	}
	if(a->nchaves == 2*t-1){
		char *noS = TARVBM_geraNomeNo();
		TARVBM *S = TARVBM_aloca(t);
		S->nchaves = 0;
		S->folha = 0;
		S->filho[0] = TARVBM_alocaFilho();
		if(!S->filho[0]){
			TARVBM_libera_no(S, t);
			free(noS);
			free(raiz);
			exit(1);
		}
		strcpy(S->filho[0], raiz);
		S = TARVBM_divisao(S, 1, a, raiz, t);
		printf(" dividindo %s", raiz);
		TARVBM_atualizaRaiz(noS);
		S = TARVBM_insereNCompleto(S, noS, imo, t);
		TARVBM_salva(S, noS, t);
		free(noS);
		free(raiz);
		TARVBM_libera_no(S, t);
		return 1;
	}
	printf(" %s", raiz);
	a = TARVBM_insereNCompleto(a, raiz,imo, t);
	free(raiz);
	return 1;
}

TARVBM* TARVBM_insereNCompleto(TARVBM *a,char *raiz, TIM *imo, int t){
	if(!a || !imo) return 0;
	int i;
	if(!a->imovel)
		a->imovel = (TIM**)calloc(2*t-1, sizeof(TIM*));
	i = a->nchaves - 1;
	if(a->folha){
		a->imovel[a->nchaves] = TIM_aloca();
		while((i >= 0) && (imo->id < a->chave[i])){
			a->chave[i + 1] = a->chave[i];
			a->imovel[i + 1] = a->imovel[i];
			i--;
		}
		a->chave[i + 1] = imo->id;
		a->imovel[i + 1] = imo;
		a->nchaves++;
		TARVBM_salva(a, raiz, t);
		return a;
	}
	while((i >= 0) && (imo->id < a->chave[i]))
		i--;
	i++;
	char *noX = (char*)calloc(MAX_TAM_ARQ, sizeof(char));
	if(!noX) exit(1);
	strcpy(noX, a->filho[i]);
	TARVBM *x = TARVBM_carrega(a->filho[i], t);
	if(x->nchaves == 2*t-1){
		printf(" Dividiu %s", noX);
		a = TARVBM_divisao(a, i + 1, x, a->filho[i], t);
		if(imo->id > a->chave[i]) i++;
	}
	printf(" -> %s", a->filho[i]);
	TARVBM_salva(x, noX, t);
	TARVBM_libera_no(x, t);
	x = TARVBM_carrega(a->filho[i], t);
	x = TARVBM_insereNCompleto(x, a->filho[i], imo, t);
	free(noX);
	TARVBM_salva(a, raiz, t);
	return a;
}

TARVBM* TARVBM_divisao(TARVBM *x, int i, TARVBM* y, char *noY, int t){
	TARVBM *z = TARVBM_aloca(t);
	char *noZ = TARVBM_geraNomeNo();
	int j;
	z->folha = y->folha;
	if(!y->folha){
		z->nchaves = t-1;
		for(j=0;j<t-1;j++) z->chave[j] = y->chave[j+t];
		for(j=0;j<t;j++){
		    z->filho[j] = TARVBM_alocaFilho();
            strcpy(z->filho[j], y->filho[j+t]);
            free(y->filho[j+t]);
            y->filho[j+t] = NULL;
    	}
	}
	else {
    	z->nchaves = t;
	    if(!y->imovel){
	    	y->imovel = TARVBM_alocaVetImo(t);
	    	if(!y->imovel){
				libera_nos_divisao(x, y, z, noY, noZ, t);
	    		exit(1);
	    	}
	    }
	    z->imovel = TARVBM_alocaVetImo(t);
	    if(!z->imovel){
			libera_nos_divisao(x, y, z, noY, noZ, t);
			exit(1);
	    }
	    for(j=0;j < t;j++){
	    	 z->chave[j] = y->chave[j+t-1];
	    	 z->imovel[j] = y->imovel[j+t-1];
	    }
	    if(y->prox){
	    	z->prox = TARVBM_alocaFilho();
		    if(!z->prox){
				libera_nos_divisao(x, y, z, noY, noZ, t);
		    	exit(1);
		    }
	    	strcpy(z->prox, y->prox);
	    	free(y->prox);
	    }
		y->prox = TARVBM_alocaFilho();
	    if(!y->prox){
			libera_nos_divisao(x, y, z, noY, noZ, t);
		 	exit(1);
		 }
	    strcpy(y->prox, noZ);
	}	
	y->nchaves = t-1;
	if(!x->filho[x->nchaves + 1]){
		x->filho[x->nchaves + 1] = TARVBM_alocaFilho();
		if(!x->filho[x->nchaves + 1]){
			libera_nos_divisao(x, y, z, noY, noZ, t);
			exit(1);
		}
	}
	for(j = x->nchaves; j >= i; j--){
		x->chave[j] = x->chave[j-1];
		if(x->filho[j + 1])
			free(x->filho[j + 1]);
		x->filho[j + 1] = TARVBM_alocaFilho();
		if(!x->filho[j + 1]){
			libera_nos_divisao(x, y, z, noY, noZ, t);
			exit(1);
		}
		strcpy(x->filho[j+1], x->filho[j]);
	}
	x->chave[i-1] = y->chave[t-1];
	x->nchaves++;
	if(x->filho[i])
		free(x->filho[i]);
	x->filho[i] = TARVBM_alocaFilho();
	strcpy(x->filho[i], noZ);
	if(x->imovel){
		for(i = 0; i < x->nchaves; i++){
			if(x->imovel[i]){
				free(x->imovel[i]);
				x->imovel[i] = NULL;
			}
		}
		free(x->imovel);
		x->imovel = NULL;
	}
	TARVBM_salva(z, noZ, t);
	TARVBM_libera_no(z, t);
	free(noZ);
	TARVBM_salva(y, noY, t);
	return x;
}

TARVBM* TARVBM_remover(TARVBM* a, char *nomeNo, TIM *imo, int t){
	if(!a) return a;
	int i;
	for(i = 0; i < a->nchaves && a->chave[i] < imo->id; i++);
	if((i < a->nchaves) && (imo->id == a->chave[i]) && (a->folha)){
	   printf("\nCASO 1\n");
	   int j;
	   for(j=i; j<a->nchaves-1;j++) a->chave[j] = a->chave[j+1];
	   a->nchaves--;
		if(!a->nchaves){
			a = TARVBM_libera_no(a, t);
			remove(nomeNo);
			return NULL;
		}
		return a;      
    }
    if((i < a->nchaves) && (imo->id == a->chave[i]) && (a->folha)){
    	a = TARVBM_remove_3a(a, imo, i, t);
    	TARVBM_salva(a, nomeNo, t);
    	return a;
	}
	return a;
}

TARVBM* TARVBM_remove_3a(TARVBM *a, TIM * imo, int i, int t){
	  TARVBM *y = TARVBM_carrega(a->filho[i], t), *z = NULL, *k;
	if((i < a->nchaves) && (y->nchaves >=t)){ //CASO 3A
		z = TARVBM_carrega(a->filho[i+1], t);
		if(!y->folha){
			y->chave[t-1] = a->chave[i];
			a->chave[i] = z->chave[0];
		}
		else{ 
			a->chave[i] = z->chave[0] + 1;
			y->chave[t-1] = z->chave[0];
		}
		y->nchaves++;
		int j;
		for(j=0; j < z->nchaves-1; j++)  //ajustar chaves de z
        	z->chave[j] = z->chave[j+1];
        y->filho[y->nchaves] = z->filho[0]; //enviar ponteiro menor de z para o novo elemento em y
        for(j=0; j < z->nchaves; j++)       //ajustar filhos de z
        	z->filho[j] = z->filho[j+1];
		z->nchaves--;
		k = TARVBM_carrega(a->filho[i], t);
		k = TARVBM_remover(k, a->filho[i],imo, t);
		if(k){
			TARVBM_salva(k, a->filho[i], t);
			TARVBM_libera_no(k, t);
		}
		TARVBM_salva(z, a->filho[i+1], t);
		TARVBM_libera_no(z, t);
        return a;
    }
	if((i > 0) && (!z) && (y->nchaves >= t)){ //CASO 3A
		printf("\nCASO 3A: i igual a nchaves\n");
		z = TARVBM_carrega(a->filho[i-1], t);
		int j;
		for(j = y->nchaves; j>0; j--)               //encaixar lugar da nova chave
			y->chave[j] = y->chave[j-1];
		for(j = y->nchaves+1; j>0; j--) //encaixar lugar dos filhos da nova chave
			y->filho[j] = y->filho[j-1];

		if(!y->folha){
			y->chave[0] = a->chave[i-1];    //dar a y a chave i da arv
			a->chave[i-1] = z->chave[z->nchaves - 1];   //dar a arv uma chave de z
		}
		else{ 
			a->chave[i-1] = z->chave[z->nchaves - 1];
			y->chave[0] = z->chave[z->nchaves-1];
		}
		y->nchaves++;
      //enviar ponteiro de z para o novo elemento em y
		y->filho[0] = z->filho[z->nchaves];
		z->nchaves--;
		k = TARVBM_carrega(a->filho[i], t);
		k = TARVBM_remover(y, a->filho[i], imo, t);
		if(k){
			TARVBM_salva(k, a->filho[i], t);
			TARVBM_libera_no(k, t);
		}
		TARVBM_salva(z, a->filho[i - 1], t);
		TARVBM_libera_no(z, t);
		return a;
    }
}

void TARVBM_atualizaRaiz(char *no){
	FILE *fp = fopen("raiz.bin", "wb+");
	if(!fp){
		perror("Falha ao abrir arquivos \"nosExtremos.bin\"");
		exit(1);
	}
	fwrite(no, sizeof(char) * MAX_TAM_ARQ, 1, fp);
	fclose(fp);
}

char* TARVBM_alocaFilho(){
	char *filho = (char*)calloc(MAX_TAM_ARQ, sizeof(char));
	if(!filho){
		perror("Falha ao alocar filho!");
		return NULL;
	}
	return filho;
}

TIM** TARVBM_alocaVetImo(int t){
	TIM** novo = (TIM**)calloc(2*t-1, sizeof(TIM*));
	if(!novo){
		perror("Falha ao alocar vetor de moveis!");
		return NULL;
	}
	return novo;
}

char* TARVBM_noMaisAEsq(char *raiz, int t){
	TARVBM *x = TARVBM_carrega(raiz, t);
	if(!x) {
		free(raiz);
		return NULL;
	}
	if(x->folha)
		return raiz;
	free(raiz);
	char *c = TARVBM_alocaFilho();
	strcpy(c, x->filho[0]);
	TARVBM_libera_no(x, t);
	return TARVBM_noMaisAEsq(c, t);
}

char* TARVBM_pegaRaiz(){
	FILE *fp = fopen("raiz.bin", "rb");
	if(!fp){
		fp = fopen("raiz.bin", "wb");
		if(!fp){
			perror("Falha ao abrir arquivos \"nosExtremos.bin\"");
			exit(1);
		}
		char *no = TARVBM_geraNomeNo();
		fwrite(no, sizeof(char) * MAX_TAM_ARQ, 1, fp);
		fclose(fp);
		return no;
	}
	char *no = TARVBM_alocaFilho();
	fread(no, sizeof(char) * MAX_TAM_ARQ, 1, fp);
	fclose(fp);
	return no;
}

char* TARVBM_geraNomeNo(){
	int num = pega_ultimo_no();
	return concat_nome_no(num);
}

void TARVBM_salva_grau_no(int t){
	FILE *fp = fopen("grau_no.bin", "wb+");
	if(!fp){
		perror("Falha ao abrir arquivo \"grau_no.bin\"");
		exit(1);
	}
	fwrite(&t, sizeof(int), 1, fp);
	fclose(fp);
}

int TARVBM_pega_grau_salvo(){
	int t;
	FILE *fp = fopen("grau_no.bin", "rb");
	if(!fp){
		perror("Falha ao abrir arquivo \"grau_no.bin\"");
		limpa_arquivos();
		exit(1);
	}
	fread(&t, sizeof(int), 1, fp);
	fclose(fp);
}

//funções auxiliares

char* intToString3d(int num){
	char* nums = (char*)malloc(sizeof(char) * 4);
	if(!nums){
		perror("Falha ao alocar vetor do tipo char");
		exit(1);
	}
	int numI, i = 0;
	if(num >= 100){
		numI = num/100;
		nums[i] = (char)numI + 48;
		num -= 100 * numI;
		i++;
		if(num < 10){
			nums[i] = '0';
			i++;
		}
	}
	if((num < 100) && (num >= 10)){
		numI = num/10;
		nums[i] = (char)numI + 48;
		num -= 10 * numI;
		i++;
	}
	nums[i] = (char)num + 48;
	nums[i + 1] = '\0';
	return nums;
}

int pega_ultimo_no(){
	FILE* fp = fopen("arv_b_ultima_geracao.bin", "rb+");
	int num = 0;
	if(!fp){
		fp = fopen("arv_b_ultima_geracao.bin", "wb");
		if(!fp){
			perror("Falha ao abrir arquivos \"nosExtremos.bin\"");
			exit(1);
		}
		fwrite(&num, sizeof(int), 1, fp);
		fclose(fp);
		return 0;
	}
	fread(&num, sizeof(int), 1, fp);
	fseek(fp, 0, SEEK_SET);
	num++;
	fwrite(&num, sizeof(int), 1, fp);
	fclose(fp);
	return num;
}

void limpa_arquivos(){
	int ultimono = pega_ultimo_no();
	for(int i = -1; i <= ultimono; i++){
		char* temp = concat_nome_no(i);
		remove(temp);
		free(temp);
	}
	remove("raiz.bin");
	remove("arv_b_ultima_geracao.bin");
	remove("imoveis_a_venda.bin");
	remove("imoveis_cep.bin");
	remove("grau_no.bin");
	remove("imoveis_lat.bin");
	remove("imoveis_long.bin");
	remove("imoveis_rua.bin");
}

char* concat_nome_no(int num){
	char *nomeArq = (char*)calloc(MAX_TAM_ARQ, sizeof(char));
	char *nums;
	if(!nomeArq){
		free(nomeArq);
		perror("Falha ao alocar nome do arquivo!");
		exit(1);
	}
	strcat(nomeArq, "no");
	nums = intToString3d(num);
	strcat(nomeArq, nums);
	strcat(nomeArq, ".bin");
	free(nums);
	return nomeArq;
}

void mostra_no(TARVBM *a){
	if(!a) return;
	int i;
	printf("\nÉ folha? %d\n", a->folha);
	printf("nchaves: %d\n", a->nchaves);
	printf("Chaves: ");
	for(i = 0; i < a->nchaves; i++){
		printf("%ld, ", a->chave[i]);
	}
	if(!a->folha){
		printf("\nProx: NULL\n");
		if(a->filho){
			printf("Filhos: ");
			for(i = 0; i <= a->nchaves; i++)
				printf("%s, ", a->filho[i]);
		}
		printf("\n");
	}
	else{
		if(a->prox){
			printf("\nProx arquivo: %s\n", a->prox);
		}
		if(a->imovel){
			printf("\n\n*********** IMÓVEIS ***********\n\n");
			for(i = 0; i < a->nchaves; i++){
				mostra_imovel(a->imovel[i]);
				printf("\n\n");
			}
		}
	}
}

int status_imovel(TIM *imo){
	if(strstr(imo->desc, "vende") || strstr(imo->desc, "venda") || strstr(imo->desc, "vendo") || strstr(imo->desc, "VENDE") || strstr(imo->desc, "VENDA") || strstr(imo->desc, "VENDO") || strstr(imo->desc, "Vende") || strstr(imo->desc, "Venda") || strstr(imo->desc, "Vendo"))
		return 1;
	if(strstr(imo->desc, "alug") || strstr(imo->desc, "Alug") || strstr(imo->desc, "ALUG"))
		return 2;
	return 0;
}

void mostra_arquivo_imoveis(char *arq){
	FILE *fp = fopen(arq, "rb");
	if(!fp){
		perror("Falha ao abir arquivo! kk");
		exit(1);
	}
	TIM *imo;
	char cont = 'a';
	fread(&cont, sizeof(char), 1, fp);
	if(cont == '\0'){
		printf("Nenhum imóvel encontrado!\n");
		return;
	}
	while(cont != '\0'){
		fseek(fp, -sizeof(char), SEEK_CUR);
		imo = TIM_carrega0(fp);
		printf("\n\n");
		mostra_imovel(imo);
		printf("\n\n");
		free(imo);
		fread(&cont, sizeof(char), 1, fp);
		if(feof(fp)) break;
	}
	fclose(fp);
}

void libera_nos_divisao(TARVBM *x, TARVBM *y, TARVBM *z, char *noY, char *noZ, int t){
	TARVBM_libera_no(x, t);
	TARVBM_libera_no(y, t);
	TARVBM_libera_no(z, t);
	free(noY);
	free(noZ);
}