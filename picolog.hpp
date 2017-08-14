#ifndef _PICOLOG_HPP
#define _PICOLOG_HPP

#include <sstream>
#include <iomanip>
#include <ctime>

class Log {
public:
        enum Severity {
                VERBOSE,
                DEBUG,
                WARNING,
                ERROR
        };

        Log(std::ostream& os);

        ~Log();

        Log& operator<<(const Severity& severity);

        template<class T>
        Log& operator<<(const T& t);

        Log& v();

        Log& d();

        Log& w();

        Log& e();

        void setMinSeverity(const Severity& severity);

        typedef std::ostream& (*ostream_manipulator)(std::ostream&);

        Log& operator<<(ostream_manipulator om);

private:
        std::ostream& os;

        Severity currentSeverity = VERBOSE;
        Severity minSeverity = VERBOSE;

        int errorCount = 0;
        int warningCount = 0;
};

#endif // _PICOLOG_HPP

#ifdef PICOLOG_IMPL

Log::Log(std::ostream& os)
        : os(os)
{
}

Log::~Log()
{
        // Report number of errors and warnings
        this->v() << "summary" << std::endl;
        this->v() << warningCount << " warnings" << std::endl;
        this->v() << errorCount << " errors" << std::endl;
}

Log& Log::operator<<(const Severity& severity)
{
        currentSeverity = severity;

        if (currentSeverity < minSeverity) {
                return *this;
        }

        std::time_t t = std::time(nullptr);
        std::tm* tm = std::localtime(&t);

        os << std::put_time(tm, "%H:%M:%S-");

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
Log& Log::operator<<(const T& t)
{
        if (currentSeverity < minSeverity) {
                return *this;
        }

        os << t;

        return *this;
}

Log& Log::v()
{
        return *this << VERBOSE;
}

Log& Log::d()
{
        return *this << DEBUG;
}

Log& Log::w()
{
        return *this << WARNING;
}

Log& Log::e()
{
        return *this << ERROR;
}

void Log::setMinSeverity(const Severity& severity)
{
        minSeverity = severity;
}

Log& Log::operator<<(ostream_manipulator om)
{
        return operator<< <ostream_manipulator> (om);
}

#endif // PICOLOG_IMPL
