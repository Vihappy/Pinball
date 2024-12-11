// Pinball PablitoClavito y Violetiguis
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Bumper.hpp>
#include <Pared.hpp>
#include <Ball.hpp>
#include<Rebotadores.hpp>
using namespace std;

int main()
{
    float posicion;
    int fuerza = 1;
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 635), "Pinball");
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
        if (!music.openFromFile("./assets/music/Musica.ogg"))
    {
        // Error al cargar el archivo de música
        return -1;
    }
    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

    // Vértices del triángulo (en metros)
    std::array<b2Vec2, 3> vertices = {
        b2Vec2(-1.0f, -0.5f), // Vértice inferior izquierdo
        b2Vec2(1.0f, -0.5f),  // Vértice inferior derecho
        b2Vec2(1.0f, 1.0f)    // Vértice superior
    };

    // Crear un triángulo
    Triangulo triangulo(mundo, vertices, 1.0f, 300.0f, 470.0f, 0.0f); // Ficción, posición, ángulo

    Bumper b1(mundo,28,1,237.0,215);
    Bumper b2(mundo,28,1,120, 130.0f);
    Bumper b3(mundo,28,1,354, 130.0f);
    //Limites
    Pared l1(mundo,20,635,1,10,318,0.0f);
    Pared l2(mundo,20,635,1,466,318,0.0f);
    Pared l3(mundo,476,20,1,238,625,0.0f);
    Pared l4(mundo,476,20,1,238,10,0.0f);
    //Sección con angulo
    Pared l5(mundo,100,20,1,100,475,33.0f);
    Pared l6(mundo,100,20,1,375,475,147.0f);
    //Pared de paletas
    Pared l7(mundo,15,94,1,65,397,0.0f);
    Pared l8(mundo,15,94,1,410,397,0.0f);
    

    //Bola dimámica
    Ball p1(mundo,15,0.7,0.01,150,30.0f);
   // Ball p2(mundo,15,0.7,0.01,250,30.0f);
    Ball p3(mundo,15,0.7,0.01,350,30.0f);
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
        // Esperar hasta que la música termine
        if (music.getStatus() != sf::Music::Playing)
        {
            window.close();
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
        triangulo.Dibujar(window);
        p1.Dibujar(window);
       /*if(posicion==599)
        {
             Ball p2(mundo,15,0.7,0.01,250,30.0f);
             window.clear();
            p2.Dibujar(window);
        }
        p3.Dibujar(window);    */     
        // Mostrar la ventana
        window.display();
    }
    return 0;
}