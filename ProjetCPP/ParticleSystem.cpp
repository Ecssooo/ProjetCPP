#include "ParticleSystem.h"

void ParticleSystem::AddParticleToSystem(float lifeDuration)
{
    Particle particle = Particle { lifeDuration };

    int size = rand() % (this->minParticleSize + this->maxParticleSize); 
    particle.shape.setRadius(size);

    float angle = pi * 2.0f * (float)rand() / RAND_MAX;
    float distance = this->spawnRadius * sqrt((float)rand() / RAND_MAX);
    float x = this->origin.x + cos(angle) * distance;
    float y = this->origin.y + sin(angle) * distance;
    particle.shape.setPosition(x, y);

    particle.speed = this->maxParticleSpeed;
    sf::Vector2f dir = sf::Vector2f(cos(angle), sin(angle));

    particle.direction = dir;

    particle.shape.setFillColor(this->particleColor);
    
    
    this->allParticle.push_back(particle);
}


void ParticleSystem::UpdateParticleSystem(sf::RenderWindow* window, float deltaTime)
{

    //Update System life time;
    std::list<Particle>::iterator it = this->allParticle.begin();
    this->systemLifeTime += deltaTime;
    if(systemLifeTime >= systemLifeDuration)
    {
        StopParticleSystem();
        this->ClearParticleSystem();
        return;
    }

    this->createNewSystem += deltaTime;

    //Create new System
    // if(this->createNewSystem >= 1)
    // {
    //     allSystem.push_back(CreateRandomSystem());
    //     createNewSystem = 0;
    // }

    //Update all particle of the system;
    while(it != this->allParticle.end())
    {
        (*it).lifeTime += deltaTime;
        
        //Update
            //Scale
        float scale = sin(pi * ((*it).lifeTime/(*it).lifeDuration));
        (*it).shape.setScale(scale,scale);

            //Position
        sf::Vector2f pos = (*it).shape.getPosition();
        pos += (*it).direction * (*it).speed * deltaTime;
        (*it).shape.setPosition(pos);

            //Speed
        (*it).speed -= (*it).speed * deltaTime ;

            //Life time
        if((*it).lifeTime >= (*it).lifeDuration)
        {
            it = this->allParticle.erase(it);
        }

        
        if(this->allParticle.empty())
        {
            break;
        }
        
        it++;
    }
    
    //Spawn new particle;
    this->createCooldown += deltaTime;
    while(this->createCooldown >= this->createParticleTime)
    {
        this->createCooldown -= this->createParticleTime;
        float lifeTime = this->minLifeTime + (this->maxLifeTime - this->minLifeTime) * (float)rand() / RAND_MAX;
        
        this->AddParticleToSystem(lifeTime);
    }
    this->DrawParticleSystem(*window);
}

void ParticleSystem::ClearParticleSystem()
{
    this->allParticle.clear();
    this->createCooldown = 0;
    this->systemLifeTime = 0;
}

ParticleSystem CreateParticleSystem(float createParticleTime, float minLifeTime, float maxLifeTime,
    sf::Vector2f origin, float spawnRadius, int minParticleSize, int maxParticleSize,
    float maxParticleSpeed, float systemLifeDuration, sf::Color particleColor)
{
    return ParticleSystem {{},
        createParticleTime, 0, minLifeTime, maxLifeTime, systemLifeDuration,
        origin, spawnRadius, minParticleSize, maxParticleSize, maxParticleSpeed, particleColor};
}

void ParticleSystem::DrawParticleSystem(sf::RenderWindow& window)
{
    std::list<Particle>::iterator it = this->allParticle.begin();
    while(it != this->allParticle.end())
    {
        window.draw((*it).shape);
        it++;
    }
}

void ParticleSystem::PlayParticleSystem() { this->isPlaying = true; }
void ParticleSystem::StopParticleSystem() { this->isPlaying = false; }
bool ParticleSystem::IsParticleSystemPlaying() { return this->isPlaying; }

ParticleSystem CreateRandomSystem()
{
    
    int x = rand() % 1920;
    int y = rand() % 1080;

    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    ParticleSystem newSystem = CreateParticleSystem(0.1f, 1, 2, sf::Vector2f(x,y),250,1,20,400,5, sf::Color(r,g,b));
    return newSystem;
}

