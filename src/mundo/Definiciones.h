#ifndef DEFINICIONES
#define DEFINICIONES

#include <exception>
#include "Cadena.h"

#define CONSTRUCCIONES 1
#define ENEMIGOS 2
#define PERSONAJES 4
#define POWERUPS 8
#define DISPAROS 16

#define MSG_NOSIGNAL 0
#define MAXIMALONGITUDBUFFER 1000

#define GRAVEDAD 10

#define ENERGIAMEGAMAN 50
#define MASAMEGAMAN 57
#define MAXIMACANTIDADPLASMA 50
#define CANTIDADINFINITAPLASMA -1
#define MAXIMACANTIDADVIDAS 127
#define VIDASINICIALES 3
#define DANOPORCONTACTO 5
#define MEGAMANJUMPBOX 500

#define VELOCIDADMEGAMANCORRIENDO 2
#define POSICIONDISPAROMEGAMAN 0.8
#define POSICIONLANZAMIENTOMEGAMAN 1.6
#define IMPULSOSALTOMEGAMAN 6

#define ANCHOSPRITEMEGAMAN 1.13
#define ALTOSPRITEMEGAMAN 1.6


#define ANCHOSPRITEENEMIGO 200
#define ALTOSPRITEENEMIGO 400

#define ANCHOSPRITEPOWERUP 100
#define ALTOSPRITEPOWERUP 100

#define ENERGIAMAXIMABUMBY 100
#define MASABUMBY 50

#define ENERGIAMAXIMAMET 100
#define MASAMET 50
#define ESCUDOMET 50


#define MASAPOWERUP 10
#define VELOCIDADPOWERUP (0,-10)
#define PROBANUEVAVIDA 0.01f
#define PROBAENERGIACHICA 0.1f
#define PROBAENERGIAGRANDE 0.05f
#define PROBAPLASMACHICA 0.1f
#define PROBAPLASMAGRANDE 0.05f

#define RADIOEXPLOSION 3
#define TIEMPOEXPLOSIONBOMBA 5
#define DANOBOMBA 100
#define MASABOMBA 5
#define MULTIPLICADORVELOCIDADBOMBA 3
#define ANCHOSPRITEBOMBA 0.5
#define ALTOSPRITEBOMBA 0.5

#define DANOPLASMA 15
#define MASAPLASMA 1
#define MULTIPLICADORVELOCIDADPLASMA 7;
#define ANCHOSPRITEPLASMA 0.2
#define ALTOSPRITEPLASMA 0.2

typedef unsigned int uint;
typedef float real;
typedef unsigned short ushort;

class NoPudoCrearseConexion : public std::exception {};
class NoHayConexion : public std::exception {};
class ErrorEnLaConexion : public std::exception {};
class EstadoParametroIncorrecto : public std::exception {};
class ClaveInvalida : public std::exception {};
class ParametroEsPunteroNulo : public std::exception {};
class NoPudoLanzarseHilo : public std::exception {};

#endif
