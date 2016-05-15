#ifndef MEGAMAN
#define MEGAMAN

#include "Entidad.h"
#include "Definiciones.h"
#include <vector>
#include "Disparo.h"

#define MEGAMANNOCORRE 0
#define MEGAMANEMPEZANDOACORRRER 1
#define MEGAMANCORRIENDO 2

class Megaman : public Entidad
{
private:

	struct Arma
	{
		Disparo *arma;
		char plasma;
	};

	uint vida;
	bool puedeSaltar;
	bool saltando, disparando, lanzando;
	char corriendo;
	std::vector<Arma> armas;
	char armaSeleccionada;
public:
	Megaman(Mundo &mundo,
			const b2Vec2 &posicion,
			const b2Vec2 &velocidad = b2Vec2_zero,
			Orientaciones orientacion = derecha);

	~Megaman();
	void habilitarSalto();
	void deshabilitarSalto();

	void saltar();
	void correr();
	void dejarCorrer();
	void disparar();

	void seleccionarArma(char slot);

	void aumentarVida();
	void recuperarPlasma(int cantidadPlasma);
	char obtenerCantidadPlasma();

	char tipoCuerpo() const;

	void actualizar(real deltaT);

	void agregarArma(Disparo *disparo);
};

#endif
