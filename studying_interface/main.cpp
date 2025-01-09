#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
    /// Tela inicial
    sf::RenderWindow window(sf::VideoMode(512, 512), "Jogo Torcido");

    /// Textura da tela inicial
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("abertura.bmp")) {
        cout << "Erro ao carregar a imagem de fundo!" << endl;
        return -1;
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
            if (event.type == sf::Event::Closed)
                window.close();

            /// Detecta clique do mouse
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    /// Coordenadas do clique do mouse
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    /// Verifica se o clique foi na área do botão "Jogar"
                    if (botaoJogar.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        cout << "Jogar! Vamos começar o jogo!" << endl;

                        /// Fecha a janela inicial
                        window.close();

                        /// Cria uma nova janela para o jogo
                        sf::RenderWindow gameWindow(sf::VideoMode(512, 512), "Jogando...");

                        /// Textura de fundo para a tela do jogo
                        sf::Texture gameBackgroundTexture;
                        if (!gameBackgroundTexture.loadFromFile("fundo8.bmp")) {
                            cout << "Erro ao carregar a imagem de fundo do jogo!" << endl;
                            return -1;
                        }

                        /// Sprite para o fundo do jogo
                        sf::Sprite gameBackgroundSprite;
                        gameBackgroundSprite.setTexture(gameBackgroundTexture);

                        /// Loop principal da tela do jogo
                        while (gameWindow.isOpen()) {
                            sf::Event gameEvent;
                            while (gameWindow.pollEvent(gameEvent)) {
                                /// Fecha a janela quando clicar no "X"
                                if (gameEvent.type == sf::Event::Closed)
                                    gameWindow.close();
                            }

                            /// Limpa e desenha o fundo da janela do jogo
                            gameWindow.clear();
                            gameWindow.draw(gameBackgroundSprite);
                            gameWindow.display();
                        }
                    }

                    /// Verifica se o clique foi na área do botão "Ajuda"
                    else if (botaoAjuda.contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                        cout << "Ajuda! Aqui estão as instruções." << endl;

                        /// Fecha a janela inicial
                        window.close();

                        /// Cria uma nova janela para a ajuda
                        sf::RenderWindow helpWindow(sf::VideoMode(512, 512), "Ajuda!");

                        /// Textura de fundo para a tela de ajuda
                        sf::Texture helpBackgroundTexture;
                        if (!helpBackgroundTexture.loadFromFile("ajuda.bmp")) {
                            cout << "Erro ao carregar a imagem de fundo da ajuda!" << endl;
                            return -1;
                        }

                        /// Sprite para o fundo da ajuda
                        sf::Sprite helpBackgroundSprite;
                        helpBackgroundSprite.setTexture(helpBackgroundTexture);

                        /// Loop principal para a tela da ajuda
                        while (helpWindow.isOpen()) {
                            sf::Event helpEvent;
                            while (helpWindow.pollEvent(helpEvent)) {
                                /// Fecha a janela quando clicar no "X"
                                if (helpEvent.type == sf::Event::Closed)
                                    helpWindow.close();
                            }

                            /// Limpa e desenha a tela de ajuda
                            helpWindow.clear();
                            helpWindow.draw(helpBackgroundSprite);
                            helpWindow.display();
                        }
                    }
                }
            }
        }

        /// Limpa e desenha o fundo da janela inicial
        window.clear();
        window.draw(backgroundSprite);
        window.display();
    }

    return 0;
}
