#ifndef _STRUCT_H
#define _STRUCT_H

#include <stddef.h>

//Definição de artigo
typedef struct artigo
{
	 int codigo;
	 int nome;
	 float preco;
}artigo;

//Definição de String
typedef struct string
{
	char *nome;

}string;

//Definição de stock
typedef struct stock
{
	int stock;

}stock;

//Definição de Venda
typedef struct venda
{
	int codigo;
	int quantidade;
	float total;

}venda;

//Definição de preco
typedef struct precoM
{
	float preco;
	int cod;
}precoM;



#endif /* _STRUCT_H */