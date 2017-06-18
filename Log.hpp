#ifndef LOG_HPP
#define LOG_HPP

#include<iostream>
#include<sstream>
#include<iomanip>
#include<ctime>

class Log {
public:
        enum Severity {
                VERBOSE,
                DEBUG,
                WARNING,
                ERROR
        };

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
                        case VERBOSE:
                                os << "ver: ";
                                break;
                        case DEBUG:
                                os << "dbg: ";
                                break;
                        case WARNING:
                                os << "wrn: ";
                                warningCount++;
                                break;
                        case ERROR:
                                os << "err: ";
                                errorCount++;
                                break;
                }

                return os;
        }

        /* Singleton */
        static Log logger;

        static std::ostream& v()
        {
                return logger.log(VERBOSE);
        }

        static std::ostream& d()
        {
                return logger.log(DEBUG);
        }

        static std::ostream& w()
        {
                return logger.log(WARNING);
        }

        static std::ostream& e()
        {
                return logger.log(ERROR);
        }

private:
        std::ostream& os;

        int errorCount = 0;
        int warningCount = 0;
};

Log Log::logger = Log(std::cout);

#endif
