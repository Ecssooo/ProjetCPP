#pragma once
#include <list>
#include <SFML/Graphics.hpp>

const float pi = 3.14159265358979323846;

struct Particle
{
    float lifeDuration;
    sf::Vector2f direction;
    float speed;
    float lifeTime = 0;
    sf::CircleShape shape;
};

struct ParticleSystem
{
    std::list<Particle> allParticle;

    //Create field
    float createParticleTime;
    float createCooldown = 0;
    float minLifeTime;
    float maxLifeTime;
    float systemLifeDuration;
    
    //SFML field
    sf::Vector2f origin;
    float spawnRadius;
    int minParticleSize;
    int maxParticleSize;
    float maxParticleSpeed;
    sf::Color particleColor;
    
    float systemLifeTime = 0;
    float createNewSystem = 0;
    bool isPlaying = false;
    
    //Method
    void AddParticleToSystem(float lifeDuration);
    void UpdateParticleSystem(sf::RenderWindow* window, float deltaTime);
    void ClearParticleSystem();
    void DrawParticleSystem(sf::RenderWindow& window);
    void PlayParticleSystem();
    void StopParticleSystem();
    bool IsParticleSystemPlaying();
};

ParticleSystem CreateParticleSystem(float createParticleTime, float minLifeTime, float maxLifeTime, sf::Vector2f origin, float spawnRadius, int minParticleSize, int maxParticleSize, float maxParticleSpeed, float systemLifeDuration, sf::Color particleColor);
ParticleSystem CreateRandomSystem();