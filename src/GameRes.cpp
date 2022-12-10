#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class GameRes {
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
        text.setCharacterSize(160);
        text.setStyle(sf::Text::Bold); 
        text.setFillColor(sf::Color::White);
        text.setPosition(1530, 30);
        winmus_buffer.loadFromFile("sound_effects/winmus.wav");
        win_mus.setBuffer(winmus_buffer);
    }
    void playMusic(){
        win_mus.play();
    }
    
};