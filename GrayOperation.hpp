//
//  GrayOperation.hpp
//  GrayDiffRoop
//
//  Created by Hanna Saito on 2017/11/29.
//

#pragma once

#include <stdio.h>
#include "ofxOpenCv.h"

class GrayOperation{
    
public:
    int countBrightness(ofImage cell); //セルの明度合計を出す
    
    unsigned char* cellpix;
    
    int w;
    int h;
    
    int totalBrightness = 0;
    int average;
    int pixnum;
    
};


