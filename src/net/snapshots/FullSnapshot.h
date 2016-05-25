#ifndef FULLSNAPSHOT
#define FULLSNAPSHOT

#include <map>
#include <vector>
#include "Snapshot.h"
#include "Snapshotable.h"
#include <set>


/**
Representa la full snapshot, con info de todos los entes del mundo en un momento
*/
typedef std::vector<SnapshotSerializada> FSSerializada;
typedef std::map<uint,Snapshot> SnapshotMap;
class FullSnapshot{
	private:
	SnapshotMap snapshots;
	std::set<const Snapshot*> no_revisadas;
	
	FullSnapshot deserializar(const FSSerializada& serializada);
	
	public:
	const Snapshot& get(uint id);//...eliminar!
	const Snapshot& get(const Snapshotable& snapshotable);
	
	void reiniciarRevisadas();
	void marcarRevisada(Snapshotable& snapshotable);
	const std::set<const Snapshot*> noRevisadas();
	
	void add(const Snapshot& es);
	bool existe(const Snapshotable& snapshotable) const;
	const FSSerializada serializar() const;
	static FullSnapshot desdeSerializada(const FSSerializada& serializada);
	
};


#endif
