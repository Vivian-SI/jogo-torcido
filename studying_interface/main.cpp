#include <SFML/Graphics.hpp>
#include <iostream>
#include <locale>

using namespace std;

void TelaInicial(sf::RenderWindow &window);

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
                        cout << "Jogar! Vamos começar o jogo!" << endl;
                        window.close(); /// Fecha a tela inicial

                        /// Cria uma nova janela para o jogo
                        sf::RenderWindow gameWindow(sf::VideoMode(512, 512), "Jogando...");

                        /// Textura de fundo para a tela do jogo
                        sf::Texture gameBackgroundTexture;
                        if (!gameBackgroundTexture.loadFromFile("fundo8.bmp")) {
                            cout << "Erro ao carregar a imagem de fundo do jogo!" << endl;
                            return;
                        }

                        /// Sprite para o fundo do jogo
                        sf::Sprite gameBackgroundSprite;
                        gameBackgroundSprite.setTexture(gameBackgroundTexture);

                        /// Loop principal da tela do jogo
                        while (gameWindow.isOpen()) {
                            sf::Event gameEvent;
                            while (gameWindow.pollEvent(gameEvent)) {
                                if (gameEvent.type == sf::Event::Closed)
                                    gameWindow.close();
                            }

                            gameWindow.clear();
                            gameWindow.draw(gameBackgroundSprite);
                            gameWindow.display();
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

int main() {
    setlocale(LC_ALL, "Portuguese");

    /// Tela inicial
    sf::RenderWindow window(sf::VideoMode(512, 512), "Jogo Torcido");
    TelaInicial(window);

    return 0;
}
