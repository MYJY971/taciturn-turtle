#pragma once

#include <vector>
#include "ofMain.h"

#include "Camera.h"
#include "Material.h"
#include "Cube.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void exit();
		void update();
		void draw();
		void drawAxes();

        void moveMouse(int x, int y);
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

        ofTrueTypeFont verdana;

        Camera cam;

        std::vector<Cube*> cubes;
        std::vector<Material*> materials;

        bool init;

    //modif Partie 4 ___________________________________________

        ofFbo fbo;
        ofPixels pix;
        ofShader shader;
        ofTexture destroyText[10];
    //__________________________________________________________
};
