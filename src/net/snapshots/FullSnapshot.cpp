#include "FullSnapshot.h"
#include "../../common/exceptions.h"
#include <map>
#include <vector>
#include <iostream>

void FullSnapshot::deserializar(const FSSerializada& serializada){
	FSSerializada::const_iterator it;
	for(it=serializada.begin(); it!=serializada.end(); ++it){
		add(Snapshot(*it));
	}
}

const Snapshot& FullSnapshot::get(uint id){
	if(snapshots.count(id)==0){
		throw CustomException("No existe un snapshot con ese id asi que no te lo puedo dar");
	}
	
	return snapshots.find(id)->second;
}

void FullSnapshot::add(Snapshot es){
	if(snapshots.count(es.getID())==1){
		throw CustomException("Ya existe un snapshot con ese id y no la quiero pisar");
	}
	snapshots.insert(std::pair<uint,Snapshot>(es.getID(),es));
}

const FSSerializada FullSnapshot::serializar() const{
	FSSerializada resultado;
	SnapshotMap::const_iterator it; 
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

bool FullSnapshot::existe(const Snapshotable& snapshotable) const{
	bool resultado = false;
	uint id = snapshotable.obtenerID();
	if(snapshots.count(id)){
		const Snapshot& sn = snapshots.find(id)->second;
		if(sn.getTipo() == snapshotable.getTipo()){
			resultado = true;
		}
	}
	return resultado;
}

const Snapshot& FullSnapshot::get(const Snapshotable& snapshotable){
	if(!existe(snapshotable)){
		throw CustomException("No existe el snapshotable");
		
	}
	return get(snapshotable.obtenerID());
}

void FullSnapshot::reiniciarRevisadas(){
	SnapshotMap::iterator it;
	for(it=snapshots.begin(); it!=snapshots.end(); ++it){
		no_revisadas.insert(&(it->second));
	}
}
void FullSnapshot::marcarRevisada(Snapshotable& snapshotable){
	const Snapshot* e = &(get(snapshotable));
	no_revisadas.erase(e);
}
const std::set<const Snapshot*> FullSnapshot::noRevisadas(){
	return no_revisadas;
}

void FullSnapshot::mostrar(){
	std::cout<<"------------mostrando fullsnapshot---------__"<<std::endl;
	SnapshotMap::const_iterator it; 
	for(it=snapshots.begin(); it!=snapshots.end(); ++it){
		std::cout<<(it->second).serializar()<<std::endl;
	}
}
