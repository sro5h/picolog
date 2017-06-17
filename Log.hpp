#ifndef LOG_HPP
#define LOG_HPP

#include<iostream>
#include<sstream>
#include<iomanip>
#include<ctime>

#define LOG_VER Log::logger.log(eVerbose)
#define LOG_DEB Log::logger.log(eDebug)
#define LOG_WRN Log::logger.log(eWarning)
#define LOG_ERR Log::logger.log(eError)

enum Severity
{
        eVerbose,
        eDebug,
        eWarning,
        eError
};

class Log
{
public:
        static Log logger;

        Log(std::ostream& os)
                : os(os)
        {
                os << "log initialized" << std::endl;
        }

        ~Log()
        {
                os << std::endl << std::endl << std::endl;

                // Report number of errors and warnings
                os << warningCount << " warnings" << std::endl;
                os << errorCount << " errors" << std::endl;
        }

        std::ostream& log(Severity severity)
        {
                std::time_t t = std::time(nullptr);
                std::tm* tm = std::localtime(&t);

                os << std::endl << std::put_time(tm, "%H:%M:%S ");

                switch(severity) {
                        case eVerbose:
                                os << "ver: ";
                                break;
                        case eDebug:
                                os << "dbg: ";
                                break;
                        case eWarning:
                                os << "wrn: ";
                                warningCount++;
                                break;
                        case eError:
                                os << "err: ";
                                errorCount++;
                                break;
                }

                return os;
        }

private:
        std::ostream& os;

        int errorCount = 0;
        int warningCount = 0;
};

Log Log::logger = Log(std::cout);

#endif
