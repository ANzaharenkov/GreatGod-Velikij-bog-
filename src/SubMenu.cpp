#include "json.hpp"
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>

using json = nlohmann::json;

class SubMenu{
private:
   float e = 1;
   int HEIGHT = e * 1800;
   int WIDTH = e * 3200;
   sf::Text infoText;
   sf::Text head;
   sf::Font font;
   float x,y, center;
   std::string arr[5] = {"Name", "Xp", "Recharge time", "Speed", "Torpeds"};
   std::string arr_of_parameters[5] = {"name", "maxXp", "recharge_time", "maxV", "quantity_of_torpeds"};
   std::string listOfships[3] = {"Iowa", "Bismark", "Yamato"};
   sf::Sprite shipPict[3];
   sf::Image imgOfShips[3];
   sf::Texture shipTexture[3];
   const int pic_gap = e * 200;
   sf::CircleShape indicator;
   const float indicator_radius = e * 15.0;
public:
    float time_of_press;
    SubMenu(double _x, double _y):x(_x),y(_y) {
        font.loadFromFile("fonts/Rockwell.ttf");
        infoText.setFillColor(sf::Color::White);
        infoText.setCharacterSize(e * 75);
        infoText.setFont(font);
        indicator.setFillColor(sf::Color::White);
        indicator.setRadius(indicator_radius);
        time_of_press = 0;
        center = e * 0.5 * HEIGHT;
        for (size_t i = 0; i < 3; i++)
        {
            imgOfShips[i].loadFromFile("pictures/"+listOfships[i]+ "_side.png");
            shipTexture[i].loadFromImage(imgOfShips[i]);
            shipPict[i].setTexture(shipTexture[i]);
            shipPict[i].setScale(e * 0.7, e * 0.7);
            shipPict[i].setPosition(x - 20 * e + center - imgOfShips[i].getSize().x/7, 5 * y+pic_gap*i - 100 * e);
            shipPict[i].setColor(sf::Color(160,160,160));
        }
        head.setFont(font);
        head.setCharacterSize(e * 140);
        head.setPosition(x + center - e * 150, y);
        head.setFillColor(sf::Color::Yellow);
    }

    void drawIndicator(sf::RenderWindow &window, int k){
        indicator.setPosition(x + center + e * 600, y - pic_gap * (k - 2) + imgOfShips[k].getSize().y + 160*e);
        window.draw(indicator);
    }

    void drawInfo(json &data, sf::RenderWindow &window, int k){
      int gap = e * 100;
      std::string s  = "juno";
      for (size_t i = 0; i < 5; i++){
                std::stringstream ss;
                ss << data[listOfships[k]][arr_of_parameters[i]];
                std::string s = ss.str();
                ss.clear();
        
         infoText.setString(arr[i] + ": " + s);
         infoText.setPosition(x + 5 * WIDTH/ 19, y + e * 1000 + i * gap);
         window.draw(infoText);
      }
    
   }

    void drawImages(sf::RenderWindow &window){
        for (size_t i = 0; i < 3; i++)
        {
            window.draw(shipPict[i]);
        }
        
    }

    void drawHead(sf::RenderWindow &window, std::string text){
        head.setString(text);
        window.draw(head);
    }
};