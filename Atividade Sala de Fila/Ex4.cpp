/* Classe Fila encadeada
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    int premio;
    char tipo;
    int tempo;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " Premio: " << umDado.premio << " Tipo: " << umDado.tipo << " Tempo: " << umDado.tempo << endl;
}

class Noh {
    friend class Fila;
private:
    Dado mDado; // poderia ser outro tipo de variável
    Noh* mProx;
public:
    Noh(Dado v) {
        mDado = v;
        mProx = NULL;
    }
};

class Fila {
public:
    // Constrói Fila vazia.
    Fila();
    // Destrutor que desaloca memória.
    ~Fila();
    // Retira e retorna o elemento que estiver na frente da Fila.
    // Escreve uma mensagem de erro se não for possível desenfileirar.
    Dado Desenfileirar();
    // Insere um elemento na Fila.
    void Enfileirar(const Dado& d);
    // Apagar todos os dados da Fila.
    void LimparTudo();
    // Retorna o elemento que está na frente da Fila, sem desenfileirar.
    inline void Primeiro();
    // Informa se a Fila está Vazia.
    inline bool Vazia();
    void RetornaPremio(char t);
private:
    Noh* mPtPrimeiro;
    Noh* mPtrUltimo;
    int tamanho;
};

Fila::Fila() {
    mPtPrimeiro = NULL;
    mPtrUltimo = NULL;
    tamanho = 0;
}

Fila::~Fila() {
    while (!Vazia()) {
        Desenfileirar();
    }
}

Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");

    Noh* temp = mPtPrimeiro;
    Dado aux = temp->mDado;
    mPtPrimeiro = mPtPrimeiro->mProx;
    delete temp;
    tamanho--;
    if (Vazia()) {
        mPtrUltimo = NULL;
    }
    return aux;
}

void Fila::Enfileirar(const Dado& d) {
    Noh* novo = new Noh(d);
    if (Vazia()) {
        mPtPrimeiro = novo;
    }
    else {
        mPtrUltimo->mProx = novo;
    }
    mPtrUltimo = novo;
    tamanho++;
}

void Fila::LimparTudo() {
    while (!Vazia()) {
        Desenfileirar();
    }
}

void Fila::Primeiro() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    imprimir_dado(mPtPrimeiro->mDado);
}

bool Fila::Vazia() {
    return tamanho == 0;
}

void Fila::RetornaPremio(char t) {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");

    Fila* diferentes = new Fila();
    Fila* iguais = new Fila();
    int soma = 0;

    while (!Vazia()) {
        if (mPtPrimeiro->mDado.tipo == t) {
            soma += mPtPrimeiro->mDado.premio;
            iguais->Enfileirar(Desenfileirar());
        }
        else {
            diferentes->Enfileirar(Desenfileirar());
        }
    }

    while (!iguais->Vazia()) {
        Enfileirar(iguais->Desenfileirar());
    }

    while (!diferentes->Vazia()) {
        Enfileirar(diferentes->Desenfileirar());
    }

    cout << soma << endl;
    delete diferentes;
    delete iguais;
}

int main() {
    Fila fila;
    Dado info;
    char comando;
    do {
        try {
            cin >> comando;
            switch (comando) {
            case 'i': // inserir
                cin >> info.nome >> info.premio >> info.tipo >> info.tempo;
                fila.Enfileirar(info);
                break;
            case 'r': // remover
                imprimir_dado(fila.Desenfileirar());
                break;
            case 'l': // limpar tudo
                fila.LimparTudo();
                break;
            case 'p': // limpar tudo
                char t;
                cin >> t;
                fila.RetornaPremio(t);
                break;
            case 'e': // espiar                
                fila.Primeiro();
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
    while (not fila.Vazia()) {
        imprimir_dado(fila.Desenfileirar());
    }
    cout << endl;
    return 0;
}