#pragma once
#include <SFML/Graphics.hpp>

namespace IIM {

    bool IsOverlappingCircleOnCircle(sf::Vector2f aPosition, float aRadius, sf::Vector2f bPosition, float bRadius);
    bool IsOverlappingBoxOnBox(sf::Vector2f aPosition, sf::Vector2f aSize, sf::Vector2f bPosition, sf::Vector2f bSize);
    bool IsOverlappingCircleOnBox(sf::Vector2f circlePosition, float radius, sf::Vector2f boxPosition, sf::Vector2f boxSize);

    sf::Vector2f ConvertAngleToDirection(float degree, bool flipX = false, bool flipY = true);
    sf::Vector2f ConvertRadianToDirection(float radian, bool flipX = false, bool flipY = true);
    float ConvertVectorToRadian(sf::Vector2f vector, bool flipX = false, bool flipY = true);
    float ConvertVectorToDegree(sf::Vector2f vector, bool flipX = false, bool flipY = true);

    float DegreeToRadian(float degree);
    float RadianToDegree(float radian);

    float GetMagnitude(sf::Vector2f v);
    sf::Vector2f Normalize(sf::Vector2f v);
    float Dot(sf::Vector2f a, sf::Vector2f b);
    float GetDistance(sf::Vector2f a, sf::Vector2f b);
    float GetDistanceToLine(sf::Vector2f position, sf::Vector2f a, sf::Vector2f b);
    sf::Vector2f GetProjectionOnLine(sf::Vector2f position, sf::Vector2f a, sf::Vector2f b);

    float Lerp(float a, float b, float t);
    sf::Vector2f Lerp(sf::Vector2f a, sf::Vector2f b, float t);

}
