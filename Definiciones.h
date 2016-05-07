#ifndef DEFINICIONES
#define DEFINICIONES

#include <exception>
#include "Cadena.h"

#define OK 0
#define MSG_NOSIGNAL 0
#define MAXIMALONGITUDBUFFER 1000

#define ENERGIAMEGAMAN 50
#define MAXIMACANTIDADPLASMA 50
#define CANTIDADINFINITAPLASMA -1
#define MAXIMACANTIDADVIDAS 127
#define VIDASINICIALES 3
#define FACTORSALTOMEGAMAN 3

#define ANCHOSPRITEMEGAMAN 200
#define ALTOSPRITEMEGAMAN 400


#define MASAPOWERUP 10
#define VELOCIDADPOWERUP (0,-10)
#define PROBANUEVAVIDA 0.01
#define PROBAENERGIACHICA 0.1
#define PROBAENERGIAGRANDE 0.05
#define PROBAPLASMACHICA 0.1
#define PROBAPLASMAGRANDE 0.05

#define RADIOEXPLOSION 10
#define TIEMPOEXPLOSIONBOMBA 5
#define DANOBOMBA 100
#define MASABOMBA 10
#define MULTIPLICADORVELOCIDADBOMBA 3;

#define DANOPLASMA 15
#define MASANULA 0
#define MULTIPLICADORVELOCIDADPLASMA 7;

typedef unsigned int uint;
typedef double real;

class NoPudoCrearseConexion : public std::exception {};
class NoHayConexion : public std::exception {};
class ErrorEnLaConexion : public std::exception {};
class EstadoParametroIncorrecto : public std::exception {};
class ClaveInvalida : public std::exception {};
class ParametroEsPunteroNulo : public std::exception {};
class NoPudoLanzarseHilo : public std::exception {};

#endif
