#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Paleta.hpp> // Clase Paleta
#include <iostream>

int main() {
    // Crear el mundo de Box2D
    b2Vec2 gravedad(0.0f, 10.0f); // Gravedad hacia abajo
    b2World mundo(gravedad);

    const float SCALE = 30.0f;

    // Crear una ventana SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Pinball");

    // Crear una instancia de Paleta
    float anchoPaleta = 200.0f; // Ancho en píxeles
    float altoPaleta = 20.0f;   // Alto en píxeles
    float posX = 400.0f;        // Posición X en píxeles
    float posY = 500.0f;        // Posición Y en píxeles
    float angulo = 0.0f;        // Ángulo inicial de la paleta

    Paleta paleta(mundo, anchoPaleta, altoPaleta, 0.5f, posX, posY, angulo);

    // Crear un suelo estático
    b2BodyDef sueloDef;
    sueloDef.position.Set(400.0f / SCALE, 580.0f / SCALE);
    b2Body* suelo = mundo.CreateBody(&sueloDef);

    b2PolygonShape sueloShape;
    sueloShape.SetAsBox(800.0f / SCALE, 10.0f / SCALE);

    b2FixtureDef sueloFixture;
    sueloFixture.shape = &sueloShape;
    suelo->CreateFixture(&sueloFixture);

    // Bucle principal
    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
            // Control de la paleta
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                paleta.Presionar();
            } else {
                paleta.Soltar();
            }
        }

        // Actualizar el mundo de física
        mundo.Step(1.0f / 60.0f, 8, 3);

        // Renderizar
        ventana.clear();
        paleta.Dibujar(ventana);
        ventana.display();
    }

    return 0;
}