#include "Camera.h"
#include "ofMain.h"

//modif Partie 3 : Rotation_________________________________

float tx=0;
float tz=0;
float ty=0;

float tmp=0;
float tmpRotX=0;

ofVec3f eye(0,0,400);
ofVec3f target=eye;
ofVec3f origine(0,0,0);


//__________________________________________________________

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::init(int windowWidth, int windowHeight)
{
    width = windowWidth;
    height = windowHeight;
    aim_dist = 400;
    rotX = 0;
    rotY = 0;
    lastX = width/2;
    lastY = height/2;
    axeX = 0;
    axeZ = -aim_dist;
    axeY = 0;

}


 void Camera::applyMatrix()
 {
    ofLoadIdentityMatrix();
    //modif Partie 3 : Translation______________________________

    ofTranslate(axeX ,axeY , axeZ);

    //__________________________________________________________
    ofRotateX(rotX);
    ofRotateY(rotY);
 }

void Camera::update(int x, int y, bool drag, bool translat, bool rot, bool tp)
{
    if(drag)
    {
      float rateX = 180.0/float(height);
      float rateY = 180.0/float(width);
      float diffX = x - lastX;
      float diffY = lastY - y;
      lastX = x;
      lastY = y;
      rotX += diffY * rateY;
      rotY += diffX * rateX;

    }
    //modif Partie 3 : ________________________________________
    if(translat)
    {
      //modif Partie 5 -----
      if(x>0 && y>0)
        axeY+=x;
      else
        if(x<0 && y<0)
        axeY+=x;

        else
        {
      //--------------------

        //modif Partie 3 : Translation______________________________
        axeX+=x;
        axeZ+=y;
        //__________________________________________________________


    //modif Partie 3 : Rotation_________________________________
      eye.x-=x;
      eye.z-=y;
     }
    }

    if(rot)
    {

          //rotation autour de x
          if(y>lastY)
          {
            rotX--;
          }
          if(y<lastY)
          {
            rotX++;
          }

          lastY=y;



          tmpRotX=rotX-tmpRotX;

          target=eye.getRotated(tmpRotX,origine,ofVec3f(1, 0, 0));

          ty=eye.y - target.y;
          tz=eye.z - target.z;

          axeY+=ty;
          axeZ+=tz;

          origine.y+=ty;
          origine.z+=tz;

          tmpRotX=rotX;


        //rotation autour de y
        if(x>lastX)
        {
          rotY++;
        }
        if(x<lastX)
        {
          rotY--;
        }
        lastX=x;



        tmp=rotY-tmp;

        target=eye.getRotated(tmp,origine,ofVec3f(0, 1, 0));

        tx=eye.x - target.x;
        tz=eye.z - target.z;

        axeX+=tx;
        axeZ+=tz;

        origine.x+=tx;
        origine.z+=tz;

        tmp=rotY;



    }

    if(tp)
    {

        axeX+=(-axeX);
        axeY+=(-axeY);
        axeZ+=(-axeZ)-aim_dist;


    }
    //__________________________________________________________

}

void Camera::mousePressed(int x, int y)
{
    lastX = x;
    lastY = y;
}

void Camera::drawAim()
{
    ofDisableDepthTest();

    ofPushMatrix();
    ofTranslate(width/2, height/2);
    ofSetLineWidth(4);
    ofSetColor(100, 100, 100);
    ofLine(-10, 0, 10, 0);
    ofLine(0, -10, 0, 10);
    ofPopMatrix();

    ofEnableDepthTest();
}
