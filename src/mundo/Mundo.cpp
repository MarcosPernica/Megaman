#include "Mundo.h"
#include "Callbacks.h"
#include <algorithm>
#include <iostream>
#include "CajaAccion.h"
#include "Cuerpo.h"
#include "Escalera.h"
#include "../net/snapshots/FullSnapshot.h"
#include "Enemigo.h"
#include "PowerUp.h"
#include "Puas.h"
#include "../common/Cadena.h"
#include "../common/exceptions.h"
#include "../tinyxml/tinyxml.h"
#include "../net/Debug.h"
#include "Definiciones.h"

#define MUNDOVIVO 0
#define MUNDOTERMINADO 1

Mundo::Mundo(real anchoCamara, 
	     real altoCamara, 
	     b2Vec2 posicionCamara,
	     const std::string& n,
	     uint cantidad_jugadores) : 
	     mundo(b2Vec2(0,GRAVEDAD)), 
	     terminado(false),
	     anterior_ID(cantidad_jugadores)
{
	
	nombre_nivel = n;
	Cadena nombre(nombre_nivel);

	mundo.SetContactListener(&listenerColisiones);
	camara = new ZonaCamara(*this, anchoCamara, altoCamara, posicionCamara);

	cargarNivel(nombre);	
	
	anterior_ID = 0;
	for(uint i=0; i<cantidad_jugadores; i++){
		agregarMegaman();
	}
	
	camara->reiniciar();
}

#define GENERAR_LIBERAR_MAPA(_nombreMapa,_nombreClase)\
	{\
		std::map<uint, _nombreClase*>::iterator it;\
		for(it = _nombreMapa.begin(); it!= _nombreMapa.end(); ++it){\
			delete it->second;\
		}\
	}\

Mundo::~Mundo()
{
	GENERAR_LIBERAR_MAPA(megamanes,Megaman)
	GENERAR_LIBERAR_MAPA(enemigos,Enemigo)
	GENERAR_LIBERAR_MAPA(powerUps,PowerUp)
	GENERAR_LIBERAR_MAPA(disparos,Disparo)
	GENERAR_LIBERAR_MAPA(puertas,Puerta)
	
	
	delete camara;

	std::list<CajaAccion*>::iterator f = controladores.begin();

	while(f != controladores.end())
		delete *(f++);
	
	std::list<Interactuable*>::iterator g = zonas.begin();

	while(g != zonas.end())
		delete *(g++);

	std::list<Construccion*>::iterator h = construcciones.begin();

	while(h != construcciones.end())
		delete *(h++);
}

void Mundo::setEstadisticas(EstadisticasMundo& estadisticas){
	this->estadisticas = estadisticas;
	const std::vector<int>& armas = estadisticas.obtenerArmas();
	std::vector<int>::const_iterator it;
	for(it = armas.begin(); it!= armas.end(); ++it){
		std::map<uint, Megaman*>::iterator it_m;
		for(it_m = megamanes.begin(); it_m!=megamanes.end(); ++it_m){
			it_m->second->agregarArma(*it,100);
		}
	}
	uint pos = 0;
	std::map<uint, Megaman*>::iterator it_m;
	for(it_m=megamanes.begin(); it_m != megamanes.end(); ++it_m){
		it_m->second->setCantidadVidas(estadisticas.vidasDe(pos));
		pos += 1;
	}
}
EstadisticasMundo& Mundo::obtenerEstadisticas(){
	return estadisticas;
}

void Mundo::notificarMuerteMegaman(Megaman* muerto){
	estadisticas.perderUnaVida(muerto->obtenerID()-1);
}


b2Vec2 Mundo::obtenerPosicionCamara()
{
	return camara->obtenerPosicion();
}

void Mundo::reiniciar()
{
	std::map<uint, Megaman*>::const_iterator i = megamanes.begin();

	while(i != megamanes.end())
		i++->second->reSpawn();

	camara->reiniciar();
}

void Mundo::finalizar()
{
	terminado = true;
}
uint Mundo::generarID()
{
	return ++anterior_ID;
}

EstadoMundo Mundo::obtenerEstadoMundo()
{
	if(terminado)
		return ganado;

	bool muertos = true;

	std::map<uint, Megaman*>::const_iterator i = megamanes.begin();

	while(i != megamanes.end())
		muertos &= (i++)->second->estaMuerta();

	if(muertos)
	{
		if(!megamanes.begin()->second->obtenerCantidadVidas())
			return gameover;
		else
			return perdido;
	}
	else
		return vivo;
}

void Mundo::obtenerAtributosXML(TiXmlAttribute *atributo, std::map<std::string,real>& mapaAtributos)
{
	while(atributo)
	{
		mapaAtributos[atributo->Name()] = atributo->DoubleValue();		
		atributo = atributo->Next();
	}
}

void Mundo::cargarNivel(Cadena nombre){
	std::string valor;
	TiXmlDocument doc( nombre_nivel.c_str() );
	if(!doc.LoadFile())
		throw CustomException("Tiny XML no cargó el archivo");
		
    	TiXmlElement *elemento = doc.RootElement()->FirstChildElement();
   	while(elemento)
    	{
		std::map<std::string,real> atributos;
		obtenerAtributosXML(elemento->FirstAttribute(), atributos);
		valor = elemento->Value();
		
       		if(valor == "CuboMadera")
			agregarCuboMadera(atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "CuboMetal")
			agregarCuboMetal(atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "CuboLadrillo")
			agregarCuboLadrillo(atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "CuboTierra")
			agregarCuboTierra(atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "CuboVacio")
			agregarCuboVacio(atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "ZonaMortal")
			agregarZonaMortal(atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "ZonaTransporte")
			agregarZonaTransporte(atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]),b2Vec2(atributos["destX"],atributos["destY"]));
		else if(valor == "ZonaGuardado")
			agregarZonaGuardado(atributos["ancho"], atributos["alto"], b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "ZonaCerradura")
			agregarZonaCerradura(atributos["idPuerta"], atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "Puerta")
			agregarPuerta(atributos["id"], atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "Puas")
			agregarPuas(atributos["ancho"],atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "Escalera")
			agregarEscalera(atributos["alto"],b2Vec2(atributos["x"],atributos["y"]));
    		else if(valor == "ZonaSpawnMegaman")
			agregarZonaSpawnMegaman(atributos["longitud"], b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "Met")
			agregarZonaSpawnMet(b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "Bumby")
			agregarZonaSpawnBumby(b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "Sniper")
			agregarZonaSpawnSniper(b2Vec2(atributos["x"],atributos["y"]));
		else if(valor == "JumpingSniper")
			agregarZonaSpawnJumpingSniper(b2Vec2(atributos["x"], atributos["y"]));
		else if(valor == "Bombman")
			agregarZonaSpawnBombman(atributos["idPuerta"] ,b2Vec2(atributos["x"], atributos["y"]));
		else if(valor == "Sparkman")
			agregarZonaSpawnSparkman(atributos["idPuerta"] ,b2Vec2(atributos["x"], atributos["y"]));
		else if(valor == "Magnetman")
			agregarZonaSpawnMagnetman(atributos["idPuerta"] ,b2Vec2(atributos["x"], atributos["y"]));
		else if(valor == "Ringman")
			agregarZonaSpawnRingman(atributos["idPuerta"] ,b2Vec2(atributos["x"], atributos["y"]));
		else if(valor == "Fireman")
			agregarZonaSpawnFireman(atributos["idPuerta"] ,b2Vec2(atributos["x"], atributos["y"]));

       		elemento = elemento->NextSiblingElement();
    	}
}

b2World & Mundo::obtenerMundo()
{
	return mundo;
}

Megaman *Mundo::obtenerMegamanCercano(const b2Vec2 posicion, bool incluirMuertos)
{
	Megaman *cercano = megamanes.begin()->second;
	real normaCuadrada = (cercano->obtenerPosicion() - posicion).LengthSquared(), normaAux;
	std::map<uint, Megaman*>::iterator i = ++megamanes.begin();

	while(i != megamanes.end())
	{
		if(!i->second->estaMuerta() || incluirMuertos)
		{	
			normaAux = (i->second->obtenerPosicion() - posicion).LengthSquared();
			if( normaAux < normaCuadrada)
			{
				normaCuadrada = normaAux;
				cercano = i->second;
			}
		}
		i++;
	}

	return cercano;
}

Enemigo *Mundo::obtenerEnemigoCercano(const b2Vec2 posicion)
{
	Enemigo *cercano = enemigos.begin()->second;
	real normaCuadrada = (cercano->obtenerPosicion() - posicion).LengthSquared(), normaAux; 
	std::map<uint, Enemigo*>::iterator i = ++enemigos.begin();

	while(i != enemigos.end())
	{
		normaAux = (i->second->obtenerPosicion() - posicion).LengthSquared();
		if(i->second->tipoCuerpo() == ENEMIGOS)
			if( normaAux < normaCuadrada)
			{
				normaCuadrada = normaAux;
				cercano = i->second;
			}
		
		i++;
	}

	return cercano;
}

Entidad *Mundo::obtenerEntidad(uint ID)
{
	std::map<uint, Enemigo*>::iterator iEnemigo;

	if((iEnemigo = enemigos.find(ID)) != enemigos.end())
		return iEnemigo->second;

	std::map<uint, Megaman*>::iterator iMegaman;

	if((iMegaman = megamanes.find(ID)) != megamanes.end())
		return iMegaman->second;

	return NULL;	
}

void Mundo::danarZona(b2AABB zona, uint dano, Bomba *bomba)
{
	DanarRadio danoRadio(dano, bomba);
	
	mundo.QueryAABB(&danoRadio, zona);
}

void Mundo::eliminar(Enemigo * elemento)
{
	destrucciones.push_back(DatosEliminacion(elemento->obtenerID(),enemigo));
}

void Mundo::eliminar(PowerUp * elemento)
{
	destrucciones.push_back(DatosEliminacion(elemento->obtenerID(),powerUp));
}

void Mundo::eliminar(Disparo * elemento)
{
	destrucciones.push_back(DatosEliminacion(elemento->obtenerID(),disparo));
}

void Mundo::agregar(Disparo * disparo)
{
	disparos[disparo->obtenerID()] = disparo;
}

void Mundo::agregar(PowerUp * powerUp)
{
	powerUps[powerUp->obtenerID()] = powerUp;
}

void Mundo::agregar(Enemigo* enemigo)
{
	enemigos[enemigo->obtenerID()] = enemigo;
}

void Mundo::agregarCuboMadera(real ancho, real alto, b2Vec2 posicion)
{
	construcciones.push_back(new CuboMadera(IDCONSTRUCCIONES,*this,posicion, ancho, alto));
}

void Mundo::agregarCuboMetal(real ancho, real alto, b2Vec2 posicion)
{
	construcciones.push_back(new CuboMetal(IDCONSTRUCCIONES,*this,posicion, ancho, alto));
}

void Mundo::agregarCuboLadrillo(real ancho, real alto, b2Vec2 posicion)
{
	construcciones.push_back(new CuboLadrillo(IDCONSTRUCCIONES,*this,posicion, ancho, alto));
}

void Mundo::agregarCuboTierra(real ancho, real alto, b2Vec2 posicion)
{
	construcciones.push_back(new CuboTierra(IDCONSTRUCCIONES,*this,posicion, ancho, alto));
}

void Mundo::agregarCuboVacio(real ancho, real alto, b2Vec2 posicion)
{
	construcciones.push_back(new CuboVacio(IDCONSTRUCCIONES,*this,posicion, ancho, alto));
}

void Mundo::agregarPuas(real ancho, real alto, b2Vec2 posicion)
{
	controladores.push_back(new Puas(*this, ancho, alto, posicion));
}


void Mundo::agregarEscalera(real alto, b2Vec2 posicion)
{
	construcciones.push_back(new Escalera(IDCONSTRUCCIONES,*this,posicion, alto));
}

void Mundo::agregarZonaSpawnMegaman(real longitud, b2Vec2 posicion)
{
	zonaSpawnMegaman.inicio = posicion;
	zonaSpawnMegaman.longitud = longitud;
}

Megaman *Mundo::agregarMegaman()
{
 	Megaman *megaman = new Megaman(generarID(),*this, b2Vec2(zonaSpawnMegaman.inicio.x + ((zonaSpawnMegaman.longitud/CANTIDADMAXIMAJUGADORES)*megamanes.size()), zonaSpawnMegaman.inicio.y),megamanes.size());
	
	megamanes[megaman->obtenerID()] = megaman;
	return megaman;
}

void Mundo::agregarZonaMortal(real ancho, real alto, b2Vec2 posicion)
{
	controladores.push_back(new ZonaMortal(*this, ancho, alto, posicion));
}

void Mundo::agregarZonaTransporte(real ancho, real alto, b2Vec2 posicion, b2Vec2 posicionDestino)
{
	controladores.push_back(new ZonaTransporte(*this, ancho, alto, posicion, posicionDestino));
}

void Mundo::agregarZonaGuardado(real ancho, real alto, b2Vec2 posicion)
{
	controladores.push_back(new ZonaGuardado(*this, ancho, alto, posicion));
}

void Mundo::agregarZonaCerradura(uint IDPuerta, real ancho, real alto, b2Vec2 posicion)
{
	Puerta *puerta = obtenerPuerta(IDPuerta);

	controladores.push_back(new ZonaCerradura(*this, ancho, alto, posicion, puerta));
}

void Mundo::agregarPuerta(uint IDInterno, real ancho, real alto, b2Vec2 posicion)
{
	uint ID = generarID();

	puertas[ID] = (new Puerta(ID, IDInterno, *this, ancho, alto, posicion));
}

Puerta *Mundo::obtenerPuerta(uint IDInterno)
{
	std::map<uint, Puerta*>::iterator i = puertas.begin();

	while (i != puertas.end())
	{
		if(i->second->obtenerIDInterno() == IDInterno)
			return i->second;
		i++;
	}

	return NULL;
}

void Mundo::agregarZonaSpawnMet(b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnMet(generarID(),*this, posicion));
}

void Mundo::agregarZonaSpawnBumby(b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnBumby(generarID(),*this, posicion));
}

void Mundo::agregarZonaSpawnSniper(b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnSniper(generarID(),*this, posicion));
}

void Mundo::agregarZonaSpawnJumpingSniper(b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnJumpingSniper(generarID(),*this, posicion));
}

void Mundo::agregarZonaSpawnBombman(uint IDPuerta, b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnBombman(generarID(), obtenerPuerta(IDPuerta),*this, posicion));
}

void Mundo::agregarZonaSpawnMagnetman(uint IDPuerta, b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnMagnetman(generarID(), obtenerPuerta(IDPuerta),*this, posicion));
}

void Mundo::agregarZonaSpawnSparkman(uint IDPuerta, b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnSparkman(generarID(), obtenerPuerta(IDPuerta),*this, posicion));
}

void Mundo::agregarZonaSpawnRingman(uint IDPuerta, b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnRingman(generarID(), obtenerPuerta(IDPuerta),*this, posicion));
}

void Mundo::agregarZonaSpawnFireman(uint IDPuerta, b2Vec2 posicion)
{
	controladores.push_back(new CajaSpawnFireman(generarID(), obtenerPuerta(IDPuerta),*this, posicion));
}

void Mundo::destruirCuerpos()
{
	std::list<DatosEliminacion>::iterator i = destrucciones.begin();

	while (i != destrucciones.end())	
	{
		switch((*i).categoria)
		{
			case enemigo:
				delete enemigos[(*i).ID];
				enemigos.erase((*i).ID);
				break;
			case powerUp:
				delete powerUps[(*i).ID];
				powerUps.erase((*i).ID);
				break;

			case disparo:
				delete disparos[(*i).ID];
				disparos.erase((*i).ID);
				break;
		}
		i++;
	}

	destrucciones.clear();
}

void Mundo::agregarTareaDiferida(Callback *callback)
{
	tareasDiferidas.push_back(callback);
}

void Mundo::ejecutarTareasDiferidas()
{
	std::list<Callback*>::iterator a = tareasDiferidas.begin();

	while(a != tareasDiferidas.end())
	{
		(*a)->ejecutar();
		delete *a;
		a++;
	}

	tareasDiferidas.clear();
}

bool Mundo::existeMegaman(uint ID)
{
	if(megamanes.find(ID) != megamanes.end())
		return true;
	return false;
}

bool Mundo::existeEnemigo(uint ID)
{
	if(enemigos.find(ID) != enemigos.end())
		return true;
	return false;
}

bool Mundo::existeElemento(uint ID)
{
	if(enemigos.find(ID) != enemigos.end() || disparos.find(ID) != disparos.end() || powerUps.find(ID) != powerUps.end()|| megamanes.find(ID) != megamanes.end())
		return true;
	return false;
}

void Mundo::actualizarCuerpos(real deltaT)
{
	std::map<uint, Megaman*>::const_iterator a = megamanes.begin();
	while(a != megamanes.end())
		(a++)->second->actualizar(deltaT);	

	std::map<uint, Enemigo*>::const_iterator b = enemigos.begin();
	while(b != enemigos.end())
		(b++)->second->actualizar(deltaT);

	std::map<uint, Disparo*>::const_iterator c = disparos.begin();
	while(c != disparos.end())
		(c++)->second->actualizar(deltaT);

	std::map<uint, PowerUp*>::const_iterator d = powerUps.begin();
	while(d != powerUps.end())
		(d++)->second->actualizar(deltaT);

	std::list<CajaAccion*>::const_iterator e = controladores.begin();
	while(e != controladores.end())
		(*e++)->actualizar(deltaT);	

	std::map<uint, Puerta*>::const_iterator f = puertas.begin();
	while(f != puertas.end())
		(f++)->second->actualizar(deltaT);	
}

void Mundo::actualizar(real segundosDesdeUltima)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	
	mundo.Step(segundosDesdeUltima, velocityIterations, positionIterations);
	ejecutarTareasDiferidas();

	actualizarCuerpos(segundosDesdeUltima);

	std::list<CajaAccion*>::const_iterator a = controladores.begin();

	while(a != controladores.end())
		(*a++)->actualizar(segundosDesdeUltima);

	destruirCuerpos();
	
	camara->actualizar(segundosDesdeUltima);
}

std::list<Megaman *> Mundo::obtenerMegamanes(bool incluirMuertos)
{
	std::list<Megaman *> megas;

	std::map<uint, Megaman*>::iterator i = megamanes.begin();

	while(i != megamanes.end())
	{
		if(!i->second->estaMuerta() || incluirMuertos)
			megas.push_back(i->second);
		i++;	
	}

	return megas;
}

#ifndef compiling_server
std::list<Dibujable *> Mundo::elementosEnZona(b2Vec2 posicion, real ancho, real alto)
{
	b2AABB consulta;
	b2Vec2 posicionMegaman;
	
	std::list<Dibujable *> aux;
	ElementosEnZona zona(aux);

	consulta.upperBound = b2Vec2(posicion.x+ancho, posicion.y+alto);
	consulta.lowerBound = posicion;

	mundo.QueryAABB(&zona, consulta);

	return aux;
}
#endif

void Mundo::limpiar(b2Vec2 posicion, real ancho, real alto)
{
	
	/* Limpia (elimina de los mapas) lo que esta fuera del area circular que pasa por todos los vertices del area cuadrada.*/

	real radio = (posicion.x+ancho)*(posicion.x+ancho) +  (posicion.y+alto)*(posicion.y+alto);

	std::map<uint, Enemigo*>::const_iterator b = enemigos.begin();
	while(b != enemigos.end())
	{
		if((b->second->obtenerPosicion() - posicion).LengthSquared() >= radio)
			eliminar(b->second);
		b++;	
	}

	std::map<uint, Disparo*>::const_iterator c = disparos.begin();
	while(c != disparos.end())
	{
		if((c->second->obtenerPosicion()-posicion).LengthSquared() >= radio)
			eliminar(c->second);
		c++;	
	}

	std::map<uint, PowerUp*>::const_iterator d = powerUps.begin();
	while(d != powerUps.end())
	{
		if((d->second->obtenerPosicion()-posicion).LengthSquared() >= radio)
			eliminar(d->second);
		d++;	
	}
}

#ifndef compiling_server
std::list<Dibujable *> Mundo::obtenerElementosCamara()
{
	return elementosEnZona(camara->obtenerPosicion(),camara->obtenerAncho(),camara->obtenerAlto());
}
#endif

#define GENERAR_AGREGAR_SNAPSHOTABLES(_nombreClase,_nombreMapa)\
	{\
		std::map<uint, _nombreClase*>::const_iterator it;\
		for(it= _nombreMapa.begin(); it != _nombreMapa.end(); ++it){\
			mapa[it->first]=it->second;\
		}\
	}\

void Mundo::obtenerSnapshotables(std::map<uint, Snapshotable*> &mapa)
{
	//Marcos refactoricé esto porque con los whiles a veces me tiraba segfault y a veces no. 
	//lo de las macros es porque soy un enfermo.
	if(!terminado){
		GENERAR_AGREGAR_SNAPSHOTABLES(Megaman,megamanes)
		GENERAR_AGREGAR_SNAPSHOTABLES(Enemigo,enemigos)
		GENERAR_AGREGAR_SNAPSHOTABLES(Disparo,disparos)
		GENERAR_AGREGAR_SNAPSHOTABLES(PowerUp,powerUps)
	}
	/*
	std::map<uint, Megaman*>::const_iterator a = megamanes.begin();
	for(a=megamanes.begin(); a!= megamanes.end(); ++a){
		mapa[a->first] = a->second;
	}
	
	std::map<uint, Enemigo*>::const_iterator b = enemigos.begin();
	while(b != enemigos.end())
		mapa[b->first] = (b++)->second;	

	std::map<uint, Disparo*>::const_iterator c = disparos.begin();
	while(c != disparos.end())
		mapa[c->first] = (c++)->second;

	std::map<uint, PowerUp*>::const_iterator d = powerUps.begin();
	while(d != powerUps.end())
		mapa[d->first] = (d++)->second;
	*/
	mapa[estadisticas.obtenerID()] = &estadisticas;//se sincronizan las estadísticas!!
}

void Mundo::obtenerSnapshot(FullSnapshot& en){
	std::map<uint, Snapshotable*> mapa;
	obtenerSnapshotables(mapa);

	FullSnapshot nueva;
	std::map<uint, Snapshotable*>::iterator it;
	for(it=mapa.begin(); it!=mapa.end(); ++it){
		nueva.add((it->second)->getSnapshot());
	}
	en=nueva;
}

/**
 * Inyecta un FullSnapshot.
 * -Los objetos en mundo pero no en el fs, son destruídos
 * -A los objetos en el mundo y en el fs se les inyecta una Snapshot
 * -Los objetos que están sólo en el fs se crean en cualquier estado
 * y se les inyecta una snapshot
 * 
 * Dejo comentadas líneas utilizadas para debugging porque pueden ser útiles
 * 
 * Dos Snapshotables representan al mismo objeto sii su ID y su tipo son iguales.
 * */
void Mundo::inyectarSnapshot(FullSnapshot& fs){
	fs.reiniciarRevisadas();
	/*
	//-----------------------------------------------------------------
	std::cout<<"-------------------actual:---------------------"<<std::endl;
	FullSnapshot fsActual;
	obtenerSnapshot(fsActual);
	fsActual.mostrar();
	//-----------------------------------------------------------------
	std::cout<<"-------------------inyectada:---------------------"<<std::endl;
	fs.mostrar();
	//-----------------------------------------------------------------
	*/
	
	//-----iterar sobre los Snapshotables, encontrar cuales remover y actualizar los que sea necesario
	std::map<uint, Snapshotable*> mapa;
	obtenerSnapshotables(mapa);

	std::map<uint, Snapshotable*>::iterator it;
	std::set<Snapshotable*> a_eliminar;
	for(it=mapa.begin(); it != mapa.end(); ++it){
		Snapshotable* snapshotable =it->second;
		if(fs.existe(*snapshotable)){
			snapshotable->setStateFromSnapshot(fs.get(*snapshotable));
			fs.marcarRevisada(*snapshotable);
		}else{
			//std::cout<<"voy a eliminar un snapshotable porque no existe"<<std::endl;
			//if(snapshotable->getTipo()!=TIPO_MEGAMAN){
				a_eliminar.insert(snapshotable);
				//std::cout<<"Voy a eliminar un snapshotable de tipo "<<snapshotable->getTipo()<<std::endl;
			//}
		}
	}
	
	//-----remover los Snapshotable que estén en mundo y no en fs
	std::set<Snapshotable*>::iterator ite;
	for(ite=a_eliminar.begin(); ite!=a_eliminar.end(); ++ite){
		(*ite)->eliminarse(*this);
	}
	
	//-----crear los snapshotables que no fueron revisados al princípio porque no estaban
	const std::set<const Snapshot*> no_revisadas = fs.noRevisadas();
	std::set<const Snapshot*>::const_iterator itr;
	for(itr = no_revisadas.begin(); itr!=no_revisadas.end(); ++itr){
		agregarDesdeSnapshot(*(*itr));
	}
	
	destruirCuerpos();
}

#define GENERAR_CASE_AGREGAR(clase) \
case TIPO_##clase :\
	agregar(clase::desdeSnapshot(sn,*this));\
	break;

void Mundo::agregarDesdeSnapshot(const Snapshot& sn){
	switch(sn.getTipo()){
		GENERAR_CASE_AGREGAR(Bumby)
		GENERAR_CASE_AGREGAR(Met)
		GENERAR_CASE_AGREGAR(Plasma)
		GENERAR_CASE_AGREGAR(Chispa)
		GENERAR_CASE_AGREGAR(NuevaVida)
		GENERAR_CASE_AGREGAR(CapsulaEnergiaChica)
		GENERAR_CASE_AGREGAR(CapsulaEnergiaGrande)
		GENERAR_CASE_AGREGAR(CapsulaPlasmaChica)
		GENERAR_CASE_AGREGAR(CapsulaPlasmaGrande)
		GENERAR_CASE_AGREGAR(HabilitadorBomba)
		GENERAR_CASE_AGREGAR(HabilitadorIman)
		GENERAR_CASE_AGREGAR(HabilitadorChispa)
		GENERAR_CASE_AGREGAR(HabilitadorAnillo)
		GENERAR_CASE_AGREGAR(HabilitadorFuego)
		GENERAR_CASE_AGREGAR(Anillo)
		GENERAR_CASE_AGREGAR(Fuego)
		GENERAR_CASE_AGREGAR(Iman)
		GENERAR_CASE_AGREGAR(Bomba)
		GENERAR_CASE_AGREGAR(JumpingSniper)
		GENERAR_CASE_AGREGAR(Sniper)
		GENERAR_CASE_AGREGAR(Bombman)
	}
}

Megaman* Mundo::obtenerMegaman(uint posicion){
	std::map<uint, Megaman*>::iterator it = megamanes.begin();
	for(uint i = 0; i < posicion; i++){
		++it;
	}
	return it->second;
}

void Mundo::agregarArma(int tipo_arma){
	estadisticas.agregarArma(tipo_arma);
	
}
