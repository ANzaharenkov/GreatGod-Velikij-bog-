#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Modelships.cpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using kbd = sf::Keyboard;

class Gameplay{
private:
    float e = 1;
    int WIDTH = e * 3200;
    int HEIGHT = e * 1800;
    
    float x;
    float y;
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
    std::string listOfships[3] = {"Iowa", "Bismark", "Yamato"};
    sf::Sprite shipPict[3];
    sf::Image imgOfShips[3];
    sf::Texture shipTexture[3];
    
    bool inRectangle(float c_x, float c_y, float a, float b, float x_0, float y_0, float alpha, sf::RenderWindow &window){
        bool ans = false;
        float dx = c_x - x_0;
        float dy = c_y - y_0;
        /*
        sf::VertexArray lines1(sf::Lines, 2);
        lines1[0].position = sf::Vector2f(c_x,c_y );
        lines1[1].position = sf::Vector2f(c_x +a/2 * std::cos(alpha), c_y +a/2 * -sin(alpha));
        window.draw(lines1);
        sf::VertexArray lines2(sf::Lines, 2);
        lines2[0].position = sf::Vector2f(c_x,c_y );
        lines2[1].position = sf::Vector2f(c_x +b/2 * cos(3.1415 * 0.5 - alpha), c_y + b/2*std::sin(3.1415 *0.5 - alpha));
        window.draw(lines2);
        */
        float A = dx*std::cos(alpha) + dy * -sin(alpha);
        float B = dx* std::cos(3.1415 * 0.5 - alpha) + dy * std::sin(3.1415 *0.5 - alpha);
        if((fabs(A) < a/2)&&(fabs(B) <b/2)){
            ans = true;
        }
        return ans;
    }

public:
    
    
    float startPosRx = WIDTH;
    float startPosRy = HEIGHT - 100;
    float startPosLx = 0;
    float startPosLy = HEIGHT - 100;
    GameShip lpl;
    GameShip rpl;
    sf::Text text;
    std::string winner_message;
    int gap = e * 28;
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
        sublineXp.setFillColor(sf::Color(160, 160, 160));
        sublineXp.setSize(sf::Vector2f(e*600, e*24));
        realXp.setFillColor(sf::Color::White);
        //forTime
        winner_message = "Left is winner";
        font.loadFromFile("fonts/Rockwell.ttf");
        text.setString("0::");
        text.setFont(font);
        text.setCharacterSize(e * 80);
        text.setStyle(sf::Text::Bold);
        text.setFillColor(sf::Color::White);
        text.setPosition(e * 1530, e * 30);
        //for names of players
        playerName.setFont(font);
        playerName.setCharacterSize(e * 120);
        playerName.setStyle(sf::Text::Bold);
        playerName.setFillColor(sf::Color::White);
        //for time
        
       
    }
    
    void drawName(sf::RenderWindow &window){
        //left
        int gap = e * 30;
        playerName.setString(lpl.name);
        playerName.setPosition(gap, gap * 0.2);
        window.draw(playerName);
        //right
        playerName.setString(rpl.name);
        playerName.setPosition(WIDTH - gap - rpl.name.length() * 65 * e, gap * 0.2);
        window.draw(playerName);
    }
    
    void drawTime(int time, sf::RenderWindow &window){
        std::string sec = std::to_string((300 - time) % 60);
        if((300 - time) % 60 == 0){
            sec = "00";
        }
        if(((300 - time) % 60 < 10)&&((300 - time) % 60 >0)){
            sec = "0" + sec;
        }
        std::string min = std::to_string((300 - time) / 60);
        text.setString(min + ":" + sec);
        window.draw(text);
    }

    void drawTorpedIndicators(sf::RenderWindow &window, float time){
        int a = e * 76;
        //for left
        x = gap;
        y = e * 1800 - gap - a;
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
                torp_ind.setSize(sf::Vector2f(a - e * 12, height));
                torp_ind.setPosition(x + i * (a + gap) + e * 6, y + e * 6 + a - e * 12 - height);
                window.draw(torp_ind);
            }
        }
        //for right
        x = WIDTH - (gap + a) * rpl.quantity_of_torpeds;
        y = HEIGHT - gap - a;
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
                torp_ind.setSize(sf::Vector2f(a - e * 12, height));
                torp_ind.setPosition(x + i * (a + gap) + e * 6, y + e * 6 + a - e * 12 - height);
                window.draw(torp_ind);
            }
        }

    }

    void drawXP(sf::RenderWindow &window){
        //for left
        sublineXp.setPosition(e * 30, e *160);
        realXp.setPosition(e * 30, e * 160);
        realXp.setSize(sf::Vector2f(e *600 * lpl.xp/lpl.maxXp,  e * 24));
        window.draw(sublineXp);
        window.draw(realXp);
        //for right
        //lpl.xp/lpl.maxXp
        sublineXp.setPosition(e*(3200 - 600 - 30), e*160);
        realXp.setPosition(e*(3200 - 600 - 30),e*160);
        realXp.setSize(sf::Vector2f(e*600 *rpl.xp/rpl.maxXp, e*24));
        window.draw(sublineXp);
        window.draw(realXp);
        //
    }
    
    void drawShipL(sf::RenderWindow &window, int kL, int x_0, int y_0, float t){
        
        imgOfShips[kL].loadFromFile("pictures/"+listOfships[kL]+ "_top.png");
        shipTexture[kL].loadFromImage(imgOfShips[kL]);
        shipPict[kL].setTexture(shipTexture[kL]);
        shipPict[kL].setScale(e * 0.3, e * 0.3);
        shipPict[kL].setPosition(x_0 + imgOfShips[kL].getSize().x / 10 , y_0  - imgOfShips[kL].getSize().y / 2 - 130 * e);
        shipPict[kL].setOrigin(imgOfShips[kL].getSize().x / 2, imgOfShips[kL].getSize().y / 2);
        shipPict[kL].setColor(sf::Color(160,160,160));
        shipPict[kL].setRotation(-90);
        shipPict[kL].move(lpl.dxL, lpl.dyL);
        shipPict[kL].rotate(lpl.alphaL);
        window.draw(shipPict[kL]);
    }
            
    void moveshipL(int kL, float t){

        if (kbd::isKeyPressed(kbd::A)){
            lpl.shipRotationL(-1, kL, t);
        }
        if (kbd::isKeyPressed(kbd::D)){
            lpl.shipRotationL(1, kL, t);
        }
        
        if (kbd::isKeyPressed(kbd::W)){
            if(lpl.V <= lpl.maxV){
                lpl.V += t*10;
                std::cout<<lpl.V<< std::endl;  
            }
        }
        if (kbd::isKeyPressed(kbd::S)){
            if(lpl.V >= -lpl.maxV){
                lpl.V -= t*10;
            std::cout<<lpl.V<< std::endl;
            }
            
        }
        
       
    }
   
    void moveshipR(int kR, float t){
        
        if (kbd::isKeyPressed(kbd::Left)){
            rpl.shipRotationR(-1, kR, t);
        }
        if (kbd::isKeyPressed(kbd::Right)){
            rpl.shipRotationR(1, kR, t);
        }
        if (kbd::isKeyPressed(kbd::Up)){
            if(rpl.V <= rpl.maxV){
                rpl.V += t*10;
                std::cout<<rpl.V<< std::endl;  
            }
        }
        if (kbd::isKeyPressed(kbd::Down)){
            if(rpl.V >= -rpl.maxV){
                rpl.V -= t*10;
            }
            
        }
    }

    void drawShipR(sf::RenderWindow &window, int kR, int x_0, int y_0, float t){
        imgOfShips[kR].loadFromFile("pictures/"+listOfships[kR]+"_top.png");
        shipTexture[kR].loadFromImage(imgOfShips[kR]);
        shipPict[kR].setTexture(shipTexture[kR]);
        shipPict[kR].setScale(e * 0.3, e * 0.3);
        shipPict[kR].setPosition(x_0  - imgOfShips[kR].getSize().x / 10 , y_0 - imgOfShips[kR].getSize().y / 2 - 130 * e);
        shipPict[kR].setColor(sf::Color(160,160,160)); 
        shipPict[kR].setRotation(-90);
        shipPict[kR].setOrigin(imgOfShips[kR].getSize().x / 2, imgOfShips[kR].getSize().y / 2);
        shipPict[kR].move(rpl.dxR, rpl.dyR);
        shipPict[kR].rotate(rpl.alphaR);
        window.draw(shipPict[kR]);
        std::cout << rpl.dxR << std::endl;   
    }
 
    void fireTorpds(int side, int plr, float time, int kR, int kL){
        if(plr == 1){
            if(rpl.fireR(array_of_torpeds, time, shipPict[kR], side)){
                sound.setBuffer(fire);
                sound.play();
            }
        } else {
            if(lpl.fireL(array_of_torpeds, time, shipPict[kL], side)){
                sound.setBuffer(fire);
                sound.play();
            }
        }
        
    }
    
    void collisionCheck(float time,  int kL, int kR, sf::RenderWindow &window){
        //функция проверки столкновения
        for (size_t i = 0; i < array_of_torpeds.size(); i++)
        {   
            std::cout << shipTexture[kR].getSize().x << " " << shipTexture[kR].getSize().y << std::endl;
            float head_x = array_of_torpeds[i].x + 0.18*e * torped_texture.getSize().x * std::cos(array_of_torpeds[i].alpha);
            float head_y = array_of_torpeds[i].y + 0.18*e * torped_texture.getSize().y * std::sin(array_of_torpeds[i].alpha);
             /* //============
                sf::CircleShape shape;
                shape.setRadius(10);
                shape.setFillColor(sf::Color::Green);
                shape.setPosition(head_x, head_y);
                window.draw(shape);
                //============= */
            if(inRectangle(shipPict[kL].getPosition().x, shipPict[kL].getPosition().y, shipTexture[kL].getSize().x * e*0.3, shipTexture[kL].getSize().y * e*0.3,head_x, head_y,(90 - lpl.alphaL)*0.00555 * 3.1415,window)){
                
                if(array_of_torpeds[i].detonate == false){
                    lpl.xp -= 50.0; 
                    array_of_torpeds[i].detonate = true;
                    array_of_torpeds[i].detonate_time = time;
                    sound.setBuffer(boom);
                    sound.play();
                }
            }
            if(inRectangle(shipPict[kR].getPosition().x, shipPict[kR].getPosition().y, shipTexture[kR].getSize().x * e*0.3, shipTexture[kR].getSize().y * e*0.3,head_x, head_y,(90 - rpl.alphaR)*0.00555 * 3.1415, window)){
                
                if(array_of_torpeds[i].detonate == false){
                    rpl.xp -= 50.0;  
                    array_of_torpeds[i].detonate = true;
                    array_of_torpeds[i].detonate_time = time;
                    sound.setBuffer(boom);
                    sound.play();
                }
            }
        }
    }

    void drawTorpeds(sf::RenderWindow &window, float time){
        float showTime = 1.8;
        for (size_t i = 0; i < array_of_torpeds.size(); i++)
        {
            if (array_of_torpeds[i].detonate)
            {   
                if(time - array_of_torpeds[i].detonate_time <= showTime){
                    float head_x = array_of_torpeds[i].x + 0.18*e * torped_texture.getSize().x * std::cos(array_of_torpeds[i].alpha);
                    float head_y = array_of_torpeds[i].y + 0.18*e * torped_texture.getSize().y * std::sin(array_of_torpeds[i].alpha);
                    int k = (int)((time - array_of_torpeds[i].detonate_time)* 26/showTime);
                    array_of_bangs_sprite[k].setScale(0.7*e, 0.7*e);
                    array_of_bangs_sprite[k].setPosition(head_x - array_of_bangs_texture[k].getSize().x * 0.5 * 0.7*e,head_y - array_of_bangs_texture[k].getSize().y * 0.5 * 0.7*e);
                    window.draw(array_of_bangs_sprite[(int)((time - array_of_torpeds[i].detonate_time)* 26/showTime)]);
                } else {
                 //удаление из с=массива торпед
                }
                    
            } else {
                array_of_torpeds[i].moveTorpedo();
                torped_sprite.setScale(e*0.12, e*0.12);
                torped_sprite.setPosition(array_of_torpeds[i].x, array_of_torpeds[i].y);
                torped_sprite.setRotation(array_of_torpeds[i].alpha * 180 / 3.14);
                window.draw(torped_sprite);
            }
            
        }
        
    }
    
    void reload(){
        array_of_torpeds.clear();
    }
};