#ifndef CMYLOGGER_H
#define CMYLOGGER_H

#include <QObject>
#include <QCoreApplication>


#include <log4qt/logger.h>
#include <log4qt/basicconfigurator.h>
#include <log4qt/propertyconfigurator.h>

#define print_Log(logLevel, message) g_myLogger.printOutMessage(logLevel, __FILE__, __LINE__, message)

enum LOGLEVEL
{
    LEVEL_DEBUG = 96,
    LEVEL_INFO = 128,
    LEVEL_WARN = 150,
    LEVEL_ERROR = 182,
    LEVEL_OFF_INT = 255
};

class CMyLogger : public QObject
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER
public:
    CMyLogger()
    {
        // 一个简单的基础配置        
        Log4Qt::BasicConfigurator::configure();
    }
    void configFile(QString filePath)
    {


        if (QFile::exists(filePath))
        {
            Log4Qt::PropertyConfigurator::configureAndWatch(filePath);
        }
    }

    void printOutMessage(int logLevel, const char *file, const int line, const QString &message)
    {
        const QString data = "[" + QString(file) + " : " + QString::number(line) + "] >>> " + message;

        switch (logLevel)
        {
        case Log4Qt::Level::DEBUG_INT:
            logger()->debug(data);
            break;
        case Log4Qt::Level::INFO_INT:
            logger()->info(data);
            break;
        case Log4Qt::Level::WARN_INT:
            logger()->warn(data);
            break;
        case Log4Qt::Level::ERROR_INT:
            logger()->error(data);
            break;
        default:
            break;
        }
        return;
    }
};


extern CMyLogger g_myLogger;

#endif // CMYLOGGER_H

#if 0
# 定义 rootLogger
#log=E:/#log4j.rootLogger=WARN, FILE
# 定义 fileAppender
#log4j.appender.FILE=org.apache.log4j.FileAppender
#log4j.appender.FILE.File=${log}/out.log
# 为 fileAppender 定义 layout
#log4j.appender.FILE.layout=org.apache.log4j.PatternLayout
#log4j.appender.FILE.layout.conversionPattern={%-d{yyyy-MM-dd HH:mm:ss}} [%p] >>> %m%n

#ERROR > WARN > INFO > DEBUG
log4j.rootLogger=DEBUG, CONSOLE
log4j.appender.CONSOLE=org.apache.log4j.ConsoleAppender
log4j.appender.CONSOLE.layout=org.apache.log4j.PatternLayout
log4j.appender.CONSOLE.layout.ConversionPattern={%-d{yyyy-MM-dd HH:mm:ss}} [%p] >>> %m%n
#endif
