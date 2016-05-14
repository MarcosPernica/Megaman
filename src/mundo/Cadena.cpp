#include "Cadena.h"
#include <stdlib.h>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <sstream>

Cadena::Cadena(std::string cadena) : std::string(cadena)
{
}

Cadena::Cadena(const Cadena &cadena) : std::string(cadena)
{
}

Cadena::Cadena(const char *cadena) : std::string(cadena)
{
}

Cadena::Cadena(char caracter)
{
	assign(&caracter);
}

Cadena::Cadena(unsigned int numero)
{
	std::ostringstream flujo;

	flujo << numero;

	assign(flujo.str());
}

std::vector<unsigned int> Cadena::buscarCaracteres(unsigned int origen,
		                                           Cadena delim,
		                                           bool unicoResultado) const
{
	std::vector<unsigned int>posiciones;
	bool noTexto = true;

	for (unsigned int i = origen; i < this->size(); i++)
	{
		if (this->at(i) == '"' && this->at(i - 1) != '\\')
		{
			noTexto = !noTexto;
			continue;
		}

		if (delim.find_first_of(this->at(i)) != std::string::npos && noTexto)
		{
			posiciones.push_back(i);
			if (unicoResultado)
				break;
		}
	}

	return posiciones;
}

void Cadena::comprimir(char caracter)
{
	for (unsigned int i = 0, a = 0; i < this->size(); i++)
	{
		if (this->at(i) != caracter)
		{
			if ((i - a) > 1)
			{
				a += 2;
				this->erase(a, i - a);
			}
			a = i;
		}
	}
}

void Cadena::buscarReplazar(char buscar, char reemplazar)
{
	for (unsigned int i = 0; i < size(); i++)
		if (at(i) == buscar)
			at(i) = reemplazar;
}

Cadena::operator double()
{
	return strtod(this->c_str(),NULL);
}

std::vector<Cadena> Cadena::partir(Cadena delim) const
{
	unsigned a, i;
	std::vector<Cadena> partes;
	Cadena aux("");


	bool noTexto = true;

	for (i = 0, a = 0; i < this->size(); i++)
	{
		if (this->at(i) == '"' && this->at(i - 1) != '\\')
		{
			noTexto = !noTexto;
			continue;
		}

		if (noTexto &&  delim.find_first_of(this->at(i)) != std::string::npos)
		{
			aux = Cadena(this->substr(a, i - a));
			if (i - a != 0)
				partes.push_back(aux);
			partes.push_back(Cadena(this->substr(i,1)));
			a = i + 1;
		}
	}

	if (i != a)
		partes.push_back(Cadena(this->substr(a)));


	return partes;
}

bool Cadena::quitarCaracteres(Cadena caracteres)
{
	std::vector<unsigned int> posicion;

	posicion = buscarCaracteres(0, caracteres);

	for (unsigned int i = 0; i < posicion.size(); i++)
		this->erase(posicion.at(i));

	if (posicion.size())
		return true;
	return false;
}
