#ifndef MEGAMAN
#define MEGAMAN

#include "Entidad.h"
#include "Definiciones.h"
#include <vector>
#include "Disparo.h"
#include "../graficos/Imagen.h"
#define MEGAMANNOCORRE 0
#define MEGAMANEMPEZANDOACORRRER 1
#define MEGAMANCORRIENDO 2

class Megaman : public Entidad, public Imagen
{
private:

	struct Arma
	{
		Disparo *arma;
		char plasma;
	};

	uint vida;
	int puedeSaltar;
	bool saltando, disparando, lanzando, agarrado;
	bool subiendoEscalera, bajandoEscalera;
	int puedeSubir;
	bool corriendo;
	std::vector<Arma> armas;
	char armaSeleccionada;
	real agarreX;
public:
	Megaman(uint ID,
			Mundo &mundo,
			const b2Vec2 &posicion,
			const b2Vec2 &velocidad = b2Vec2_zero,
			Orientaciones orientacion = derecha);

	~Megaman();
	void habilitarSalto();
	void deshabilitarSalto();

	void habilitarAgarre(real agarreX);
	void deshabilitarAgarre();
	void subirEscalera();
	void dejarSubirEscalera();
	void bajarEscalera();
	void dejarBajarEscalera();
	
	void saltar();
	void correr();
	void dejarCorrer();
	void disparar();
	void mirarIzquierda();
	void mirarDerecha();

	void seleccionarArma(char slot);

	void aumentarVida();
	void recuperarPlasma(int cantidadPlasma);
	char obtenerCantidadPlasma();

	ushort tipoCuerpo() const;

	void actualizar(real deltaT);

	void agregarArma(Disparo *disparom, uint cantidadPlasma);
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo() const {return TIPO_MEGAMAN;};
	
	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion) const{
		Imagen::dibujarEn(cr,origen,factorAmplificacion);
	}
	/**
	 * Devuelve el rectángulo en unidades de render
	 * */
	virtual const Rectangulo obtenerRepresentacion() const;
};

#endif
