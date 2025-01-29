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
void logicaJogo(TLista &lista, const string &idioma, sf::RenderWindow &window);



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

void jogo(sf::RenderWindow &window, const string &idioma) {
    TLista lista;
    cria(lista);

    if (idioma == "Portugues") {
        alfabetoPortu(lista);
    } else {
        alfabetoIngles(lista);
    }

    logicaJogo(lista, idioma, window);
}
void telaJogo(sf::RenderWindow &window, const string &idioma) {


    /// texturas, lógica específica e comportamento dependendo do idioma
    sf::Texture gamingBackgroundTexture;
    if (!gamingBackgroundTexture.loadFromFile("fundo8.bmp")) {
        cout << "Erro ao carregar a janela de jogo!" << endl;
        return;
    }

    sf::Sprite gamingBackgroundSprite;
    gamingBackgroundSprite.setTexture(gamingBackgroundTexture);

    /// Lógica do jogo pode variar dependendo do idioma
    cout << "Idioma selecionado: " << idioma << endl;

    while (window.isOpen()) {
        sf::Event gamingEvent;
        while (window.pollEvent(gamingEvent)) {
            if (gamingEvent.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(gamingBackgroundSprite);
        window.display();
    }
}



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
    sf::FloatRect botaoSair(165, 336, 170, 56);

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

                        /// Coordenadas dos botões de linguagem
                        sf::FloatRect botaoJogarP(110, 194, 304, 68);
                        sf::FloatRect botaoJogarI(110, 295, 215, 70);

                        /// Loop principal da tela de escolha
                        while (choiceWindow.isOpen()) {
                            sf::Event choiceEvent;
                            while (choiceWindow.pollEvent(choiceEvent)) {
                                if (choiceEvent.type == sf::Event::Closed)
                                    choiceWindow.close();

                                /// Detectar o clique do mouse
                                if (choiceEvent.type == sf::Event::MouseButtonPressed) {
                                    if (choiceEvent.mouseButton.button == sf::Mouse::Left) {
                                        /// Coordenadas do clique do mouse
                                        sf::Vector2i mousePosition = sf::Mouse::getPosition(choiceWindow);
                                        /// Verifica se foi em 'portugues'

                                        if (botaoJogarP.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                                            cout << "Idioma selecionado: Português!" << endl;
                                            choiceWindow.close();
                                            telaJogo(window,"Portugues");
                                        }
                                        /// Verifica se foi em ingles
                                        else if (botaoJogarI.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                                            cout << "Idioma selecionado: Inglês!" << endl;
                                            choiceWindow.close();
                                            telaJogo(window,"Ingles");
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
                    } else if (botaoSair.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        cout << "Saindo..." << endl;
                        window.close();
                        exit(0);
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }
}

void logicaJogo(TLista &lista, const string &idioma, sf::RenderWindow &window) {
    string aux;
    int numero = 0;
    string continuar;

    numero = std::rand() % ((idioma == "Portugues") ? 124 : 433) + 1;

    while (continuar != "N" && continuar != "n") {
        embaralhar(lista, numero, aux);
        comparar(lista, aux);
        numero = std::rand() % ((idioma == "Portugues") ? 124 : 433) + 1;

        cout << "Deseja continuar? (S/N): ";
        cin >> continuar;
    }

    imprimeLista(lista);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    /// Tela inicial
    sf::RenderWindow window(sf::VideoMode(512, 512), "Jogo Torcido");
    TelaInicial(window);

    return 0;
}

void cria(TLista &lista) {
    lista.primeiro = new NodoLista;
    lista.primeiro->proximo = NULL;
    lista.ultimo = lista.primeiro;
}

void comparar(TLista lista, string palavra) {
    string digitar;
    int pontos = 0;

    cout << "Digite a palavra exibida: ";
    cin >> digitar;

    if (digitar == palavra) {
        cout << "Parabéns! Você acertou!" << endl;
        pontos++;
    } else {
        cout << "Palavra incorreta! A palavra certa era: " << palavra << endl;
    }

    cout << "Pontos atuais: " << pontos << endl;
}

void embaralhar(TLista &lista, int num, string &palavra) {
    Apontador atual = lista.primeiro->proximo;
    while (atual != NULL) {
        if (atual->item.numero == num) {
            palavra = atual->item.palavra;
            string embaralhada = palavra;

            // Embaralhando a palavra
            random_device rd;
            mt19937 g(rd());
            shuffle(embaralhada.begin(), embaralhada.end(), g);

            cout << "A palavra embaralhada é: " << embaralhada << endl;
            return;
        }
        atual = atual->proximo;
    }

    cout << "Número não encontrado na lista!" << endl;
}

void insereFinal(TLista &lista, Tinfo item) {
    Apontador novo = new NodoLista;
    novo->item = item;
    novo->proximo = NULL;
    lista.ultimo->proximo = novo;
    lista.ultimo = novo;
}

void imprimeLista(TLista lista) {
    Apontador atual = lista.primeiro->proximo;
    while (atual != NULL) {
        cout << "Número: " << atual->item.numero << " Palavra: " << atual->item.palavra << endl;
        atual = atual->proximo;
    }
}

void alfabetoPortu(TLista &lista) {
    ifstream arquivo("dicionario.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de palavras em português!" << endl;
        return;
    }

    Tinfo item;
    while (arquivo >> item.numero >> item.palavra) {
        insereFinal(lista, item);
    }

    arquivo.close();
}

void alfabetoIngles(TLista &lista) {
    ifstream arquivo("ingles.txt");
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo de palavras em inglês!" << endl;
        return;
    }

    Tinfo item;
    while (arquivo >> item.numero >> item.palavra) {
        insereFinal(lista, item);
    }

    arquivo.close();
}
