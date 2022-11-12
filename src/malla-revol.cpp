// *********************************************************************
// **
// ** Informática Gráfica, curso 2019-20
// ** Implementación de la clase 'MallaRevol'
// **
// *********************************************************************

#include "ig-aux.h"
#include "lector-ply.h"
#include "malla-revol.h"

using namespace std ;

// *****************************************************************************




// Método que crea las tablas de vértices, triángulos, normales y cc.de.tt.
// a partir de un perfil y el número de copias que queremos de dicho perfil.
void MallaRevol::inicializar
(
   const std::vector<Tupla3f> & perfil,     // tabla de vértices del perfil original
   const unsigned               num_copias  // número de copias del perfil
)
{
   // COMPLETAR: Práctica 2: completar: creación de la malla....
   vertices.clear();
   for(uint i = 0; i < num_copias; i++){
      for (uint j = 0; j < perfil.size(); j++){
         Tupla3f aux = MAT_Rotacion(360.0f*i/(num_copias-1)*1.0,{0,1,0})*perfil.at(j);
         //Tupla3f aux = {float(cos(2*M_PI*i/(num_copias-1)*perfil.at(j)(0))+sin(2*M_PI*i/(num_copias-1))*perfil.at(j)(2)),float(perfil.at(j)(1)),float(-sin(2*M_PI*i/(num_copias-1))*perfil.at(j)(0) + cos(2*M_PI*i/(num_copias-1)*perfil.at(j)(2)))};
         vertices.push_back(aux);
      }
   }
   CError();

   for(uint i = 0; i < num_copias - 1; i++){
      for (uint j = 0; j < perfil.size() - 1; j++){
         uint k = i*perfil.size() + j;
         triangulos.push_back({k, k + (uint)perfil.size(),k + (uint)perfil.size() + 1});
         triangulos.push_back({k, k + (uint)perfil.size() + 1, k + 1});
      }
   }
   CError();
}

// -----------------------------------------------------------------------------
// constructor, a partir de un archivo PLY

MallaRevolPLY::MallaRevolPLY
(
   const std::string & nombre_arch,
   const unsigned      nperfiles
)
{
   ponerNombre( std::string("malla por revolución del perfil en '"+ nombre_arch + "'" ));
   // COMPLETAR: práctica 2: crear la malla de revolución
   // Leer los vértice del perfil desde un PLY, después llamar a 'inicializar'
   // ...........................
   std::vector<Tupla3f> perfil;
   LeerVerticesPLY(nombre_arch, perfil);
   inicializar(perfil, nperfiles);
   CError();
}

Cilindro::Cilindro
(
   const int num_verts_per, // número de vértices del perfil original (m)
   const unsigned nperfiles // número de perfiles (n)
)
{   
   ponerNombre(std::string("Cilindro"));
   std::vector<Tupla3f> perfil;

   for(int i = 0; i < num_verts_per; i++){
      perfil.push_back({1,float(i*1.0/(num_verts_per - 1)*1.0),0});
   }
   CError();
   inicializar(perfil, nperfiles);
}

Cono::Cono
(
   const int num_verts_per, // número de vértices del perfil original (m)
   const unsigned nperfiles // número de perfiles (n)
)
{
   ponerNombre(std::string("Cono"));
   std::vector<Tupla3f> perfil;

   for(int i = 0; i < num_verts_per; i++){
      Tupla3f aux = {float(1.0-i*1.0/(num_verts_per - 1)*1.0),float(i*1.0/(num_verts_per)*1.0),0};
      perfil.push_back(aux);
   }
   
   CError();
   inicializar(perfil, nperfiles);
}

Esfera::Esfera
(
   const int num_verts_per, // número de vértices del perfil original (M )
   const unsigned nperfiles // número de perfiles (N )
)
{
   ponerNombre(std::string("Esfera"));
   std::vector<Tupla3f> perfil;

   /** Esta forma genera una esfera, pero es menos smooth por el ecuador
   for(int i = num_verts_per/2 - 1; i >= 0; i--){
      perfil.push_back({float(1.0*i/(num_verts_per/2 - 1)*1.0),float(-1.0*sqrt(1-1.0*i/(num_verts_per/2 - 1)*1.0*i/(num_verts_per/2 - 1)*1.0)),0});
   }

   for(int i = 0; i < num_verts_per/2; i++){
      perfil.push_back({float(1.0*i/(num_verts_per/2 - 1)*1.0),float(sqrt(1-1.0*i/(num_verts_per/2 - 1)*1.0*i/(num_verts_per/2 - 1)*1.0)),0});
   }
   **/

   // Otra forma: Esta forma es mejor por el ecuador de la esfera
   for(int i = 0; i < num_verts_per; i++){
      float alpha = M_PI*(i/((float) num_verts_per - 1) - 0.5);
      perfil.push_back({cos(alpha), sin(alpha),0});
   }
   

   CError();
   inicializar(perfil, nperfiles);
}