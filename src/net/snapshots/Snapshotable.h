#ifndef SNAPSHOTABLE
#define SNAPSHOTABLE
class Snapshot;
class Mundo;
#include "../../mundo/Definiciones.h"

#define TIPO_CUERPO 	1//"tipo_cuerpo" habría que volarlos...
#define TIPO_ENTIDAD 	2//"tipo_entidad"
//#define TIPO_DISPARO 	3//"tipo_disparo"
#define TIPO_Bumby 		4//"tipo_bumby"
#define TIPO_Megaman 	5//"tipo_megaman"
//#define TIPO_POWERUP 	6//"tipo_powerup"
#define TIPO_Met 		7//"tipo_met"
//#define TIPO_PROTEGIDO 	8//"tipo_protegido"

#define TIPO_Plasma	9
#define TIPO_Chispa	10

#define TIPO_NuevaVida				11
#define TIPO_CapsulaEnergiaChica	12
#define TIPO_CapsulaEnergiaGrande	13
#define TIPO_CapsulaPlasmaChica		14
#define TIPO_CapsulaPlasmaGrande	15
#define TIPO_HabilitadorBomba		16
#define TIPO_HabilitadorIman		17
#define TIPO_HabilitadorChispa		18
#define TIPO_HabilitadorAnillo		19
#define TIPO_HabilitadorFuego		20

#define TIPO_Anillo	21
#define TIPO_Fuego	22
#define TIPO_Iman	23
#define TIPO_Bomba	24

#define TIPO_JumpingSniper	25
#define TIPO_Sniper			26
#define TIPO_Bombman		27

#define GENERAR_GET_TIPO(clase) virtual int getTipo() const {return TIPO_ ## clase;}

class Snapshotable{
private:
	uint ID;
public:
	Snapshotable(uint ID) : ID(ID){};
	virtual void agregarPropiedadesASnapshot(Snapshot& snapshot) = 0;
	virtual void setStateFromSnapshot(const Snapshot& snapshot) = 0;
	virtual int getTipo() const = 0;
	uint obtenerID() const{return ID;};
	
	virtual Snapshot getSnapshot();
	/**
	 * De esta manera me aseguro que todos los snapshotables sepan 
	 * eliminarse de un mundo sin hacer casteo. casi un "Double dispatch".
	 * */
	virtual void eliminarse(Mundo& de) = 0;
};
#endif
