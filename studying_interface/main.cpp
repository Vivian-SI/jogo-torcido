#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <ctime>
#include <algorithm> // Para std::shuffle
#include <random>    // Para std::random_device e std::mt19937
#include <locale>
#include <thread> //para o tempo

typedef struct NodoLista *Apontador;

typedef struct {
    int numero;
    std::string palavra;
} Tinfo;

struct NodoLista {
    Tinfo item;
    Apontador proximo;
};

typedef struct {
    Apontador primeiro;
    Apontador ultimo;
} TLista;


using namespace std;

void cria(TLista &lista);
void escolha(string &palavra);
void alfabetoPortu(TLista &lista);
void alfabetoIngles(TLista &lista);
void insereFinal(TLista &lista, Tinfo item);
void imprimeLista(TLista lista);
void comparar(TLista lista, string palavra);
void embaralhar(TLista &lista, int num, string &palavra);
/////////////////////////////////////////////////////////////////////////////////////////////////

void TelaInicial(sf::RenderWindow &window);
//-------------------------------------------------------------
void TelaAjuda(sf::RenderWindow &window) {
    /// Textura de fundo para a tela de ajuda
    sf::Texture helpBackgroundTexture;
    if (!helpBackgroundTexture.loadFromFile("ajuda.bmp")) {
        cout << "Erro ao carregar a imagem de fundo da ajuda!" << endl;
        return;
    }

    /// Sprite para o fundo da ajuda
    sf::Sprite helpBackgroundSprite;
    helpBackgroundSprite.setTexture(helpBackgroundTexture);

    /// Coordenadas do botão "Voltar"
    sf::FloatRect botaoVoltar(344, 454, 144, 37);

    /// Loop principal para a tela da ajuda
    while (window.isOpen()) {
        sf::Event helpEvent;
        while (window.pollEvent(helpEvent)) {
            if (helpEvent.type == sf::Event::Closed)
                window.close();

            /// Detecta clique do mouse
            if (helpEvent.type == sf::Event::MouseButtonPressed) {
                if (helpEvent.mouseButton.button == sf::Mouse::Left) {
                    /// Coordenadas do clique do mouse
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    /// Verifica se o clique foi na área do botão "Voltar"
                    if (botaoVoltar.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        cout << "Voltando para a tela inicial..." << endl;
                        return; /// Sai da tela de ajuda para voltar à inicial
                    }
                }
            }
        }

        window.clear();
        window.draw(helpBackgroundSprite);
        window.display();
    }
}
void janelaJogo(sf::RenderWindow &window) {
    sf::Texture gameBackgroundTexture;
    if (!gameBackgroundTexture.loadFromFile("fundo8.bmp")) {
        cout << "Erro ao carregar a janela de fundo do jogo" << endl;
        return;
    }

    sf::Sprite gameBackgroundSprite;
    gameBackgroundSprite.setTexture(gameBackgroundTexture);

    while (window.isOpen()) {
        sf::Event gameEvent;
        while (window.pollEvent(gameEvent)) {
            if (gameEvent.type == sf::Event::Closed)
                window.close();
        }

        // Atualização da janela (renderização)
        window.clear();
        window.draw(gameBackgroundSprite);
        window.display();
    }
}

void jogoPort(sf::RenderWindow &window) {
    // Cria uma nova janela para o jogo
    sf::RenderWindow gameWindow(sf::VideoMode(512, 512), "Jogo - Português");
    janelaJogo(gameWindow);

}


//-------------------------------------------------------------------------------------------------------------------------
void TelaInicial(sf::RenderWindow &window) {
    /// Textura da tela inicial
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("abertura.bmp")) {
        cout << "Erro ao carregar a imagem de fundo!" << endl;
        return;
    }

    /// Sprite para o fundo da tela inicial
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    /// Coordenadas para os botões
    sf::FloatRect botaoJogar(165, 175, 229, 63);
    sf::FloatRect botaoAjuda(165, 262, 214, 52);


    /// Loop principal da tela inicial
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            /// Fecha a janela quando clicar no "X"
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }

            /// Detecta clique do mouse
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    /// Coordenadas do clique do mouse
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    /// Verifica se o clique foi na área do botão "Jogar"
                    if (botaoJogar.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        cout << "Jogar! Escolha a linguagem para começar o jogo!" << endl;
                        window.close(); /// Fecha a tela inicial

                        /// Cria uma nova janela para a escolha da linguagem do jogo
                        sf::RenderWindow choiceWindow(sf::VideoMode(512, 512), "Escolha!");

                        /// Textura de fundo para a tela da escolha
                        sf::Texture choiceBackgroundTexture;
                        if (!choiceBackgroundTexture.loadFromFile("escolha.bmp")) {
                            cout << "Erro ao carregar a imagem de fundo da escolha!" << endl;
                            return;
                        }

                        /// Sprite para o fundo da escolha
                        sf::Sprite choiceBackgroundSprite;
                        choiceBackgroundSprite.setTexture(choiceBackgroundTexture);

                        ///coordenadas dos botoes de linguagem
                        sf::FloatRect botaoJogarP(110, 194, 304, 68);
                        sf::FloatRect botaoJogarI(110, 295, 215, 70);

                        /// Loop principal da tela de escolha
                        while (choiceWindow.isOpen()) {
                            sf::Event choiceevent;
                            while (choiceWindow.pollEvent(choiceevent)) {
                                if (choiceevent.type == sf::Event::Closed)
                                    choiceWindow.close();

                                    ///Detectar o clique do mouse
                                    if(choiceevent.type == sf::Event::MouseButtonPressed){
                                        if(choiceevent.mouseButton.button == sf::Mouse::Left){
                                            ///cooordenadas do clique do mouse
                                            sf::Vector2i mousePosition = sf::Mouse::getPosition(choiceWindow);
                                            ///verifica se foi em 'portugues'

                                            if(botaoJogarP.contains(static_cast<float>(mousePosition.x),static_cast<float>(mousePosition.y))){
                                                cout<<"Idioma selecionado: Português!"<<endl;

                                                choiceWindow.close();
                                                    jogoPort(window);
                                                ///idiomaPort(FUNÇÃO)/////////////////////////

                                            }
                                            ///verifica se foi em ingles
                                            else if(botaoJogarI.contains(static_cast<float>(mousePosition.x),static_cast<float>(mousePosition.y))){
                                                cout<<"Idioma selecionado: Inglês!"<<endl;

                                            choiceWindow.close();
                                            ///logica jogo ingles(funcao)


                                            }
                                        }
                                    }
                            }

                            choiceWindow.clear();
                            choiceWindow.draw(choiceBackgroundSprite);
                            choiceWindow.display();
                        }
                    }

                    /// Verifica se o clique foi na área do botão "Ajuda"
                    else if (botaoAjuda.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        cout << "Abrindo tela de ajuda..." << endl;
                        TelaAjuda(window); /// Chama a tela de ajuda
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }
}

//----------------------------------------------------------------------------------------------
int main() {
    setlocale(LC_ALL, "Portuguese");

    /// Tela inicial
    sf::RenderWindow window(sf::VideoMode(512, 512), "Jogo Torcido");
    TelaInicial(window);

    std::srand(std::time(0));

    TLista lista;
    cria(lista);
    Tinfo item;

    string palavra;
    escolha(palavra);
    string aux = "";
    int numero = 0;

    if(palavra == "Portugues" || palavra == "p"){
        alfabetoPortu(lista);
        numero = std::rand() % 124 + 1;

    } else {
        alfabetoIngles(lista);
        numero = std::rand() % 433 + 1;
    }

    string continuar = "";
    while(continuar != "N" || continuar != "n"){
        embaralhar(lista, numero, aux);
        comparar(lista, aux);
        numero = std::rand() % 124 + 1;

        cout << "Deseja continuar?";
        cin >> continuar;
        system("cls");
    }




    imprimeLista(lista);

    return 0;
}

void escolha(string &palavra){
    cout << "Informe sua escolha:";
    cin >> palavra;
}

void cria(TLista &lista) {
    lista.primeiro = new NodoLista;
    lista.primeiro->proximo = NULL;
    lista.ultimo = lista.primeiro;
}

void comparar(TLista lista, string palavra) {
    string digitar;
    int pontos = 0;

    cout << "Palavra embaralhada: " << palavra << endl;
    while (pontos < 5) {
        cout << "Digite uma palavra: ";
        cin >> digitar;

        Apontador atual = lista.primeiro->proximo;
        while (atual != nullptr) {
            if (digitar == atual->item.palavra) {
                pontos++;
                break;
            }
            atual = atual->proximo;
        }
    }

}

void embaralhar(TLista &lista, int num, string &palavra) {
    Apontador atual = lista.primeiro->proximo;

    while (atual != nullptr) {
        if (atual->item.numero == num) {
            palavra = atual->item.palavra;
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(palavra.begin(), palavra.end(), g);
            break;
        }
        atual = atual->proximo;
    }

}
void alfabetoPortu(TLista &lista) {
    Tinfo item;

    ifstream arq("dicionario.txt");

    int contador = 0;
    string palavra;
    if (arq.is_open()) {
        while (getline(arq, palavra)) {
            item.palavra = palavra;
            item.numero = contador;
            insereFinal(lista, item);
            contador++;
        }
        arq.close();
    } else {
        cout << "Arquivo nao encontrado." << endl;
    }
}

void alfabetoIngles(TLista &lista) {
    Tinfo item;
    string palavra;

    ifstream arq("ingles.txt");

    int contador = 0;
    if (arq.is_open()) {
        while (getline(arq, palavra)) {
            item.palavra = palavra;
            item.numero = contador;
            insereFinal(lista, item);
            contador++;
        }
        arq.close();
    } else {
        cout << "Arquivo nao encontrado." << endl;
    }
}

void insereFinal(TLista &lista, Tinfo item) {
    Apontador novoNodo = new NodoLista;
    novoNodo->item = item;
    novoNodo->proximo = NULL;
    lista.ultimo->proximo = novoNodo;
    lista.ultimo = novoNodo;
}

void imprimeLista(TLista lista) {
    Apontador nodo = lista.primeiro->proximo;
    while (nodo != NULL) {
        cout << nodo->item.palavra << " - " << nodo->item.numero << endl;
        nodo = nodo->proximo;
    }
}
