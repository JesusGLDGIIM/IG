// *********************************************************************
// **
// ** Informática Gráfica, curso 2020-21
// ** Declaraciones de la clase Objeto3D.hpp
// **
// *********************************************************************

#include "ig-aux.h"
#include "malla-ind.h"   // declaración de 'ContextoVis'
#include "lector-ply.h"

// *****************************************************************************
// funciones auxiliares

// *****************************************************************************
// métodos de la clase MallaInd.

MallaInd::MallaInd()
{
   // nombre por defecto
   ponerNombre("malla indexada, anónima");
}
// -----------------------------------------------------------------------------

MallaInd::MallaInd( const std::string & nombreIni )
{
   // 'identificador' puesto a 0 por defecto, 'centro_oc' puesto a (0,0,0)
   ponerNombre(nombreIni) ;
}

//-----------------------------------------------------------------------------
// calcula la tabla de normales de triángulos una sola vez, si no estaba calculada

void MallaInd::calcularNormalesTriangulos()
{

   // si ya está creada la tabla de normales de triángulos, no es necesario volver a crearla
   const unsigned nt = triangulos.size() ;
   assert( 1 <= nt );
   if ( 0 < nor_tri.size() )
   {
      assert( nt == nor_tri.size() );
      return ;
   }

   // COMPLETAR: Práctica 4: creación de la tabla de normales de triángulos
   // ....

}


// -----------------------------------------------------------------------------
// calcula las dos tablas de normales

void MallaInd::calcularNormales()
{
   // COMPLETAR: en la práctica 4: calculo de las normales de la malla
   // se debe invocar en primer lugar 'calcularNormalesTriangulos'
   // .......


}



// --------------------------------------------------------------------------------------------

void MallaInd::visualizarGL( ContextoVis & cv )
{
   using namespace std ;
   assert( cv.cauce != nullptr );
   CError();

   if ( triangulos.size() == 0 || vertices.size() == 0 )
   {  cout << "advertencia: intentando dibujar malla vacía '" << leerNombre() << "'" << endl << flush ;
      return ;
   }

   // guardar el color previamente fijado y fijar el color del objeto actual
   const Tupla4f color_previo = leerFijarColVertsCauce( cv );

   // COMPLETAR: práctica 1: si el nombre del VAO es 0, crear el VAO con sus VBOs:
   //   * en primer lugar se crea y activa el VAO , con 'CrearVAO'.
   //   * después se añade el VBO con la tabla de coordenadas de posición, 'CrearVBOAtrib'.
   //   * se añade el VBO con la tabla de índices (la tabla de triángulos), con 'CrearVBOInd'.
   //   * finalmente se añaden al VAO los VBOs con tablas de atributos (opcionales) que haya, con 'CrearVBOAtrib'.
   // si el VAO ya está creado, (nombre_vao > 0), activarlo, con 'glBindVertexArray'
   //
   //  hay que tener en cuenta que el nombre del VAO y los nombres de losVBOs deben quedar en las correspondientes 
   //  variables de instancia. Estos nombres son los devueltos por las 
   //  funciones 'CrearVAO', 'CrearVBOAtrib' y 'CrearVBOInd'.
   //
   if(nombre_vao == 0){
      nombre_vao = CrearVAO();
      CError();
      nombre_vbo_pos = CrearVBOAtrib(ind_atrib_posiciones, vertices);
      CError();
      nombre_vbo_tri = CrearVBOInd(triangulos);
      CError();

      //VBO opcionales
      if(col_ver.size() > 0){
         nombre_vbo_col = CrearVBOAtrib(ind_atrib_colores, col_ver);
      }
      if(nor_ver.size() > 0){
         nombre_vbo_nor = CrearVBOAtrib(ind_atrib_normales, nor_ver);
      }
      if(nor_tri.size() > 0){
         nombre_vbo_nor = CrearVBOAtrib(ind_atrib_normales, nor_tri);
      }
      if(cc_tt_ver.size() > 0){
         nombre_vbo_cct = CrearVBOAtrib(ind_atrib_coord_text, cc_tt_ver);
      }
   }
   else{
      glBindVertexArray(nombre_vao);
   }

   CError();

   // COMPLETAR: práctica 1: visualizar con 'glDrawElements' y desactivar VAO.

   glDrawElements(GL_TRIANGLES, triangulos.size() * 3, GL_UNSIGNED_INT, 0);
   CError();
   glBindVertexArray(0);

   // restaurar el color previamente fijado
   cv.cauce->fijarColor( color_previo );
   CError();
}


// -----------------------------------------------------------------------------
// visualizar pura y simplemente la geometría, sin colores, normales, coord. text. etc...
// (se supone que el estado de OpenGL está fijado antes de esta llamada de alguna forma adecuada)

void MallaInd::visualizarGeomGL( ContextoVis & cv )
{
   // COMPLETAR: práctica 1: asegurarnos de que el VAO de geometría está creado y activado
   // ....
   if(nombre_vao_geom == 0){
      nombre_vao_geom = CrearVAO();
      glBindBuffer(GL_ARRAY_BUFFER, nombre_vbo_pos);
      glVertexAttribPointer(ind_atrib_posiciones, 3 , GL_FLOAT, GL_FALSE, 0, 0);
      glEnableVertexAttribArray(ind_atrib_posiciones);
      glBindBuffer(GL_ARRAY_BUFFER, 0);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, nombre_vbo_tri);
      CError();
   }
   else
      glBindVertexArray(nombre_vao_geom);

   glDrawElements(GL_TRIANGLES, triangulos.size() * 3, GL_UNSIGNED_INT, 0);

   glBindVertexArray(0);

   CError();
}


// ****************************************************************************
// Clase 'MallaPLY'

MallaPLY::MallaPLY( const std::string & nombre_arch )
{
   ponerNombre( std::string("malla leída del archivo '") + nombre_arch + "'" );

   // COMPLETAR: práctica 2: leer archivo PLY e inicializar la malla
   // ..........................
   LeerPLY(nombre_arch, vertices, triangulos);

   // COMPLETAR: práctica 4: invocar  a 'calcularNormales' para el cálculo de normales
   // .................

}

// ****************************************************************************
// Clase 'Cubo'

Cubo::Cubo()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

// ****************************************************************************
// Clase 'CuboTejado'

CuboTejado::CuboTejado()
:  MallaInd( "cubo 8 vértices" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
         { +0.0, +2.0, +0.0 }, // 8
      } ;

   for( Tupla3f & v : vertices )
      v = 2.0f*v +Tupla3f({0.0,2.0,0.0});


   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         //{2,3,7}, {2,7,6}, // Y+ (+2)   // quito cara superior
         {2,3,8}, {3,7,8}, {7,6,8}, {6,2,8}, // añado tejado 

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

}

// ****************************************************************************
// Clase 'Tetraedro'

Tetraedro::Tetraedro()
:  MallaInd( "Tetraedro con color" )
{

   vertices =
      {  { 1.0, 0.0, 0.0 }, // 0
         { 0.0, 1.0, 0.0 }, // 1
         { 0., 0.0, 1.0 }, // 2
         { 0.0, 0.0, 0.0 }, // 3
      } ;



   triangulos =
      {  {0,1,2}, {1,2,3},
         {2,3,0}, {0,1,3}
      } ;

   Tupla3f color = {0.25, 0.75, 0.0};
   ponerColor(color);
}

// ****************************************************************************
// Clase 'CuboColores'
CuboColores::CuboColores()
:  MallaInd( "cubo 8 vértices con colores" )
{

   vertices =
      {  { -1.0, -1.0, -1.0 }, // 0
         { -1.0, -1.0, +1.0 }, // 1
         { -1.0, +1.0, -1.0 }, // 2
         { -1.0, +1.0, +1.0 }, // 3
         { +1.0, -1.0, -1.0 }, // 4
         { +1.0, -1.0, +1.0 }, // 5
         { +1.0, +1.0, -1.0 }, // 6
         { +1.0, +1.0, +1.0 }, // 7
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,5,1}, {0,4,5}, // Y-
         {2,3,7}, {2,7,6}, // Y+ (+2)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3}  // Z+ (+1)
      } ;

   col_ver =
      {  { 0, 0, 0 }, // 0
         { 0, 0, 1 }, // 1
         { 0, 1, 0 }, // 2
         { 0, 1, 1 }, // 3
         { 1, 0, 0 }, // 4
         { 1, 0, 1 }, // 5
         { 1, 1, 0 }, // 6
         { 1, 1, 1 }, // 7
      } ;
}

// ****************************************************************************
// Clase 'EstrellaZ'

EstrellaZ::EstrellaZ(unsigned n) : MallaInd("Estrela de n puntas"){
   assert(n>1);
   vertices.push_back({0.5,0.5,0});
   for(unsigned int i = 0; i < 2*n; i+=2){
      vertices.push_back({float(cos(i*M_PI/n)/2 + 0.5), float(sin(i*M_PI/n)/2 + 0.5), 0});
      vertices.push_back({float(cos((i+1)*M_PI/n)/4+0.5), float(sin((i+1)*M_PI/n)/4 + 0.5), 0});
   }

   for(unsigned int i = 1; i < 2*n ; i++){
      triangulos.push_back({0, i, i+1});
   }

   triangulos.push_back({0,2*n,1});

   col_ver.push_back({1.0, 1.0, 1.0});
   for(unsigned int i = 0; i < 2*n; i+=2){
      col_ver.push_back({float(cos(i*M_PI/n)/2 + 0.5), float(sin(i*M_PI/n)/2 + 0.5), 0});
      col_ver.push_back({float(cos((i+1)*M_PI/n)/4+0.5), float(sin((i+1)*M_PI/n)/4 + 0.5), 0});
   }
}

// ****************************************************************************
// Clase 'EstrellaY'

EstrellaY::EstrellaY(unsigned n) : MallaInd("Estrela de n puntas"){
   assert(n>1);
   vertices.push_back({0.5,0,0.5});
   for(unsigned int i = 0; i < 2*n; i+=2){
      vertices.push_back({float(cos(i*M_PI/n)/2 + 0.5), 0, float(sin(i*M_PI/n)/2 + 0.5)});
      vertices.push_back({float(cos((i+1)*M_PI/n)/4+0.5), 0, float(sin((i+1)*M_PI/n)/4 + 0.5)});
   }

   for(unsigned int i = 1; i < 2*n ; i++){
      triangulos.push_back({0, i, i+1});
   }

   triangulos.push_back({0,2*n,1});

   col_ver.push_back({1.0, 1.0, 1.0});
   for(unsigned int i = 0; i < 2*n; i+=2){
      col_ver.push_back({float(cos(i*M_PI/n)/2 + 0.5), 0, float(sin(i*M_PI/n)/2 + 0.5)});
      col_ver.push_back({float(cos((i+1)*M_PI/n)/4+0.5), 0, float(sin((i+1)*M_PI/n)/4 + 0.5)});
   }
}

// ****************************************************************************
// Clase 'EstrellaX'

EstrellaX::EstrellaX(unsigned n) : MallaInd("Estrela de n puntas"){
   assert(n>1);
   vertices.push_back({0,0.5,0.5});
   for(unsigned int i = 0; i < 2*n; i+=2){
      vertices.push_back({0, float(cos(i*M_PI/n)/2 + 0.5), float(sin(i*M_PI/n)/2 + 0.5)});
      vertices.push_back({0, float(cos((i+1)*M_PI/n)/6+0.5), float(sin((i+1)*M_PI/n)/6 + 0.5)});
   }

   for(unsigned int i = 1; i < 2*n ; i++){
      triangulos.push_back({0, i, i+1});
   }

   triangulos.push_back({0,2*n,1});

   col_ver.push_back({1.0, 1.0, 1.0});
   for(unsigned int i = 0; i < 2*n; i+=2){
      col_ver.push_back({0, float(cos(i*M_PI/n)/2 + 0.5), float(sin(i*M_PI/n)/2 + 0.5)});
      col_ver.push_back({0, float(cos((i+1)*M_PI/n)/6+0.5), float(sin((i+1)*M_PI/n)/6 + 0.5)});
   }
}

// ****************************************************************************
// Clase 'CasaX'

CasaX::CasaX() : MallaInd("Casa en el eje X"){
   vertices =
      {  { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, 0.5 }, // 1
         { 0.0, 0.5, 0.0 }, // 2
         { 0.0, 0.5, 0.5 }, // 3
         { 1.0, 0.0, 0.0 }, // 4
         { 1.0, 0.0, 0.5 }, // 5
         { 1.0, 0.5, 0.0 }, // 6
         { 1.0, 0.5, 0.5 }, // 7
         { 0.0, 1.0, 0.25}, // 8
         { 1.0, 1.0, 0.25}  // 9
      } ;



   triangulos =
      {  {0,1,3}, {0,3,2}, // X-
         {4,7,5}, {4,6,7}, // X+ (+4)

         {0,6,4}, {0,2,6}, // Z-
         {1,5,7}, {1,7,3},  // Z+ (+1)

         {2, 8, 3}, {6, 9, 7}, // Caras tejado
         {2, 8, 6}, {6, 9, 8}, //Lado 0
         {3, 8, 7}, {7, 9, 8}  //Lado 1
      } ;

   col_ver =
      {  { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 0.0, 0.5 }, // 1
         { 0.0, 0.5, 0.0 }, // 2
         { 0.0, 0.5, 0.5 }, // 3
         { 1.0, 0.0, 0.0 }, // 4
         { 1.0, 0.0, 0.5 }, // 5
         { 1.0, 0.5, 0.0 }, // 6
         { 1.0, 0.5, 0.5 }, // 7
         { 0.0, 1.0, 0.25}, // 8
         { 1.0, 1.0, 0.25}  // 9
      } ;
}

// ****************************************************************************
// Clase 'MallaTriangulo'
MallaTriangulo::MallaTriangulo() :MallaInd("Es solo un triangulo"){
   vertices =
   {  { 0.5, 0.0, 0.0 },
      { 0.0, sqrt(2), 0.0 },
      { -0.5, 0.0, 0.0 }
   };

   triangulos =
   {  {0, 1, 2}
   };
}


// ****************************************************************************
// Clase 'MallaTriangulo'
MallaCuadrado::MallaCuadrado() :MallaInd("Es solo un cuadrado"){
      vertices =
      {  { 0.0, 0.0, 0.0 }, // 0
         { 0.0, 2.0, 0.0 }, // 1
         { 2.0, 0.0, 0.0 }, // 2
         { 2.0, 2.0, 0.0 }, // 3
      };

      triangulos =
   {  {0, 1, 2},
      {1, 2, 3}
   };

}


// ****************************************************************************
// Clase 'MallaTriangulo'
MallaPiramideL::MallaPiramideL() :MallaInd("Es solo una piramide"){
   vertices =
   {  { 0.0, 0.0, 0.0 },   // 0
      { 0.0, 0.0, 1.0 },   // 1
      { 0.5, 0.0, 1.0 },   // 2
      { 0.5, 0.0, 0.5 },   // 3
      { 1.5, 0.0, 0.5 },   // 4
      { 1.5, 0.0, 0.0 },   // 5
      { 0.5, 1.0, 0.5 }    // 6
   };

   triangulos =
   {
      {0, 1, 2},
      {0, 2, 3},
      {0, 3, 4},
      {0, 4, 5},
      {0, 1, 2},
      {0, 1, 6},
      {0, 1, 6},
      {1, 2, 6},
      {2, 3, 6},
      {3, 4, 6},
      {4, 5, 6},
      {0, 5, 6},
   };
}

// ****************************************************************************
// Clase 'PiramideEstrellaZ'
PiramideEstrellaZ::PiramideEstrellaZ(unsigned n){
   assert(n>1);
   vertices.push_back({0.5,0.5,0});
   for(unsigned int i = 0; i < 2*n; i+=2){
      vertices.push_back({float(cos(i*M_PI/n)/2 + 0.5), float(sin(i*M_PI/n)/2 + 0.5), 0});
      vertices.push_back({float(cos((i+1)*M_PI/n)/4+0.5), float(sin((i+1)*M_PI/n)/4 + 0.5), 0});
   }
   
   vertices.push_back({0.5,0.5,0.5});

   for(unsigned int i = 1; i < 2*n ; i++){
      triangulos.push_back({0, i, i+1});
   }

   triangulos.push_back({0,2*n,1});

   for(unsigned int i = 1; i < 2*n ; i++){
      triangulos.push_back({2*n+1, i, i+1});
   }

   triangulos.push_back({2*n+1,2*n,1});

   col_ver.push_back({1.0, 1.0, 1.0});
   for(unsigned int i = 0; i < 2*n; i+=2){
      col_ver.push_back({float(cos(i*M_PI/n)/2 + 0.5), float(sin(i*M_PI/n)/2 + 0.5), 0});
      col_ver.push_back({float(cos((i+1)*M_PI/n)/4+0.5), float(sin((i+1)*M_PI/n)/4 + 0.5), 0});
   }
   col_ver.push_back({1.0, 1.0, 1.0});
}

// ****************************************************************************
// Clase 'RejillaY'
RejillaY::RejillaY(unsigned m, unsigned n){
   assert(n > 1);
   assert(m > 1);

   for(uint i = 0; i < m; i++){
      for(uint j = 0; j < n; j++){
         vertices.push_back({i*1.0f/(m-1),0.0f,j*1.0f/(n-1)});
      }
   }

   for(uint i = 0; i < m - 1; i++){
      for(uint j = 0; j < n - 1; j++){
         triangulos.push_back({n*i+j, n*(i+1)+j, n*i+j+1});
         triangulos.push_back({n*(i+1)+j+1, n*(i+1)+j, n*i+j+1});
      }
   }

   for(uint i = 0; i < m; i++){
      for(uint j = 0; j < n; j++){
         col_ver.push_back({i*1.0f/(m-1),0.0f,j*1.0f/(n-1)});
      }
   }
}

// ****************************************************************************
// Clase 'MallaTorre'
MallaTorre::MallaTorre(unsigned n){
   for(uint i = 0; i <= n; i++){
      vertices.push_back({0.0,i*1.0f,0.0});
      vertices.push_back({1.0,i*1.0f,0.0});
      vertices.push_back({1.0,i*1.0f,1.0});
      vertices.push_back({0.0,i*1.0f,1.0});
   }

   triangulos.push_back({0,3,4});
   for(uint i = 0; i < 4*n - 1; i++){
      triangulos.push_back({i,i+4,i+1});
      triangulos.push_back({i+1,i+5,i+4});
   }
   triangulos.push_back({4*n,4*(n-1)+3,4*n+3});

   /** Añadir color
   for(uint i = 0; i <= n; i++){
      col_ver.push_back({0.0,i*1.0f,0.0});
      col_ver.push_back({1.0,i*1.0f,0.0});
      col_ver.push_back({1.0,i*1.0f,1.0});
      col_ver.push_back({0.0,i*1.0f,1.0});
   }
   **/
}