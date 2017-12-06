#include "ofApp.h"




//--------------------------------------------------------------
void ofApp::setup(){
    //arduino
    
    serial.setup(0,9600);
    
    //General
    ofSetWindowShape(800, 800);
    
    //Gui Controller
    gui.setup();
    gui.add(info1.setup("waves", 2.75, 0, 10));
    gui.add(info2.setup("height", 0, 0, 10));
    gui.add(info3.setup("wake speed", 1, 0, 10));
    gui.add(diam.setup("diameter", 13, 10, 100));
    gui.add(hueWave.setup("wave Hue", 141, 0, 255));
    gui.add(satWave.setup("wave Saturation", 153, 0, 255));
    gui.add(balWave.setup("wave Balance", 255, 0, 255));
//    gui.add(drainSpeed.setup("drain speed", 0, 0, ofGetWindowHeight()));
    
    
    
    //Wave
    t=0;
    
    aridImage.load("arid.png");
    
    //Potentiometer
    waveBegin = ofGetWindowHeight()-(ofGetWindowHeight()*0.9);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    imageW = ofGetWindowWidth();
    imageH = ofGetWindowWidth()*1333/2000;
    
    
    while(serial.available()) {
        char b = serial.readByte();

        if (b=='\n') {
            radius = ofToInt(buffer);
            buffer = "";
        } else {
            buffer += b;
        }
    }
//
//    cout << radius << endl;
//
    //Wave
    diameter = ofGetWindowWidth()*diam/800;
    d = ofGetWindowWidth()*(diam*18/30)/800;
    
    slider1 = ofGetWindowWidth()*info1/800;
    slider2 = ofGetWindowWidth()*info2/800;
    slider3 = ofGetWindowWidth()*info3/800;
   
    t++;
    
    
    
    
    waveSpeed = ofMap(radius, 0, ofGetWindowWidth(), 0, 4);
    waveBegin += waveSpeed;
    
    cout << waveBegin <<endl;
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofSetColor(255);
    
    aridImage.draw(0,ofGetWindowHeight()-imageH, imageW, imageH);
    waveCol.setHsb(hueWave, satWave, balWave);
    ofSetColor(waveCol);
    

    freq = ofMap(slider1,1,10,0.3,3);
    ampl = ofMap(slider2,1,10, ofGetWindowHeight()/10, ofGetWindowHeight()/2);
    n = ofGetWindowWidth()/d;
    offset = t * ofMap(slider3,1,10,0.01,0.05);
    
    
    ofPushMatrix();
    ofTranslate(0, waveBegin);
   
    for (int diff = 0; diff < ofGetWindowHeight(); diff++) {
        
            for (int i = 0; i < n; i++) {
                
            
                
                float theto;
                theto = ofMap(i, 0, n, 0, (M_PI*2) * freq);
                float x = (i * d);
                float y = (sin(theto + offset) * ampl)+diff;
                ofDrawCircle(x,y,diameter/2);
            }
        
    }
            ofSetColor(19,44,56);
            for (int i = 0; i < n; i++) {

                float theto;
                theto = ofMap(i, 0, n, 0, (M_PI*2) * freq);
                float x = (i * d)-10;
                float y = (sin(theto + offset) * ampl)+7;
                ofDrawCircle(x,y,diameter/2);
            }

            ofSetColor(61,132,167);
            for (int i = 0; i < n; i++) {

                float theto;
                theto = ofMap(i, 0, n, 0, (M_PI*2) * freq);
                float x = (i * d)-5;
                float y = (sin(theto + offset) * ampl)+20;
                ofDrawCircle(x,y,diameter/2);
            }
    ofPopMatrix();
    
    gui.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'r'){
        waveBegin = ofGetWindowHeight()-(ofGetWindowHeight()*0.9);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    mX = x;
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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
