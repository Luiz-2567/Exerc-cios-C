#ifndef CATALOGO_IMOVEIS_H
#define CATALOGO_IMOVEIS_H

#include "TARVBM_TIM.h"

int salva_imoveis_a_venda(int t);
void salva_imoveis_a_venda0(char *raiz, int t, FILE *fp);
TIM* imovelAVendaMaisBarato(int t);
void imovelAVendaMaisBarato0(char *raiz, TIM **imo, int t);
TIM* imovelAlugadoMaisBarato(int t);
void imovelAlugadoMaisBarato0(char *raiz, TIM **imo, int t);
TIM* imovelAlugadoMaisCaro(int t);
void imovelAlugadoMaisCaro0(char *raiz, TIM **imo, int t);
TIM* imovelAVendaMaisCaro(int t);
void imovelAVendaMaisCaro0(char *raiz, TIM **imo, int t);
void imoveis_do_cep(int cep, int t);
void imoveis_do_cep0(char *raiz, int cep, int t, FILE *fp);
void imoveis_da_lat(float lat, int t);
void imoveis_da_lat0(char *raiz, float lat, int t, FILE *fp);
void imoveis_da_long(float lon, int t);
void imoveis_da_long0(char *raiz, float lon, int t, FILE *fp);
void imoveis_da_rua(char *rua, int t);
void imoveis_da_rua0(char *raiz, char *rua, int t, FILE *fp);
 #endif 