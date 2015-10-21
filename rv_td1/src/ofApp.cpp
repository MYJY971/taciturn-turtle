#include "ofApp.h"
#include <ctime>

//--------------------------------------------------------------

//modif Partie 2 : Animer le cube de TNT______________________________

const int vitesseRebond = 7;
int t;
int rebond;
int indTnt;

//_____________________________________________________________________

//modif Partie 3 : Translation_________________________________________
const int speed = 7;
//_____________________________________________________________________






void ofApp::setup()
{
    cam.init(ofGetWidth(),ofGetHeight());
    init = true;

    //modif Partie 4 ___________________________________________
    fbo.allocate( ofGetWidth(), ofGetHeight() );
    //__________________________________________________________

    ofBackground(0,0,0);
    ofEnableDepthTest();
    ofEnableNormalizedTexCoords();
    ofEnableAntiAliasing();
    ofDisableArbTex();

    ofTrueTypeFont::setGlobalDpi(72);
    verdana.loadFont("verdana.ttf", 18, true, true, true);
    verdana.setLineHeight(18.0f);
    verdana.setLetterSpacing(1.037);

    //modif Partie 4 __________________________________________________
    //texture
    ofLoadImage(destroyText[0], "destroy_stage_0.png");
    ofLoadImage(destroyText[1], "destroy_stage_1.png");
    ofLoadImage(destroyText[2], "destroy_stage_2.png");
    ofLoadImage(destroyText[3], "destroy_stage_3.png");
    ofLoadImage(destroyText[4], "destroy_stage_4.png");
    ofLoadImage(destroyText[5], "destroy_stage_5.png");
    ofLoadImage(destroyText[6], "destroy_stage_6.png");
    ofLoadImage(destroyText[7], "destroy_stage_7.png");
    ofLoadImage(destroyText[8], "destroy_stage_8.png");
    ofLoadImage(destroyText[9], "destroy_stage_9.png");

    //shader
    shader.load("shader/textureShader.vert","shader/textureShader.frag");
    //__________________________________________________________________

    // Create cubes and their materials
    Material* sand = new Material("sand.png");
    materials.push_back(sand);

    Material* stonebrick = new Material("stonebrick.png");
    materials.push_back(stonebrick);


    //modif Partie 2 : Ajouter des cubes moussus______________________________

    Material* stonebrick_mossy = new Material("stonebrick_mossy.png");
    materials.push_back(stonebrick_mossy);

    srand(time(NULL));

    //________________________________________________________________________

    Cube* c;
    for (int i=0; i < 2; i++) {
        for (int j=-10; j < 10; j++) {
            for (int k=-10; k < 10; k++) {
                if (i==1){
                    c = new Cube(sand);
                }else{
    //modif Partie 2 : Ajouter des cubes moussus______________________________

                    if(rand()%2==0)
                      c = new Cube(stonebrick);
                    else
                      c = new Cube(stonebrick_mossy);
    //________________________________________________________________________

                }
                c->move(j, i+1, k);
                cubes.push_back(c);
            }
        }
    }




    Material* tnt = new Material("tnt.png");
    materials.push_back(tnt);

    //modif Partie 2 : Animer le cube de TNT______________________________

    c = new Cube(tnt);
    c->move(2, 0, -1);
    cubes.push_back(c);

    indTnt=cubes.size()-1;
    t = 0;
    rebond = 1;

    //_____________________________________________________________________
}

//--------------------------------------------------------------
void ofApp::exit()
{
    for (unsigned int i=0; i<cubes.size(); i++) {
        delete cubes[i];
    }
    for (unsigned int i=0; i<materials.size(); i++) {
        delete materials[i];
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Constrain mouse cursor inside window
    if(init){
        moveMouse(ofGetWidth()/2, ofGetHeight()/2);
        init = false;
    }else{
        int x = ofGetMouseX();
        int y = ofGetMouseY();
        if(x >= ofGetWindowWidth()-1)
            moveMouse(1,y);
        if(x <= 0)
            moveMouse(ofGetWindowWidth()-2,y);
        if(y <= 0)
            moveMouse(x,ofGetHeight()-2);
        if(y >= ofGetHeight()-1)
            moveMouse(x,1);
    }

    //modif Partie 2 : Animer le cube de TNT______________________________
    Cube* c;
    c=cubes[indTnt];

    if(t%vitesseRebond==0)
    {
      rebond=rebond*-1;
      c->move(0,rebond,0);
    }


    t++;

    //_____________________________________________________________________

    //cam.update()

}

//--------------------------------------------------------------
void ofApp::draw()
{
    //modif Partie 4 __________________________________________________
    fbo.begin();
    ofClear(255,255,255, 0);

    ofPushMatrix();
    cam.applyMatrix();
    drawAxes();

    ofPushMatrix();
    ofScale(100,100,100);

    for (unsigned int i=0; i<cubes.size(); i++) {
        cubes[i]->giveColor();

    }

    ofPopMatrix();
    ofPopMatrix();

    cam.drawAim();

    fbo.end();

    fbo.readToPixels(pix);
    //____________________________________________________________

    ofPushMatrix();
    cam.applyMatrix();
    drawAxes();

    ofPushMatrix();
    ofScale(100,100,100);


for (unsigned int i=0; i<cubes.size(); i++) {
    //modif Partie 4 ______________________________________________
    if(cubes[i]->degats > 0)
    {
        shader.begin();
        shader.setUniformTexture("tex1", destroyText[cubes[i]->degats-1], 1);
        cubes[i]->draw();
        shader.end();
    }
    else
    //_____________________________________________________________
      cubes[i]->draw();
}


    ofPopMatrix();
    ofPopMatrix();

    cam.drawAim();




}

//--------------------------------------------------------------
void ofApp::drawAxes()
{
    ofPushMatrix();
    ofSetLineWidth(2);
    ofSetColor(255, 0, 0);
    ofLine(0, 0, 0, 20, 0, 0);
    verdana.drawStringAsShapes("x", 25, 0);
    ofSetColor(0, 255, 0);
    ofLine(0, 0, 0, 0, 20, 0);
    verdana.drawStringAsShapes("y", 5, 25);
    ofSetColor(0, 0, 255);
    ofLine(0, 0, 0, 0, 0, 20);
    ofTranslate(0,0,22);
    verdana.drawStringAsShapes("z", -5, -5);
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::moveMouse(int x, int y)
{
#if defined(__APPLE__)
    CGWarpMouseCursorPosition(CGPointMake(ofGetWindowPositionX()+x,ofGetWindowPositionY()+y));
#elif defined(_WIN32)
    SetCursorPos(x,y); // not tested
#else // xlib
    Display *display = XOpenDisplay(0);
    Window window;
    int state;
    XGetInputFocus(display,&window,&state);
    XWarpPointer(display, None, window, 0, 0, 0, 0, x, y);
    XCloseDisplay(display);
#endif
    cam.mousePressed(x, y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'f')
        ofToggleFullscreen();

    //modif Partie 3 : Translation______________________________

    if(key == 'z')
    {

          cam.update(0,speed,false,true,false, false);
    }

    if(key == 's')
    {

          cam.update(0,-speed,false,true,false, false);
    }

    if(key == 'q')
    {

          cam.update(speed,0,false,true,false, false);
    }

    if(key == 'd')
    {

          cam.update(-speed,0,false,true,false, false);
    }

    //_________________________________________________________

    //modif Partie 5 ? ________________________________________

    //voler
    if(key == ' ')
    {
          cam.update(speed,speed,false,true,false, false);
    }

    //descendre
    //if(key == OF_KEY_SHIFT)
    if(key == OF_KEY_DOWN)
    {
          cam.update(-speed,-speed,false,true,false, false);
    }

    //teleportation à la position initial
    if(key == 't')
    {
          cam.update(0,0,false,false ,false, true);
    }

    //_________________________________________________________


}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
  //modif Partie 3 : Rotation_________________________________
    cam.update(x, y,false , false, true, false);
  //__________________________________________________________
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(button==0)
        cam.update(x, y, true, false, false, false);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

  //modif Partie 4 __________________________________________________
    ofColor c = pix.getColor(x, y);

    //clic gauche, détruit le cube
    if(button==0 && x>0 && y>0)
        {
          cam.mousePressed(x, y);


          for (unsigned int i=0; i<cubes.size(); i++)
            {
              if(cubes[i]->colorId == c)
              {
                  cubes[i]->degats++;

                    if(cubes[i]->degats > 10)
                        cubes.erase(cubes.begin()+i);
              }
            }

        }

    //clic droit, crée un cube au dessus
    if(button==2)
    {
       ofVec3f pos;

       for (unsigned int i=0; i<cubes.size(); i++)
            if(cubes[i]->colorId == c)
                 pos =cubes[i]->getPosition();



      Cube* c;
      Material* stone = new Material("stone.png");
      materials.push_back(stone);
      c = new Cube(stone);

      pos.y--;
      c->move(pos);

      cubes.push_back(c);
    }

    //clic molette, change la couleur du cube
    if(button==1)
    {
        for (unsigned int i=0; i<cubes.size(); i++)
        {
            if(cubes[i]->colorId == c)
                cubes[i]->colorize();

        }
    }

    //modif Partie 4 __________________________________________________

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    cam.init(ofGetWidth(),ofGetHeight());
}
