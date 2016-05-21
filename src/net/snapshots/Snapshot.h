#ifndef SNAPSHOT
#define SNAPSHOT
#include <string>
#include <map>
#include <vector>
#include "../../mundo/Definiciones.h"

typedef uint ID;
typedef std::string SnapshotSerializada;
typedef std::map<std::string,int> MapaPropiedades;
/**
Full snapshot de una entidad, tiene un ID asociado
*/
class Snapshot{
	public:
	SnapshotSerializada serializar();
	Snapshot(const SnapshotSerializada& serializada);
	Snapshot(uint de);
	
	//éstas deberían estar protegido de alguna forma para que sólo los Snapshotable tengan acceso.
	//protected + herencia?
	void agregarPropiedad(const std::string& nombre, int valor);
	int obtenerPropiedad(const std::string& nombre) const;
	
	int getID() const;
	
	private:
	Snapshot();
	MapaPropiedades propiedades;
	uint id;
	void deserializar(const SnapshotSerializada& serializada);
	
};

#endif