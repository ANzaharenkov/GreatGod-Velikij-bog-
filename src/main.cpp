#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameRes.cpp"
#include "Menu.cpp"
//#include <Kairos/TimestepLite.hpp>

using kbd = sf::Keyboard;
int main()
{
    float e = 1;
    int WIDTH = e * 3200;
    int HEIGHT = e * 1800;
    std::string listOfships[3] = {"Iowa", "Bismark", "Yamato"};
    sf::Sprite shipPict[3];
    sf::Image imgOfShips[3];
    sf::Texture shipTexture[3];
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),"Torpedo-Bombers");
    std::string screenType = "menu";
    sf::Clock clock;
    sf::Time frameTime{ sf::Time::Zero };
    
    //Создание объектов этапов игры
    Gameplay gameplay;
    GameRes gameres;    
    mainMenu menu("Iowa", "Iowa");
    float timeOflastFrame =0;
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        float deltaT = time - timeOflastFrame;
        
        sf::Event event;
         while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        
        window.clear(sf::Color(100, 149, 237));

        if (screenType == "menu")
        {   menu.drawSubmenus(window);  
            if(kbd::isKeyPressed(kbd::S)){ menu.button(-1, -1, time);}
            if(kbd::isKeyPressed(kbd::W)){ menu.button(-1, 1, time);}
            if(kbd::isKeyPressed(kbd::Down)){ menu.button(1, -1, time);}
            if(kbd::isKeyPressed(kbd::Up)){ menu.button(1, 1, time);}
        
            if((kbd::isKeyPressed(kbd::Space))&&(menu.kleft != menu.kright)){
                menu.reloadShips(gameplay.lpl, gameplay.rpl);
                gameplay.reload();
                screenType = "gameplay";
                clock.restart();
                //к этому моменту в пуймплей уже загружены все данные, поэтому просто совершается переход
            }
        } else if (screenType == "gameplay")
        {   
            if(kbd::isKeyPressed(kbd::X)){gameplay.fireTorpds(-1, -1, time, menu.kright, menu.kleft);}
            if(kbd::isKeyPressed(kbd::C)){gameplay.fireTorpds(1, -1, time, menu.kright, menu.kleft);}
            if(kbd::isKeyPressed(kbd::Comma)){gameplay.fireTorpds(-1, 1, time, menu.kright, menu.kleft);}
            if(kbd::isKeyPressed(kbd::Period)){gameplay.fireTorpds(1, 1, time, menu.kright, menu.kleft);}
            gameplay.moveshipL(menu.kleft, deltaT);
            gameplay.moveshipR(menu.kright, deltaT);
            gameplay.drawShipL(window, menu.kleft, gameplay.startPosLx, gameplay.startPosLy, deltaT);
            gameplay.drawShipR(window, menu.kright, gameplay.startPosRx, gameplay.startPosRy, deltaT);
            gameplay.lpl.moveL(deltaT);
            gameplay.rpl.moveR(deltaT);
            gameplay.drawName(window);
            gameplay.drawTime((int)time,window);
            gameplay.drawXP(window);
            gameplay.drawTorpedIndicators(window, time);
            gameplay.collisionCheck(time, menu.kleft, menu.kright,window);
            gameplay.drawTorpeds(window, time);
            if((time >= 300)||(gameplay.lpl.xp <= 0)||(gameplay.rpl.xp <= 0)){
                if(time>= 300){
                    gameplay.winner_message = "DRAW";
                }
                if(gameplay.lpl.xp <= 0){
                    gameplay.winner_message = "RIGHT IS WINNER!!!";
                }
                if(gameplay.rpl.xp <= 0){
                    gameplay.winner_message = "LEFT IS WINNER!!!";
                }
                screenType = "results";
                gameres.text.setString(gameplay.winner_message);
                gameres.text.setPosition(WIDTH/2 - gameplay.winner_message.length()*0.5 * 70, HEIGHT/2 - 0.5 * 80 );
                gameres.playMusic();
                clock.restart();
            }
        } else if (screenType == "results")
        {
            if(time <= 7){
                window.draw(gameres.text);
            } else {
                screenType = "menu";
                clock.restart();
            }
            
        }
        
        window.display();
        timeOflastFrame = time;
    }

    return 0;
}