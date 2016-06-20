#include "Definiciones.h"
#include <iostream>
#include <locale>

namespace SJuego
{
	const Preconfiguracion preconf;
	std::string Preconfiguracion::leerIP(){
		std::ifstream iss("ip.conf");
		std::string ret;
		std::getline(iss,ret);
		return ret;
	}
	uint Preconfiguracion::leerPort(){
		std::ifstream iss("port.conf");
		uint ret;
		iss>>ret;
		return ret;
	}
	
	Preconfiguracion::Preconfiguracion():
							ip(leerIP()),
							port(leerPort()){}
	
	Constantes attr;

	void Constantes::cargar(std::string nombreArchivo)
	{
		 AGREGARMAPA(distanciavision)
		 AGREGARMAPA(gravedad)
		 AGREGARMAPA(anchoescalera)
		 AGREGARMAPA(anchopuerta)
		 AGREGARMAPA(altopuerta)
		 AGREGARMAPA(energiamegaman)
		 AGREGARMAPA(masamegaman)
		 AGREGARMAPA(maximacantidadplasma)
		 AGREGARMAPA(cantidadinfinitaplasma)
		 AGREGARMAPA(maximacantidadvidas)
		 AGREGARMAPA(vidasiniciales)
		 AGREGARMAPA(danoporcontacto)
		 AGREGARMAPA(cuerpoprincipal)
		 AGREGARMAPA(megamanjumpbox)
		 AGREGARMAPA(velocidadmegamancorriendo)
		 AGREGARMAPA(velocidadmegamanescalera)
		 AGREGARMAPA(posiciondisparomegaman)
		 AGREGARMAPA(posicionlanzamientomegaman)
		 AGREGARMAPA(velocidadsaltomegaman)
		 AGREGARMAPA(tiempoinmunidadmegaman)
		 AGREGARMAPA(anchospritemegaman)
		 AGREGARMAPA(altospritemegaman)
		 AGREGARMAPA(masapowerup)
		 AGREGARMAPA(velocidadpowerup)
		 AGREGARMAPA(anchospritepowerup)
		 AGREGARMAPA(altospritepowerup)
		 AGREGARMAPA(masabumby)
		 AGREGARMAPA(anchobumby)
		 AGREGARMAPA(altobumby)
		 AGREGARMAPA(velocidadsaltobumby)
		 AGREGARMAPA(velocidadcorrerbumby)
		 AGREGARMAPA(masamet)
		 AGREGARMAPA(anchomet)
		 AGREGARMAPA(altomet)
		 AGREGARMAPA(velocidadsaltomet)
		 AGREGARMAPA(velocidadcorrermet)
		 AGREGARMAPA(masasniper)
		 AGREGARMAPA(anchosniper)
		 AGREGARMAPA(altosniper)
		 AGREGARMAPA(velocidadsaltosniper)
		 AGREGARMAPA(velocidadcorrersniper)
		 AGREGARMAPA(masajumpingsniper)
		 AGREGARMAPA(anchojumpingsniper)
		 AGREGARMAPA(altojumpingsniper)
		 AGREGARMAPA(velocidadsaltojumpingsniper)
		 AGREGARMAPA(velocidadcorrerjumpingsniper)
		 AGREGARMAPA(masabombman)
		 AGREGARMAPA(anchobombman)
		 AGREGARMAPA(altobombman)
		 AGREGARMAPA(velocidadsaltobombman)
		 AGREGARMAPA(velocidadcorrerbombman)
		 AGREGARMAPA(masasparkman)
		 AGREGARMAPA(anchosparkman)
		 AGREGARMAPA(altosparkman)
		 AGREGARMAPA(velocidadsaltosparkman)
		 AGREGARMAPA(velocidadcorrersparkman)
		 AGREGARMAPA(masamagnetman)
		 AGREGARMAPA(anchomagnetman)
		 AGREGARMAPA(altomagnetman)
		 AGREGARMAPA(velocidadsaltomagnetman)
		 AGREGARMAPA(velocidadcorrermagnetman)

		 AGREGARMAPA(masaringman)
		 AGREGARMAPA(anchoringman)
		 AGREGARMAPA(altoringman)
		 AGREGARMAPA(velocidadsaltoringman)
		 AGREGARMAPA(velocidadcorrerringman)

		 AGREGARMAPA(masafireman)
		 AGREGARMAPA(anchofireman)
		 AGREGARMAPA(altofireman)
		 AGREGARMAPA(velocidadsaltofireman)
		 AGREGARMAPA(velocidadcorrerfireman)

		 AGREGARMAPA(probanuevavida)
		 AGREGARMAPA(probaenergiachica)
		 AGREGARMAPA(probaenergiagrande)
		 AGREGARMAPA(probaplasmachica)
		 AGREGARMAPA(probaplasmagrande)
		 AGREGARMAPA(radioexplosion)
		 AGREGARMAPA(tiempoexplosionbomba)
		 AGREGARMAPA(masabomba)
		 AGREGARMAPA(multiplicadorvelocidadbomba)
		 AGREGARMAPA(anchospritebomba)
		 AGREGARMAPA(altospritebomba)
		 AGREGARMAPA(masaplasma)
		 AGREGARMAPA(multiplicadorvelocidadplasma)
		 AGREGARMAPA(anchospriteplasma)
		 AGREGARMAPA(altospriteplasma)
		 AGREGARMAPA(masachispa)
		 AGREGARMAPA(multiplicadorvelocidadchispa)
		 AGREGARMAPA(anchospritechispa)
		 AGREGARMAPA(altospritechispa)
		 AGREGARMAPA(masaanillo)
		 AGREGARMAPA(multiplicadorvelocidadanillo)
		 AGREGARMAPA(anchospriteanillo)
		 AGREGARMAPA(altospriteanillo)
		 AGREGARMAPA(tiempoanillo)
		 AGREGARMAPA(masafuego)
		 AGREGARMAPA(multiplicadorvelocidadfuego)
		 AGREGARMAPA(anchospritefuego)
		 AGREGARMAPA(altospritefuego)
		 AGREGARMAPA(masaiman)
		 AGREGARMAPA(multiplicadorvelocidadiman)
		 AGREGARMAPA(anchospriteiman)
		 AGREGARMAPA(altospriteiman)
		 AGREGARMAPA(impulsoiman)

		Cadena linea("");
		std::string nombre;
		std::vector<Cadena> partes;

		std::fstream archivo;
		archivo.open(nombreArchivo.c_str(), std::ios::in);
		
		while(!archivo.eof())
		{
			archivo >> linea;
			partes = linea.partir(Cadena("="));	

			/*Setea el formato decimal al de la maquina.*/
			Cadena::buscarReemplazar(partes.at(2), ',' , std::use_facet< std::numpunct<char> >(std::cout.getloc()).decimal_point());	
	
			*punteros[partes.at(0)] = partes.at(2);			
		}

	}
	
	
}

