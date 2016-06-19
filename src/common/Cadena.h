#ifndef CADENA
#define CADENA

#include <string>
#include <vector>

class Cadena : public std::string
{
public:
	explicit Cadena(std::string cadena);

	Cadena(const Cadena &cadena);

	explicit Cadena(const char*cadena);

	explicit Cadena(char caracter);

	explicit Cadena(unsigned int numero);

	std::vector<Cadena> partir(Cadena separadores) const;

	bool quitarCaracteres(Cadena caracteres);

	std::vector<unsigned int> buscarCaracteres(unsigned int origen, 
		                                       Cadena delim,
		                                       bool unicoResultado = false) const;
	
	/*Comprime las apariciones contiguas de un caracter en uno solo.*/
	void comprimir(char caracter);

	static void buscarReemplazar(std::string &cadena, char buscar, 
		                char reemplazar);

	operator double();
};

#endif
