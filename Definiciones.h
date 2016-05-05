#ifndef DEFINICIONES
#define DEFINICIONES

#include <exception>
#include "Cadena.h"

#define OK 0
#define MSG_NOSIGNAL 0
#define MAXIMALONGITUDBUFFER 1000

typedef unsigned int uint;

class NoPudoCrearseConexion : public std::exception {};
class NoHayConexion : public std::exception {};
class ErrorEnLaConexion : public std::exception {};
class EstadoParametroIncorrecto : public std::exception {};
class ClaveInvalida : public std::exception {};
class ParametroEsPunteroNulo : public std::exception {};
class NoPudoLanzarseHilo : public std::exception {};

#endif
