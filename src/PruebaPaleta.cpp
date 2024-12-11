#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Paleta.hpp> // Asegurate de que este archivo esté en el mismo directorio o configure el include path

int main() {
    // Crear el mundo de Box2D
    b2Vec2 gravedad(0.0f, 9.8f); // Gravedad hacia abajo
    b2World mundo(gravedad);

    // Crear una ventana SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Pinball");
    ventana.setFramerateLimit(60);

    // Crear una instancia de Paleta
    float anchoPaleta = 100.0f; // Ancho de la paleta en píxeles
    float altoPaleta = 20.0f;   // Alto de la paleta en píxeles
    float friccion = 0.5f;      // Fricción de la paleta
    float posX = 400.0f;        // Posición X inicial de la paleta (en píxeles)
    float posY = 500.0f;        // Posición Y inicial de la paleta (en píxeles)
    float angulo = 0.0f;        // Ángulo inicial de la paleta

    // Convertir las dimensiones a Box2D (metros)
    Paleta paleta(
        mundo,
        anchoPaleta,
        altoPaleta,
        friccion,
        posX,
        posY,
        angulo
    );

    // Bucle principal
    while (ventana.isOpen()) {
        // Manejo de eventos
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed) {
                ventana.close();
            }
            // Control de la paleta
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                paleta.Presionar(); // Mueve la paleta hacia arriba
            } else {
                paleta.Soltar();    // Regresa la paleta a su posición inicial
            }
        }

        // Actualizar el mundo de física
        float tiempoStep = 1.0f / 60.0f; // Duración del paso de tiempo
        int32 velocidadIteraciones = 8;
        int32 posicionIteraciones = 3;
        mundo.Step(tiempoStep, velocidadIteraciones, posicionIteraciones);

        // Renderizar
        ventana.clear();
        paleta.Dibujar(ventana);
        ventana.display();
    }

    return 0;
}
