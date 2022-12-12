#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class GameRes {
    private:
    float e = 0.5;
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
        text.setPosition(e * 1500, e * 30);
        winmus_buffer.loadFromFile("sound_effects/winmus.wav");
        win_mus.setBuffer(winmus_buffer);
    }
    void playMusic(){
        win_mus.play();
    }
    
};