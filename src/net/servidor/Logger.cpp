#include "Logger.h"
#include "../../log4cpp/Category.hh"
#include "../../log4cpp/Appender.hh"
#include "../../log4cpp/FileAppender.hh"
#include "../../log4cpp/OstreamAppender.hh"
#include "../../log4cpp/Layout.hh"
#include "../../log4cpp/BasicLayout.hh"
#include "../../log4cpp/Priority.hh"

Logger::Logger(std::string archivo) : app(new log4cpp::FileAppender("default", archivo)), cat(log4cpp::Category::getInstance(std::string("sub")))
{
	app->setLayout(new log4cpp::BasicLayout());
	cat.addAppender(app);
}

void Logger::log(std::string mensaje)
{
	cat.info(mensaje);
}


Logger serverLog("log.log");

