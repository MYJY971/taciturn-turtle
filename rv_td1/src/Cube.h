#pragma once

#include "ofMain.h"

#include "Material.h"

class Cube : public ofNode
{
public:
    Cube(Material* m);
    virtual ~Cube();
    virtual void customDraw();

    //modif Partie 4 __________________________________________________
    virtual void giveColor();
    void colorize();
    ofColor colorId;
    int degats;
    //_________________________________________________________________

private:
    Material* _m;
    ofVboMesh _mesh;
    //modif Partie 4 __________________________________________________
    static int redId;
    static int greenId;
    static int blueId;
    bool colored;
    //_________________________________________________________________

};
