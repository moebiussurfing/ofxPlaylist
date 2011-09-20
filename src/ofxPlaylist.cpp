/*
 *  ofxPlaylist.cpp
 *
 *
 *                                                   ____         ___                __      __
 *                          __                     /|  _ \       /\_ \    __        /\ \    /\ \__
 *   _____     ___     ___ /\_\     __    ____     |/\   |       \//\ \  /\_\     __\ \ \___\ \ ,_\
 *  /\ '__`\  / __`\ /' _ `\/\ \  /'__`\ /',__\     \// __`\/\     \ \ \ \/\ \  /'_ `\ \  _ `\ \ \/
 *  \ \ \L\ \/\ \L\ \/\ \/\ \ \ \/\  __//\__, `\    /|  \L>  <_     \_\ \_\ \ \/\ \L\ \ \ \ \ \ \ \_
 *   \ \ ,__/\ \____/\ \_\ \_\ \_\ \____\/\____/    | \_____/\/     /\____\\ \_\ \____ \ \_\ \_\ \__\
 *    \ \ \/  \/___/  \/_/\/_/\/_/\/____/\/___/      \/____/\/      \/____/ \/_/\/___L\ \/_/\/_/\/__/
 *     \ \_\                                                                      /\____/
 *      \/_/                                                                      \_/__/
 *
 *
 *  Created by Timothy Gfrerer on 19/10/2010.
 *  Copyright 2010 ponies & light. All rights reserved.
 */

#include "ofxPlaylist.h"

ofxEasingLinear Playlist::tweenLinear;				// 	declare global tween objects for tweeners
ofxEasingSine Playlist::tweenSine;
ofxEasingQuad Playlist::tweenQuad;


// ----------------------------------------------------------------------

ofxPlaylist* ofxPlaylist::addKeyFrame(ofPtr<ofxPlaylistAction> _action){
	// tim-debug: this function was leaking memory like a whole geriatric ward!
	// no more. ofPtr to the rescue.

	lastDuration = _action->getDuration();
	duration += lastDuration;

	playlistBuffer.push_back(ofPtr<Keyframe> (new Keyframe()));

	// add keyframe to the playlistBuffer
	playlistBuffer.back()->push_back(_action);

	anim_idle = FALSE;
	return this;
}

// ----------------------------------------------------------------------

ofxPlaylist* ofxPlaylist::addToKeyFrame(ofPtr<ofxPlaylistAction> _action){
	// get the last element of the queue

	if (_action->getDuration() > lastDuration) {
		duration -= lastDuration;	// take away the smaller value from the total
		lastDuration = _action->getDuration();
		duration += lastDuration;  // and exchange it for the larger value
	}

	//  add ofxKeyFrame to the list.
	playlistBuffer.back()->push_back(_action);
	anim_idle = FALSE;
	return this;
}

// ----------------------------------------------------------------------

void ofxPlaylist::update(){

	if (playlistMutex.tryLock()){
		playlistMutex.unlock();
	} else {
		ofLog(OF_LOG_FATAL_ERROR) << "Did you just try to update a playlist from within an event?. Recursive updates, or what? That's forbidden.";
		ofExit();
	}

	if (bShouldClear == true) {
		bShouldClear = false;
		ofLog(OF_LOG_VERBOSE) << "Did catch soft-clear at the start.";
		clear();
		return;
	}

	playlistMutex.lock();

	flush();

	if (!playlist.empty()){
		if (anim_idle == TRUE){
			anim_idle = doNext();
		} else {
			// do some animation here!

			Keyframe currentKeyframe = *(playlist.front());
			int _boolCount = 0;

			for (int i=0; i<currentKeyframe.size(); i++){
				currentKeyframe[i]->execute();
				if (currentKeyframe[i]->is_idle) _boolCount++;
			}

			if (_boolCount == currentKeyframe.size()) {
				// all the tweens report true, so all the work is done for this frame
				anim_idle = TRUE;
				// check if there are more frames to do work on...
				do {
					anim_idle = doNext();
				} while (anim_idle==TRUE);
			} else {
				// there's still some more stuff to do.
				anim_idle = FALSE;
			}

			if (duration > 0)
				duration--;

		}
	}

	playlistMutex.unlock();

	if (bShouldClear == true) {
		bShouldClear = false;
		ofLog(OF_LOG_NOTICE) << "Did catch soft-clear at the end.";
		clear();
		return;
	}


};

// ----------------------------------------------------------------------

void ofxPlaylist::clear(){
	if(playlistMutex.tryLock()){
		ofLog(OF_LOG_NOTICE) << "Clearing ofxPlaylist.playlist";
		playlist.clear(); 					// aah...... the beauty of
		bShouldClear = false;
		playlistMutex.unlock();
	} else {
		ofLog(OF_LOG_WARNING) << "playlist cannot be cleared currently. Activating soft-clear.";
		bShouldClear = true;
	}
};

// ----------------------------------------------------------------------
// MARK: - event based update helpers

void ofxPlaylist::attach(){
	if (!isAttached) {
		ofAddListener(ofEvents.update, this, &ofxPlaylist::update);
		isAttached = TRUE;
	}
}

// ----------------------------------------------------------------------

void ofxPlaylist::detach(){
	if (isAttached) {
		ofRemoveListener(ofEvents.update, this, &ofxPlaylist::update);
		isAttached = FALSE;
	}

}

// ----------------------------------------------------------------------
// MARK: - private functions

bool ofxPlaylist::doNext(){
	bool _r = TRUE;

	// don't do anything if you are requested to clear.
	if (bShouldClear == true) return FALSE;


	ofLog(OF_LOG_VERBOSE) << "deleting front of queue";
	playlist.pop_front();

	ofLog(OF_LOG_VERBOSE) << "Playlist size now:" << playlist.size();

	if (!playlist.empty()) {
		Keyframe currentKeyframe = *(playlist.front());
//		int idleCount = 0;
		for (int i=0; i<currentKeyframe.size(); i++){
			currentKeyframe[i]->start();
			currentKeyframe[i]->execute();
			if (bShouldClear == true) {
				playlistMutex.unlock();
				return TRUE;
			}

			_r &= currentKeyframe[i]->is_idle;			// &= means, if even one of the result values is other than the initial _r value, _r will be false
		}
		// make sure the caller of this function sets anim_idle to the return value _r!

	} else {
		_r = false;
	}

	return _r;
}

// ----------------------------------------------------------------------

void ofxPlaylist::flush(){
		// push stuff from the playlistBuffer into the playlist, if there's stuff left in there.
		while (!playlistBuffer.empty()) {
			playlist.push_back(playlistBuffer.front());
			playlistBuffer.pop_front();
			ofLog(OF_LOG_VERBOSE) << "flushing one object";
		}
}
