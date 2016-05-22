#ifndef SNAPSHOTABLE
#define SNAPSHOTABLE
#include "Snapshot.h"
#include "../../mundo/Definiciones.h"
/**
14/5 Defino lo de snapshotable ahora, voy a hacer que vayan y vengan x e y nada más,
después podemos meter la librería que decías
*/
class Snapshotable{
private:
	uint ID;
public:
	Snapshotable(uint ID) : ID(ID){};
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot) = 0;
	virtual void setStateFromSnapshot(const Snapshot& snapshot) = 0;
	uint obtenerID(){return ID;};
	virtual Snapshot getSnapshot(){
		Snapshot sn(obtenerID());
		agregarPropiedadesASnapshot(sn);
		return sn;
	};
};
#endif
