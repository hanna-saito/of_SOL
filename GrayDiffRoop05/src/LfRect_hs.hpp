//
//  LfRect.hpp
//  lightface_multi_hngt
//
//  Created by Shin Hanagatata on 2017/08/17.
//  Edited by Hanna Saito on 2018/01.
//


#include "ofMain.h"
#include <stdio.h>



class LfRect{
private:
    int w,h;
    ofVec2f pos;
    float gradationSpeed;
    
public:
    LfRect();
    void setup(ofVec2f _pos, int _w, int _h, float _gradationSpeed);
    void setStatus(int _status);
    void update();
    void draw();
    void drawStatus(int _rx, int _ry, float _ce);
    void updateGradationSpeed(int val);
    int status;
    int brightness;
    int gradationvalue;
    int getBrightness();
    float g1;
    float g2;
    float fbrightness;
    string statusStr;  
};
