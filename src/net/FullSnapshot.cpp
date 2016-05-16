#include "FullSnapshot.h"
#include "../common/exceptions.h"
#include <map>
#include <vector>

FullSnapshot FullSnapshot::deserializar(const FSSerializada& serializada){
	FSSerializada::const_iterator it;
	for(it=serializada.begin(); it!=serializada.end(); ++it){
		add(Snapshot(*it));
	}
}

const Snapshot& FullSnapshot::get(ID id){
	if(snapshots.count(id)==0){
		throw CustomException("No existe un snapshot con ese id asi que no te lo puedo dar");
	}
	
	return snapshots.find(id)->second;
}

void FullSnapshot::add(const Snapshot& es){
	if(snapshots.count(es.getID())==1){
		throw CustomException("Ya existe un snapshot con ese id y no la quiero pisar");
	}
	snapshots.insert(std::pair<ID,Snapshot>(es.getID(),es));
}

const FSSerializada FullSnapshot::serializar(){
	FSSerializada resultado;
	SnapshotMap::iterator it; 
	for(it=snapshots.begin(); it!=snapshots.end(); ++it){
		resultado.push_back(it->second.serializar());
	}
	//throw CustomException("Todavía no implementado FS::serialize");
	return resultado;
}
FullSnapshot FullSnapshot::desdeSerializada(const FSSerializada& serializada){
	FullSnapshot full;
	full.deserializar(serializada);
	return full;
}
