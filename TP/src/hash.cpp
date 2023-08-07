#include "hash.h"

tabelaH::tabelaH(int M,std::ofstream * output)
// Descricao: construtor da tabela;
// entrada: M = quantidade de linhas na tabela;
//          output = referencia para arquivo a ser escrito;
// saida: objeto construido.
{
    this->M = M;
    this->output = output; 
    dados = new arvore[M];
}

tabelaH::~tabelaH()
// Descricao: destrutor da tabela;
// Ao se excluir uma tabela, deve-se desalocar todos os seus dados.
{
    delete[] this->dados;
}

node_t *tabelaH::insere(email *e)
// Descricao: operacao de insercao na tabela;
// entrada: email a ser inserido;
// saida: objeto inserido.
{
    // B = funcao de hash;
    int b = e->get_idUsuario() % this->M;
    node_t * retorno = dados[b].insere(e);
    (*output) << "OK: MENSAGEM " << retorno->idMensagem << " PARA " << retorno->idUsuario <<" ARMAZENADA EM "<< b << std::endl;
    return retorno;
}

node_t *tabelaH::pesquisa(int idUsuario, int idMensagem)
// Descricao: operacao de pesquisa na tabela;
// entrada: email a ser pesquisado;
// saida: objeto pesquisado.
{
    // B = funcao de hash;
    int b = idUsuario % M;
    node_t * retorno = dados[b].pesquisa(idUsuario,idMensagem);

    // Se elemento existir;
    if(retorno != nullptr)
    {
        (*output) <<"CONSULTA " << retorno->idUsuario << " " << retorno->idMensagem << ": ";
        retorno->conteudo->impressao(output); 
    }
    // Se nao;
    else
        (*output) <<"CONSULTA " << idUsuario << " " << idMensagem << ": MENSAGEM INEXISTENTE" << std::endl;

    return retorno;
}

bool tabelaH::apaga(int idUsuario, int idMensagem)
// Descricao: operacao de remocao na tabela;
// entrada: email a ser removido;
// saida: objeto removido.
{
    int b = idUsuario % M;
    bool retorno = dados[b].apaga(idUsuario,idMensagem);
    if(retorno)
        (*output) <<"OK: MENSAGEM APAGADA" << std::endl;
    else
        (*output) <<"ERRO: MENSAGEM INEXISTENTE" << std::endl;
    return retorno;
}
