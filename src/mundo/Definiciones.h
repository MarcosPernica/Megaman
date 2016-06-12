#ifndef DEFINICIONES
#define DEFINICIONES

#include <exception>
#include "Cadena.h"
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream>

#define NULO 0

#define FANTASMAS 0
#define CONSTRUCCIONES 1
#define ENEMIGOS 2
#define PERSONAJES 4
#define POWERUPS 8
#define DISPAROS 16
#define ESCALERAS 32
#define JUMPBOX 64
#define CAJASACCION 128
#define LEFTBOX 256
#define RIGHTBOX 512
#define AURAENEMIGOS 1024

#define CUERPOPRINCIPAL 0
#define MEGAMANJUMPBOX 1

#define BOMBA 1
#define IMAN 2
#define ANILLO 3
#define FUEGO 4
#define CHISPA 5

#define IDCONSTRUCCIONES 0
#define MAXIMALONGITUDBUFFER 1000

typedef unsigned int uint;
typedef float real;
typedef unsigned short ushort;

/*Me fabrico un RTT para esto sino me vuelvo viejo cargando 105 constantes a mano y dependiendo del orden x.x */
#define AGREGARMAPA(S) punteros[#S] = &S;

namespace SJuego
{
	struct Constantes
	{
		 real distanciavision;
		 real nulo;
		 real fantasmas ;
		 real construcciones;
		 real enemigos;
		 real personajes;
		 real powerups;
		 real disparos;
		 real escaleras;
		 real jumpbox;
		 real cajasaccion;
		 real leftbox;
		 real rightbox;
		 real auraenemigos;
		 real bomba;
		 real idconstrucciones;
		 real maximalongitudbuffer;
		 real gravedad;
		 real anchoescalera;
		 real anchopuerta;
		 real altopuerta;
		 real energiamegaman;
		 real masamegaman;
		 real maximacantidadplasma;
		 real cantidadinfinitaplasma;
		 real maximacantidadvidas;
		 real vidasiniciales;
		 real danoporcontacto;
		 real cuerpoprincipal;
		 real megamanjumpbox;
		 real velocidadmegamancorriendo;
		 real velocidadmegamanescalera;
		 real posiciondisparomegaman;
		 real posicionlanzamientomegaman;
		 real velocidadsaltomegaman;
		 real tiempoinmunidadmegaman;
		 real anchospritemegaman;
		 real altospritemegaman;
		 real masapowerup;
		 real velocidadpowerup;
		 real anchospritepowerup;
		 real altospritepowerup;
		 real energiamaximabumby;
		 real masabumby;
		 real anchobumby;
		 real altobumby;
		 real velocidadsaltobumby;
		 real velocidadcorrerbumby;
		 real energiamaximamet;
		 real masamet;
		 real escudomet;
		 real anchomet;
		 real altomet;
		 real velocidadsaltomet;
		 real velocidadcorrermet;
		 real energiamaximasniper;
		 real masasniper;
		 real escudosniper;
		 real anchosniper;
		 real altosniper;
		 real velocidadsaltosniper;
		 real velocidadcorrersniper;
		 real energiamaximajumpingsniper;
		 real masajumpingsniper;
		 real escudojumpingsniper;
		 real anchojumpingsniper;
		 real altojumpingsniper;
		 real velocidadsaltojumpingsniper;
		 real velocidadcorrerjumpingsniper;
		 real energiamaximabombman;
		 real masabombman;
		 real escudobombman;
		 real anchobombman;
		 real altobombman;
		 real velocidadsaltobombman;
		 real velocidadcorrerbombman;

		 real energiamaximasparkman;
		 real masasparkman;
		 real escudosparkman;
		 real anchosparkman;
		 real altosparkman;
		 real velocidadsaltosparkman;
		 real velocidadcorrersparkman;

		 real energiamaximamagnetman;
		 real masamagnetman;
		 real escudomagnetman;
		 real anchomagnetman;
		 real altomagnetman;
		 real velocidadsaltomagnetman;
		 real velocidadcorrermagnetman;

		 real energiamaximaringman;
		 real masaringman;
		 real escudoringman;
		 real anchoringman;
		 real altoringman;
		 real velocidadsaltoringman;
		 real velocidadcorrerringman;

		 real energiamaximafireman;
		 real masafireman;
		 real escudofireman;
		 real anchofireman;
		 real altofireman;
		 real velocidadsaltofireman;
		 real velocidadcorrerfireman;

		 real probanuevavida;
		 real probaenergiachica;
		 real probaenergiagrande;
		 real probaplasmachica;
		 real probaplasmagrande;
		 real radioexplosion;
		 real tiempoexplosionbomba;
		 real danobomba;
		 real masabomba;
		 real multiplicadorvelocidadbomba;
		 real anchospritebomba;
		 real altospritebomba;
		 real danoplasma;
		 real masaplasma;
		 real multiplicadorvelocidadplasma;
		 real anchospriteplasma;
		 real altospriteplasma;
		 real danochispa;
		 real masachispa;
		 real multiplicadorvelocidadchispa;
		 real anchospritechispa;
		 real altospritechispa;
		 real danoanillo;
		 real masaanillo;
		 real multiplicadorvelocidadanillo;
		 real anchospriteanillo;
		 real altospriteanillo;
		 real tiempoanillo;
		 real danofuego;
		 real masafuego;
		 real multiplicadorvelocidadfuego;
		 real anchospritefuego;
		 real altospritefuego;
		 real danoiman;
		 real masaiman;
		 real multiplicadorvelocidadiman;
		 real anchospriteiman;
		 real altospriteiman;
		 real impulsoiman;

		std::map<std::string, real*> punteros;

		Constantes(){};

		void cargar(std::string nombreArchivo);

	};

	extern Constantes attr;
}


/*Las remapeo para no tener que cambiar todo el codigo. Que el Preprocesador sirva para lo que fue creado.*/

#define DISTANCIAVISION SJuego::attr.distanciavision
#define GRAVEDAD SJuego::attr.gravedad
#define ANCHOESCALERA SJuego::attr.anchoescalera
#define ANCHOPUERTA SJuego::attr.anchopuerta
#define ALTOPUERTA SJuego::attr.altopuerta
#define ENERGIAMEGAMAN SJuego::attr.energiamegaman
#define MASAMEGAMAN SJuego::attr.masamegaman
#define MAXIMACANTIDADPLASMA SJuego::attr.maximacantidadplasma
#define CANTIDADINFINITAPLASMA SJuego::attr.cantidadinfinitaplasma
#define MAXIMACANTIDADVIDAS SJuego::attr.maximacantidadvidas
#define VIDASINICIALES SJuego::attr.vidasiniciales
#define DANOPORCONTACTO SJuego::attr.danoporcontacto
#define VELOCIDADMEGAMANCORRIENDO SJuego::attr.velocidadmegamancorriendo
#define VELOCIDADMEGAMANESCALERA SJuego::attr.velocidadmegamanescalera
#define POSICIONDISPAROMEGAMAN SJuego::attr.posiciondisparomegaman
#define POSICIONLANZAMIENTOMEGAMAN SJuego::attr.posicionlanzamientomegaman
#define VELOCIDADSALTOMEGAMAN SJuego::attr.velocidadsaltomegaman
#define TIEMPOINMUNIDADMEGAMAN SJuego::attr.tiempoinmunidadmegaman
#define ANCHOSPRITEMEGAMAN SJuego::attr.anchospritemegaman
#define ALTOSPRITEMEGAMAN SJuego::attr.altospritemegaman
#define MASAPOWERUP SJuego::attr.masapowerup
#define VELOCIDADPOWERUP SJuego::attr.velocidadpowerup
#define ANCHOSPRITEPOWERUP SJuego::attr.anchospritepowerup
#define ALTOSPRITEPOWERUP SJuego::attr.altospritepowerup
#define ENERGIAMAXIMABUMBY SJuego::attr.energiamaximabumby
#define MASABUMBY SJuego::attr.masabumby
#define ANCHOBUMBY SJuego::attr.anchobumby
#define ALTOBUMBY SJuego::attr.altobumby
#define VELOCIDADSALTOBUMBY SJuego::attr.velocidadsaltobumby
#define VELOCIDADCORRERBUMBY SJuego::attr.velocidadcorrerbumby
#define ENERGIAMAXIMAMET SJuego::attr.energiamaximamet
#define MASAMET SJuego::attr.masamet
#define ESCUDOMET SJuego::attr.escudomet
#define ANCHOMET SJuego::attr.anchomet
#define ALTOMET SJuego::attr.altomet
#define VELOCIDADSALTOMET SJuego::attr.velocidadsaltomet
#define VELOCIDADCORRERMET SJuego::attr.velocidadcorrermet
#define ENERGIAMAXIMASNIPER SJuego::attr.energiamaximasniper
#define MASASNIPER SJuego::attr.masasniper
#define ESCUDOSNIPER SJuego::attr.escudosniper
#define ANCHOSNIPER SJuego::attr.anchosniper
#define ALTOSNIPER SJuego::attr.altosniper
#define VELOCIDADSALTOSNIPER SJuego::attr.velocidadsaltosniper
#define VELOCIDADCORRERSNIPER SJuego::attr.velocidadcorrersniper
#define ENERGIAMAXIMAJUMPINGSNIPER SJuego::attr.energiamaximajumpingsniper
#define MASAJUMPINGSNIPER SJuego::attr.masajumpingsniper
#define ESCUDOJUMPINGSNIPER SJuego::attr.escudojumpingsniper
#define ANCHOJUMPINGSNIPER SJuego::attr.anchojumpingsniper
#define ALTOJUMPINGSNIPER SJuego::attr.altojumpingsniper
#define VELOCIDADSALTOJUMPINGSNIPER SJuego::attr.velocidadsaltojumpingsniper
#define VELOCIDADCORRERJUMPINGSNIPER SJuego::attr.velocidadcorrerjumpingsniper
#define ENERGIAMAXIMABOMBMAN SJuego::attr.energiamaximabombman
#define MASABOMBMAN SJuego::attr.masabombman
#define ESCUDOBOMBMAN SJuego::attr.escudobombman
#define ANCHOBOMBMAN SJuego::attr.anchobombman
#define ALTOBOMBMAN SJuego::attr.altobombman
#define VELOCIDADSALTOBOMBMAN SJuego::attr.velocidadsaltobombman
#define VELOCIDADCORRERBOMBMAN SJuego::attr.velocidadcorrerbombman

#define ENERGIAMAXIMASPARKMAN SJuego::attr.energiamaximasparkman
#define MASASPARKMAN SJuego::attr.masasparkman
#define ESCUDOSPARKMAN SJuego::attr.escudosparkman
#define ANCHOSPARKMAN SJuego::attr.anchosparkman
#define ALTOSPARKMAN SJuego::attr.altosparkman
#define VELOCIDADSALTOSPARKMAN SJuego::attr.velocidadsaltosparkman
#define VELOCIDADCORRERSPARKMAN SJuego::attr.velocidadcorrersparkman

#define ENERGIAMAXIMAMAGNETMAN SJuego::attr.energiamaximamagnetman
#define MASAMAGNETMAN SJuego::attr.masamagnetman
#define ESCUDOMAGNETMAN SJuego::attr.escudomagnetman
#define ANCHOMAGNETMAN SJuego::attr.anchomagnetman
#define ALTOMAGNETMAN SJuego::attr.altomagnetman
#define VELOCIDADSALTOMAGNETMAN SJuego::attr.velocidadsaltomagnetman
#define VELOCIDADCORRERMAGNETMAN SJuego::attr.velocidadcorrermagnetman

#define ENERGIAMAXIMARINGMAN SJuego::attr.energiamaximaringman
#define MASARINGMAN SJuego::attr.masaringman
#define ESCUDORINGMAN SJuego::attr.escudoringman
#define ANCHORINGMAN SJuego::attr.anchoringman
#define ALTORINGMAN SJuego::attr.altoringman
#define VELOCIDADSALTORINGMAN SJuego::attr.velocidadsaltoringman
#define VELOCIDADCORRERRINGMAN SJuego::attr.velocidadcorrerringman

#define ENERGIAMAXIMAFIREMAN SJuego::attr.energiamaximafireman
#define MASAFIREMAN SJuego::attr.masafireman
#define ESCUDOFIREMAN SJuego::attr.escudofireman
#define ANCHOFIREMAN SJuego::attr.anchofireman
#define ALTOFIREMAN SJuego::attr.altofireman
#define VELOCIDADSALTOFIREMAN SJuego::attr.velocidadsaltofireman
#define VELOCIDADCORRERFIREMAN SJuego::attr.velocidadcorrerfireman

#define PROBANUEVAVIDA SJuego::attr.probanuevavida
#define PROBAENERGIACHICA SJuego::attr.probaenergiachica
#define PROBAENERGIAGRANDE SJuego::attr.probaenergiagrande
#define PROBAPLASMACHICA SJuego::attr.probaplasmachica
#define PROBAPLASMAGRANDE SJuego::attr.probaplasmagrande
#define RADIOEXPLOSION SJuego::attr.radioexplosion
#define TIEMPOEXPLOSIONBOMBA SJuego::attr.tiempoexplosionbomba
#define DANOBOMBA SJuego::attr.danobomba
#define MASABOMBA SJuego::attr.masabomba
#define MULTIPLICADORVELOCIDADBOMBA SJuego::attr.multiplicadorvelocidadbomba
#define ANCHOSPRITEBOMBA SJuego::attr.anchospritebomba
#define ALTOSPRITEBOMBA SJuego::attr.altospritebomba
#define DANOPLASMA SJuego::attr.danoplasma
#define MASAPLASMA SJuego::attr.masaplasma
#define MULTIPLICADORVELOCIDADPLASMA SJuego::attr.multiplicadorvelocidadplasma
#define ANCHOSPRITEPLASMA SJuego::attr.anchospriteplasma
#define ALTOSPRITEPLASMA SJuego::attr.altospriteplasma
#define DANOCHISPA SJuego::attr.danochispa
#define MASACHISPA SJuego::attr.masachispa
#define MULTIPLICADORVELOCIDADCHISPA SJuego::attr.multiplicadorvelocidadchispa
#define ANCHOSPRITECHISPA SJuego::attr.anchospritechispa
#define ALTOSPRITECHISPA SJuego::attr.altospritechispa
#define DANOANILLO SJuego::attr.danoanillo
#define MASAANILLO SJuego::attr.masaanillo
#define MULTIPLICADORVELOCIDADANILLO SJuego::attr.multiplicadorvelocidadanillo
#define ANCHOSPRITEANILLO SJuego::attr.anchospriteanillo
#define ALTOSPRITEANILLO SJuego::attr.altospriteanillo
#define TIEMPOANILLO SJuego::attr.tiempoanillo
#define DANOFUEGO SJuego::attr.danofuego
#define MASAFUEGO SJuego::attr.masafuego
#define MULTIPLICADORVELOCIDADFUEGO SJuego::attr.multiplicadorvelocidadfuego
#define ANCHOSPRITEFUEGO SJuego::attr.anchospritefuego
#define ALTOSPRITEFUEGO SJuego::attr.altospritefuego
#define DANOIMAN SJuego::attr.danoiman
#define MASAIMAN SJuego::attr.masaiman
#define MULTIPLICADORVELOCIDADIMAN SJuego::attr.multiplicadorvelocidadiman
#define ANCHOSPRITEIMAN SJuego::attr.anchospriteiman
#define ALTOSPRITEIMAN SJuego::attr.altospriteiman
#define IMPULSOIMAN SJuego::attr.impulsoiman

class NoPudoCrearseConexion : public std::exception {};
class NoHayConexion : public std::exception {};
class ErrorEnLaConexion : public std::exception {};
class EstadoParametroIncorrecto : public std::exception {};
class ClaveInvalida : public std::exception {};
class ParametroEsPunteroNulo : public std::exception {};
class NoPudoLanzarseHilo : public std::exception {};

#endif
