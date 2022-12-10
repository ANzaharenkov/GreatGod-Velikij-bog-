#include <iostream>
#include <SFML/Graphics.hpp>
#include "Modelships.cpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


class Gameplay{
private:
    int WIDTH = 1800;
    int HEIGHT = 900;
    float e = 0.5;
    sf::Font font;
    sf::RectangleShape sublineXp;
    sf::RectangleShape realXp;
    sf::RectangleShape torp_ind;
    sf::Text playerName;
    sf::Texture torped_texture;
    sf::Sprite torped_sprite;
    std::vector<Torpedo> array_of_torpeds;
    sf::Texture array_of_bangs_texture[26];
    sf::Sprite array_of_bangs_sprite[26];
    sf::SoundBuffer fire, boom;
    sf::Sound sound;
public:
    GameShip lpl;
    GameShip rpl;
    sf::Text text;
    std::string winner_message;
    Gameplay(){
        //Sounds
        fire.loadFromFile("sound_effects/fire.wav");
        boom.loadFromFile("sound_effects/Boom.wav");
        //for torpeds detonation
        for (size_t i = 0; i < 26; i++){
            array_of_bangs_texture[i].loadFromFile("pictures/Boompict/" + std::to_string(i+1) + ".png");
            array_of_bangs_sprite[i].setTexture(array_of_bangs_texture[i]);
        }
        //for torpeds
        torped_texture.loadFromFile("pictures/torpedo.png");
        torped_sprite.setTexture(torped_texture);
        //forXP
        sublineXp.setFillColor(sf::Color(100, 149, 237));
        sublineXp.setSize(sf::Vector2f(e * 600, e * 24));
        realXp.setFillColor(sf::Color::White);
        //forTime
        winner_message = "Left is winner";
        font.loadFromFile("fonts/Rockwell.ttf");
        text.setString("0::");
        text.setFont(font);
        text.setCharacterSize(e * 80);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setPosition(e * 1530, 30);
        //for names of players
        playerName.setFont(font);
        playerName.setCharacterSize(120);
        playerName.setStyle(sf::Text::Bold);
        playerName.setFillColor(sf::Color::White);
    }
    
    void drawName(sf::RenderWindow &window){
        //left
        int gap = e * 30;
        playerName.setString(lpl.name);
        playerName.setPosition(gap, gap * 0.2);
        window.draw(playerName);
        //right
        playerName.setString(rpl.name);
        playerName.setPosition(WIDTH - gap - rpl.name.length() * 65, gap * 0.2);
        window.draw(playerName);
    }
    
    void drawTime(int time, sf::RenderWindow &window){
        std::string sec = std::to_string((300 - time) % 60);
        if((300 - time) % 60 == 0){
            sec = "00";
        }
        std::string min = std::to_string((300 - time) / 60);
        text.setString(min + ":" + sec);
        window.draw(text);
    }

    void drawTorpedIndicators(sf::RenderWindow &window, float time){
        int x = 0;
        int y = 0;
        int a = e* 76;
        int gap = e* 28;
        //for left
        x = gap;
        y = e* 1800 - gap - a;
        for(int i = 0; i<lpl.quantity_of_torpeds; i++){
                torp_ind.setFillColor(sf::Color(160,160,160));
                torp_ind.setSize(sf::Vector2f(a,a));
                torp_ind.setPosition(x + i*(a + gap), y);
                window.draw(torp_ind);
            if ((time - lpl.torped_tubes[i]) >= lpl.recharge_time)
            {
                torp_ind.setFillColor(sf::Color::White);
                torp_ind.setSize(sf::Vector2f(a,a));
                torp_ind.setPosition(x + i*(a + gap), y);
                window.draw(torp_ind);
            } else {
                float k = (time - lpl.torped_tubes[i])/lpl.recharge_time;
                float height = k * (a - e * 12);
                torp_ind.setFillColor(sf::Color::White);
                torp_ind.setSize(sf::Vector2f(a - 12, height));
                torp_ind.setPosition(x + i * (a + gap) + e * 6, y + e * 6 + a - e * 12 - height);
                window.draw(torp_ind);
            }
        }
        //for right
        x = HEIGHT - (gap + a) * rpl.quantity_of_torpeds;
        y = WIDTH - gap - a;
        for(int i = 0; i<rpl.quantity_of_torpeds; i++){
                torp_ind.setFillColor(sf::Color(160,160,160));
                torp_ind.setSize(sf::Vector2f(a,a));
                torp_ind.setPosition(x + i*(a + gap), y);
                window.draw(torp_ind);
            if ((time - rpl.torped_tubes[i]) >= rpl.recharge_time)
            {
                torp_ind.setFillColor(sf::Color::White);
                torp_ind.setSize(sf::Vector2f(a,a));
                torp_ind.setPosition(x + i*(a + gap), y);
                window.draw(torp_ind);
            } else {
                float k = (time - rpl.torped_tubes[i])/rpl.recharge_time;
                float height = k*(a - e * 12);
                torp_ind.setFillColor(sf::Color::White);
                torp_ind.setSize(sf::Vector2f(a-12, height));
                torp_ind.setPosition(x + i * (a + gap) + e * 6, y + e * 6 + a - e * 12 - height);
                window.draw(torp_ind);
            }
        }

    }

    void drawXP(sf::RenderWindow &window){
        //for left
        sublineXp.setPosition(30, 160);
        realXp.setPosition(30,160);
        realXp.setSize(sf::Vector2f(300, 24));
        window.draw(sublineXp);
        window.draw(realXp);
        //for right
        //lpl.xp/lpl.maxXp
        sublineXp.setPosition(3200 - 600 - 30, 160);
        realXp.setPosition(3200 - 600 - 30,160);
        realXp.setSize(sf::Vector2f(300, 24));
        window.draw(sublineXp);
        window.draw(realXp);
    }
    
    void fireTorpds(int side, int to, float time){
        if(side == 1){
            if(rpl.fire(array_of_torpeds, time)){
                sound.setBuffer(fire);
                sound.play();
            }
        } else {
            if(lpl.fire(array_of_torpeds, time)){
                sound.setBuffer(fire);
                sound.play();
            }
        }
        
    }
    
    void collisionCheck(float time){
        //функция проверки столкновения
        for (size_t i = 0; i < array_of_torpeds.size(); i++)
        {
            if (array_of_torpeds[i].detonate == false)
            {
                array_of_torpeds[i].detonate = true;
                array_of_torpeds[i].detonate_time = time;
                sound.setBuffer(boom);
                sound.play(); 
            } 
        }
    }

    void drawTorpeds(sf::RenderWindow &window, float time){
        float showTime = 1.8;
        for (size_t i = 0; i < array_of_torpeds.size(); i++)
        {
            if (array_of_torpeds[i].detonate)
            {   
                if(time - array_of_torpeds[i].detonate_time <= showTime)
                    window.draw(array_of_bangs_sprite[(int)((time - array_of_torpeds[i].detonate_time)* 26/showTime)]);
            } else {
                array_of_torpeds[i].moveTorpedo();
                torped_sprite.setPosition(array_of_torpeds[i].x, array_of_torpeds[i].y);
                torped_sprite.setRotation(array_of_torpeds[i].alpha);
                window.draw(torped_sprite);
            }
            
        }
        
    }


};