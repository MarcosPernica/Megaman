#include "FullSnapshot.h"
#include <map>
#include <vector>

//-------------NO SÉ SI COMPILA!!!!!!!!!--------------------
FullSnapshot FullSnapshot::deserializar(const FSSerializada& serializada);{
	FSSerializada::const_iterator it;
	for(it=serializada.begin(); it!=serializada.end(); ++it){
		add(it->deserializar());
	}
}

const Snapshot& FullSnapshot::get(ID id){
	if(snapshots[id]==NULL){
		throw CustomException("No existe un snapshot con id: ", id, " asi que no te lo puedo dar");
	}
	
	return snapshots[id];
}

void FullSnapshot::add(const Snapshot& es){
	if(snapshots[id]!=NULL){
		throw CustomException("Ya existe un snapshot con id ", id," y no la quiero pisar");
	}
	snapshots[id]=es;
}

const FSSerializada FullSnapshot::serializar(){
	FSSserializada resultado;
	SnapshotMap::iterator it; 
	for(it=snapshots.begin(); it!=snapshots.end(); ++it){
		resultado.push_back(it->second.serializar());
	}
	//throw CustomException("Todavía no implementado FS::serialize");
	return resultado;
}
static FullSnapshot FullSnapshot::desdeSerializada(const FSSerializada& serializada){
	FullSnapshot full;
	full.deserializar(serializada);
	return full;
}