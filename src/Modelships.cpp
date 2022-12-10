#include <iostream>
#include <vector>
#include "Torpedo.cpp"
class GameShip{
public:
    int xp;
    int x;
    int y;
    int alpha;
    int Vx;
    int Vy;
    int maxV;
    int maxXp;
    int quantity_of_torpeds;
    int recharge_time;
    float time_of_last_fire;
    std::vector<double> torped_tubes;
    std::string side;
    std::string name;
    //GameShip(int _xp, int _x, int _y, int _alpha, int _Vx, int _Vy, std::string _side, std::string _name): name(_name), side(_side), xp(_xp), x(_x), y(_y), alpha(_alpha), Vx(_Vx), Vy(_Vy) {
    //}
    GameShip(){
        time_of_last_fire = 0;
    }
    bool fire(std::vector<Torpedo> &array, float time){
        bool flag = false;
        for (size_t i = 0; i < quantity_of_torpeds; i++)
        {   
            if((flag == false)&&(time - torped_tubes[i] > recharge_time)){
                if(time - time_of_last_fire > 0.2){
                    time_of_last_fire = time;
                    torped_tubes[i] = time;
                    array.push_back(Torpedo(100, 100, 30));
                    flag = true;
                }
            }
            
        }
        return flag;
    }
    void reloadBeforeNewGame(){
        for (size_t i = 0; i < quantity_of_torpeds; i++) {
            torped_tubes.push_back(0.0);
        }
        
    }
};

