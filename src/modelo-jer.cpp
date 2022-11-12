#include "modelo-jer.h"

Robot::Robot(){
    NodoGrafoEscena *piernas = new NodoGrafoEscena;
    piernas->agregar(MAT_Traslacion({0.5,0.0,0.0}));
    piernas->agregar(new Pierna);
    piernas->agregar(MAT_Traslacion({-1.0,0.0,0.0}));
    piernas->agregar(new Pierna);

    NodoGrafoEscena *brazo_izq = new NodoGrafoEscena;
    brazo_izq->agregar(MAT_Traslacion({-1.0,0.0,0.0}));
    brazo_izq->agregar(new Brazo);

    NodoGrafoEscena *brazo_dcho = new NodoGrafoEscena;
    brazo_dcho->agregar(MAT_Traslacion({1.0,0.0,0.0}));
    brazo_dcho->agregar(new Brazo);

    NodoGrafoEscena *taladro = new NodoGrafoEscena;
    taladro->agregar(MAT_Traslacion({1.0,-0.25,1.25}));
    taladro->agregar(taladradora);

    NodoGrafoEscena *shuriken = new NodoGrafoEscena;
    shuriken->agregar(MAT_Traslacion({-1.0,-0.25,1.26}));
    shuriken->agregar(estrella);
    shuriken->agregar(MAT_Rotacion(90,{0.0,0.0,1.0}));
    shuriken->agregar(estrella);
    shuriken->agregar(MAT_Rotacion(90,{0.0,1.0,0.0}));
    shuriken->agregar(estrella);


    agregar(new Cabeza);
    agregar(new Cuello);
    agregar(new Cuerpo);
    agregar(piernas);
    agregar(brazo_izq);
    agregar(brazo_dcho);
    agregar(taladro);
    agregar(shuriken);
}

unsigned Robot::leerNumParametros() const{
    return NUM_PARAMS;
}

void Robot::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
    case 0:
        taladradora->actualizarEstadoParametro(iParam,tSec);
        break;
    case 1:
        taladradora->actualizarEstadoParametro(iParam,tSec);
        break;
    case 2:
        estrella->actualizarEstadoParametro(0,tSec/10.0f);
        break;
    default:
        break;
    }
}

Cabeza::Cabeza(){
    Esfera *cabeza = new Esfera(50,50);
    cabeza->ponerColor({0.0,0.0,1.0});

    Esfera *ojo = new Esfera(50,50);
    ojo->ponerColor({1.0,1.0,1.0});
    
    NodoGrafoEscena *ojo_dcho = new NodoGrafoEscena;
    ojo_dcho->agregar(MAT_Traslacion({1.5,2.0,3.5}));
    ojo_dcho->agregar(ojo);

    NodoGrafoEscena *ojo_izq = new NodoGrafoEscena;
    ojo_izq->agregar(MAT_Traslacion({-1.5,2.0,3.5}));
    ojo_izq->agregar(ojo);

    agregar(MAT_Traslacion({0.0,3.0,0.0}));
    agregar(cabeza);
    agregar(MAT_Escalado(0.2,0.2,0.2));
    agregar(ojo_dcho);
    agregar(ojo_izq);
    
}

Cuello::Cuello(){
    Cilindro *cilindro = new Cilindro(50,50);
    cilindro->ponerColor({0.0,1.0,0.0});
    agregar(MAT_Traslacion({0.0,1.5,0.0}));
    agregar(MAT_Escalado(0.25,0.70,0.25));
    agregar(cilindro);
}

Cuerpo::Cuerpo(){
    Cubo *cubo = new Cubo();
    cubo->ponerColor({1.0,0.0,0.0});
    agregar(MAT_Escalado(0.75,1.5,0.75));
    agregar(cubo);
}

Pierna::Pierna(){
    Cubo *cubo = new Cubo();
    cubo->ponerColor({0.25,0.5,0.75});
    agregar(MAT_Traslacion({0.0,-2.0,0.0}));
    agregar(MAT_Escalado(0.25,0.5,0.25));
    agregar(cubo);
}

Brazo::Brazo(){
    Cubo *cubo = new Cubo();
    cubo->ponerColor({0.75,0.5,0.25});

    NodoGrafoEscena *antebrazo = new NodoGrafoEscena;
    antebrazo->agregar(MAT_Traslacion({0.0,-0.25,0.5}));
    antebrazo->agregar(MAT_Rotacion(90.0,{1.0,0.0,0.0}));
    antebrazo->agregar(MAT_Escalado(0.25,0.75,0.25));
    antebrazo->agregar(cubo);

    agregar(antebrazo);
    agregar(MAT_Traslacion({0.0,0.5,0.0}));
    agregar(MAT_Escalado(0.25,0.5,0.25));
    agregar(cubo);
}

Taladro::Taladro(){
    PiramideEstrellaZ *taladro = new PiramideEstrellaZ(num_puntas);
    unsigned indice_rot = agregar(MAT_Rotacion(0,{1.0,0.0,0.0}));
    unsigned indice_tras = agregar(MAT_Traslacion({0.0,0.0,0.0}));
    agregar(MAT_Traslacion({-0.5,-0.5,0.0}));
    agregar(taladro);
    pm_rot = leerPtrMatriz(indice_rot);
    pm_tras = leerPtrMatriz(indice_tras);
}

unsigned Taladro::leerNumParametros() const{
    return NUM_PARAMS;
}

void Taladro::actualizarEstadoParametro(const unsigned iParam, const float tSec){
    switch (iParam)
    {
    case 0:
        *pm_rot = MAT_Rotacion(angulo*tSec, {0.0,0.0,1.0});
        break;
    case 1:
        *pm_tras = MAT_Traslacion({0.0,0.0,angulo * (sin(tSec) + 1)/100.0f});
        break;
    default:
        break;
    }
    
}