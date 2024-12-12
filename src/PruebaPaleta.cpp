#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <Paleta.hpp> // Asegurate de que este archivo esté en el mismo directorio o configure el include path
#include <Ball.hpp>
int main() {
    // Crear el mundo de Box2D
    b2Vec2 gravedad(0.0f, 10.0f); // Gravedad hacia abajo
    b2World mundo(gravedad);

    // Crear una ventana SFML
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Pinball");
    ventana.setFramerateLimit(60);

    // Crear una instancia de Paleta
    float anchoPaleta = 200.0f; // Ancho de la paleta en píxeles
    float altoPaleta = 20.0f;   // Alto de la paleta en píxeles
    float friccion = 0.5f;      // Fricción de la paleta
    float posX = 400.0f;        // Posición X inicial de la paleta (en píxeles)
    float posY = 500.0f;        // Posición Y inicial de la paleta (en píxeles)
    float angulo = -30.0f;        // Ángulo inicial de la paleta

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
    Ball  p1(mundo,15,0.7,0.01,10,10.0f);
    Ball  p2(mundo,15,0.7,0.01,50,10.0f);
    Ball  p3(mundo,15,0.7,0.01,100,10.0f);
    Ball  p4(mundo,15,0.7,0.01,150,10.0f);
    Ball  p5(mundo,15,0.7,0.01,200,10.0f);
    Ball  p6(mundo,15,0.7,0.01,240,10.0f);
    Ball  p7(mundo,15,0.7,0.01,280,10.0f);
    Ball  p8(mundo,15,0.7,0.01,320,10.0f);
    Ball  p9(mundo,15,0.7,0.01,360,10.0f);
    Ball  p10(mundo,15,0.7,0.01,400,10.0f);
    Ball  p11(mundo,15,0.7,0.01,450,10.0f);
    Ball  p12(mundo,15,0.7,0.01,500,10.0f);
    Ball  p13(mundo,15,0.7,0.01,550,10.0f);
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
        p1.Dibujar(ventana);
        p2.Dibujar(ventana);
        p3.Dibujar(ventana);
        p4.Dibujar(ventana);
        p5.Dibujar(ventana);
        p6.Dibujar(ventana);
        p7.Dibujar(ventana);
        p8.Dibujar(ventana);
        p9.Dibujar(ventana);
        p10.Dibujar(ventana);
        p11.Dibujar(ventana);
        p12.Dibujar(ventana);   
        p13.Dibujar(ventana);        
        ventana.display();
    }

    return 0;
}
