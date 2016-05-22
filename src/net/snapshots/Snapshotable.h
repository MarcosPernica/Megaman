#ifndef SNAPSHOTABLE
#define SNAPSHOTABLE
#include "Snapshot.h"
class Mundo;
#include "../../mundo/Definiciones.h"

#define TIPO_CUERPO 	1//"tipo_cuerpo"
#define TIPO_ENTIDAD 	2//"tipo_entidad"
//#define TIPO_DISPARO 	3//"tipo_disparo"
#define TIPO_BUMBY 		4//"tipo_bumby"
#define TIPO_MEGAMAN 	5//"tipo_megaman"
//#define TIPO_POWERUP 	6//"tipo_powerup"
#define TIPO_MET 		7//"tipo_met"
#define TIPO_PROTEGIDO 	8//"tipo_protegido"

#define TIPO_DISPARO_PLASMA	9
#define TIPO_DISPARO_BOMBA	10


#define TIPO_PWRUP_NUEVA_VIDA		11
#define TIPO_PWRUP_ENRG_CHICA		12
#define TIPO_PWRUP_ENRG_GDE			13
#define TIPO_PWRUP_PLASM_CHICA		14
#define TIPO_PWRUP_PLASM_GDE		15
#define TIPO_PWRUP_HABILITA_BOMBA	16

class Snapshotable{
private:
	uint ID;
public:
	Snapshotable(uint ID) : ID(ID){};
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot) = 0;
	virtual void setStateFromSnapshot(const Snapshot& snapshot) = 0;
	virtual int getTipo() const = 0;
	uint obtenerID() const{return ID;};
	
	virtual Snapshot getSnapshot(){
		Snapshot sn(obtenerID());
		sn.agregarPropiedad(PROP_TIPO,getTipo());
		agregarPropiedadesASnapshot(sn);
		return sn;
	};
	/**
	 * De esta manera me aseguro que todos los snapshotables sepan 
	 * eliminarse de un mundo sin hacer casteo. casi un "Double dispatch".
	 * */
	virtual void eliminarse(Mundo& de) = 0;
};
#endif
