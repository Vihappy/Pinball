#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <array>

constexpr float SCALE = 30.0f; // Píxeles por metro

class Triangulo
{
private:
    b2PolygonShape formaLimite;
    b2Body* cuerpoLimite;
    sf::ConvexShape visual; // Forma para dibujar el triángulo

public:
    Triangulo(b2World& mundo, const std::array<b2Vec2, 3>& vertices, float friccion, float x, float y, float anguloGrado)
    {
        // Crear el cuerpo físico
        b2BodyDef cuerpoLimitedef;
        cuerpoLimitedef.position.Set(x, y);
        constexpr float DEG2RAD = 3.14159f / 180.0f;
        cuerpoLimitedef.angle = anguloGrado * DEG2RAD;

        cuerpoLimite = mundo.CreateBody(&cuerpoLimitedef);

        // Crear una forma triangular
        formaLimite.Set(vertices.data(), vertices.size());

        // Agregar la forma al cuerpo con atributos físicos
        b2FixtureDef fixtureLimite;
        fixtureLimite.shape = &formaLimite;
        fixtureLimite.friction = friccion;
        cuerpoLimite->CreateFixture(&fixtureLimite);

        // Inicializar la forma gráfica
        visual.setPointCount(3);
        for (size_t i = 0; i < vertices.size(); ++i) {
            visual.setPoint(i, sf::Vector2f(vertices[i].x * SCALE, vertices[i].y * SCALE));
        }
        visual.setOrigin(
            (vertices[0].x + vertices[1].x + vertices[2].x) / 3.0f * SCALE,
            (vertices[0].y + vertices[1].y + vertices[2].y) / 3.0f * SCALE);
        visual.setFillColor(sf::Color::Red);
    }
    ~Triangulo() {}
    void Dibujar(sf::RenderWindow& window) {
        // Actualizar posición y rotación para el dibujo
        visual.setPosition(
            cuerpoLimite->GetPosition().x,
            cuerpoLimite->GetPosition().y);
        visual.setRotation(cuerpoLimite->GetAngle() * 180.0f / 3.14159f); // Convertir radianes a grados
        window.draw(visual);
    }
};