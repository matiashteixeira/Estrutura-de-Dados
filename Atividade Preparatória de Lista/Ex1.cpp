#include <iostream>

using namespace std;


struct equipe {
    string nomeEquipe;
    string lider;
    string linguagem;
    int qtdMembros;
};

class noh {
    friend class lista;
private:
    equipe elenco;
    noh* proximo;
public:
    noh(equipe d);
};

noh::noh(equipe d) {
    elenco = d;
    proximo = NULL;
}

class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos();
    //void imprimeReversoAux(noh* umNoh);
public:
    lista();
    //lista(const lista& umaLista);
    ~lista();
    //lista& operator=(const lista& umaLista);
    void insereVazia(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor);
    void imprime();
    void imprimeDado(equipe elenco);
    //void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};

lista::lista() {
    primeiro = NULL;
    ultimo = NULL;
    tamanho = 0;
}

lista::~lista() {
    removeTodos();
}

void lista::removeTodos() {
    while (!vazia()) {
        removeNoFim();
    }
}

/*lista& lista::operator=(const lista& umaLista) {
    // limpa a lista atual
    removeTodos();
    // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;

    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;
    }

    return *this;
}*/

void lista::insereVazia(equipe elenco) {
    noh* novo = new noh(elenco);
    primeiro = novo;
    ultimo = novo;
    tamanho = 1;
}

void lista::insereNoFim(equipe elenco) {
    if (vazia()) {
        insereVazia(elenco);
    }
    else {
        noh* novo = new noh(elenco);
        ultimo->proximo = novo;
        ultimo = novo;
        tamanho++;
    }
}

void lista::insereNoInicio(equipe elenco) {
    if (vazia()) {
        insereVazia(elenco);
    }
    else {
        noh* novo = new noh(elenco);
        novo->proximo = primeiro;
        primeiro = novo;
        tamanho++;
    }
}

void lista::insereNaPosicao(int posicao, equipe elenco) {
    if (vazia()) {
        insereVazia(elenco);
    }
    else if (posicao == 0) {
        insereNoInicio(elenco);
    }
    else if (posicao == tamanho) {
        insereNoFim(elenco);
    }
    else {
        noh* novo = new noh(elenco);
        noh* aux = primeiro;
        int posAux = 0;

        while (posAux < (posicao - 1)) {
            aux = aux->proximo;
            posAux++;
        }
        novo->proximo = aux->proximo;
        aux->proximo = novo;
        tamanho++;
    }
}

int lista::procura(string valor) {
    if (vazia()) throw runtime_error("Lista vazia!");

    noh* aux = primeiro;
    int posicao = 0;

    while (aux != NULL) {
        if (aux->elenco.nomeEquipe == valor) {
            return posicao;
        }
        aux = aux->proximo;
        posicao++;
    }

    return -1;
}

void lista::imprime() {
    if (vazia()) throw runtime_error("Lista vazia!");

    noh* aux = primeiro;

    while (aux != NULL) {
        cout << "(" << aux->elenco.nomeEquipe << ", " << aux->elenco.lider << ", " << aux->elenco.linguagem << ", " << aux->elenco.qtdMembros << ")" << endl;
        aux = aux->proximo;
    }
}

void lista::imprimeDado(equipe elenco) {
    if (vazia()) throw runtime_error("Lista vazia!");
    cout << "( " << elenco.nomeEquipe << ", " << elenco.lider << ", " << elenco.linguagem << ", " << elenco.qtdMembros << ")" << endl;
}

inline bool lista::vazia() {
    return (primeiro == NULL);
}

void lista::removeNoFim() {
    if (vazia()) throw runtime_error("Remocao em lista vazia!");

    noh* aux = primeiro;
    noh* anterior = NULL;

    while (aux->proximo != NULL) {
        anterior = aux;
        aux = aux->proximo;
    }

    if (anterior == NULL) {
        primeiro = NULL;
        ultimo = NULL;
    }
    else {
        anterior->proximo = NULL;
        ultimo = anterior;
    }

    delete aux;
    tamanho--;
}

void lista::removeNoInicio() {
    if (vazia()) throw runtime_error("Remocao em lista vazia!");

    noh* aux = primeiro;
    primeiro = aux->proximo;
    delete aux;
    tamanho--;

    if (vazia()) ultimo = NULL;
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i':
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoInicio(info);
                break;
            case 'h':
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNoFim(info);
                break;
            case 'm':
                cin >> posicao;
                cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                minhaLista.insereNaPosicao(posicao, info);
                break;
            case 's':
                cin >> nomeEquipe;
                posicao = minhaLista.procura(nomeEquipe);
                if (posicao == -1) {
                    cout << "Nao encontrado" << endl;
                }
                else {
                    cout << posicao << endl;
                }
                break;
            case 'r':
                minhaLista.removeNoInicio();
                break;
            case 'a':
                minhaLista.removeNoFim();
                break;
            case 'p':
                minhaLista.imprime();
                break;
            case 'f':
                break;
            default:
                cerr << "comando inválido\n";
            }
        }
        catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f');
    cout << endl;
    return 0;
}
