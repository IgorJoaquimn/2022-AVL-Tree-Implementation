#ifndef NODE
#define NODE
#include <stdio.h>
#include "email.h"

class node_t
{
private:
    int idUsuario, idMensagem, altura = 1;
    email *conteudo     = nullptr;


    // Ponteiros para gerir arvore AVL.
    node_t *direita     = nullptr;
    node_t *esquerda    = nullptr;

    node_t *pai         = nullptr;

public:
    // Construtor.
    node_t();
    node_t(int idUsuario, int idMensagem, email *email);

    //Funcoes
    int atualiza_altura();
    int fator_balanceamento();

    // Operadores
    bool operator==(const node_t &outro) const;
    bool operator< (const node_t &outro) const;
    friend class arvore;
    friend class tabelaH;
};
#endif
