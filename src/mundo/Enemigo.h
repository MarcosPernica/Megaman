#ifndef ENEMIGO
#define ENEMIGO

#include "Definiciones.h"
#include <Box2D/Box2D.h>
#include "Callbacks.h"
#include "Entidad.h"
#include "Saltador.h"

class Disparo;

class Enemigo : public Entidad, public Saltador
{
private:
	real aleatorio;
	/*Algebra de colisiones*/
	int contadorPiso;

	/*Variable de estado.*/
	char estadoSalto, estadoDisparo;//snapshoteados
	bool corriendo;//snapshoteado
	char tocandoIzquierda, tocandoDerecha;//snapshoteados
	uint escudo;//snapshoteado
	bool cubierto;//snapshoteado

	Disparo *arma;//NO SNAPSHOTEADO
	b2Vec2 direccionDisparo;//snapshoteado

	bool powerUpMorir;//snapshoteado
	real velocidadSalto;//snapshoteado
	real velocidadCorrer;//snapshoteado
public:
	Enemigo(uint ID,
			  Mundo &mundo,
			  real ancho,
			  real alto,
			  Disparo *arma,
			  uint energiaMaxima,
			  uint escudo,
			  real masa,
			  real velocidadSalto,
			  real velocidadCorrer,
			  ushort categoria,
			  ushort colisionaCon,
			  const b2Vec2 &posicion,
			  bool rotable = false,
			  bool gravitacional = true,
			  const b2Vec2 &velocidad = b2Vec2_zero,
			  Orientaciones orientacion = izquierda,
			  bool powerUpMorir = true);
	
	virtual void alMorir();
	void habilitarSalto();
	void deshabilitarSalto();

	void tocoIzquierda();
	void dejoTocarIzquierda();
	void tocoDerecha();
	void dejoTocarDerecha();

	bool puedeIrIzquierda();
	bool puedeIrDerecha();
	bool puedeCorrer();

	bool puedeSaltar();
	void saltar();
	void correr();
	void dejarCorrer();
	virtual void disparar(b2Vec2 direccion = b2Vec2_zero);
	void mirarIzquierda();
	void mirarDerecha();	
	void virar();

	void atacado(uint danio);

	void cubrirse();
	void exponerse();
	bool estaCubierto();

	real numeroAleatorio(real desde, real hasta);
	void actualizar(real deltaT);	

	void eliminarse(Mundo& de);
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot);
	virtual void setStateFromSnapshot(const Snapshot& snapshot);
	virtual int getTipo(){return TIPO_PROTEGIDO;};
	
private:
	void ruletaPowerUp(uint ID, Mundo &mundo, const b2Vec2 &posicion);
};

#endif
