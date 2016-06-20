#include "Animacion.h"
#include <sstream>
#include <iostream>
#include "CacheImagenes.h"
void Animacion::avanzar(float segundos){
	//std::cout<<"Hola soy Animacion: "<<segundos<<" "<<segundos_desde_cambio<<" "<<segundos_por_cuadro<<std::endl;
		
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
		/*
		try{
			cargadas[cuadro_actual]= Gdk::Pixbuf::create_from_file(nombre_con_nro.str());
		}catch(const Glib::Error& ex){
			cantidad_cuadros = cuadro_actual;
			cuadro_actual = 0;
		}
		*/
		//por que? porque la animacion forma parte del Mundo, 
		//del lado del server, lo de arriba causa un error de runtime.
		//Entonces, me aseguro que sólo se cargue la imagen si será dibujada 
		//(==si estoy del lado del cliente) de esta manera.
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
