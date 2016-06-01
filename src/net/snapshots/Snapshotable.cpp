#include "Snapshotable.h"
#include "Snapshot.h"
Snapshot Snapshotable::getSnapshot(){
	Snapshot sn(obtenerID());
	sn.agregarPropiedad(PROP_TIPO,getTipo());
	agregarPropiedadesASnapshot(sn);
	return sn;
}
