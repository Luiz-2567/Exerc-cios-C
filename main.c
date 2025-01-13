#include "catalogo_imoveis.h"
#include <stdio.h>

void interface();
int pega_escolha();
int pega_grau();
void teste_leitura();
TIM* pega_imo_no_arquivo(int pos);
void switch_escolha(int escolha, int t);
int verifica_arquivo_salvo(int *t);
void gera_arvore(int t);

int main(int argc, char *argv[])
{
	int t, escolha, controle;
	controle = verifica_arquivo_salvo(&t);
	if(!controle){
		limpa_arquivos();
		t = pega_grau();
		gera_arvore(t);
	}
	interface();
	escolha = pega_escolha();
	switch_escolha(escolha, t);
	while(escolha){
		interface();
		escolha = pega_escolha();
		switch_escolha(escolha, t);
	}
	/*TARVBM *teste = TARVBM_carrega("no14.bin", 2);
	mostra_no(teste);*/
	//printf("%lf", a->lon - a->decLong/divisor_casas_decimais(a->decLong));
	return 0;
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
	printf("\t(08) LISTAR IMOVEIS DE UMA RUA\n");
	//printf("\t(09) LISTAR IMOVEIS DE UM BAIRRO\n");
	//printf("\t(10) LISTAR IMOVEIS DE UM TIPO\n");
	//printf("\t(11) FORNECER UMA DESCRIÇÃO E BUSCAR PELO IMÓVEL\n");
	//printf("\t (12) BUSCAR POR IMÓVEL DE UMA METRAGEM\n");
	//printf("\t(13) FORNECER DESCRIÇÃO E OBTER INFORMAÇOES ADICIONAIS\n");
	//printf("\t(14) INSERIR IMÓVEL\n");
	//printf("\t(15) REMOVER IMÓVEIS POR FAIXA DE PREÇO\n");
	printf("\t(00) ENCERRAR\n");
}

int pega_grau(){
	int escolha;
	printf("Ecolha um valor para t(grau da árvore, deve ser maior que 2): ");
	scanf("%d", &escolha);
	while(escolha < 2){
		printf("\nOPÇÃO INVÁLIDA!\n");
		printf("Ecolha um valor para t(grau da árvore, deve ser maior que 2): ");
		
		scanf(" %d", &escolha);
	}
	printf("\n\n");
	return escolha;
}

int pega_escolha(){
	int escolha;
	printf("Sua escolha: ");
	scanf("%d", &escolha);
	while((escolha < 0) || (escolha > 15)){
		printf("OPÇÃO INVÁLIDA!\n");
		printf("Sua escolha: ");
		scanf(" %d", &escolha);
	}
	return escolha;
}

void switch_escolha(int escolha, int t){
	char esc;
	switch(escolha){
		case 1: {
			TIM *resp = imovelAVendaMaisBarato(t);
			printf("\n\n*************** IMÓVEL A VENDA MAIS BARATO ***************\n\n");
			mostra_imovel(resp);
			break;
		}
		case 2: {
			TIM *resp = imovelAVendaMaisCaro(t);
			printf("\n\n*************** IMÓVEL A VENDA MAIS CARO ***************\n\n");
			mostra_imovel(resp);
			break;
		}
		case 3: {
			TIM *resp = imovelAlugadoMaisBarato(t);
			printf("\n\n*************** IMÓVEL ALUGADO MAIS BARATO ***************\n\n");
			mostra_imovel(resp);
			break;
		}
		case 4: {
			TIM *resp = imovelAlugadoMaisCaro(t);
			printf("\n\n*************** IMÓVEL ALUGADO MAIS CARO ***************\n\n");
			mostra_imovel(resp);
			break;
		}
		case 5: {
			int cep;
			printf("Digite o cep: ");
			scanf("%d", &cep);
			imoveis_do_cep(cep, t);
			printf("\n\n*************** LISTA DE.IMÓVEIS COM CEP %d ***************\n\n", cep);		mostra_arquivo_imoveis("imoveis_cep.bin");
			break;
		}
		case 6: {
			float lat;
			printf("Digite a latitude: ");
			scanf("%f", &lat);
			imoveis_da_lat(lat, t);
			printf("\n\n*************** LISTA DE.IMÓVEIS COM LATITUDE %f ***************\n\n", lat);		mostra_arquivo_imoveis("imoveis_lat.bin");
			break;
		}
		case 7: {
			float lon;
			printf("Digite a longitude: ");
			scanf("%f", &lon);
			imoveis_da_long(lon, t);
			printf("\n\n*************** LISTA DE.IMÓVEIS COM LONGITUDE %f ***************\n\n", lon);		mostra_arquivo_imoveis("imoveis_long.bin");
			break;
		}
		case 8: {
			char *rua = calloc(MAX_TAM_RUA, sizeof(char));
			printf("Digite a rua: ");
			getchar();
			fgets(rua, MAX_TAM_RUA, stdin);
			rua[strcspn(rua, "\n")] = '\0';
			imoveis_da_rua(rua, t);
			printf("\n\n*************** LISTA DE.IMÓVEIS DA RUA %s ***************\n\n", rua);		mostra_arquivo_imoveis("imoveis_rua.bin");
			break;
		}
		default: {
			printf("Deseja manter os arquivos salvos(S/N)?: ");
			scanf(" %c", &esc);
			while((esc != 's') && (esc != 'S') && (esc != 'n') && (esc != 'N')){
				printf("OPÇÃO INVÁLIDA!\n");
				printf("Deseja manter os arquivos salvos(S/N)?: ");
			}
			if((esc == 'n') || (esc == 'N'))
				limpa_arquivos();
			else
				TARVBM_salva_grau_no(t);
			exit(1);
		}
	}
}

void gera_arvore(int t){
	FILE *fp = fopen("TC_EDA_LIMPO.csv", "r");
	if(!fp) exit(1);
	char c;
	char buffer[MAX_TAM_LINHA];
	TIM *imo;
	int i = 0, cont;
	do{
		fscanf(fp, "%c", &c);
	} while(c != '\n');
	while (i < 199) {
	    fgets(buffer, sizeof(buffer), fp);
        buffer[strcspn(buffer, "\n")] = '\0';
        imo = TIM_lineToTIM(buffer);
        printf("\n\n\nInserindo %d: %ld...", i + 1,  imo->id);
        cont = TARVBM_insere(imo, t);
        if(cont == 0)
        	printf("\n\nFalha ao inserir imóvel %d chave %ld, imóvel ja foi salvo!\n\n", i + 1, imo->id);
        free(imo);
        i++;
	}
	fclose(fp);
}

int verifica_arquivo_salvo(int *t){
	FILE *fp = fopen("grau_no.bin", "rb");
	if(!fp){
		FILE *fp = fopen("no0.bin", "rb");
		if(fp){
			fclose(fp);
			limpa_arquivos();
		}
		return 0;
	}
	char esc;
	printf("Existe um arquivo de imóveis salvo, deseja usa-lo? ");
	scanf("%c", &esc);
	while((esc != 's') && (esc != 'S') && (esc != 'n') && (esc != 'N')){
		printf("OPÇÃO INVÁLIDA!\n");
		printf("Deseja manter os arquivos salvos(S/N)?: ");
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
	return imo;
	fclose(fp);
}