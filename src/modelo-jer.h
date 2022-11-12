#ifndef MODELO_JER_H
#define MODELO_JER_H

#include "grafo-escena.h"

using namespace std;

class Cabeza : public NodoGrafoEscena{
    public:
        Cabeza();
};

class Cuello : public NodoGrafoEscena{
    public:
        Cuello();
};

class Cuerpo : public NodoGrafoEscena{
    public:
        Cuerpo();
};

class Pierna : public NodoGrafoEscena{
    public:
        Pierna();
};

class Brazo : public NodoGrafoEscena{
    public:
        Brazo();
};

class Taladro : public NodoGrafoEscena{
    private:
        const unsigned num_puntas = 8;
        const unsigned NUM_PARAMS = 2;
        const float angulo = 60;
    protected:
        Matriz4f * pm_rot = nullptr;
        Matriz4f * pm_tras = nullptr;
    public:
        Taladro();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
};

class Robot : public NodoGrafoEscena{
    private:
        const unsigned NUM_PARAMS = 3;
        const unsigned num_puntas = 8;
        Taladro *taladradora = new Taladro;
        GrafoEstrellaX * estrella = new GrafoEstrellaX(num_puntas);
    protected:
        Matriz4f * pm_rot = nullptr;
    public:
        Robot();
        unsigned leerNumParametros() const;
        void actualizarEstadoParametro(const unsigned iParam, const float tSec);
        void fijarAlpha(const float alpha_nuevo);
        void fijarBeta(const float alpha_nuevo);
        void fijarGamma(const float alpha_nuevo);
};

#endif // MODELO_JER_H