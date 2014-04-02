#pragma once

#include "ofMain.h"

class Silhouette : public ofBaseApp{

    private:
        ofFbo fbo;
		ofShader silhouette;
		ofShader shashader;

        ofPlanePrimitive plane;
        ofBoxPrimitive box;
        ofLight pointLight;
        //ofMaterial material;
        ofImage texture;

        ofVec3f modelAngle;
        ofVec2f mouseOrigin;

        void setupFbo();
        void center();

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
};
