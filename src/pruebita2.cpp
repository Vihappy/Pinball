// Pinball PablitoClavito y Violetiguis
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <iostream>
#include <Bumper.hpp>
#include <Pared.hpp>
#include <Ball.hpp>
using namespace std;

int main()
{
    int fuerza = 1;
    // Crear una ventana
    sf::RenderWindow window(sf::VideoMode(800, 635), "Pinball");
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

    
    Bumper b1(mundo,28,1,237.0,215);
    Bumper b2(mundo,28,1,120, 130.0f);
    Bumper b3(mundo,28,1,354, 130.0f);
    Pared l1(mundo,20,635,1,20,318);
    Pared l2(mundo,20,635,1,500,318);
    Pared l3(mundo,476,20,1,238,625);
    Ball p1(mundo,15,0.7,0.01,250,0);
    //Crear el limite izquierdo.
    b2BodyDef limiteizq;
    limiteizq.position.Set(20,318.0f);
    int boxWidth = 30; // 600 pixeles de ancho
    int boxHeight = 222; // 10 pixeles de alto
    b2Body* limite11= mundo.CreateBody(&limiteizq);
    //Crear una forma rectangular
    b2PolygonShape formalimite1;
    formalimite1.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);
    //Agregar la forma al cuerpo
    b2FixtureDef fixturelimite1;
    fixturelimite1.shape = &formalimite1;
    fixturelimite1.friction = 1.0f;
    limite11->CreateFixture(&fixturelimite1);

    //Crear el limite derecho.
    b2BodyDef limiteder;
    limiteder.position.Set(410,318.0f);
    b2Body* limite22= mundo.CreateBody(&limiteder);
    //Crear una forma rectangular
    b2PolygonShape formalimite2;
    formalimite2.SetAsBox(boxWidth / 2.0f, boxHeight / 2.0f);
    //Agregar la forma al cuerpo
    b2FixtureDef fixturelimite2;
    fixturelimite2.shape = &formalimite2;
    fixturelimite2.friction = 1.0f;
    limite22->CreateFixture(&fixturelimite2);

    //Crear el limite superior.
    b2BodyDef limitesup;
    limitesup.position.Set(52,0.0f);
    int boxWidth3 = 350; // 600 pixeles de ancho
    int boxHeight3 = 25; // 10 pixeles de alto
    b2Body* limite33= mundo.CreateBody(&limitesup);
    //Crear una forma rectangular
    b2PolygonShape formalimite3;
    formalimite3.SetAsBox(boxWidth, boxHeight);
    //Agregar la forma al cuerpo
    b2FixtureDef fixturelimite3;
    fixturelimite3.shape = &formalimite3;
    fixturelimite3.friction = 1.0f;
    limite33->CreateFixture(&fixturelimite3);

    //Crear el limite inferior.
    b2BodyDef limiteinf1;
    limiteinf1.position.Set(52,600.0f);
    int boxWidth4 = 350; // 600 pixeles de ancho
    int boxHeight4 = 25; // 10 pixeles de alto
    b2Body* limite44= mundo.CreateBody(&limiteinf1);
    //Crear una forma rectangular
    b2PolygonShape formalimite4;
    formalimite4.SetAsBox(boxWidth4, boxHeight4);
    //Agregar la forma al cuerpo
    b2FixtureDef fixturelimite4;
    fixturelimite4.shape = &formalimite4;
    fixturelimite4.friction = 1.0f;
    limite44->CreateFixture(&fixturelimite4);

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
        
        //Dibujar limite 1
        sf::RectangleShape limite(sf::Vector2f(boxWidth, boxHeight));
        limite.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f); // El origen x,y está en el centro de la forma
        limite.setFillColor(sf::Color::Blue);
        limite.setPosition(		
            limite11->GetPosition().x, 
            limite11->GetPosition().y);

        //Dibujar limite derecho
        sf::RectangleShape limite2(sf::Vector2f(boxWidth, boxHeight));
        limite.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f); // El origen x,y está en el centro de la forma
        limite2.setFillColor(sf::Color::Blue);
        limite2.setPosition(		
            limite22->GetPosition().x, 
            limite22->GetPosition().y);

        //Dibujar limite superior
        sf::RectangleShape limite3(sf::Vector2f(boxWidth3, boxHeight3));
       // limite.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f); // El origen x,y está en el centro de la forma
        limite3.setFillColor(sf::Color::Blue);
        limite3.setPosition(		
            limite33->GetPosition().x, 
            limite33->GetPosition().y);

        //Dibujar limite inferior
        sf::RectangleShape limite4(sf::Vector2f(boxWidth4, boxHeight4));
       // limite.setOrigin(boxWidth / 2.0f, boxHeight / 2.0f); // El origen x,y está en el centro de la forma
        limite4.setFillColor(sf::Color::Blue);
        limite4.setPosition(		
            limite44->GetPosition().x, 
            limite44->GetPosition().y);

        // Dibujar el sprite en la ventana
        window.draw(sprite);
        //Mostrar texto
         window.draw(text);
        sf::RectangleShape rectangle(sf::Vector2f(100, 100));
        rectangle.setFillColor(sf::Color::Black);
        rectangle.setPosition(150,50);
        window.draw(rectangle);
        // Dibujar el sprite en la ventana
        

        //window.draw(limite);
        window.draw(limite2);
        window.draw(limite3);
        window.draw(limite4);

        b1.Dibujar(window);
        b2.Dibujar(window);
        b3.Dibujar(window);
        p1.Dibujar(window);
        // Mostrar la ventana
        window.display();
    }

    return 0;
}


