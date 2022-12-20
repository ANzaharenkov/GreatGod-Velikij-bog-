#include "gameplay.cpp"
#include "SubMenu.cpp"
#include <fstream>

using json = nlohmann::json;

class mainMenu{
   private:
   std::string left_name;
   std::string right_name;
   json data;
   float e = 1; 
   
   SubMenu lSubMenu;
   SubMenu rSubMenu;
   std::string listOfships[3] = {"Iowa", "Bismark", "Yamato"};
   public:
   int kleft = 2;
   int kright = 2;
   mainMenu(std::string _left_name, std::string _right_name):lSubMenu({e * 20.0, e * 100.0}), rSubMenu({e * 900.0, e * 100.0}), right_name(_right_name), left_name(_left_name){
      std::ifstream f("config.json");
      data = json::parse(f);
   }    

   void reloadShips(GameShip &lpl, GameShip &rpl){
      left_name = listOfships[kleft];
      right_name = listOfships[kright];
      lpl.name = data[left_name]["name"];
      rpl.name = data[right_name]["name"];

      lpl.quantity_of_torpeds = data[left_name]["quantity_of_torpeds"];
      rpl.quantity_of_torpeds = data[right_name]["quantity_of_torpeds"];

      lpl.recharge_time = data[left_name]["recharge_time"];
      rpl.recharge_time = data[right_name]["recharge_time"];

      lpl.maxV = data[left_name]["maxV"];
      rpl.maxV = data[right_name]["maxV"];

      lpl.maxXp = data[left_name]["maxXp"];
      rpl.maxXp = data[right_name]["maxXp"];

      lpl.xp = lpl.maxXp;
      rpl.xp = rpl.maxXp;

      lpl.reloadBeforeNewGame();
      rpl.reloadBeforeNewGame();
   }

   void drawSubmenus(sf::RenderWindow &window){
     rSubMenu.drawInfo(data, window, kright);
     rSubMenu.drawImages(window);
     rSubMenu.drawIndicator(window, kright);
     rSubMenu.drawHead(window, "Right Player");

     lSubMenu.drawInfo(data, window, kleft);
     lSubMenu.drawImages(window);
     lSubMenu.drawIndicator(window, kleft);
     lSubMenu.drawHead(window, "Left PLayer");
   }
   
   //up == +1 down -1
   void button(int side, int direction, float time){
      if((side == 1)&& time - lSubMenu.time_of_press > 0.2){
         lSubMenu.time_of_press = time;
         kright += direction;
         if(kright == -1)
            kright = 2;
         if(kright == 3)
            kright = 0;
      std::cout<< kright << std::endl; 
      }

      if((side == -1)&& time - rSubMenu.time_of_press > 0.2){
         rSubMenu.time_of_press = time;
         kleft += direction;
         if(kleft == -1)
            kleft = 2;
         if(kleft == 3)
            kleft = 0;
      std::cout<< kleft << std::endl; 
      }
   }
};