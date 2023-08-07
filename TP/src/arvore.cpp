#include "arvore.h"

node_t *arvore::insere(email *e)
// Descricao: Insere um novo email na árvore;
// entrada: email *e = referência ao email a ser armazenado;
// saida: referência ao nó inserido.
{
    int id = e->get_idMensagem();
    node_t *node = new node_t(e->get_idUsuario(), e->get_idMensagem(), e);
    node_t *aux = raiz;

    // Caso base: primeira insercao.
    if (raiz == nullptr)
        raiz = node;

    // Caminhamento na arvore binaria. 
    // Elemento é inserido no primeiro nó vazio encontrado no caminhamento.
    while (aux != nullptr)
    {
        LEMEMLOG((long int)((aux)),sizeof(node_t),0);
        if (id < aux->idMensagem)
        {
            if (aux->esquerda == nullptr)
            {
                node->pai = aux;
                aux->esquerda = node;
                break;
            }
            aux = aux->esquerda;
        }
        else
        {
            if (aux->direita == nullptr)
            {
                node->pai = aux;
                aux->direita = node;
                break;
            }
            aux = aux->direita;
        }
    }

    // Sempre que um novo nó é inserido, deve-se recalcular a altura de seus ancestrais na arvore.
    node->atualiza_altura();
    // // // Alem disso, deve se re-balancear a arvore, a partir do no inserido;
    balanceia(node);
    return node;
}

node_t *arvore::pesquisa(int idUsuario, int idMensagem)
// Descricao: Funcao que procura no na arvore. Um email esta na arvore se e somente se existir um no com os mesmos ids de Usuario e de Mensagem daquele procurado.
// entrada: ids de Usuario e de Mensagem para procura.
// saida: referencia ao nó se ele for encontrado, nullptr caso contrario.
{
    node_t *aux = raiz;
    // Caminhamento na arvore binaria. Condicao de parada, encontrar o fim da arvore ou encontrar um email com o mesmo id de mensagem procurado. 
    while (aux != nullptr)
    {
        LEMEMLOG((long int)((aux)),sizeof(node_t),2);
        if(aux->idMensagem == idMensagem) break;
        if (idMensagem < aux->idMensagem)
            aux = aux->esquerda;
        else
            aux = aux->direita;
    }
    LEMEMLOG((long int)((aux)),sizeof(node_t),2);
    // Caso o no exista, seu id de usuario deve ser o mesmo que o id procurado, caso contrario, retorna nullptr.
    return (aux != nullptr && (aux->idUsuario == idUsuario && aux->idMensagem == idMensagem)) ? aux : nullptr;
}

bool arvore::apaga(int idUsuario, int idMensagem)
// Descricao: Funcao que apaga no na arvore. Um email pode ser apagado se estiver na arvore.
// A fim de manter o balanceamento, devem ser feitas balanceamentos adicionais.
// entrada: ids de Usuario e de Mensagem para procura.
// saida: true se ele for encontrado e removido, false caso contrario.
{

    node_t *alvo = pesquisa(idUsuario, idMensagem);
    // Mensagem nao encontrada
    if (alvo == nullptr)
        return false;
    node_t *actual = nullptr;
    node_t *filho;
    LEMEMLOG((long int)((alvo)),sizeof(node_t),3);
    LEMEMLOG((long int)((alvo->esquerda)),sizeof(node_t),3);
    LEMEMLOG((long int)((alvo->direita)),sizeof(node_t),3);
    LEMEMLOG((long int)((alvo->pai)),sizeof(node_t),3);
    if(alvo != raiz)
    {
        LEMEMLOG((long int)((alvo->pai->esquerda)),sizeof(node_t),3);
        LEMEMLOG((long int)((alvo->pai->direita)),sizeof(node_t),3);
    }
    // Caso 1: No folha
    if (alvo->esquerda == nullptr && alvo->direita == nullptr)
    {
        
        // Caso base: remover Folha que tambem é raiz da arvore;
        if (alvo == raiz)
            raiz = nullptr;
        // Se nao for raiz, o pai do nó deve deixar de referenciar o elemento alvo, verificando se ele é o filho esquerdo ou direito do pai; 
        else
        {
            alvo->pai->esquerda = (alvo->pai->esquerda == alvo) ? nullptr : alvo->pai->esquerda;
            alvo->pai->direita  = (alvo->pai->direita  == alvo) ? nullptr : alvo->pai->direita;
        }
        
        // Nesse caso, o balanceamento deve comecar a partir do pai do atual;
        actual = alvo->pai;
        delete alvo;
    }
    // Caso 2: No com 1 filho;
    else if ((alvo->esquerda == nullptr || alvo->direita == nullptr))
    {
        if(alvo->direita != nullptr)
        {
            filho = alvo->direita;
            alvo->direita = nullptr;
        }
        else
        {
             filho = alvo->esquerda;
            alvo->esquerda = nullptr;
        }


        delete[] alvo->conteudo->mensagem;
        // O filho deve tomar o lugar do pai;
        alvo->conteudo   = filho->conteudo;
        alvo->idMensagem = filho->idMensagem;
        alvo->idUsuario  = filho->idUsuario;

        if(filho->esquerda != nullptr)
        {
            filho->esquerda->pai = alvo;
            alvo->esquerda = filho->esquerda;
        }
        if(filho->direita != nullptr)
        {
            filho->direita->pai = alvo;
            alvo->direita = filho->direita;
        }
        actual = alvo;
        delete filho;
    }
    // Caso 3: No com 2 filhos;
    else if ((alvo->esquerda != nullptr && alvo->direita != nullptr))
    {
        
        // Primeiro, deve-se encontrar o antecessor do alvo;
        node_t *antecessor = alvo->esquerda;
        while (antecessor->direita != nullptr)
            antecessor = antecessor->direita;
        // O filho deve tomar o lugar do pai;
        delete[] alvo->conteudo->mensagem;
        alvo->conteudo   = antecessor->conteudo;
        alvo->idMensagem = antecessor->idMensagem;
        alvo->idUsuario  = antecessor->idUsuario;

        // Nesse caso, o balanceamento deve comecar a partir do pai do antecessor;
        actual =  antecessor->pai;

        // Movendo o filho do antecessor para cima;
        if(antecessor->pai != alvo)
        {
            antecessor->pai->direita = antecessor->esquerda;
            if(antecessor->esquerda != nullptr)
            antecessor->esquerda->pai = antecessor->pai;
        }
        else if (antecessor->pai != nullptr)
        {
            alvo->esquerda = antecessor->esquerda;
            if(antecessor->esquerda != nullptr)
            antecessor->esquerda->pai = alvo;
        }

        delete antecessor;
    }


    // Caso o primeiro nó a ser considerado o balanceamento exista, sua altura e de seus antepassados devem ser atualizadas. 
    if (actual != nullptr)
        actual->atualiza_altura();
    // Para manter a propriedade de balanceamento, a arvore precisa ser re-balanceada, a partir do no atual;
    balanceia(actual);
    // Após, deve-se apagar o no em questao;
    return true;
}

void arvore::balanceia(node_t *node)
// Descricao: Funcao recursiva que balanceia a arvore.
// entrada: nó para ser balanceado.
// saida: arvore balanceada.
{
    // Caso base, nó não existe;
    if (node == nullptr)
        return;

    LEMEMLOG((long int)((node)),sizeof(node_t),1);
    node_t *filho;
    // Casos recursivos 
    // Se o fator de balanceamento for negativo, existe um desbalanceamento na esquerda;
    if (node->fator_balanceamento() == -2)
    {
        filho = node->esquerda;
        // Caso 1 (Insercao): filho nao possui filho direito; 
        if ((filho->fator_balanceamento() == -1))
            rotaciona_direita(node);
        // Caso 3 (Insercao): caso complexo da insercao, deve-se transformar o caso 3 em caso 1;
        // Caso   (Remocao):  filho possui 2 filhos, sendo a altura do filho esquerdo maior que o direito, deve-se transformar em caso 1; 
        else
        {
            rotaciona_esquerda(filho);
            rotaciona_direita(node);
        }
    }

    else if (node->fator_balanceamento() == 2)
    {
        filho = node->direita;
        // Caso 2 (Insercao): filho nao possui filho esquerdo; 
        if ((filho->fator_balanceamento() == 1))
            rotaciona_esquerda(node);
        // Caso 4 (Insercao): caso complexo da insercao, deve-se transformar o caso 4 em caso 2;
        // Caso   (Remocao):  filho possui 2 filhos, sendo a altura do filho esquerdo menor que o direito, deve-se transformar em caso 2; 
        else
        {
            rotaciona_direita(filho);
            rotaciona_esquerda(node);
        }
    }
    balanceia(node->pai); 
}

void arvore::rotaciona_direita(node_t *node)
// Descricao: executa rotacao para direita. Premissa: node tem um pai;
// entrada: nó para ser balanceado.
// saida: arvore balanceada.
{
    LEMEMLOG((long int)((node)),sizeof(node_t),1);
    LEMEMLOG((long int)((node->direita)),sizeof(node_t),1);
    LEMEMLOG((long int)((node->esquerda)),sizeof(node_t),1);
    node_t *x = node->esquerda;
    node_t *T2 = x->direita;

    x->direita = node;
    node->esquerda = T2;
 
    if(node->pai != nullptr)
    {
        node->pai->esquerda = (node->pai->esquerda == node) ? x : node->pai->esquerda;
        node->pai->direita  = (node->pai->direita  == node) ? x : node->pai->direita;
    }
    else
        raiz = x;

    x->pai = node->pai;
    node->pai = x;
    if(T2 != nullptr)
    T2->pai = node; 
    node->atualiza_altura();
    if(T2 != nullptr)
    T2->atualiza_altura();
}

void arvore::rotaciona_esquerda(node_t *node)
// Descricao: executa rotacao para esquerda. Premissa: node tem um pai;
// entrada: nó para ser balanceado.
// saida: arvore balanceada.
{
    LEMEMLOG((long int)((node)),sizeof(node_t),1);
    LEMEMLOG((long int)((node->direita)),sizeof(node_t),1);
    LEMEMLOG((long int)((node->esquerda)),sizeof(node_t),1);
    node_t *x = node->direita;
    node_t *T2 = x->esquerda;

    x->esquerda = node;
    node->direita = T2;
 
    if(node->pai != nullptr)
    {
        node->pai->esquerda = (node->pai->esquerda == node) ? x : node->pai->esquerda;
        node->pai->direita  = (node->pai->direita  == node) ? x : node->pai->direita;
    }
    else
        raiz = x;

    x->pai = node->pai;
    node->pai = x;
    if(T2 != nullptr)
    T2->pai = node; 
    node->atualiza_altura();
    if(T2 != nullptr)
    T2->atualiza_altura();
}

void arvore::desaloca(node_t * node) 
// Descricao: desaloca recursivamente toda sub-arvore filha do no passado;
// entrada: node - nó para ser considerada a remocao;
{
    if(node == nullptr) return;

    // Caso base:
    // Remove filhos do no;
    desaloca(node->esquerda);
    desaloca(node->direita);
    node->esquerda = nullptr;
    node->direita = nullptr;
    // Remove no;
    delete[] node->conteudo->mensagem;
    
    delete node;
}

arvore::~arvore()   
// Descricao: destrutor da arvore, deve chamar uma funcao auxiliar para desalocar memoria dos nós;
{
    desaloca(raiz);
}