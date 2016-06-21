#include "Animacion.h"
#include <sstream>
#include <iostream>
#include "CacheImagenes.h"
void Animacion::avanzar(float segundos){
		
	segundos_desde_cambio+=segundos;
	if(segundos_desde_cambio>segundos_por_cuadro){
		segundos_desde_cambio-=segundos_por_cuadro;
		
		if( (cuadro_actual + 1) < cantidad_cuadros)
			cuadro_actual++;
		else if(loop)
			cuadro_actual = 0;
	}
	
}
ArchivoImagen Animacion::a_dibujar(){
	if(cargadas.count(cuadro_actual)==0 || cargadas[cuadro_actual]==NULL){
		std::ostringstream nombre_con_nro;
		nombre_con_nro << nombre << cuadro_actual + 1 << ".png";
		ArchivoImagen* nuevo = new ArchivoImagen(nombre_con_nro.str());
		if(CacheImagenes::existe(*nuevo)){
			cargadas[cuadro_actual] = nuevo;
		}else{
			cantidad_cuadros = cuadro_actual;
			cuadro_actual = 0;
		}
	}
	if(cargadas[cuadro_actual]!=NULL){
		return *cargadas[cuadro_actual];
	}else{
		return ArchivoImagen("imagenes/principal.png");
	}
}

bool Animacion::operator==(const Animacion& animacion)
{
	return this->nombre == animacion.nombre;
}

Animacion::Animacion(const std::string& nom, float s, bool loop, unsigned int cantidadCuadros):
						segundos_por_cuadro(s),
						segundos_desde_cambio(0),
						cuadro_actual(0),
						nombre(nom),
						cantidad_cuadros(cantidadCuadros),
						loop(loop){}

void Animacion::reiniciar(){
	cuadro_actual = 0;
}

Animacion::~Animacion(){
	std::map<int, ArchivoImagen* >::iterator it;
	for(it = cargadas.begin(); it != cargadas.end(); ++it){
		delete it->second;
	}
}
