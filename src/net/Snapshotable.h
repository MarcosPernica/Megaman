#ifndef SNAPSHOTABLE
#define SNAPSHOTABLE
#include "Snapshot.h"
/**
14/5 Defino lo de snapshotable ahora, voy a hacer que vayan y vengan x e y nada más,
después podemos meter la librería que decías
*/
class Snapshotable{
	virtual Snapshot getSnapshot() = 0;
	virtual void setStateFromSnapshot(const Snapshot& snapshot) = 0;
	virtual ID getID()=0;
}
#endif