#include "node.h"

int max(int a, int b) 
{
    return a > b ? a : b;
}

node_t::node_t( )
// Descricao: Construtor do no, a partir de um email.
// entrada: id do Usuario e da Mensagem, alem do email a ser referenciado.
// saida: objeto construido.
{
    this->idMensagem = 1;
    this->idUsuario = 1;
    this->conteudo = nullptr;
    this->altura = 1;
    this->direita = nullptr;
    this->esquerda = nullptr;
    this-> pai = nullptr;
}
node_t::node_t(int idUsuario, int idMensagem, email *email)
// Descricao: Construtor do no, a partir de um email.
// entrada: id do Usuario e da Mensagem, alem do email a ser referenciado.
// saida: objeto construido.
{
    this->idMensagem    = idMensagem;
    this->idUsuario     = idUsuario;
    this->conteudo      = email;
    this->altura = 1;
    this->direita = nullptr;
    this->esquerda = nullptr;
    this-> pai = nullptr;
}


int node_t::atualiza_altura()
// Descricao: Funcao para atualizar a altura de um nó e seus "antepassados", recursivamente.
// saida: alturas da arvore atualizadas.
{
    // Todo nó comeca com altura 1.
    // Caso ele nao tenha filhos, ele é folha e sua altura é 1.
    altura = 1;
    // // Caso ele tenha 2 filhos, sua altura é incrementada pela maior alturas entre eles.
    if ((this->direita != nullptr) && (this->esquerda != nullptr))
    {
        altura = altura + std::max(this->direita->altura,this->esquerda->altura);

    }
    // Caso ele tenha 1 filho, sua altura é incrementada pela altura de seu filho;
    else if (direita != nullptr)
        altura += direita->altura;
    else if (esquerda != nullptr)
        altura += esquerda->altura;

    // Com a altura atualizada, deve-se re-calcular a altura do pai do nó atual, se ele existir. 

    if(pai != nullptr)
    pai->atualiza_altura();
    return altura;
}

int node_t::fator_balanceamento()
// Descricao: Funcao para calcular o fator de balanceamento de um no.
// saida: fator de balanceamento do no.
{
    int balance = 0;
    // Se o no possui 2 filhos, o fator de balanceamento é a diferenca entre a altura deles;
    if (direita != nullptr && esquerda != nullptr)
        balance = direita->altura - esquerda->altura;
    // Se existir apenas o filho direito, o fator é a altura de seu filho;
    else if (direita != nullptr)
        balance = direita->altura;
    // Se existir apenas o filho esquerdo, o fator é a altura de seu filho negativada;
    else if (esquerda != nullptr)
        balance = esquerda->altura*-1;
    return balance;
}

bool node_t::operator==(const node_t &outro) const
// Descricao: operador de igualde em nós, um nó é igual ao outro se e somente se eles tiverem os mesmos ids de Usuario e de Mensagem.
// saida: saida da condicao de igualdade.
{
    return (this->idUsuario == outro.idUsuario && this->idMensagem == outro.idMensagem);
}

bool node_t::operator<(const node_t &outro) const
// Descricao: operador "menor que" entre nós, um nó é menor que outro se seu id de mensagem for menor que o outro.
// saida: saida da condicao de menor.
{
    return (this->idMensagem < outro.idMensagem);
}