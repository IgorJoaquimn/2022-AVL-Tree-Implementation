#ifndef EMAIL
#define EMAIL

#include <iostream>
#include <fstream>
#include <string>
#include "memlog.h"

#define MAX 200

class email
// Descrição: TAD para representar um email.
{
private:
    int idUsuario, idMensagem;

public:
    int NumeroDePalavras;
    std::string *mensagem = nullptr;
    // Construtor.
    email(int idUsuario, int idMensagem, int NumeroDePalavras);

    // Funções de acesso.
    int get_idUsuario();
    int get_idMensagem();
    std::string *get_mensagem();

    // Funcoes de manipulacao de arquivo.
    void impressao(std::ofstream * output);
    void leitura(std::ifstream * input);

    // Operadores
    // bool operator==(const email &outra) const;
    // bool operator< (const email &outra) const;
    friend class node_t;
};
#endif
