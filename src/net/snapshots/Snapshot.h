#ifndef SNAPSHOT
#define SNAPSHOT
#include <string>
#include <map>
#include <vector>
#include "../../mundo/Definiciones.h"
#include "../../mundo/Orientaciones.h"
class Disparo;

#define PROP_TIPO "tipo"

#define SN_AGREGAR_PROPIEDAD(variable) sn.agregarPropiedad(#variable, variable)
#define SN_OBTENER_PROPIEDAD(variable) sn.obtenerPropiedad(#variable, variable)

//typedef uint ID;
typedef std::string SnapshotSerializada;
typedef std::map<std::string,int> MapaPropiedades;

/**
Full snapshot de una entidad, tiene un ID asociado
*/
class Snapshot{
	public:
	SnapshotSerializada serializar() const;
	explicit Snapshot(const SnapshotSerializada& serializada);
	explicit Snapshot(uint de);//... mejor: Snapshot(const Snapshotable& de);
	
	//-------------------int----------------------------------//
	void agregarPropiedad(const std::string& nombre, int valor);
	void obtenerPropiedad(const std::string& nombre, int& ponerEn) const;
	int obtenerPropiedad(const std::string& nombre) const;
	
	//-------------------uint----------------------------------//
	void agregarPropiedad(const std::string& nombre, uint valor);
	void obtenerPropiedad(const std::string& nombre, uint& ponerEn) const;
	
	//-------------------ushort----------------------------------//
	void agregarPropiedad(const std::string& nombre, ushort valor);
	void obtenerPropiedad(const std::string& nombre, ushort& ponerEn) const;
	
	//-------------------bool--------------------------------//
	void agregarPropiedad(const std::string& nombre, bool valor);
	void obtenerPropiedad(const std::string& nombre, bool& ponerEn) const;
	
	//-------------------real--------------------------------//
	void agregarPropiedad(const std::string& nombre, real valor);
	void obtenerPropiedad(const std::string& nombre, real& ponerEn) const;
	
	//-------------------char--------------------------------//
	void agregarPropiedad(const std::string& nombre, char valor);
	void obtenerPropiedad(const std::string& nombre, char& ponerEn) const;
	
	//--------------------Orientacion-------------------------//
	void agregarPropiedad(const std::string& nombre, Orientaciones valor);
	void obtenerPropiedad(const std::string& nombre, Orientaciones& ponerEn) const;
	
	//-------------------Arma*--------------------------------//
	void agregarPropiedad(const std::string& nombre, Disparo* valor);
	/**
	 * Esto crea una nueva Arma y borra la que esté en ponerEn!!
	 * */
	void obtenerPropiedad(const std::string& nombre, Disparo*& ponerEn) const;
	
	
	int getID() const;
	int getTipo() const;
	
	private:
	Snapshot();
	MapaPropiedades propiedades;
	uint id;
	void deserializar(const SnapshotSerializada& serializada);
	
};

#endif
