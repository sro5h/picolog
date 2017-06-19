#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

#define LOG Log::logger

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
                os << "-- beginning of log" << std::endl;
        }

        ~Log()
        {
                os << std::endl << std::endl;

                // Report number of errors and warnings
                os << "-- summary" << std::endl;
                os << "-- " << warningCount << " warnings" << std::endl;
                os << "-- " << errorCount << " errors" << std::endl;
        }

        Log& operator<<(const Severity& severity)
        {
                currentSeverity = severity;

                if (currentSeverity < minSeverity) {
                        return *this;
                }

                std::time_t t = std::time(nullptr);
                std::tm* tm = std::localtime(&t);

                os << std::endl << std::put_time(tm, "%H:%M:%S ");

                switch (severity) {
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

                return *this;
        }

        template<class T>
        Log& operator<<(const T& t)
        {
                if (currentSeverity < minSeverity) {
                        return *this;
                }

                os << t;

                return *this;
        }

        Log& v()
        {
                return *this << VERBOSE;
        }

        Log& d()
        {
                return *this << DEBUG;
        }

        Log& w()
        {
                return *this << WARNING;
        }

        Log& e()
        {
                return *this << ERROR;
        }

        void setMinSeverity(const Severity& severity)
        {
                minSeverity = severity;
        }

        /* Singleton */
        static Log logger;

private:
        std::ostream& os;

        Severity currentSeverity = VERBOSE;
        Severity minSeverity = VERBOSE;

        int errorCount = 0;
        int warningCount = 0;
};

Log Log::logger = Log(std::cout);

#endif
