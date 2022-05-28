#include "Simulation.hpp"
#include <iostream>

/*
Modificar render para que los haga 60 veces en una segundo, aniadir mas timeFixed
para controlar update de velocidad y posicion
*/

Simulation::Simulation()
    : m_window("Simulacion de Cinematica", sf::Vector2u(800, 600)),
      m_floor(sf::Color::White, sf::Vector2f(400, 500), sf::Vector2f(600, 30)),
      m_ball(sf::Color(204.0f, 77.0f, 5.0f), sf::Vector2f(500, 400),
             sf::Vector2f(30, 30)) {
    m_elapsed_fixedTime = 0.0f;
    // m_window.GetRenderWindow()->setFramerateLimit(60);
}

Simulation::~Simulation() {}

void Simulation::HandleInput() {
    const float vel = 300.0f;
    m_window.Update();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_floor.Move(0.0f, -vel * m_elapsed.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_floor.Move(0.0f, vel * m_elapsed.asSeconds());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_ball.Move(-vel * m_elapsed.asSeconds(), 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_ball.Move(vel * m_elapsed.asSeconds(), 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        m_ball.setVelocity(-20.f);
    }
}

void Simulation::Update() {
    float timestep = 1.0f / framesPerSecond;
    static bool collsionDetected { false };

    if (m_floor.GetCollider()->CheckColision(*m_ball.GetCollider(), 1)) {
        collsionDetected = true;
        m_ball.setVelocity(0.0f);
    } else {
        collsionDetected = false;
    }

    if (m_elapsed_fixedTime >= timestep) {
        m_elapsed_fixedTime -= timestep;
        // Calcular la collision
        if (!collsionDetected) {
            m_ball.UpdateVelocity(1.0f);
            m_ball.UpdateYPosition(1.0f);
        } else {
            m_ball.setVelocity(0.0f);
        }
    }
}

void Simulation::Render() {
    m_window.BeginDraw();
    m_floor.Render(*m_window.GetRenderWindow());
    m_ball.Render(*m_window.GetRenderWindow());
    m_window.EndDraw();
}

Window* Simulation::GetWindow() { return &m_window; }

sf::Time Simulation::getElapsedTime() { return m_elapsed; }

void Simulation::RestartClock() {
    m_elapsed = m_clock.restart();
    m_elapsed_fixedTime += m_elapsed.asSeconds();
}
