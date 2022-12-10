#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
class Torpedo{
    private:
    
    public:
    float x;
    float y;
    float alpha;
    float v = 1.0;
    bool detonate;
    float detonate_time;
    Torpedo(float _x, float _y, float _alpha): x(_x), y(_y), alpha(_alpha), detonate(false) {}
    void Boom(float time, sf::RenderWindow &window){
        
    }
    void moveTorpedo(){
        x+= v*std::cos(alpha);
        y+= v*std::sin(alpha);
    }
};