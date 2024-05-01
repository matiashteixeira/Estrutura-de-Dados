#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma {
    int identificador;
    string nomeAcao;
    int tempoExecucao;
    int tempoConsumido;
};


class noh {
    friend class listadup;
private:
    acaoPrograma acao; 
    noh* proximo;
    noh* anterior;
public:
    noh(acaoPrograma d);
};

noh::noh(acaoPrograma d) {
    acao = d;
    proximo = NULL;
    anterior = NULL;
}

class listadup {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista    
public:
    listadup();
    //listadup(const listadup& umaLista);
    ~listadup();
    //listadup& operator=(const listadup& umaLista);
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    void insereVazia(acaoPrograma acao);
    int procura(string valor); 
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

listadup::listadup() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

/*listadup::listadup(const listadup& umaLista) {

}*/

listadup::~listadup() {
    removeTodos();
}

void listadup::removeTodos() {
    while (!vazia()) {
        removeNoFim();
    }
}

/*listadup& listadup::operator=(const listadup& umaLista) {
    // limpa a lista atual
    removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;

    while (aux != NULL) {
        insereNoFim(aux->acao);
        aux = aux->proximo;
    }

    return *this;
}*/

void listadup::insereNoFim(acaoPrograma acao) {
    if (vazia()) {
        insereVazia(acao);
    }
    else {
        noh* novo = new noh(acao);
        ultimo->proximo = novo;
        novo->anterior = ultimo;
        ultimo = novo;
        tamanho++;
    }
}

void listadup::insereVazia(acaoPrograma acao) {
    noh* novo = new noh(acao);
    primeiro = novo;
    ultimo = novo;
    tamanho = 1;
}

void listadup::insereNoInicio(acaoPrograma acao) {
    if (vazia()) {
        insereVazia(acao);
    }
    else {
        noh* novo = new noh(acao);
        primeiro->anterior = novo;
        novo->proximo = primeiro;
        primeiro = novo;
        tamanho++;
    }
}

void listadup::insereNaPosicao(int posicao, acaoPrograma acao) {
    if (vazia()) {
        insereVazia(acao);
    }
    else if (posicao == 0) {
        insereNoInicio(acao);
    }
    else if (posicao == tamanho) {
        insereNoFim(acao);
    }
    else {
        noh* novo = new noh(acao);
        noh* aux = primeiro;
        int posAux = 0;

        while (posAux < (posicao - 1)) {
            aux = aux->proximo;
            posAux++;
        }
        aux->proximo->anterior = novo;
        novo->proximo = aux->proximo;

        aux->proximo = novo;
        novo->anterior = aux;

        tamanho++;
    }
}

int listadup::procura(string valor) {
    if (vazia()) throw runtime_error("Lista vazia!");

    noh* aux = primeiro;
    int posicao = 0;

    while (aux != NULL) {
        if (aux->acao.nomeAcao == valor) {
            return posicao;
        }
        aux = aux->proximo;
    }

    return -1;
}

void listadup::imprime() {
    if (vazia()) throw runtime_error("Lista vazia!");

    noh* aux = primeiro;

    while (aux != NULL) {
        cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao << ", " << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->proximo;
    }

    cout << " IMPRIMINDO REVERSO" << endl;

    aux = ultimo;

    while (aux != NULL) {
        cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao << ", " << aux->acao.tempoConsumido << ")" << endl;
        aux = aux->anterior;
    }

}

inline bool listadup::vazia() {
    return (primeiro == NULL);
}

void listadup::removeNoInicio() {
    if (vazia()) throw runtime_error("Remocao em lista vazia!");

    noh* aux = primeiro;
    primeiro = aux->proximo;
    primeiro->anterior = NULL;
    delete aux;
    tamanho--;

    if (vazia()) ultimo = NULL;
}

void listadup::removeNoFim() {
    if (vazia()) throw runtime_error("Remocao em lista vazia!");

    noh* aux = ultimo;

    if (aux->anterior == NULL) {
        primeiro = NULL;
        ultimo = NULL;
    }
    else {
        ultimo = ultimo->anterior;
        ultimo->proximo = NULL;
    }
    delete aux;
    tamanho--;
}

int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoInicio(info);
                break;
            case 'h': // inserir
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNoFim(info);
                break;
            case 'm': // inserir
                cin >> posicao;
                cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                minhaLista.insereNaPosicao(posicao, info);
                break;
            case 's': // procurar
                cin >> nomeEquipe;
                posicao = minhaLista.procura(nomeEquipe);
                if (posicao == -1)
                    cout << "Nao encontrado" << endl;
                else
                    cout << posicao << endl;
                break;
            case 'r': // remover
                minhaLista.removeNoInicio();
                break;
            case 'a': // remover
                minhaLista.removeNoFim();
                break;
            case 'p': // limpar tudo
                minhaLista.imprime();
                break;
            case 'f': // finalizar
                // checado no do-while
                break;
            default:
                cerr << "comando inválido\n";
            }
        }
        catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    cout << endl;
    return 0;
}
