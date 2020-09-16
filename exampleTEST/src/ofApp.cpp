#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
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
void ofApp::update() {

	// this will update all values controlled by mainPlaylist. 
	// to see which values are controlled by mainPlaylist, 
	// jump to ofApp::mouseReleased(), which is where the
	// playlist is set up.

	mainPlaylist.update();

}

//--------------------------------------------------------------
void ofApp::draw() {
	ofPushMatrix();
	ofPushStyle();
	{
		//ofTranslate(rectPos);
		//ofRotateZ(rectRotation);

		r.x = vr.x;
		r.y = vr.y;
		r.setWidth(rw);
		r.setHeight(rh);

		ofNoFill;
		ofColor(128);
		
		ofDrawRectangle(r);

		//-

		//dots
		ofTranslate(100, 500);

		float rad = 15;
		float pad = 20;

		ofPushStyle();
		ofFill();
		ofSetColor(64);
		for (int i = 0; i < 5; i++) {
			ofDrawCircle((i * (pad + rad * 2)) + r.x, r.y, rad);
		}
		ofPopStyle();

		ofPushStyle();
		ofFill();
		int fr = ofGetFrameNum() % 30;
		if (fr < 15) ofSetColor(200);
		else ofSetColor(64);

		if (val > 0.8) ofDrawCircle((4 * (pad + rad * 2)) + r.x, r.y, rad);
		else if (val > 0.6) ofDrawCircle((3 * (pad + rad * 2)) + r.x, r.y, rad);
		else if (val > 0.4) ofDrawCircle((2 * (pad + rad * 2)) + r.x, r.y, rad);
		else if (val > 0.2) ofDrawCircle((1 * (pad + rad * 2)) + r.x, r.y, rad);
		else ofDrawCircle((0 * (pad + rad * 2)) + r.x, r.y, rad);
		ofPopStyle();
	}
	ofPopStyle();
	ofPopMatrix();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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
		
		float duration = 1000.f;
		float pause = 600;

		//bubble box
		mainPlaylist.addKeyFrame(Action::tween(duration, &vr.x, vr2.x));
		mainPlaylist.addToKeyFrame(Action::tween(duration, &vr.y, vr2.y));
		mainPlaylist.addToKeyFrame(Action::tween(duration, &rw, r2w));
		mainPlaylist.addToKeyFrame(Action::tween(duration, &rh, r2h));
		mainPlaylist.addKeyFrame(Action::event([this]() { ofLogNotice() << "event 1: " << rectPos; }));

		mainPlaylist.addKeyFrame(Action::pause(pause));

		//-

		//dots
		for (int i = 0; i < 10; i++) {
			mainPlaylist.addKeyFrame(Action::tween(0, &val, 1, TWEEN_LIN, TWEEN_EASE_IN_OUT));
			mainPlaylist.addKeyFrame(Action::tween(duration, &val, 0, TWEEN_LIN, TWEEN_EASE_IN_OUT));
			mainPlaylist.addKeyFrame(Action::pause(pause));
		}

		mainPlaylist.addKeyFrame(Action::event([this]() { ofLogNotice() << "event 2: " << rectPos; }));
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

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
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
