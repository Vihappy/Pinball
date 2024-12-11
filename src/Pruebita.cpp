// Pinball PablitoClavito y Violetiguis
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
using namespace std;

int main()
{
    int fuerza = 1;
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 635), "SFML Image");
    sf::Font font;
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

    b2Vec2 vectorGravedad(0.0f, 10.0f);
    b2World mundo(vectorGravedad);

        // Crear un suelo estático
    b2BodyDef cuerpoSueloDef;
    cuerpoSueloDef.position.Set(400, 500.0f); // Posición del centro del cuerpo
    b2Body* cuerpoSuelo = mundo.CreateBody(&cuerpoSueloDef);

    // Crear una forma rectangular
    b2PolygonShape formaSuelo;
    int boxWidth = 10; // 600 pixeles de ancho
    int boxHeight = 10; // 10 pixeles de alto
    formaSuelo.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureSueloDef;
    fixtureSueloDef.shape = &formaSuelo;
    fixtureSueloDef.friction = 1.0f;
    cuerpoSuelo->CreateFixture(&fixtureSueloDef);

    // Crear un cuerpo dinámico
    b2BodyDef cuerpoBolaDef;
    cuerpoBolaDef.type = b2_dynamicBody;
    cuerpoBolaDef.position.Set(200.0f, 0.0f);
    b2Body* cuerpoBola = mundo.CreateBody(&cuerpoBolaDef);

    // Crear una forma circular
    b2CircleShape formaBola;
    formaBola.m_radius = 15.0f;

    // Agregar la forma al cuerpo
    b2FixtureDef fixtureBolaDef;
    fixtureBolaDef.shape = &formaBola;
    fixtureBolaDef.density = 0.01f;
    fixtureBolaDef.friction = 0.7f;
    cuerpoBola->CreateFixture(&fixtureBolaDef);



    // Crear un sprite y asignarle la textura
    sf::Sprite sprite(texture);
    
    // Crear un objeto de texto LOTR
    sf::Text text;
    text.setFont(font);
    text.setString("Pinball");
    text.setCharacterSize(40);
    text.setPosition(500, 100);

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
        // Dibujar el suelo
        sf::RectangleShape suelo(sf::Vector2f(boxWidth, boxHeight));
        suelo.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f); // El origen x,y está en el centro de la forma
        suelo.setPosition(
            cuerpoSuelo->GetPosition().x, 
            cuerpoSuelo->GetPosition().y);

        // Dibujar la bola
        sf::CircleShape bola(formaBola.m_radius);
        bola.setOrigin(formaBola.m_radius, formaBola.m_radius);
        bola.setFillColor(sf::Color::Red);
        bola.setPosition(
            cuerpoBola->GetPosition().x, 
            cuerpoBola->GetPosition().y);


        // Dibujar el sprite en la ventana
        window.draw(sprite);
        //Mostrar texto
         window.draw(text);
        // Dibujar el sprite en la ventana
        window.draw(bola);
        window.draw(suelo);


        // Mostrar la ventana
        window.display();
    }

    return 0;
}


