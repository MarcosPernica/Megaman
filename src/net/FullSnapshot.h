#ifndef FULLSNAPSHOT
#define FULLSNAPSHOT

#include <map>
#include <vector>
#include "Snapshot.h"


/**
Representa la full snapshot, con info de todos los entes del mundo en un momento
*/
typedef std::vector<SnapshotSerializada> FSSerializada;
typedef std::map<ID,Snapshot> SnapshotMap;
class FullSnapshot{
	private:
	SnapshotMap snapshots;
	FullSnapshot deserializar(const FSSerializada& serializada);
	
	public:
	const Snapshot& get(ID id);
	void add(const Snapshot& es);
	const FSSerializada serializar();
	static FullSnapshot desdeSerializada(const FSSerializada& serializada);
	
};


#endif
