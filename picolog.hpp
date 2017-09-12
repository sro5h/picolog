/*
   picolog.hpp - 1.0

   Author:
        Paul Meffle

   Summary:
        picolog is a single-file header that implements a simple log class that
        uses stream semantics.

   Revision history:
        1.0   (14.08.2017) initial release
*/

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
};

#endif // _PICOLOG_HPP

#ifdef PICOLOG_IMPL

Log::Log(std::ostream& os)
        : os(os)
{
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
                        break;
                case ERROR:
                        os << "err: ";
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

/*
   zlib license:

   Copyright (c) 2017 Paul Meffle http://github.com/sro5h
   This software is provided 'as-is', without any express or implied warranty.
   In no event will the authors be held liable for any damages arising from the
   use of this software.
   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:
     1. The origin of this software must not be misrepresented; you must not
        claim that you wrote the original software. If you use this software in
        a product, an acknowledgment in the product documentation would be
        appreciated but is not required.
     2. Altered source versions must be plainly marked as such, and must not be
        misrepresented as being the original software.
     3. This notice may not be removed or altered from any source distribution.
*/
