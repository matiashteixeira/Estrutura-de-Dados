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
    string premio;
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
    void Ordenar();
    void VaiDarTempo(int t);
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
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");

    Dado a, b;
    Fila* aux = new Fila();
    Fila* resultante = new Fila();
    bool inLoop;

    if (tamanho > 1) {
        while (!Vazia()) {
            inLoop = true;
            a = Desenfileirar();
            while (!Vazia()) {
                inLoop = false;
                b = Desenfileirar();
                if (a.tempo > b.tempo) {
                    aux->Enfileirar(a);
                    a = b;
                    if (Vazia()) {
                        resultante->Enfileirar(b);
                    }
                }
                else {
                    aux->Enfileirar(b);
                    if (Vazia()) {
                        resultante->Enfileirar(a);
                    }
                }
            }
            while (!aux->Vazia()) {
                Enfileirar(aux->Desenfileirar());
            }
            if (inLoop) {
                resultante->Enfileirar(a);
            }
        }

        while (!resultante->Vazia()) {
            Enfileirar(resultante->Desenfileirar());
        }
    }

    delete aux;
    delete resultante;
}

void Fila::VaiDarTempo(int t) {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");

    Fila* aux = new Fila();
    int soma = 0;

    Ordenar();

    while (!Vazia()) {
        if (mPtPrimeiro->mDado.tempo + soma < t) {
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