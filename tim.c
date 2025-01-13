#include "tim.h"
//Funções do tipo imóvel

TIM* TIM_aloca(){
	TIM *novo = (TIM*)malloc(sizeof(TIM));
	if(!novo){
		perror("Falha oa alocar imóvel!");
		exit(EXIT_FAILURE);
	}
	return novo;
}

TIM* TIM_lineToTIM(char *s){
	int i = 0, j = 0;
	char num [15];
	TIM *novo = TIM_aloca();
	while(s[i] != ';'){//id unico
		num[j] = s[i];
		i++;
		j++;
	}
	num[j] = '\0';
	novo->id = stringToInt(num);
	j = 0;
	i++;
	while(s[i] != ';'){//bairro
		novo->bairro[j] = s[i];
		j++;
		i++;
	}
	novo->bairro[j] = '\0';
	j = 0;
	i++;
	while(s[i] != ';'){//tipo
		novo->tipo[j] = s[i];
		j++;
		i++;
	}
	novo->tipo[j] = '\0';
	j = 0;
	i++;
	if(s[i] == ';'){
		novo->rua[0] = '\0';
		i++;
	}
	else{
		while(s[i] != ';'){//rua
			novo->rua[j] = s[i];
			j++;
			i++;
		}
		novo->rua[j] = '\0';
		j = 0;
		i++;
	}
	if(s[i] == ';'){
		novo->num = -1;
		i++;
	}
	else{
		while(s[i] != ';'){//numero
			num[j] = s[i];
			i++;
			j++;
		}
		num[j] = '\0';
		novo->num = stringToInt(num);
		j = 0;
		i++;
	}
	while(s[i] != ','){//preco total
		num[j] = s[i];
		i++;
		j++;
	}
	num[j] = '\0';
	novo->precoTotal = stringToInt(num);
	i++;
	j = 0;
	while(s[i] != ';'){
		num[j] = s[i];
		i++;
		j++;
	}
	num[j] = '\0';
	novo->centPrecT = stringToInt(num);
	j = 0;
	i++;
	while(s[i] != ','){//preco total
		num[j] = s[i];
		i++;
		j++;
	}
	num[j] = '\0';
	novo->precoM2 = stringToInt(num);
	i++;
	j = 0;
	while(s[i] != ';'){
		num[j] = s[i];
		i++;
		j++;
	}
	num[j] = '\0';
	novo->centPrecM2 = stringToInt(num);
	j = 0;
	i++;
	while(s[i] != ';'){//descricao
		novo->desc[j] = s[i];
		i++;
		j++;
	}
	novo->desc[j] = '\0';
	j = 0;
	i++;
	while(s[i] != ';'){//cep
		num[j] = s[i];
		i++;
		j++;
	}
	num[j] = '\0';
	novo->cep = stringToInt(num);
	j = 0;
	i++;
	while(s[i] != ','){//latitude
		num[j] = s[i];
		i++;
		j++;
	}
	num[j] = '\0';
	novo->lat = stringToInt(num);
	i++;
	j = 0;
	while(s[i] != ';'){
		num[j] = s[i];
		i++;
		j++;
	}
	num[j] = '\0';
	novo->decLat = stringToInt(num);
	j = 0;
	i++;
	while(s[i] != ','){//longitude
		num[j] = s[i];			
		i++;
		j++;
	}
	num[j] = '\0';
	novo->lon = stringToInt(num);
	i++;
	j = 0;
	while(s[i] != '\0'){
		num[j] = s[i];
		i++;
		j++;
	}
	num[j - 1] = '\0';
	novo->decLong = stringToInt(num);
	return novo;
}

TIM* TIM_copia(TIM *imo){
	TIM *novo = TIM_aloca();
	novo->id = imo->id;
	novo->precoTotal = imo->precoTotal;
	novo->centPrecT = imo->centPrecT;
	novo->precoM2 = imo->precoM2;
	novo->centPrecM2 = imo->centPrecM2;
	novo->num = imo->num;
	novo->cep = imo->cep;
	novo->lat = imo->lat;
	novo->decLat = imo->decLat;
	novo->lon = imo->lon;
	novo->decLong = imo->decLong;
	strcpy(novo->bairro, imo->bairro);
	strcpy(novo->rua, imo->rua);
	strcpy(novo->tipo, imo->tipo);
	strcpy(novo->desc, imo->desc);
	return novo;
}

int TIM_salva(TIM* imovel, FILE* fp){
    if(!fp) return -1;
    char aux = 'N';
    if(!imovel){
    	fwrite(&aux, sizeof(char), 1, fp);
    	 return -1;
    }
    fwrite(&imovel->id, sizeof(long int), 1, fp);
    fwrite(&imovel->cep, sizeof(int), 1, fp);
    fwrite(&imovel->num, sizeof(int), 1, fp);
    fwrite(imovel->bairro, sizeof(char) * MAX_TAM_BAIRRO, 1, fp);
    fwrite(imovel->desc, sizeof(char) * MAX_TAM_DESC, 1, fp);
    fwrite(imovel->tipo, sizeof(char) * MAX_TAM_INFO, 1, fp);
    fwrite(imovel->rua, sizeof(char) * MAX_TAM_RUA, 1, fp);
    fwrite(&imovel->lat, sizeof(int), 1, fp);
    fwrite(&imovel->decLat, sizeof(int), 1, fp);
    fwrite(&imovel->lon, sizeof(int), 1, fp);
    fwrite(&imovel->decLong, sizeof(int), 1, fp);
    fwrite(&imovel->precoTotal, sizeof(int), 1, fp);
    fwrite(&imovel->centPrecT, sizeof(int), 1, fp);
	fwrite(&imovel->precoM2, sizeof(int), 1, fp);
	fwrite(&imovel->centPrecM2, sizeof(int), 1, fp);
    return 1;
}

int TIM_carrega(TIM **imovel, int t, FILE *fp) {
    if(feof(fp)) return -1;
    if (!fp) return -1;
    if(!imovel) return -1;
    int i;
	for(i = 0; i < t; i++){
		imovel[i] = TIM_carrega0(fp);
	}
    return 1;
}

TIM* TIM_carrega0(FILE *fp){
	TIM* imovel = TIM_aloca();
	fread(&(imovel->id), sizeof(long int), 1, fp);
	fread(&(imovel->cep), sizeof(int), 1, fp);
	fread(&(imovel->num), sizeof(int), 1, fp);
	fread(imovel->bairro, sizeof(char) * MAX_TAM_BAIRRO, 1, fp);
	fread(imovel->desc, sizeof(char) *MAX_TAM_DESC, 1, fp);
	fread(imovel->tipo, sizeof(char) *MAX_TAM_INFO, 1, fp);
	fread(imovel->rua, sizeof(char) *MAX_TAM_RUA, 1, fp);
	fread(&(imovel->lat), sizeof(int), 1, fp);
	fread(&(imovel->decLat), sizeof(int), 1, fp);
	fread(&(imovel->lon), sizeof(int), 1, fp);	fread(&(imovel->decLong), sizeof(int), 1, fp);
	fread(&(imovel->precoTotal), sizeof(int), 1, fp);
	fread(&(imovel->centPrecT), sizeof(int), 1, fp);
	fread(&(imovel->precoM2), sizeof(int), 1, fp);
	fread(&(imovel->centPrecM2), sizeof(int), 1, fp);
	return imovel;
}

TLSE_TIM* TLSE_TIM_inicializa(){
	return NULL;
}

TLSE_TIM* TLSE_TIM_cria(TIM *imo){
	TLSE_TIM *novo = (TLSE_TIM*)malloc(sizeof(TLSE_TIM));
	if(!novo){
		perror("Falha ao alocar lista!");
		exit(1);
	}
	novo->info = TIM_copia(imo);
	novo->prox = NULL;
	return novo;
}

TLSE_TIM* TLSE_TIM_insereNoInicio(TLSE_TIM *l, TIM *imo){
	TLSE_TIM *novo = TLSE_TIM_cria(imo);
	novo->prox = l;
	return novo;
}

TLSE_TIM* TLSE_TIM_remove(TLSE_TIM *l, TIM *imo){
	if(!l) return NULL;
	if(l->info->id == imo->id){
		free(l);
		return l->prox;
	}
	l->prox = TLSE_TIM_remove(l->prox, imo);
	return l;
}

TLSE_TIM* TLSE_TIM_libera(TLSE_TIM *l){
	if(!l) return NULL;
	l->prox = TLSE_TIM_libera(l->prox);
	free(l);
	return NULL;
}

void TLSE_TIM_mostra(TLSE_TIM *l){
	if(!l) return;
	mostra_imovel(l->info);
	printf("\n\n");
	TLSE_TIM_mostra(l->prox);
}

//Funções auxiliares

long int stringToInt(char *s){
	long int num = 0;
	int i = 0, aux;
	if(s[0] == '-') i++;
	while(s[i] != '\0'){
		aux = (int)s[i] - 48;
		num = num * 10 + aux;
		i++;
	}
	if(s[0] == '-') return -num;
	return num;
}

double stringToDouble(char *s){
	char parteInt[MAX_TAM_NUM];
	int i = 0, j = 0, base = 10, correcao = 1;
	double num;
	if(s[0] == '-'){
		i++;
		correcao = -1;
	}
	while(s[i] != ',' && s[i] != '\0'){
		parteInt[j] = s[i];
		j++;
		i++;
	}
	parteInt[j] = '\0';
	j = 0;
	i++;
	num = stringToInt(parteInt);
	while(s[i] != '\0'){
		num = num + ((float)s[i] - 48)/base;
		base *= 10;
		i++;
		j++;
	}
	return num * correcao;	
}

float divisor_casas_decimais(int num){
	float base = 10.0;
	while(num >= base){
		base *= 10;
	}
	return base;
}

void mostra_imovel(TIM *imo){
	if(!imo){
		printf("NULL\n");
		return;
	}
	printf("\nid: %ld\n", imo->id);
	printf("bairro: %s\n", imo->bairro);
	printf("tipo: %s\n", imo->tipo);
	imo->rua[0] == '\0' ? printf("rua: SEM RUA\n") : printf("rua: %s\n", imo->rua);
	imo->num == -1 ? printf("número: SEM NÚMERO\n") : printf("número: %d\n", imo->num);
	printf("preço: %.2f\n", imo->precoTotal + imo->centPrecT/100.0);
	printf("preco m2: %.2f\n", imo->precoM2 + imo->centPrecM2/100.0);
	printf("descrição: %s\n", imo->desc);
	printf("cep: %d\n", imo->cep);
	printf("latitude : %f\n", imo->lat-imo->decLat/divisor_casas_decimais(imo->decLat));
	printf("longitude: %f", imo->lon-imo->decLong/divisor_casas_decimais(imo->decLong));
}