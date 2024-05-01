/* 
 * Classe hash, uma tabela hash em que chaves e valores são strings
 * 
 * by Joukim, 2017-2018, Estruturas de Dados
 * Atualizado por Renato, 2023
 * 
 */
#include <iostream>

using namespace std;

const int UMPRIMO = 13;

int funcaoHash(string s, int M) {
    long h = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        h = (UMPRIMO * h + s[i]) % M;   
    }
    return h;
}

class noh {
friend class tabelaHash;
private:
    string chave;
    char tipo;
    int valor;
    noh* proximo = NULL;
public:
    noh(){
        chave = "";
        tipo = 'a';
        valor = 1;        
    }
};

class tabelaHash {
private:
    // vetor de ponteiros de nós
    noh** elementos;
    int capacidade;
public:
    // construtor padrão
    tabelaHash(int cap = 100);
    // destrutor 
    ~tabelaHash();
    // insere um valor v com chave c
    bool insere(string c, char t, int v);
    // recupera um valor associado a uma dada chave
    bool recupera(string c, char& t, int& v);
    // retira um valor associado a uma chave
    bool remove(string c);
    // percorrendo a tabela hash (para fins de debug)
    void imprime();
};

// construtor padrão
tabelaHash::tabelaHash(int cap) {
}

// destrutor
tabelaHash::~tabelaHash() {
}

// insere um valor v com chave c
bool tabelaHash::insere(string c, char t, int v) {

}

// recupera um valor associado a uma dada chave
bool tabelaHash::recupera(string c, char& t, string& v) {
 
}

// retira um valor associado a uma chave
void tabelaHash::remove(string c) {
    
}

// percorrendo a tabela hash (para fins de depuração)
void tabelaHash::imprime( ) {
    noh* atual;
    for (int i = 0; i < capacidade; i++) {
        cout << i << ":";
        atual = elementos[i];
        while (atual != NULL) {
            cout << "[" << atual->chave << "/"
                 << atual->valor << "]";
            atual = atual->proximo;
            
        }
    }
    
}

int main() {
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;    
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> chave >> tipo>> valor;
                    if (not tabela.insere(chave, tipo, valor))
                        cout << "Erro na inserção: chave já existente!" << endl;
                    break;
                case 'r': // remover
                    cin >> chave;
                    if (not tabela.remove(chave))
                        cout << "Erro na remoção: chave não encontrada!" << endl;
                    break;
                case 'l': // remover
                    cin >> chave;
                    if (not tabela.valor(chave,tipo,valor))
                        cout << "Erro na busca: chave não encontrada!" << endl;
                    else
                        cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                    break;
                case 'p': // mostrar estrutura
                    tabela.imprime();
                    break;

                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    tabela.imprime();
    cout << endl;
    return 0;
}