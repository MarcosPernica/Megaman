#ifndef SNAPSHOT
#define SNAPSHOT
#include <string>
#include <map>
#include <vector>
#include "../../mundo/Definiciones.h"

#define PROP_TIPO "tipo"

//typedef uint ID;
typedef std::string SnapshotSerializada;
typedef std::map<std::string,int> MapaPropiedades;
/**
Full snapshot de una entidad, tiene un ID asociado
*/
class Snapshot{
	public:
	SnapshotSerializada serializar();
	explicit Snapshot(const SnapshotSerializada& serializada);
	explicit Snapshot(uint de);//... mejor: Snapshot(const Snapshotable& de);
	
	//éstas deberían estar protegido de alguna forma para que sólo los Snapshotable tengan acceso.
	//protected + herencia?
	void agregarPropiedad(const std::string& nombre, int valor);
	int obtenerPropiedad(const std::string& nombre) const;
	
	int getID() const;
	int getTipo() const;
	
	private:
	Snapshot();
	MapaPropiedades propiedades;
	uint id;
	void deserializar(const SnapshotSerializada& serializada);
	
};

#endif
