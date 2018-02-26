//
//  LfRect.cpp
//  lightface_multi_hngt
//
//  Created by Shin Hanagatata on 2017/08/17.
//
//

#include "LfRect_hs.hpp"

LfRect::LfRect(){
    
    
}

void LfRect::setup(ofVec2f _pos, int _w, int _h, float _gradationSpeed){
    pos = _pos;
    w = _w;
    h = _h;
    gradationSpeed=_gradationSpeed;
}

void LfRect::setStatus(int _status){
    status = _status;
    
}

void LfRect::update(){
    switch (status) {
        default:
            statusStr = "MIN";
            brightness = 0;
            g2 = 0;
            break;
        case 1:
            statusStr = "DECREASE";
            if(brightness>0){
                fbrightness = pow(2, (g1*gradationSpeed)) - 1;
                brightness = int(fbrightness + 0.5);
                printf("floatBrightness =  %f, gradationSpeed = %f, g1 = %f \n", fbrightness, gradationSpeed, g1);
                g1 --;
            }
            else status=0;
            break;
        case 2:
            statusStr = "INCREASE";
            if(brightness<255){
                fbrightness = pow(2, (g2*gradationSpeed)) - 1;
                brightness = int(fbrightness + 0.5);
                printf("floatBrightness =  %f, gradationSpeed = %f, g2 = %f \n", fbrightness, gradationSpeed, g2);
                g2 ++;
            }
            else status=3;
            break;
        case 3:
            statusStr = "MAX";
            brightness = 255;
            g1 = 8 / gradationSpeed;
            break;

    }
    
    /*if(brightness > 255){
        brightness = 255; }
    else if(brightness < 0){
        brightness = 0;}*/
    
}

void LfRect::updateGradationSpeed(int val){
    gradationSpeed = val;
}

void LfRect::draw(){
    ofFill();
    ofSetColor(brightness);
    ofDrawRectangle(pos.x, pos.y, w, h);

    
}

void LfRect::drawStatus(int _rx, int _ry, float _ce){
    
    ofDrawBitmapStringHighlight(statusStr+": "+ofToString(status)+": "+ofToString(brightness), pos.x*_ce+_rx+10, pos.y*_ce+_ry+40);

}

int LfRect::getBrightness(){
    return brightness;
}
