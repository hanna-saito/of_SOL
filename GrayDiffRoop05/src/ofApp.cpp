#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //ofBackground(0);

}

//--------------------------------------------------------------
void ofApp::setupCam(){
    //threshold
    timeTh = 1000; //0になってから1にするまでの時間
    //gui
    //parameters.setName("Threshold");
    parameters.add(th.set("Threshold",50,1,255));
    gui.setup(parameters);
    ofSetBackgroundColor(0);

    
    //cam
    //cam.setDeviceID(1);
    //cam.setDesiredFrameRate(12);
    cam.initGrabber(camW, camH);
    //cam.listDevices();
    
    
    //cell
    cw = 4; //x軸のセルの数
    ch = 3; //y軸のセルの数
    cellNum = cw*ch;//セルの合計数
    
    
    rectS.set(iPadW/cw, iPadH/ch);//セルの一辺の長さ
    
    cout << "rectS : " << rectS << endl;
    
    
    //camWindowのcrop部分の設定
    ce = 0.8;
    rx = 40;
    ry = 40;
    rw = iPadW*ce;
    rh = iPadH*ce;
    cam_fbo.allocate(camW, camH);
    bezManager.setup(10); //WarpResolution
    bezManager.addFbo(&cam_fbo);
    bezManager.loadSettings();
    
    //初期値代入
    for (int y = 0; y < ch; y++) {
        for (int x = 0; x < cw; x++) {
        
            //cout << "val[" << cw*y+x << "] = " << val[cw*y+x] << endl;
            
            vec2.set(rectS.x*x, rectS.y*y);
            rectPos.push_back(vec2);

            cout << "rectS.xd*x = " << rectS.x*x << "rectS.y*y = " << rectS.y*y << endl;
            cout << "rectPos[" << cw*y+x << "].x,rectPos[" << cw*y+x << "].y : (" << rectPos[cw*y+x].x << ","<< rectPos[cw*y+x].y << ")" << endl;
            
            //gray.push_back(val[cw*y+x]*255);
            //cout << "gray[" << y+2*x << "]:" << gray[y+2*x]  << endl;
            //cout << "val[" << y+2*x << "]:" << val[y+2*x]  << endl;
            avr.push_back(0);
            defaultAvr.push_back(0);
            zeroCount.push_back(0);
            isSetBG.push_back(0);
            camCell.push_back(img);
            
            //lfRect setup クラスを編集せずにうまくいったら後で余計な変数を消す
            lfRect.push_back(lf);
            lfRect[cw*y+x].setup(ofVec2f(vec2.x,vec2.y), rectS.x, rectS.y, 0.025);
            
            bstatus.push_back(3); //1フレーム前のlfcellステータス
        
            threshold_Mnum = cellNum*0.4;
        
            //初期値をチェッカー柄にする
            if((x%2==0&&y%2==0)||(x%2==1&&y%2==1)){
                
                    lfRect[cw*y+x].setStatus(3); //MAX
                }
            
            else{
                
                    lfRect[cw*y+x].setStatus(0); //MIN
                
                }
            
            lfRect[cw*y+x].update(); //brightnessの初期値代入のため
            
        }
        
    }
    

}
 
//--------------------------------------------------------------
void ofApp::update(){
    
    
}


//--------------------------------------------------------------
void ofApp::updateCam(ofEventArgs & args){
    
    cam.update();
    
        //LF rect control flow
        if(cam.isFrameNew()){
            
            img.setFromPixels(cam.getPixels());
            img.crop(rx, ry, rw, rh);
            
            for(int i=0; i<cellNum; i++){
                
                if(lfRect[i].status == 3){ //lfcellの明るさがmaxなら
                    //camcellの明度平均を出す
                    camCell[i] = img;
                    camCell[i].crop(rectPos[i].x*ce,rectPos[i].y*ce, rectS.x*ce, rectS.y*ce);
                    avr[i] = gro.countBrightness(camCell[i]);
                    
                    if(lfRect[i].status!=bstatus[i]){ //1フレーム前のステータスがMAXでないなら
                        defaultAvr[i] = avr[i]; //現在のcamcellの明度平均を背景明度にする
                        }

                    if(avr[i] - defaultAvr[i] > th){ //背景明度-明度平均が閾値以上なら
                        lfRect[i].status = 1; //lfcellのステータスをDECREASEにする
                        }
                    
                    }//ok//ok//ok
                
        
                    else if(lfRect[i].status==0 && lfRect[i].status!=bstatus[i]){
                        minRectnum.push_back(i);
                        
                        if(minRectnum.size() >= threshold_Mnum){ //真っ暗なマスが閾値の数を超えたら
                            lfRect[minRectnum[0]].setStatus(2); //最初に暗くなったマスを徐々に明るくする
                            minRectnum.erase(minRectnum.begin()); //真っ暗なマスの番号入り配列の最初を削除
                        }
                    }
        
                    else if(lfRect[i].status == 2 && lfRect[i].getBrightness() >= 255){
                        lfRect[i].setStatus(3);
                    }
        
                    bstatus[i]=lfRect[i].status;
                    lfRect[i].update(); //ここでbrightnessに数値が代入される
                }
    
    
            /*//LF rect update
            for(int i=0;i< cellNum;i++){
                lfRect[i].update();
            }*/
            
    }


    
}//ok

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    for (int i = 0; i < cellNum; i++) {
        
        lfRect[i].draw();
    }

}

//--------------------------------------------------------------
void ofApp::drawCam(ofEventArgs & args){
    ofClear(0);
    
    
    //beziewarp
    cam_fbo.begin();
    cam.draw(0, 0, camW, camH);
    cam_fbo.end();
    bezManager.draw();
    //cam.draw(0, 0, camW, camH);
    
    gui.draw();
    
    ofSetColor(255,30,100);
    
    //draw status by LfRect
    for (int i = 0; i < cellNum; i++) {
        
        lfRect[i].drawStatus(rx, ry, ce);
    }
    
    ofNoFill();
    ofDrawRectangle(rx, ry, rw, rh);
    
    ofSetColor(255);
    
    //string
    /*ofEnableAlphaBlending();
    
    ofSetColor(0, 0, 0, 127);
    
    int strX = 20;
    int strY = 80;
    int strLW = 15;
    
    ofDrawRectangle(strX-10, strY-20, 250, strLW*6+30);
    
    ofSetColor(255, 0, 255);
    
    string avrStr = "Briteness Average1: "+ofToString(avr, 3);
    string defaultAvrStr = "Default Average1: "+ofToString(defaultAvr[0], 3);
    string diffStr = "Briteness Difference1: "+ofToString(defaultAvr[0] - avr[0], 3);
    string Gray1Str = "cell1: "+ofToString(gray[0], 3);
    string gray2Str = "cell2: "+ofToString(gray[1], 3);
    string thStr = "Threshold: "+ofToString(th, 3);
    string isSetBGStr = "isSetBG = "+ofToString(isSetBG, 3);
    
    ofDrawBitmapString(avrStr,strX ,strY);
    ofDrawBitmapString(defaultAvrStr, strX, strY+strLW);
    ofDrawBitmapString(diffStr, strX, strY+strLW*2);
    ofDrawBitmapString(Gray1Str, strX, strY+strLW*3);
    ofDrawBitmapString(gray2Str, strX, strY+strLW*4);
    ofDrawBitmapString(thStr, strX, strY+strLW*5);
    ofDrawBitmapString(isSetBGStr, strX, strY+strLW*6);
    
    ofSetColor(255);*/
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressedCam(ofKeyEventArgs &e){
    
   if (e.key == 'b'){
     defaultAvr = avr;
     }
    
    else if (e.key == OF_KEY_UP){
        ry--;
    }
    
    else if (e.key == OF_KEY_DOWN){
        ry++;
    }
    
    else if (e.key == OF_KEY_LEFT){
        rx--;
    }
    
    else if (e.key == OF_KEY_RIGHT){
        rx++;
    }
    
    else if (e.key == '+'){
        rw++;
    }
    
    else if (e.key == '-'){
        rw--;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseDraggedCam(ofMouseEventArgs &e){
    
    // send drag event
    bezManager.mouseDragged(e.x, e.y, e.button);
    
    /*rw = e.x;
    rh = rw*3/4;*/
    
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    

}

//--------------------------------------------------------------
void ofApp::mousePressedCam(ofMouseEventArgs &e){
    
    // send press event
    bezManager.mousePressed(e.x, e.y, e.button);
    
    /*rx = e.x;
    ry = e.y;*/
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
