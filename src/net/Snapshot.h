#define SNAPSHOT
#ifndef SNAPSHOT
typedef int ID;
typedef std::vector<char> SnapshotSerializada;
typedef std::map<std::string,int> MapaPropiedades;
/**
Full snapshot de una entidad, tiene un ID asociado
*/
class Snapshot{
	public:
	SnapshotSerializada serializar();
	Snapshot(const SnapshotSerializada& serializada);
	Snapshot(ID de);
	
	//éstas deberían estar protegido de alguna forma para que sólo los Snapshotable tengan acceso.
	//protected + herencia?
	void agregarPropiedad(const std::string& nombre, int valor);
	int obtenerPropiedad(const std::string& nombre);
	
	int getID();
	private:
	Snapshot();
	MapaPropiedades propiedades;
	ID id;
	void deserializar(const SnapshotSerializada& serializada);
	
}

#endif