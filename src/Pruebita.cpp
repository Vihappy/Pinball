// Pinball PablitoClavito y Violetiguis
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Bumper.hpp>
#include <Pared.hpp>
#include <Ball.hpp>
#include<Paleta.hpp>
#include<Colision.hpp>
using namespace std;

int main()
{
    float posicion;
    int fuerza = 1;
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 635), "Pinball");
    window.setFramerateLimit(60);
    sf::Font font;
    sf::Music music;
    if (!font.loadFromFile("./assets/fonts/Ring.ttf"))
    {
        // Manejar el error si no se puede cargar la fuente
        return -1;
    }
    // Cargar la imagen desde un archivo
    sf::Texture texture;
    if (!texture.loadFromFile("./assets/images/tableringuis.png"))
    {
        // Manejar el error si no se puede cargar la imagen
        return -1;
    }
        if (!music.openFromFile("./assets/music/Intro.ogg"))
    {
        // Error al cargar el archivo de música
        return -1;
    }
    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    Bumper b1(mundo,28,1,237.0,215);
    Bumper b2(mundo,28,1,120, 130.0f);
    Bumper b3(mundo,28,1,354, 130.0f);
    //Limites
    Pared l1(mundo,20,635,1,10,318,0.0,0.0f);
    Pared l2(mundo,20,635,1,466,318,0.0,0.0f);
    Pared l3(mundo,476,20,1,238,625,0.0,0.0f);
    Pared l4(mundo,476,20,1,238,10,0.0,0.0f);
    //Sección con angulo
    Pared l5(mundo,100,20,1,100,475,33.0,0.0f);
    Pared l6(mundo,100,20,1,375,475,147.0,0.0f);
    //Pared de paletas
   // Pared l7(mundo,15,94,1,65,397,0.0,0.0f);
    //Pared l8(mundo,15,94,1,410,397,0.0,0.0f);
    Pared l7(mundo,15,635,1,65,318,0.0,0.0f);
    Pared l8(mundo,15,639,1,410,318,0.0,0.0f);
    //Rebotador izquierdo
    Pared l9(mundo,5,64,1,108,390,9.0,0.7f);
    Pared l10(mundo,50,5,1,125,428,29.0,0.7f);
    Pared l11(mundo,5,85,1,131,399,-21.0,0.7f);
   // Pared l8(mundo,15,94,1,410,397,0.0f);

    //Rebotador derecho
    Pared l12(mundo,5,64,1,367,390,-9.0,0.7f);
    Pared l13(mundo,50,5,1,350,428,-29.0,0.7f);
    Pared l14(mundo,5,85,1,346,399,21.0,0.7f);

    Paleta paleta(mundo,50,20,1,306,517,-30.0f);

    //Bola dimámica
    Ball p1(mundo,10,0.7,0.01,150,30.0f);
   // Ball p2(mundo,15,0.7,0.01,250,30.0f);
    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    // Crear un objeto de texto LOTR
    sf::Text text;
    text.setFont(font);
    text.setString("Pinball");
    text.setCharacterSize(40);
    text.setPosition(600, 100);
    // Reproducir la música
    music.play();
    // Bucle principal
    while (window.isOpen())
    {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // Cerrar la ventana si se recibe el evento de cerrar
                window.close();
            }

            // Control de la paleta
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                paleta.Presionar(); // Mueve la paleta hacia arriba
            }
            else
            {
                paleta.Soltar(); // Regresa la paleta a su posición inicial
            }
        }
        // Ajustar el valor de 1.0 / 60.0 para cambiar la velocidad de la simulación física
        mundo.Step(1.0f / 60.0f, 6, 2);
        // Limpiar la ventana
        window.clear();
        // Dibujar el sprite en la ventana
        window.draw(sprite);
        //Mostrar texto
         window.draw(text);
        sf::RectangleShape rectangle(sf::Vector2f(100, 100));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setPosition(150,50);
        if (music.getStatus() != sf::Music::Playing)
        {
            music.play();
        }
        window.draw(rectangle);
        // Dibujar las figuras en la ventana.
        b1.Dibujar(window);
        b2.Dibujar(window);
        b3.Dibujar(window);
        l1.Dibujar(window);
        l2.Dibujar(window);
        l3.Dibujar(window);
        l4.Dibujar(window);
        l5.Dibujar(window);
        l6.Dibujar(window);
        l7.Dibujar(window);
        l8.Dibujar(window);
        l9.Dibujar(window);
        l10.Dibujar(window);
        l11.Dibujar(window);
        l12.Dibujar(window);
        l13.Dibujar(window);
        l14.Dibujar(window);
        paleta.Dibujar(window);
        p1.Dibujar(window);
        window.display();
        posicion=p1.Posicion(window);
        if(posicion>600){
            Ball p2(mundo,10,0.7,0.01,150,30.0f);
            p2.Dibujar(window);
        }
    }
    return 0;
}