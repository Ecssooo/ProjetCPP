#include "Math.h"


float SqrtMagnitude(sf::Vector2f value) {
    return value.x * value.x + value.y * value.y;
}
float Magnitude(sf::Vector2f value) {
    return sqrtf(SqrtMagnitude(value));
}

sf::Vector2f Normalize(sf::Vector2f value)
{
    float magnitude = Magnitude(value);
    value.x /= magnitude;
    value.y /= magnitude;
    return value;
}