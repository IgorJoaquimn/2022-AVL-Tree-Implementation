#ifndef HASH
#define HASH

#include <stdio.h>
#include <fstream>
#include "memlog.h"
#include "email.h"
#include "node.h"
#include "arvore.h"



class tabelaH
// Descrição: TAD para representar uma arvore AVL.
{
private:
    arvore *dados;
    int M = 1;

public:
    std::ofstream * output;
    // Construtor
    tabelaH(int M,std::ofstream * output);
    ~tabelaH();

    // Funções de controle.
    node_t *insere(email *e);
    node_t *pesquisa(int idUsuario, int idMensagem);
    bool apaga   (int idUsuario, int idMensagem);

    // Operadores
    // bool operator==(const email &outra) const;
    // bool operator< (const email &outra) const;
};
#endif
