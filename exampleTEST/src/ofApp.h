#pragma once


/*    _____    ___     
 *   /    /   /  /     ofxPlaylist Simple Example 
 *  /  __/ * /  /__    (c) ponies & light, 2012. 
 * /__/     /_____/    poniesandlight.co.uk
 * 
 * ofxPlaylist Simple Example
 * Created by Tim Gfrerer 2009-2012.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "ofMain.h"
#include "ofxPlaylist.h"

class ofApp : public ofBaseApp{

	ofxPlaylist mainPlaylist;
	
	ofVec3f		rectPos;
	float		rectRotation;
	
	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		void onKeyframe(ofxPlaylistEventArgs& args);

    ofVec3f vr, vr1, vr2;
    ofRectangle r, r1, r2;
    float rx, ry, rw, rh;
    float r1x, r1y, r1w, r1h;
    float r2x, r2y, r2w, r2h;

    vector <bool> points;

    float val;

};
