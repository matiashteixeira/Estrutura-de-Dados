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
    void VaiDarTempo(int t);
    void Ordenar();
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

void Fila::Ordenar() {
    Dado a;
    Fila* aux = new Fila();
    Fila* resultante = new Fila();
    int tam = tamanho;

    while (tamanho != 0) {
        a = Desenfileirar();
        while (!Vazia()) {
            if (a.tempo > mPtPrimeiro->mDado.tempo) {
                aux->Enfileirar(a);
                a = Desenfileirar();
            }
            else {
                aux->Enfileirar(Desenfileirar());
            }
        }
        resultante->Enfileirar(a);
        tam--;
        while (!aux->Vazia()) {
            Enfileirar(aux->Desenfileirar());
        }
    }

    while (!resultante->Vazia()) {
        Enfileirar(resultante->Desenfileirar());
    }

    delete aux;
    delete resultante;
}

void Fila::VaiDarTempo(int t) {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");

    Fila* aux = new Fila();
    int soma = 0;

    while (!Vazia()) {
        if (mPtPrimeiro->mDado.tempo < t && soma < t) {
            soma += mPtPrimeiro->mDado.tempo;
            imprimir_dado(Desenfileirar());
        }
        else {
            aux->Enfileirar(Desenfileirar());
        }
    }

    while (!aux->Vazia()) {
        Enfileirar(aux->Desenfileirar());
    }

    cout << soma << endl;
    delete aux;
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
            case 't': // limpar tudo
                int t;
                cin >> t;
                fila.VaiDarTempo(t);
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