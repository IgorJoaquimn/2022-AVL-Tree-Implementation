#include "email.h"

email::email(int idUsuario, int idMensagem, int NumeroDePalavras)
// Descricao: construtor do TAD email;
// entrada: identificador de Usuario e de Mensagem, sao unicos por hipotese;
// saida: objeto construido.
{
    this->idUsuario     = idUsuario;
    this->idMensagem    = idMensagem;
    this->NumeroDePalavras = NumeroDePalavras;
    mensagem = new std::string[NumeroDePalavras];
}


int email::get_idUsuario()
// Descricao: Acesso ao id do Usuario;
// saida: idUsuario.
{
    return this->idUsuario;
}
int email::get_idMensagem()
// Descricao: Acesso ao id da Mensagem;
// saida: idMensagem.
{
    return this->idMensagem;
}
std::string *email::get_mensagem()
// Descricao: Acesso a mensagem;
// saida: mensagem.
{
    return this->mensagem;
}

void email::impressao(std::ofstream *output)
// Descricao: Impressao do conteudo de um email em um arquivo de saida;
// entrada: referencia ao arquivo a ser escrito.
// saida: mensagem armazenada no arquivo output.
{
    for (int i = 0; i < NumeroDePalavras - 1; i++)
        (*output) << mensagem[i] << " ";
    (*output) << mensagem[NumeroDePalavras-1] << std::endl;
}

void email::leitura(std::ifstream *input)
// Descricao: Leitura do conteudo de um email a partir de um arquivo de entrada;
// entrada: referencia ao arquivo a ser lido.
// saida: mensagem[MAX] armazenada.
{
    
    for (int i = 0; i < NumeroDePalavras; i++)
        (*input) >> mensagem[i];
}