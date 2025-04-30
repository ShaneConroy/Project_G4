#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <random>
#include <optional>

float const SCREEN_WIDTH = 1200;
float const SCREEN_HEIGHT = 800;

float getDistanceBetween(sf::Vector2f, sf::Vector2f);
sf::Vector2f normaliseVector(sf::Vector2f);
sf::Vector2f randomPosOnField(const sf::Vector2f& xRange, const sf::Vector2f& yRange);
float vectorLength(const sf::Vector2f&);
sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t);
int getNumberBetween(int min, int max);