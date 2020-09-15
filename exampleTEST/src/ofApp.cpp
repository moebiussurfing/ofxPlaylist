#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	ofSetFrameRate(30);
	ofSetVerticalSync(TRUE);

	// init
	rectRotation = 0.f;
	rectPos.set(ofRandomWidth(), ofRandomHeight());


    points.push_back(false);
    points.push_back(false);
    points.push_back(false);

}

//--------------------------------------------------------------
void ofApp::update(){

	// this will update all values controlled by mainPlaylist. 
	// to see which values are controlled by mainPlaylist, 
	// jump to ofApp::mouseReleased(), which is where the
	// playlist is set up.
	
	mainPlaylist.update();
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofColor(128);
	
	ofPushMatrix();
    ofPushStyle();
    ofNoFill;

    //ofTranslate(rectPos);
//    ofRotateZ(rectRotation);

    r.x = vr.x;
    r.y = vr.y;
    r.setWidth(rw);
    r.setHeight(rh);

	ofDrawRectangle(r);

    ofTranslate(100,500);
    ofFill();

    int fr = ofGetFrameNum() % 10;

    //if (fr < 5)
    {
    float rad = 15;
    float pad = 20;
    if (val > 0.75){
        ofDrawCircle((4*(pad+rad*2)) + r.x, r.y, rad);
    }
    else if (val > 0.5){
        ofDrawCircle((3*(pad+rad*2)) + r.x, r.y, rad);
    }
    else if (val > 0.25){
        ofDrawCircle((2*(pad+rad*2)) + r.x, r.y, rad);
    }
    else {
        //ofDrawCircle((1*(pad+rad*2) + p) + r.x, r.y, rad);
    }
    }
    ofPopStyle();
    ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ')
    {
    r1 = ofRectangle(100, 100, 200, 100);

    r = ofRectangle(r1);
    vr.x = r.getX();
    vr.y = r.getY();
    rw = r.getWidth();
    rh = r.getHeight();

    r2 = ofRectangle(100, 100, 400, 200);
    vr2.x = r2.getX();
    vr2.y = r2.getY();
    r2w = r2.getWidth();
    r2h = r2.getHeight();

    using namespace Playlist;

    mainPlaylist.addKeyFrame(Action::tween(1000.f, &vr.x, vr2.x));
    mainPlaylist.addToKeyFrame(Action::tween(1000.f, &vr.y, vr2.y));
    mainPlaylist.addToKeyFrame(Action::tween(1000.f, &rw, r2w));
    mainPlaylist.addToKeyFrame(Action::tween(1000.f, &rh, r2h));

    mainPlaylist.addKeyFrame(Action::event([this](){ ofLogNotice() << "event 1: " << rectPos; }));

    // pause for 200 ms - you will only notice this if you click repeatedly.
     mainPlaylist.addKeyFrame(Action::pause(200.f));

    // wobble slightly once target position reached.
//    mainPlaylist.addKeyFrame(Action::tween(1000.f, &rectRotation, ofRandomf()*90, TWEEN_BOUNCE, TWEEN_EASE_OUT));

        float time = 500;
        for (int i = 0; i<10;i++){
            mainPlaylist.addKeyFrame(Action::tween(0, &val, 1, TWEEN_LIN, TWEEN_EASE_OUT));
            mainPlaylist.addKeyFrame(Action::tween(time, &val, 0, TWEEN_QUAD, TWEEN_EASE_OUT));
            mainPlaylist.addKeyFrame(Action::pause(time/4));
        }
//            mainPlaylist.addKeyFrame(Action::tween(1000.f, &val, 0, TWEEN_LIN, TWEEN_EASE_OUT));
//            mainPlaylist.addKeyFrame(Action::pause(1000.f));
//
//        }


        mainPlaylist.addKeyFrame(Action::event([this](){ ofLogNotice() << "event 2: " << rectPos; }));
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
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

//    using namespace Playlist;
//
//    // this will move a rectangle to the mouse position.
//    // and then wobble sigthly.
//
//    ofVec3f targetPosition = ofVec3f(x, y);
//
//    // (1) take 200ms to move to the mouse position on x axis,
//    // (2) take 200ms to move to the mouse position on y axis in sync with x.
//
//    mainPlaylist.addKeyFrame(    Action::tween(200.f, &rectPos.x, targetPosition.x));        // -- (1)
//    mainPlaylist.addToKeyFrame(    Action::tween(200.f, &rectPos.y, targetPosition.y));        // -- (2)
//    mainPlaylist.addKeyFrame(Action::event([this](){ ofLogNotice() << "event 1: " << rectPos; }));
//
//    // pause for 200 ms - you will only notice this if you click repeatedly.
//    // mainPlaylist.addKeyFrame(Action::pause(200.f));
//
//    // wobble slightly once target position reached.
//    mainPlaylist.addKeyFrame(Action::tween(1000.f, &rectRotation, ofRandomf()*90, TWEEN_BOUNCE, TWEEN_EASE_OUT));
//    mainPlaylist.addKeyFrame(Action::event([this](){ ofLogNotice() << "event 2: " << rectPos; }));
//    // --> try other TWEEN_ variations with the above- it's fun!
//    // --> try other TWEEN_EASE_ variations with the above - it's geeky!

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
