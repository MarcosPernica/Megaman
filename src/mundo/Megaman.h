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
	Animacion animacion_subiendo;
	Animacion animacion_disparando;
	Animacion animacion_disparandoCorriendo;
	Animacion animacion_disparandoSaltando;
	Animacion animacion_disparandoSubiendo;

	struct Arma
	{
		Disparo *arma;
		char plasma;
	};
	std::vector<Arma> armas;//no puedo snapshotear vectores,si son 5 armas podemos hacer algo tipo Arma->representacionInt y Arma::desdeInt
	unsigned char armaSeleccionada;//lo snaphoteo cuando tenga las armas

	uint vidas;//snapshoteado
	real timeoutDisparo;

	/*Algebra de colisiones*/
	int puedeSaltar;//snapshoteado
	int puedeSubir;//snapshoteado

	/*Variable de estado.*/
	char estadoSalto, estadoDisparo, estadoEscalado;//snapshoteado
	bool corriendo;//snapshoteado
	bool inmovilizado; //snapshoteado
	real tiempoInmunidad;

	/*Posicion X de la que megaman puede agarrarse.*/
	real agarreX;//snapshoteado
	real topeY;	//snapshoteado
	b2Vec2 posicionSpawn;
public:
	Megaman(uint ID,
			Mundo &mundo,
			const b2Vec2 &posicion,
			const b2Vec2 &velocidad = b2Vec2_zero,
			Orientaciones orientacion = derecha);

	~Megaman();
	bool reSpawn();
	void modificarPosicionSpawn(b2Vec2 spawn);
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
	void atacado(uint dano, Disparo *disparo);
	void inmovilizar(); //Por un cuadro no puede caminar

	ushort tipoCuerpo() const;

	void actualizar(real deltaT);

	void agregarArma(Disparo *disparom, uint cantidadPlasma);
	void alMorir();
	
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	GENERAR_GET_TIPO(Megaman);

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
