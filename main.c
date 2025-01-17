#include "catalogo_imoveis.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	int t, escolha, controle;
	controle = verifica_arquivo_salvo(&t);
	limpa_tela();
	if(!controle){
		limpa_arquivos();
		t = pega_grau();
        TARVBM_gera_arvore(t);
        limpa_tela();
	}
	//t = 2;
	interface();
	escolha = pega_escolha();
	switch_escolha(escolha, t);
	while(escolha){
		interface();
		escolha = pega_escolha();
		switch_escolha(escolha, t);
	}
	return 0;
}