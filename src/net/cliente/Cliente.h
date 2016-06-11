#ifndef CLIENTE
#define CLIENTE
#include "../sockets/ChannelSocket.h"
#include <set>
#include <string>
#include "../../common/Mutex.h"
#include "../sockets/Emisor.h"
class VentanaJuego;
#include "ReceptorCliente.h"
class Jugador;
/**
 * "Singleton-no-Signleton" que representa la aplicación cliente
 * */
class Cliente{
	private:
	Mutex m_pantalla;
	Mutex m_posicion;
	Mutex m_iniciado;
	VentanaJuego& ventana;
	
	ChannelSocket socket;
	int posicion;
	bool flag_iniciado;
	
	ReceptorCliente receptor;
	Emisor emisor;
	
	
	/**
	 * Envia la señal de iniciar la partida
	 * */
	 void iniciarPartida();
	 
	 std::string nombre;
	public:
	void correr();
	
	
	//interfaz para ReceptorCliente
	void agregarEstaba(const std::string& usuario);
	void agregarLlega(const std::string& usuario);
	void definirPosicion(int posicion);
	int obtenerPosicion();
	void iniciar();
	bool iniciado();
	
	void iniciarVentana(const Emisor& emisor, ReceptorCliente& receptor);
	const std::string& obtenerNombre();
	Cliente(VentanaJuego &ventana);
	
	/**
	 * Pide ip y port por cmd, y conecta el Socket
	 * */
	void conectarse(const std::string& nombre);
	
	/**
	 * Le agrega un callback al receptor, 
	 * de esta forma la Ventana puede recibir "eventos" del socket
	 * */
	void agregarCallback(const std::string& tipo_mensaje, CallbackReceptor* callback);
	
	void enviarIniciar(int nivel);
	
	Jugador* configurarNivel(VentanaJuego& ventana ,Mundo& mundo);
	
};
#endif
