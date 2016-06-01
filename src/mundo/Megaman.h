#ifndef MEGAMAN
#define MEGAMAN

#include "Entidad.h"
#include "Definiciones.h"
#include "../graficos/Animado.h"
#include "../graficos/Animacion.h"
#include <vector>
#include "Disparo.h"
#include "Saltador.h"


class Megaman : public Entidad, public Saltador, public Animado
{
private:
	Animacion animacion_corriendo;
	Animacion animacion_saltando;
	Animacion animacion_quieto;

	struct Arma
	{
		Disparo *arma;
		char plasma;
	};
	std::vector<Arma> armas;//no puedo snapshotear vectores,si son 5 armas podemos hacer algo tipo Arma->representacionInt y Arma::desdeInt
	unsigned char armaSeleccionada;//lo snaphoteo cuando tenga las armas

	uint vidas;//snapshoteado

	/*Algebra de colisiones*/
	int puedeSaltar;//snapshoteado
	int puedeSubir;//snapshoteado

	/*Variable de estado.*/
	char estadoSalto, estadoDisparo, estadoEscalado;//snapshoteado
	bool corriendo;//snapshoteado
	real tiempoInmunidad;

	/*Posicion X de la que megaman puede agarrarse.*/
	real agarreX;//snapshoteado
	real topeY;	//snapshoteado
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
	void bajarEscalera();
	void pararMovimientoEscalera();
	
	void saltar();
	void correr();
	void dejarCorrer();
	void disparar();
	void mirarIzquierda();
	void mirarDerecha();

	void seleccionarArma(unsigned char slot);

	void aumentarVida();
	void recuperarPlasma(int cantidadPlasma);
	char obtenerCantidadPlasma();
	uint obtenerCantidadVidas();
	void atacado(uint dano);

	ushort tipoCuerpo() const;

	void actualizar(real deltaT);

	void agregarArma(Disparo *disparom, uint cantidadPlasma);
	void alMorir();
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int  getTipo(){return TIPO_MEGAMAN;};

	virtual void dibujarEn(const Cairo::RefPtr<Cairo::Context>& cr, b2Vec2 origen, real factorAmplificacion){
	Imagen::dibujarEn(cr,origen,factorAmplificacion);
	}
	/**
	 * Devuelve el rectángulo en unidades de render
	 * */
	virtual const Rectangulo obtenerRepresentacion() const;
	
	virtual bool espejado() const;
	
	//virtual Glib::RefPtr<Gdk::Pixbuf> a_dibujar() const;
	void eliminarse(Mundo& de){};
};

#endif
