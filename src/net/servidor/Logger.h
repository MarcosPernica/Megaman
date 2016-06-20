#ifndef LOGGER
#define LOGGER

#include "../../log4cpp/Category.hh"
#include "../../log4cpp/Appender.hh"
#include "../../log4cpp/FileAppender.hh"
#include "../../log4cpp/OstreamAppender.hh"
#include "../../log4cpp/Layout.hh"
#include "../../log4cpp/BasicLayout.hh"
#include "../../log4cpp/Priority.hh"

#include <string>

class Logger
{
private:
	log4cpp::Appender *app;
	log4cpp::Category& cat;
public:
	Logger(std::string archivo);
	void log(std::string mensaje);
};

extern Logger serverLog;

#endif
