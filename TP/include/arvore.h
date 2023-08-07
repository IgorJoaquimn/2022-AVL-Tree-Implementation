#ifndef AVL
#define AVL

#include <stdio.h>
#include <math.h>
#include <string>
#include "memlog.h"
#include "node.h"
#include "email.h"


class arvore
// Descrição: TAD para representar uma arvore AVL.
{
private:
    node_t * raiz = nullptr;

public:
    ~arvore();
    // Funções de manipulacao
    node_t *insere(email *e);
    node_t *pesquisa(int idUsuario, int idMensagem);
    bool apaga   (int idUsuario, int idMensagem);

    // Funcoes para garantir as propriedades da AVL.
    void balanceia(node_t *node);
    void rotaciona_direita(node_t *node);
    void rotaciona_esquerda(node_t *node);

    void desaloca(node_t * node);

    // Operadores
    // bool operator==(const email &outra) const;
    // bool operator< (const email &outra) const;
    friend class tabelaH;
};
#endif
