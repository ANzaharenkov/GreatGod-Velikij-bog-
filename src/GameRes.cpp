#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class GameRes {
    float e = 1;
    int WIDTH = e * 3200;
    int HEIGHT = e * 1800;
    private:
    sf::Font font;
    sf::SoundBuffer winmus_buffer;
    sf::Sound win_mus;
    public:
    sf::Text text;
    GameRes(){
        font.loadFromFile("fonts/Rockwell.ttf");
        text.setString("0::");
        text.setFont(font);
        text.setCharacterSize(e * 160);
        text.setStyle(sf::Text::Bold); 
        text.setFillColor(sf::Color::White);
        text.setPosition(WIDTH/2 , e * 30);
        winmus_buffer.loadFromFile("sound_effects/winmus.wav");
        win_mus.setBuffer(winmus_buffer);
    }
    void playMusic(){
        win_mus.play();
    }
    
};