#include "Silhouette.h"

//--------------------------------------------------------------
void Silhouette::setup(){

    // FBO
    setupFbo();

    // SHADERS
    silhouette.load("shaders/silhouette.vert", "shaders/silhouette.frag");
    shashader.load("shaders/shashader.vert", "shaders/shashader.frag");
    shadow.load("shaders/shadow.vert", "shaders/shadow.frag");

    // SCENE
    plane.set(ofGetWidth(), ofGetHeight());
    box.set(200);
    texture.loadImage("awesome.png");

	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
    ofSetSmoothLighting(true);

    pointLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    pointLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));

	ofBackground(33);
}

//--------------------------------------------------------------
void Silhouette::update(){
    pointLight.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.5)*(ofGetWidth()*.3), ofGetHeight()/2, 500);
}

//--------------------------------------------------------------
void Silhouette::draw(){

    // FBO CAPTURE

    // Setup
	fbo.begin();
	ofClear(0);
    ofEnableDepthTest();
    ofEnableLighting();
    pointLight.enable();

	// Center and Orbit
	glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0);
    glRotatef(modelAngle.x, 0, 1, 0);
    glRotatef(modelAngle.y, 1, 0, 0);
    plane.draw();

    glRotatef(cos(ofGetElapsedTimef() * 0.05) * 360.0, cos(ofGetElapsedTimef()), sin(ofGetElapsedTimef()), 0);
	box.draw();
	glTranslatef(ofGetWidth() / 4 * cos(ofGetElapsedTimef()),0,0);
    glRotatef(cos(ofGetElapsedTimef() * 0.2) * 360.0, cos(ofGetElapsedTimef()), sin(ofGetElapsedTimef()), 0);
	box.draw();

	fbo.end();

    // Shader
	glPushMatrix();
    shashader.begin();
    shashader.setUniform1f("timeElapsed", ofGetElapsedTimef());
    shashader.setUniformTexture("texture", texture.getTextureReference(), 0);
	glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0);
    glRotatef(modelAngle.x, 0, 1, 0);
    glRotatef(modelAngle.y, 1, 0, 0);
    glRotatef(cos(ofGetElapsedTimef() * 0.05) * 360.0, cos(ofGetElapsedTimef()), sin(ofGetElapsedTimef()), 0);
	box.draw();
	glTranslatef(ofGetWidth() / 4 * cos(ofGetElapsedTimef()),0,0);
    glRotatef(cos(ofGetElapsedTimef() * 0.2) * 360.0, cos(ofGetElapsedTimef()), sin(ofGetElapsedTimef()), 0);
	box.draw();
	shashader.end();
    glPopMatrix();

	// Plane ground
	glPushMatrix();
	glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0);
    glRotatef(modelAngle.x, 0, 1, 0);
    glRotatef(modelAngle.y, 1, 0, 0);
    ofEnableDepthTest();
    ofEnableLighting();
    shadow.begin();
    shadow.setUniform1f("timeElapsed", ofGetElapsedTimef());
	shadow.setUniformTexture("fboTexture", fbo.getTextureReference(0), 0);
    plane.draw();
    shadow.end();
    glPopMatrix();

	// Plane Render
	glPushMatrix();
    ofDisableDepthTest();
    ofDisableLighting();
	glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0);
	silhouette.begin();
	silhouette.setUniformTexture("fboTexture", fbo.getTextureReference(0), 0);
    silhouette.setUniformTexture("depthTexture", fbo.getDepthTexture(), 1);
    plane.draw();
	silhouette.end();
    glPopMatrix();

}

//--------------------------------------------------------------
void Silhouette::keyPressed(int key){
	if( key == OF_KEY_ESC ){
        shashader.unload();
        silhouette.unload();
        shadow.unload();
	}
}

//--------------------------------------------------------------
void Silhouette::keyReleased(int key){

}

//--------------------------------------------------------------
void Silhouette::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void Silhouette::mouseDragged(int x, int y, int button){
    modelAngle.x = (modelAngle.x + (x - mouseOrigin.x) / ofGetWidth() * 360.0f);
    modelAngle.y = (modelAngle.y - (y - mouseOrigin.y) / ofGetHeight() * 360.0f);
    mouseOrigin.x = x;
    mouseOrigin.y = y;
}

//--------------------------------------------------------------
void Silhouette::mousePressed(int x, int y, int button){
    mouseOrigin.x = x;
    mouseOrigin.y = y;
}

//--------------------------------------------------------------
void Silhouette::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void Silhouette::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Silhouette::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Silhouette::dragEvent(ofDragInfo dragInfo){

}
void Silhouette::setupFbo() {
    // Initialize
	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	fbo.begin();
    ofClear(0);
    fbo.end();

    // set DepthBuffer as texture
	ofFbo::Settings settings;
    settings.width = ofGetWidth();
    settings.height = ofGetHeight();
    settings.useDepth = true;
    settings.useStencil = true;
    settings.depthStencilAsTexture = true;
    fbo.allocate(settings);
}
