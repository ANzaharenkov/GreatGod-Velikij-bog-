#include <iostream>
#include <SFML/Graphics.hpp>
//#include "gameplay.cpp"
#include "GameRes.cpp"
#include "Menu.cpp"
using kbd = sf::Keyboard;
int main()
{
    int WIDTH = 1800;
    int HEIGHT = 900;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),"Torpedo-Bombers");
    std::string screenType = "menu";
    sf::Clock clock;
    //Создание объектов этапов игры
    Gameplay gameplay;
    GameRes gameres;    
    mainMenu menu("Iowa", "Iowa");
    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color(100, 149, 237));

        if (screenType == "menu")
        {   menu.drawSubmenus(window);
            if(kbd::isKeyPressed(kbd::W)){ menu.button(-1, -1, time);}
            if(kbd::isKeyPressed(kbd::S)){ menu.button(-1, 1, time);}
            if(kbd::isKeyPressed(kbd::Up)){ menu.button(1, -1, time);}
            if(kbd::isKeyPressed(kbd::Down)){ menu.button(1, 1, time);}
            
            if(kbd::isKeyPressed(kbd::Space)){
                menu.reloadShips(gameplay.lpl, gameplay.rpl);
                screenType = "gameplay";
                clock.restart();
                //к этому моменту в пуймплей уже загружены все данные, поэтому просто совершается переход
            }
        } else if (screenType == "gameplay")
        {   
            gameplay.drawName(window);
            gameplay.drawTime((int)time,window);
            gameplay.drawXP(window);
            gameplay.drawTorpedIndicators(window, time);
            gameplay.collisionCheck(time);
            gameplay.drawTorpeds(window, time);
            if(kbd::isKeyPressed(kbd::Return)){gameplay.fireTorpds(-1, 1, time);}
            if(time >= 30){
                //условие победы одного из игроков
                screenType = "results";
                gameres.text.setString(gameplay.winner_message);
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
    }

    return 0;
}