#ifndef DESLOCALIZACION
#define DESLOCALIZACION
#include <locale>
//esta struct sirve para 
//transformar los enteros a 
//strings de forma 
//conveniente para la 
//configuración de los sockets

//FUENTE: http://en.cppreference.com/w/cpp/locale/numpunct/thousands_sep

struct PonerNada : std::numpunct<char>{
	char do_thousands_sep() const { return 'Q';}//separo con Q para que sea obvio si falla
	std::string do_grouping() const { return "";}//sin grupos
};

class ConComa: public std::numpunct<char> {
	protected:
		virtual char do_decimal_point() const {return (char)44;}
};
#endif
