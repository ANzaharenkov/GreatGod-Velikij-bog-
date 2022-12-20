#include <iostream>
#include <vector>
#include "Torpedo.cpp"



class GameShip{
public:
    float e =1;
    int WIDTH = e * 3200;
    int HEIGHT = e * 1800;
    float startPosRx = WIDTH;
    float startPosRy = HEIGHT - 100*e;
    float startPosLx = 0;
    float startPosLy = HEIGHT - 100*e;
    float xp;
    int maxV;
    float maxXp;
    int quantity_of_torpeds;
    int recharge_time;
    float time_of_last_fire;
    std::string listOfships[3] = {"Iowa", "Bismark", "Yamato"};
    sf::Sprite shipPict[3];
    sf::Image imgOfShips[3];
    sf::Texture shipTexture[3];
    float epsilon[3] = {5, 5, 5};
    double shipmaxOmega[3] = {20, 20, 15};
    double dxL = 0;
    double dyL = 0;
    double dxR = 0;
    double dyR = 0;
    double omegaR = 0;
    double omegaL = 0;
    float alphaR = 0;
    float alphaL = 0;
    float V = 0;

    std::vector<double> torped_tubes;
    std::string name;
    GameShip(){
        time_of_last_fire = 0;
    }
    
    bool fireR(std::vector<Torpedo> &array, float time, sf::Sprite player_ship, int side){
        bool flag = false;
        float r = 200;
        for (size_t i = 0; i < quantity_of_torpeds; i++)
        {   
            if((flag == false)&&(time - torped_tubes[i] > recharge_time)){
                if(time - time_of_last_fire > 0.2){
                    time_of_last_fire = time;
                    torped_tubes[i] = time;
                    if(side == 1){
                        array.push_back(Torpedo(player_ship.getPosition().x + r* std::cos(alphaR/180 * 3.14),player_ship.getPosition().y + r * sin(alphaR/180 * 3.14), alphaR/180 * 3.14));
                    } else {
                        array.push_back(Torpedo(player_ship.getPosition().x + -r* std::cos(alphaR/180 * 3.14),player_ship.getPosition().y - r * sin(alphaR/180 * 3.14), -(180-alphaR)/180 * 3.14));
                    }
                    
                    flag = true;
                }
            }
            
        }
        return flag;
    }
    
    bool fireL(std::vector<Torpedo> &array, float time, sf::Sprite player_ship,  int side){
        bool flag = false;
        float r = 50;
        for (size_t i = 0; i < quantity_of_torpeds; i++)
        {   
            if((flag == false)&&(time - torped_tubes[i] > recharge_time)){
                if(time - time_of_last_fire > 0.2){
                    time_of_last_fire = time;
                    torped_tubes[i] = time;
                    if(side == 1){
                        array.push_back(Torpedo(player_ship.getPosition().x + r* std::cos(alphaL/180 * 3.14),player_ship.getPosition().y + r * sin(alphaL/180 * 3.14), alphaL/180 * 3.14));
                    } else {
                        array.push_back(Torpedo(player_ship.getPosition().x + -r* std::cos(alphaL/180 * 3.14),player_ship.getPosition().y - r * sin(alphaL/180 * 3.14), -(180-alphaL)/180 * 3.14));
                    }
                    
                    flag = true;
                }
            }
            
        }
        return flag;
    }

    void reloadBeforeNewGame(){
        torped_tubes.clear();
        for (size_t i = 0; i < quantity_of_torpeds; i++) {
            torped_tubes.push_back(0.0);
        }
        dxL = 0;
        dyL = 0;
        dxR = 0;
        dyR = 0;
        omegaR = 0;
        omegaL = 0;
        alphaR = 0;
        alphaL = 0;
        V = 0;
    }    
    
    float shipRotationR(int direction, int kR, float t){
        if(fabs(omegaR) <= shipmaxOmega[kR]){
            omegaR += epsilon[kR] * t;
            alphaR += direction *  omegaR * t;  
        }else{
            //epsilon[kR] = 0;
            alphaR += direction * omegaR * t;
        }
        float alphaR_0 = shipPict[kR].getRotation();
        return alphaR;
    }

    float shipRotationL(int direction, int kL, float t){
        std::cout << omegaL << " icOmega" << std::endl;
        if(fabs(omegaL) <= shipmaxOmega[kL]){
            omegaL += epsilon[kL] * t;
            alphaL += direction * omegaL * t;   
            
        }else{
            //epsilon[kL] = 0;
            alphaL += direction * omegaL*t;
        }
        
        float alphaL_0 = shipPict[kL].getRotation();
        return alphaL;
    }

    void moveL(float deltaT){
        dxL += 10*V*deltaT * sin(alphaL * 3.14/180);
        dyL +=  -10*V*deltaT * cos(alphaL * 3.14/180); 
    }
    void moveR(float deltaT){
        dxR += 10*V*deltaT * sin(alphaR * 3.14/180);
        dyR +=  -10*V*deltaT * cos(alphaR * 3.14/180); 
    }

};
   

