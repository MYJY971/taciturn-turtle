#pragma once

class Camera
{
    public:
        Camera();
        virtual ~Camera();

        void init(int windowWidth, int windowHeight);
        void applyMatrix();
        //modif Partie 3 : ___________________________________________

        void update(int x, int y, bool drag, bool translat, bool rot, bool tp);
        //____________________________________________________________
        void mousePressed(int x, int y);
        void drawAim();

    private:
        int width;
        int height;

        float rotX;
        float rotY;

        float aim_dist;

        // Previous mouse position
        int lastX;
        int lastY;

        //modif Partie 3 _______________________________
        float axeX;
        float axeZ;
        float axeY;
        //______________________________________________
};
