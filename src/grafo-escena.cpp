// *********************************************************************
// **
// ** Gestión de una grafo de escena (implementación)
// ** Copyright (C) 2016 Carlos Ureña
// **
// ** This program is free software: you can redistribute it and/or modify
// ** it under the terms of the GNU General Public License as published by
// ** the Free Software Foundation, either version 3 of the License, or
// ** (at your option) any later version.
// **
// ** This program is distributed in the hope that it will be useful,
// ** but WITHOUT ANY WARRANTY; without even the implied warranty of
// ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// ** GNU General Public License for more details.
// **
// ** You should have received a copy of the GNU General Public License
// ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
// **
// *********************************************************************

#include "ig-aux.h"
#include "grafo-escena.h"

using namespace std ;

// *********************************************************************
// Entrada del nodo del Grafo de Escena

// ---------------------------------------------------------------------
// Constructor para entrada de tipo sub-objeto

EntradaNGE::EntradaNGE( Objeto3D * pObjeto )
{
   assert( pObjeto != NULL );
   tipo   = TipoEntNGE::objeto ;
   objeto = pObjeto ;
}
// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( const Matriz4f & pMatriz )
{
   tipo    = TipoEntNGE::transformacion ;
   matriz  = new Matriz4f() ; // matriz en el heap, puntero propietario
   *matriz = pMatriz ;
}

// ---------------------------------------------------------------------
// Constructor para entrada de tipo "matriz de transformación"

EntradaNGE::EntradaNGE( Material * pMaterial )
{
   assert( pMaterial != NULL );
   tipo     = TipoEntNGE::material ;
   material = pMaterial ;
}

// -----------------------------------------------------------------------------
// Destructor de una entrada

EntradaNGE::~EntradaNGE()
{
   /**  no funciona debido a que se hacen copias (duplicados) de punteros
   if ( tipo == TipoEntNGE::transformacion )
   {
      assert( matriz != NULL );
      delete matriz ;
      matriz = NULL ;
   }
   * **/
}

// *****************************************************************************
// Nodo del grafo de escena: contiene una lista de entradas
// *****************************************************************************

// -----------------------------------------------------------------------------
// Visualiza usando OpenGL

void NodoGrafoEscena::visualizarGL( ContextoVis & cv )
{
   // COMPLETAR: práctica 3: recorrer las entradas y visualizar cada nodo.
   
   // Guarda modelview actual
   cv.cauce->pushMM();

   tup_mat::Tupla4f color;

   // Recorrer todas visualizarGeomGL las entradas del array que hay en el nodo:
   for(unsigned i = 0; i < entradas.size(); i++)
      switch (entradas[i].tipo)
      {
      case TipoEntNGE::objeto:
         //color = entradas[i].objeto->leerFijarColVertsCauce(cv);
         entradas[i].objeto->visualizarGL(cv);
         //cv.cauce->fijarColor(color);
         break;
      
      case TipoEntNGE::transformacion:
         cv.cauce->compMM(*(entradas[i].matriz));
         break;

      case TipoEntNGE::material:
         CError();
         break;

      case TipoEntNGE::noInicializado:
         CError();
         break;
      }
      
   cv.cauce->popMM();

   // COMPLETAR: práctica 4: en la práctica 4, si 'cv.iluminacion' es 'true',
   // se deben de gestionar los materiales:
   //   1. guardar puntero al material activo al inicio (está en cv.material_act)
   //   2. si una entrada des de tipo material, activarlo y actualizar 'cv.material_act'
   //   3. al finalizar, restaurar el material activo al inicio (si es distinto del actual)



}




// *****************************************************************************
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...

void NodoGrafoEscena::visualizarGeomGL( ContextoVis & cv )
{
   // comprobar que hay un cauce en 'cv' 
   assert( cv.cauce != nullptr );
  

   // COMPLETAR: práctica 3
   //
   // Este método hace un recorrido de las entradas del nodo, parecido a 'visualizarGL', teniendo 
   // en cuenta estos puntos:
   //
   // - usar push/pop de la matriz de modelado al inicio/fin (al igual que en visualizatGL)
   // - recorrer las entradas, llamando recursivamente a 'visualizarGeomGL' en los nodos u objetos hijos
   // - ignorar el color o identificador del nodo (se supone que el color ya está prefijado antes de la llamada)
   // - ignorar las entradas de tipo material, y la gestión de materiales (se usa sin iluminación)

   cv.cauce->pushMM();

   // Recorrer todas las entradas del array que hay en el nodo:
   for(unsigned i = 0; i < entradas.size(); i++)
      switch (entradas[i].tipo)
      {
      case TipoEntNGE::objeto:
         entradas[i].objeto->visualizarGeomGL(cv);
         break;
      
      case TipoEntNGE::transformacion:
         cv.cauce->compMM(*(entradas[i].matriz));
         break;

      case TipoEntNGE::material:
         CError();
         break;

      case TipoEntNGE::noInicializado:
         CError();
         break;
      }
   cv.cauce->popMM();
}



// -----------------------------------------------------------------------------

NodoGrafoEscena::NodoGrafoEscena()
{

}

// -----------------------------------------------------------------------------
// Añadir una entrada (al final).
// genérica (de cualquier tipo de entrada)

unsigned NodoGrafoEscena::agregar( const EntradaNGE & entrada )
{
   // COMPLETAR: práctica 3: agregar la entrada al nodo, devolver índice de la entrada agregada
   entradas.push_back(entrada);
   return entradas.size() - 1; // sustituir por lo que corresponda ....

}
// -----------------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// objeto (copia solo puntero)

unsigned NodoGrafoEscena::agregar( Objeto3D * pObjeto )
{
   return agregar( EntradaNGE( pObjeto ) );
}
// ---------------------------------------------------------------------
// construir una entrada y añadirla (al final)
// matriz (copia objeto)

unsigned NodoGrafoEscena::agregar( const Matriz4f & pMatriz )
{
   return agregar( EntradaNGE( pMatriz ) );
}
// ---------------------------------------------------------------------
// material (copia solo puntero)
unsigned NodoGrafoEscena::agregar( Material * pMaterial )
{
   return agregar( EntradaNGE( pMaterial ) );
}

// devuelve el puntero a la matriz en la i-ésima entrada
Matriz4f * NodoGrafoEscena::leerPtrMatriz( unsigned indice )
{
   // COMPLETAR: práctica 3: devolver puntero la matriz en ese índice
   //   (debe de dar error y abortar si no hay una matriz en esa entrada)
   // ........(sustituir 'return nullptr' por lo que corresponda)
   assert(indice < entradas.size());
   assert(entradas[indice].tipo == TipoEntNGE::transformacion);
   assert(entradas[indice].matriz != nullptr);
   return entradas[indice].matriz;
}
// -----------------------------------------------------------------------------
// si 'centro_calculado' es 'false', recalcula el centro usando los centros
// de los hijos (el punto medio de la caja englobante de los centros de hijos)

void NodoGrafoEscena::calcularCentroOC()
{

   // COMPLETAR: práctica 5: calcular y guardar el centro del nodo
   //    en coordenadas de objeto (hay que hacerlo recursivamente)
   //   (si el centro ya ha sido calculado, no volver a hacerlo)
   // ........

}
// -----------------------------------------------------------------------------
// método para buscar un objeto con un identificador y devolver un puntero al mismo

bool NodoGrafoEscena::buscarObjeto
(
   const int         ident_busc, // identificador a buscar
   const Matriz4f &  mmodelado,  // matriz de modelado
   Objeto3D       ** objeto,     // (salida) puntero al puntero al objeto
   Tupla3f &         centro_wc   // (salida) centro del objeto en coordenadas del mundo
)
{
   assert( 0 < ident_busc );

   // COMPLETAR: práctica 5: buscar un sub-objeto con un identificador
   // Se deben de dar estos pasos:

   // 1. calcula el centro del objeto, (solo la primera vez)
   // ........


   // 2. si el identificador del nodo es el que se busca, ya está (terminar)
   // ........


   // 3. El nodo no es el buscado: buscar recursivamente en los hijos
   //    (si alguna llamada para un sub-árbol lo encuentra, terminar y devolver 'true')
   // ........


   // ni este nodo ni ningún hijo es el buscado: terminar
   return false ;
}

GrafoEstrellaX::GrafoEstrellaX(unsigned n){
   NodoGrafoEscena * estrella = new NodoGrafoEscena();
   unsigned indice = agregar(MAT_Rotacion(0,{1.0,0.0,0.0}));
   agregar(estrella);
   estrella->agregar(MAT_Escalado(1.0,2.6,2.6));
   estrella->agregar(MAT_Traslacion({0.0,-0.5,-0.5}));
   estrella->agregar(new EstrellaX(n));
   
   NodoGrafoEscena * cono_reescalado = new NodoGrafoEscena;
   Cono * cono = new Cono(10,50);
   cono_reescalado->agregar(MAT_Traslacion({0.0,1.3,0.0}));
   cono_reescalado->agregar(MAT_Escalado(0.14,0.15,0.14));
   cono_reescalado->agregar(cono);
   
   for(unsigned i = 0; i < n; i++){
      agregar(MAT_Rotacion(360/(n*1.0),{1.0,0.0,0.0}));
      agregar(cono_reescalado);
   }
   
   pm_rot = leerPtrMatriz(indice);
}

unsigned GrafoEstrellaX::leerNumParametros() const{
   return NUM_PARAMS;
}

void GrafoEstrellaX::actualizarEstadoParametro(const unsigned iParam, const float tSec){
   switch (iParam)
   {
   case 0:
      fijarAlpha(angulo*tSec);
      break;
   
   default:
      break;
   }
   
}

void GrafoEstrellaX::fijarAlpha(float alpha_nuevo){
   *pm_rot = MAT_Rotacion(alpha_nuevo, {1.0,0.0,0.0});
}

GrafoCubos::GrafoCubos(){
   NodoGrafoEscena * rejilla_mod = new NodoGrafoEscena();
   RejillaY * rejilla = new RejillaY(dim,dim);
   rejilla_mod->agregar(MAT_Traslacion({-0.5,-0.5,-0.5}));
   rejilla_mod->agregar(rejilla);

   NodoGrafoEscena * cubo_mod = new NodoGrafoEscena();
   Cubo * cubo = new Cubo();
   unsigned indice = cubo_mod->agregar(MAT_Rotacion(0,{0.0,1.0,0.0}));
   cubo_mod->agregar(MAT_Traslacion({0.0,-0.75,0.0}));
   cubo_mod->agregar(MAT_Escalado(0.15,0.25,0.15));
   cubo_mod->agregar(cubo);

   for(int i = 0; i < 4; i++){
      agregar(MAT_Rotacion(90,{1.0,0.0,0.0}));
      agregar(rejilla_mod);
      agregar(cubo_mod);
   }

   agregar(MAT_Rotacion(90,{0.0,0.0,1.0}));
   agregar(rejilla_mod);
   agregar(cubo_mod);
   agregar(MAT_Rotacion(180,{0.0,0.0,1.0}));
   agregar(rejilla_mod);
   agregar(cubo_mod);

   pm_rot = cubo_mod->leerPtrMatriz(indice);
}

unsigned GrafoCubos::leerNumParametros() const{
   return NUM_PARAMS;
}

void GrafoCubos::actualizarEstadoParametro(const unsigned iParam, const float tSec){
   switch (iParam)
   {
   case 0:
      fijarAlpha(angulo*tSec);
      break;
   
   default:
      break;
   }
}

void GrafoCubos::fijarAlpha(float alpha_nuevo){
   *pm_rot = MAT_Rotacion(alpha_nuevo, {0.0,1.0,0.0});
}
