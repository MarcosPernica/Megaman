#ifndef CALLBACKNUEVACONEXION
#define CALLBACKNUEVACONEXION
#include "ChannelSocket.h"
class CallbackNuevaConexion{
	public:
	virtual void nueva(ChannelSocket* nuevo_channel) = 0;
};

#endif
