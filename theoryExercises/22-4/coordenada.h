#ifndef _COORDENADA_H_
#define _COORDENADA_H_

class Coordenada{
    private:
        float x;
        float y;
    public:
        Coordenada(float cx=0, float cy=0);
        Coordenada();
        Coordenada(const Coordenada &);
        ~Coordenada();
        float getX() const;
        float getY() const;
        void setX(float cx);
        void setY(float cy);

};

#endif
