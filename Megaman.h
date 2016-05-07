#ifndef MEGAMAN
#define MEGAMAN

#include "Entidad.h"
#include "Definiciones.h"
#include <vector>

class Megaman : public Entidad
{
private:

	struct Arma
	{
		Disparo *arma;
		char plasma;
	};

	uint vida;
	bool saltando, corriendo, disparando, lanzando;
	std::vector<Arma> armas;
	char armaSeleccionada;
public:
	Megaman(Mundo &mundo,
			uint energiaMaxima,
			real masa,
			const Vector2D &posicion,
			bool gravitacional = true,
			const Vector2D &velocidad = Vector2D(),
			const Vector2D &orientacion = Vector2D(1, 0));

	~Megaman();
	void saltar();
	void correr();
	void disparar();

	bool estaSaltando();
	bool estaCorriendo();

	void seleccionarArma(char slot);

	void aumentarVida();
	void recuperarPlasma(int cantidadPlasma);
	char obtenerCantidadPlasma();

	void agregarArma(Disparo *disparo);
};

#endif
