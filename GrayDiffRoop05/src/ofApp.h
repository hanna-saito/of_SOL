#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxOpenCv.h"
#include "ofxBezierWarpManager.h"
#include "GrayOperation.hpp"
#include "LfRect_hs.hpp"

#include <math.h>

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void setupCam();
    void update();
    void updateCam(ofEventArgs &args);
    void draw();
    void drawCam(ofEventArgs &args);
    
    void keyPressed(int key);
    void keyPressedCam(ofKeyEventArgs &e);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mouseDraggedCam(ofMouseEventArgs &e);
    void mousePressed(int x, int y, int button);
    void mousePressedCam(ofMouseEventArgs &e);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofParameterGroup parameters;
    ofParameter<int> th;
    ofxPanel gui;
    ofVideoGrabber cam;
    ofImage img;
    ofVec2f vec2;
    LfRect lf;
    GrayOperation gro;
    
    //c920サイズ
    const int camW = 1920;
    const int camH = 1080;
    
    const int iPadW = 1024;
    const int iPadH = 768;
    
    int cw; //x軸のセルの数
    int ch; //y軸のセルの数
    int cellNum;//セルの合計数
    
    //vector <int> val;//セルの値
    //vector <int> gray; //セルの色
    vector <int> defaultAvr; //lfセルの背景色（実行中に変わる）
    vector <int> avr; //camセルの明度平均
    vector <int> zeroCount; //valが0になってからの時間
    vector <int> minRectnum;
    vector <int> bstatus; //1フレーム前のステータス
    vector <bool> isSetBG; //現在のcamセル濃度を背景色にするかどうかのフラグ
    vector <ofImage> camCell;
    vector <LfRect> lfRect;
    
    //Cell position
    vector <ofVec2f> rectPos;
    
    //Cell size
    ofVec2f rectS; //セルのwとhのサイズ
    
    bool bIn[2];
    int count,count2;
    
    //webcam映像用
    int rx, ry, rw, rh; //映像のcrop領域
    float ce; //crop領域とipadサイズの比（係数）
    ofFbo cam_fbo;
    ofxBezierWarpManager bezManager;
    
    int timeTh;
    int threshold_Mnum;
};


