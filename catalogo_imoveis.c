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

void imoveis_de_bairro(char *bairro, int t){
	FILE *fp = fopen("imoveis_bairro.bin", "wb+");
	if(!fp){
		perror("Falha ao abir \"imoveis_bairro.bin\"");
		exit(1);
	}
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	imoveis_de_bairro0(noEsq, bairro, t, fp);
	fwrite("\0", sizeof(char), 1, fp);
	fclose(fp);
}

void imoveis_de_bairro0(char *raiz, char *bairro, int t, FILE *fp){
	TARVBM *x = TARVBM_carrega(raiz, t);
	int i;
	free(raiz);
	if(!x){
		TARVBM_libera_no(x, t);
		return;
	}
	for(i = 0; i < x->nchaves; i++){
		if(strcmp(x->imovel[i]->bairro, bairro) == 0)
			TIM_salva(x->imovel[i], fp);
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	imoveis_de_bairro0(proxNo, bairro, t, fp);
}

void imoveis_de_um_tipo(char *tipo, int t){
	FILE *fp = fopen("imoveis_tipo.bin", "wb+");
	if(!fp){
		perror("Falha ao abir \"imoveis_tipo.bin\"");
		exit(1);
	}
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	imoveis_de_um_tipo0(noEsq, tipo, t, fp);
	fwrite("\0", sizeof(char), 1, fp);
	fclose(fp);
}

void imoveis_de_um_tipo0(char *raiz, char *tipo, int t, FILE *fp){
	TARVBM *x = TARVBM_carrega(raiz, t);
	int i;
	free(raiz);
	if(!x){
		TARVBM_libera_no(x, t);
		return;
	}
	for(i = 0; i < x->nchaves; i++){
		if(strcmp(x->imovel[i]->tipo, tipo) == 0)
			TIM_salva(x->imovel[i], fp);
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	imoveis_de_um_tipo0(proxNo, tipo, t, fp);
}

void imoveis_de_uma_metragem(float metragem, int t){
    FILE *fp = fopen("imoveis_metragem.bin", "wb+");
	if(!fp){
		perror("Falha ao abir \"imoveis_metragem.bin\"");
		exit(1);
	}
	char *noEsq = TARVBM_noMaisAEsq(TARVBM_pegaRaiz(), t);
	imoveis_de_uma_metragem0(noEsq, metragem, t, fp);
	fwrite("\0", sizeof(char), 1, fp);
	fclose(fp);
}

void imoveis_de_uma_metragem0(char *raiz, float metragem, int t, FILE *fp){
    TARVBM *x = TARVBM_carrega(raiz, t);
	int i;
	float precoT, precoM2, m;
	free(raiz);
	if(!x){
		TARVBM_libera_no(x, t);
		return;
	}
	for(i = 0; i < x->nchaves; i++){
        precoT = (x->imovel[i]->precoTotal) + (x->imovel[i]->centPrecT)/100.0;
        precoM2 = (x->imovel[i]->precoM2) + (x->imovel[i]->centPrecM2)/100.0;
        m = precoT/precoM2 - metragem;
        if((-1 < m) && (m < 1))
            TIM_salva(x->imovel[i], fp);
	}
	if(!x->prox){
		TARVBM_libera_no(x, t);
		return;
	}
	char *proxNo = TARVBM_alocaFilho();
	strcpy(proxNo, x->prox);
	TARVBM_libera_no(x, t);
	imoveis_de_uma_metragem0(proxNo, metragem, t, fp);
}

void limpa_tela(void){
    #if defined(_WIN32) || defined(_WIN64)
    system("cls");

    #else
    system("clear");
    #endif // defined
}

int inserir_novo_imovel(int t){
	char imovel[MAX_TAM_LINHA] = ""; // Inicializa como string vazia
    char buffer[MAX_TAM_LINHA];
    TIM *imo;

    printf("************ DIGITE AS INFORMAÇÕES DO IMÓVEL ************\n\n");
    getchar();
    printf("ID: ");
    fgets(buffer, MAX_TAM_NUM, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove o '\n'
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Bairro: ");
    fgets(buffer, MAX_TAM_BAIRRO, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Tipo: ");
    fgets(buffer, MAX_TAM_INFO, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Rua: ");
    fgets(buffer, MAX_TAM_RUA, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Número: ");
    fgets(buffer, 6, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Preço total: ");
    fgets(buffer, MAX_TAM_NUM, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Preço metro quadrado: ");
    fgets(buffer, MAX_TAM_NUM, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Descrição: ");
    fgets(buffer, MAX_TAM_DESC, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Cep: ");
    fgets(buffer, MAX_TAM_NUM, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Latitude: ");
    fgets(buffer, MAX_TAM_NUM, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);
    strcat(imovel, ";");

    printf("Longitude: ");
    fgets(buffer, MAX_TAM_BAIRRO, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    strcat(imovel, buffer);

    // Imprime a string final
    printf("\nDados do imóvel formatados: %s\n", imovel);

    // Converte para TIM e insere
    imo = TIM_lineToTIM(imovel);
    limpa_tela();
    return TARVBM_insere(imo, t);
}

void interface(){
	printf("\n\n**************** MENU ****************\n\n");
	printf("\t(01) IMÓVEL A VENDA MAIS BARATO\n");
	printf("\t(02) IMÓVEL A VENDA MAIS CARO\n");
	printf("\t(03) IMÓVEL ALUGADO MAIS BARATO\n");
	printf("\t(04) IMÓVEL ALUGADO MAIS CARO\n");
	printf("\t(05) LISTAR IMÓVEIS DE UM CEP\n");
	printf("\t(06) LISTAR IMÓVEIS DE UMA LATITUDE\n");
	printf("\t(07) LISTAR IMÓVEIS DE UMA LONGITUDE\n");
	printf("\t(08) LISTAR IMÓVEIS DE UMA RUA\n");
	printf("\t(09) LISTAR IMÓVEIS DE UM BAIRRO\n");
	printf("\t(10) LISTAR IMÓVEIS DE UM TIPO\n");
	//printf("\t(11) FORNECER UMA DESCRIÇÃO E BUSCAR PELO IMÓVEL\n");
	printf("\t(12) BUSCAR POR IMÓVEL DE UMA METRAGEM\n");
	//printf("\t(13) FORNECER DESCRIÇÃO E OBTER INFORMAÇOES ADICIONAIS\n");
	printf("\t(14) INSERIR IMÓVEL\n");
	//printf("\t(15) REMOVER IMÓVEIS POR FAIXA DE PREÇO\n");
	printf("\t(16) REMOVER IMÓVEL\n");
	printf("\t(18) BUSCAR IMÓVEL PELO ID\n");
	printf("\t(17) MOSTRAR NÓ\n");
	printf("\t(00) ENCERRAR\n");
}

int pega_grau(){
	int escolha;
	printf("Ecolha um valor para t(grau da árvore, deve ser maior ou igual a 2): ");
	scanf("%d", &escolha);
	while(escolha < 2){
		printf("\nOPÇÃO INVÁLIDA!\n");
		printf("Ecolha um valor para t(grau da árvore, deve ser maior ou igual a 2): ");

		scanf("%d", &escolha);
	}
	printf("\n\n");
	return escolha;
}

int pega_escolha(){
	int escolha;
	printf("Sua escolha: ");
	scanf("%d", &escolha);
	while((escolha < 0) || (escolha > 20)){
		printf("OPÇÃO INVÁLIDA!\n");
		printf("Sua escolha: ");
		scanf(" %d", &escolha);
	}
	return escolha;
}

void switch_escolha(int escolha, int t){
	char esc;
	limpa_tela();
	switch(escolha){
		case 1: {
			TIM *resp = imovelAVendaMaisBarato(t);
			printf("\n\n*************** IMÓVEL A VENDA MAIS BARATO ***************\n");
			mostra_imovel(resp);
			break;
		}
		case 2: {
			TIM *resp = imovelAVendaMaisCaro(t);
			printf("\n\n*************** IMÓVEL A VENDA MAIS CARO ***************\n");
			mostra_imovel(resp);
			break;
		}
		case 3: {
			TIM *resp = imovelAlugadoMaisBarato(t);
			printf("\n\n*************** IMÓVEL ALUGADO MAIS BARATO ***************\n");
			mostra_imovel(resp);
			break;
		}
		case 4: {
			TIM *resp = imovelAlugadoMaisCaro(t);
			printf("\n\n*************** IMÓVEL ALUGADO MAIS CARO ***************\n");
			mostra_imovel(resp);
			break;
		}
		case 5: {
			int cep;
			printf("Digite o cep: ");
			scanf("%d", &cep);
			imoveis_do_cep(cep, t);
			printf("\n\n*************** LISTA DE IMÓVEIS COM CEP %d ***************\n", cep);
			mostra_arquivo_imoveis("imoveis_cep.bin");
			break;
		}
		case 6: {
			float lat;
			printf("Digite a latitude: ");
			scanf("%f", &lat);
			imoveis_da_lat(lat, t);
			printf("\n\n*************** LISTA DE IMÓVEIS COM LATITUDE %f ***************\n", lat);
			mostra_arquivo_imoveis("imoveis_lat.bin");
			break;
		}
		case 7: {
			float lon;
			printf("Digite a longitude: ");
			scanf("%f", &lon);
			imoveis_da_long(lon, t);
			printf("\n\n*************** LISTA DE IMÓVEIS COM LONGITUDE %f ***************\n", lon);
			mostra_arquivo_imoveis("imoveis_long.bin");
			break;
		}
		case 8: {
			char *rua = malloc(MAX_TAM_RUA * sizeof(char));
			printf("Digite a rua: ");
			getchar();
			fgets(rua, MAX_TAM_RUA, stdin);
			rua[strcspn(rua, "\n")] = '\0';
			imoveis_da_rua(rua, t);
			printf("\n\n*************** LISTA DE IMÓVEIS DA RUA %s ***************\n", rua);
			mostra_arquivo_imoveis("imoveis_rua.bin");
			free(rua);
			break;
		}
		case 9: {
			char *bairro = malloc(MAX_TAM_BAIRRO * sizeof(char));
			printf("Digite o bairro: ");
			getchar();
			fgets(bairro, MAX_TAM_BAIRRO, stdin);
			bairro[strcspn(bairro, "\n")] = '\0';
			imoveis_de_bairro(bairro, t);
			printf("\n\n*************** LISTA DE IMÓVEIS DO BAIRRO %s ***************\n\n", bairro);
			mostra_arquivo_imoveis("imoveis_bairro.bin");
			free(bairro);
			break;
		}
		case 10: {
			char *tipo = malloc(MAX_TAM_INFO * sizeof(char));
			printf("Digite o tipo: ");
			getchar();
			fgets(tipo, MAX_TAM_INFO, stdin);
			tipo[strcspn(tipo, "\n")] = '\0';
			imoveis_de_um_tipo(tipo, t);
			printf("\n\n*************** LISTA DE IMÓVEIS DO TIPO %s ***************\n", tipo);
			mostra_arquivo_imoveis("imoveis_tipo.bin");
			free(tipo);
			break;
		}
		case 12: {
            float metragem;
			printf("Digite a metragem: ");
			scanf("%f", &metragem);
            imoveis_de_uma_metragem(metragem, t);
			printf("\n\n*************** LISTA DE IMÓVEIS DE METRAGEM %.3f ***************\n", metragem);
			mostra_arquivo_imoveis("imoveis_metragem.bin");
			break;
		}
		case 14: {
			inserir_novo_imovel(t) ? printf("\nImóvel inserido com sucesso!") : printf("\nFalha ao inserir imóvel!");
			break;
		}
		case 16: {
            long int id;
			printf("Digite o id: ");
			scanf("%ld", &id);
			TARVBM_retira(id, t) ? printf("\nImóvel removido!\n") : printf("\nImóvel não  encontrado na base de dados!\n");
			break;
		}
		case 18: {
            long int id;
            printf("Digite o id: ");
            scanf("%ld", &id);
            TIM *imo = TARVBM_busca_id(TARVBM_pegaRaiz(), id, t);
            if(imo){
                printf("\n\n*************** IMÓVEL ENCONTARDO ***************\n\n");
                mostra_imovel(imo);
            }
            else
           	printf("\n\nIMÓVEL NÃO ENCONTRADO!!!\n\n");
            break;
		}
		case 17: {
		      char *no = (char*)malloc(sizeof(char) * MAX_TAM_ARQ);
		      printf("Digite o nome do nó: ");
		      getchar();
		      fgets(no, MAX_TAM_ARQ, stdin);
		      no[strcspn(no, "\n")] = '\0';
		      TARVBM *teste = TARVBM_carrega(no, t);
		      if(!teste){
		      	printf("Nó não encontrado!\n");
		      	break;
		      }
		      mostra_no(teste);
		      TARVBM_libera_no(teste, t);
		      break;
		 }
        default: {
			printf("salvar alterações?[S/N]?: ");
			scanf(" %c", &esc);
			while((esc != 's') && (esc != 'S') && (esc != 'n') && (esc != 'N')){
				printf("OPÇÃO INVÁLIDA!\n");
				printf("Deseja manter os arquivos salvos[S/N]?: ");
			}
			if((esc == 'n') || (esc == 'N'))
				limpa_arquivos();
			else
				TARVBM_salva_grau_no(t);
			exit(1);
		}
	}
	continuidade(t);
}

int verifica_arquivo_salvo(int *t){
	FILE *fp = fopen("grau_no.bin", "rb");
	if(!fp){
		limpa_arquivos();
		return 0;
	}
	char esc;
	printf("Existe um arquivo de imóveis salvo, deseja usa-lo? ");
	scanf("%c", &esc);
	while((esc != 's') && (esc != 'S') && (esc != 'n') && (esc != 'N')){
		printf("OPÇÃO INVÁLIDA!\n");
		printf("Salvar alterações[S/N]?: ");
	}
	if((esc == 'n') || (esc == 'N')){
		fclose(fp);
		remove("grau_no.bin");
		return 0;
	}
	fread(t, sizeof(int), 1, fp);
	fclose(fp);
	return 1;
}

TIM* pega_imo_no_arquivo(int pos){
	FILE *fp = fopen("TC_EDA_LIMPO.csv", "r");
	if(!fp) exit(1);
	char c;
	char linha[MAX_TAM_LINHA];
	TIM *imo;
	int i = 0;
	do{
		fscanf(fp, "%c", &c);
	} while(c != '\n');
	while (i < pos) {
	    fgets(linha, sizeof(linha), fp);
        linha[strcspn(linha, "\n")] = '\0';
        imo = TIM_lineToTIM(linha);
        i++;
        if(feof(fp)) break;
	}
	fclose(fp);
	return imo;
}

void continuidade(int t){
    char escolha;
    printf("\nContinuar?? [S/N]: ");
    scanf(" %c", &escolha);

    if(escolha == 'S' || escolha == 's'){
        limpa_tela();
        return;
    }
    if(escolha == 'N' || escolha == 'n'){
        char escolha2_revangence;
        printf("\nSalvar alterações? [S/N]: ");
        scanf(" %c", &escolha2_revangence);
        if(escolha2_revangence == 'S' || escolha2_revangence == 's'){
            TARVBM_salva_grau_no(t);
            exit(1);
        }
        if(escolha2_revangence == 'N' || escolha2_revangence == 'n'){
            limpa_arquivos();
            exit(1);
        }
    }
    continuidade(t);
}