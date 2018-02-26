//
//  GrayOperation.cpp
//  GrayDiffRoop
//
//  Created by Hanna Saito on 2017/11/29.
//
//

#include "GrayOperation.hpp"

int GrayOperation::countBrightness(ofImage cell){
    totalBrightness = 0;
    w = cell.getWidth();
    h = cell.getHeight();
    pixnum = w*h;
    
    cell.setImageType(OF_IMAGE_GRAYSCALE);
    
    cellpix = cell.getPixels().getData();
    
    for(int i = 0; i < pixnum; i++){
        
        totalBrightness+=cellpix[i];
    
    }
    
    average = totalBrightness/pixnum; //Runtime error
    
    return average;
}
