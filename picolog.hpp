/*
   picolog.hpp - 1.1.0

   Author:
        Paul Meffle

   Summary:
        picolog is a single-file header that implements a simple log class that
        uses stream semantics.

   Revision history:
        1.0   (14.08.2017) initial release
        1.0.1 (12.09.2017) remove summary
        1.0.2 (13.09.2017) add documentation
        1.1.0 (26.09.2017) use operator() to set severity
*/

#ifndef _PICOLOG_HPP
#define _PICOLOG_HPP

#include <sstream>
#include <iomanip>
#include <ctime>

class Log {
public:
        enum Severity {
                Verbose = 0,
                Debug,
                Warning,
                Error
        };

        /**
         * @param os The std::ostream to ouput to
         */
        Log(std::ostream& os);

        /**
         * Outputs the current time followed by a short form of the severity.
         *
         * @param severity The severity to use
         *
         * @return A reference to '*this'
         */
        Log& operator()(const Severity& severity);

        /**
         * Outputs 't' to the stream.
         *
         * @param t The object to log
         *
         * @return A reference to '*this'
         */
        template<class T>
        Log& operator<<(const T& t);

        /**
         * Set the minimum severity for all following output. Output with a
         * severity lower than 'severity' will be ignored.
         *
         * @param severity The new minimum severity
         */
        void setMinSeverity(const Severity& severity);

        typedef std::ostream& (*ostream_manipulator)(std::ostream&);

        /**
         * Required for use with stream manipulators like std::endl.
         *
         * @param om The stream manipulator to pass to 'os'
         *
         * @return A reference to '*this'
         */
        Log& operator<<(ostream_manipulator om);

private:
        std::ostream& os;

        Severity currentSeverity = Verbose;
        Severity minSeverity = Verbose;
};

#endif // _PICOLOG_HPP

#ifdef PICOLOG_IMPL

Log::Log(std::ostream& os)
        : os(os)
{
}

Log& Log::operator()(const Severity& severity)
{
        currentSeverity = severity;

        if (currentSeverity < minSeverity) {
                return *this;
        }

        std::time_t t = std::time(nullptr);
        std::tm* tm = std::localtime(&t);

        os << std::put_time(tm, "%H:%M:%S-");

        switch (severity) {
                case Verbose:
                        os << "ver: ";
                        break;
                case Debug:
                        os << "dbg: ";
                        break;
                case Warning:
                        os << "wrn: ";
                        break;
                case Error:
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
