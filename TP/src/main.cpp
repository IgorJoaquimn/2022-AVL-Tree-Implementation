#include <iostream>
#include <fstream>
#include <getopt.h>
#include "email.h"
#include "arvore.h"
#include "hash.h"
#include "memlog.h"
#include "msgassert.h"

std::string input_nome, output_nome;

void parse_args(int argc, char **argv)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc e argv
// Saida (obrigatorio): input_nome,output_nome,mediana,size
{
    // variaveis externas do getopt
    extern char *optarg;
    char c;

    while ((c = getopt(argc, argv, "i:I:o:O:")) != EOF)
        switch (c)
        {
        case 'i':
        case 'I':
            input_nome = optarg;
            break;
        case 'o':
        case 'O':
            output_nome = optarg;
            break;
        default:
            return;
        }
}

int main(int argc, char **argv)
// Descricao: Parte principal do programa, função responsável por lidar com entradas e saídas.
// entrada: "entrada.txt"
// saida: "saida.txt"
{
    parse_args(argc, argv);
    std::ifstream input;
    std::ofstream output;
    input.open(input_nome);
    output.open(output_nome);
    erroAssert(input.is_open(), "Erro ao abrir arquivo de entrada");
    erroAssert(output.is_open(), "Erro ao abrir arquivo de entrada");
    
    int M;
    input >> M;
    // Controle para qual operacao realizar
    std::string parametro;

    tabelaH hash(M,&output);
    int idUsuario, idMensagem, NumeroDePalavras;

    while (input >> parametro)
    {
        input >> idUsuario >> idMensagem;
        if (parametro == "ENTREGA")
        {
            input >> NumeroDePalavras;
            email *E = new email(idUsuario,idMensagem, NumeroDePalavras);
            E->leitura(&input);
            hash.insere(E);
        }
        else if (parametro == "CONSULTA")
        {
            hash.pesquisa(idUsuario, idMensagem);
        }
        else if (parametro == "APAGA")
        {
            hash.apaga(idUsuario, idMensagem);
        }
        else
        {
            std::cout << "deu ruim" << std::endl;
            break;
        }
    }
    return 0;
}