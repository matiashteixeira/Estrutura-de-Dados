/* Classe pilha encadeada
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>
#include <stdexcept>
#include <cstring>

using namespace std;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << "  Tipo: " << umDado.tipo << "  Valor: " << umDado.valor << endl;

}

class Noh {
    friend class Pilha;
private:
    Dado mDado; // poderia ser outro tipo de variável
    Noh* mProx;
public:
    Noh(Dado v) {
        mDado = v;
        mProx = NULL;
    }
};

class Pilha {
public:
    // Constrói pilha vazia.
    Pilha();
    // Destrutor que desaloca memória.
    ~Pilha();
    // Retira e retorna o valor que estiver no mPtTopo da pilha.
    // Escreve uma mensagem de erro se não for possível desempilhar.
    Dado Desempilhar(); // retorna o mPtTopo da Pilha.
    // Insere um valor na pilha.
    void Empilhar(const Dado& d);
    // Apagar todos os dados da pilha.
    void LimparTudo();
    // Imprime o valor que está no mPtTopo sem desempilhar.
    inline void Topo();
    // Informa se a pilha está Vazia.
    inline bool Vazia();
    bool compararNomes(const string& nome1, const string& nome2);
    void Ordenar();
    //Remove todos os valores inferiores ao parametro
private:
    Noh* mPtTopo;
    unsigned tamanho;

};

Pilha::Pilha() {
    mPtTopo = NULL;
    tamanho = 0;
}

Pilha::~Pilha() {
    LimparTudo();
    delete mPtTopo;
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    Noh* temp = mPtTopo;
    Dado aux = temp->mDado;
    mPtTopo = mPtTopo->mProx;
    tamanho--;

    delete temp;
    return aux;
    // completar com o código, caso não esteja vazia
}

void Pilha::Empilhar(const Dado& d) {
    Noh* novo = new Noh(d);
    novo->mProx = mPtTopo;
    mPtTopo = novo;
    tamanho++;
}

void Pilha::LimparTudo() {
    while (!Vazia()) {
        Desempilhar();
    }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    imprimir_dado(mPtTopo->mDado);
}

bool Pilha::Vazia() {
    return tamanho == 0;
}


bool Pilha::compararNomes(const string& nome1, const string& nome2) {
    int tamanho = min(nome1.size(), nome2.size());

    for (int i = 0; i < tamanho; ++i)
    {
        if (nome1[i] < nome2[i])
            return true;
        else if (nome1[i] > nome2[i])
            return false;
    }

    if (nome1.size() < nome2.size())
        return true;
    else if (nome1.size() > nome2.size())
        return false;
    else
        return true; // Nomes são iguais
}

void Pilha::Ordenar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");

    Noh* noh_aux;
    Pilha* aux = new Pilha();
    Dado dado_princ, dado_aux;

    while (!Vazia()) {
        aux->Empilhar(Desempilhar());
        if (!aux->mPtTopo == NULL and !mPtTopo == NULL) {
            dado_princ = Desempilhar();
            dado_aux = aux->Desempilhar();
            if (dado_aux.nome < dado_princ.nome) {
                noh_aux = mPtTopo;
                mPtTopo = mPtTopo->mProx;
                noh_aux->mProx = aux->mPtTopo->mProx;
                aux->mPtTopo->mProx = noh_aux;
                while (!aux->Vazia()) {
                    Empilhar(aux->Desempilhar());
                }
            }
        }
    }
    mPtTopo = aux->mPtTopo;
}

int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> info.nome >> info.tipo >> info.valor;
                pilha.Empilhar(info);
                break;
            case 'r': // remover
                imprimir_dado(pilha.Desempilhar());
                break;
            case 'l': // limpar tudo
                pilha.LimparTudo();
                break;
            case 'e': // espiar                
                pilha.Topo();
                break;
            case 'o': // espiar                
                pilha.Ordenar();
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
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}