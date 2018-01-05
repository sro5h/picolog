picolog
=======
A simple c++ log class that uses stream semantics.

Installation
------------
Copy `picolog.hpp` into your projects include path. Done.

How to use
----------
Either use the `log` function to get a reference to a `Log` instance using
`std::cout`:
~~~c++
pico::log().d() << "This is message number " << 4 << std::endl;
~~~

Or create your own `Log` with using a different `ostream`:
~~~c++
std::ofstream file;
file.open("test.txt");

pico::Log log(file);
log.d() << "This is a test" << std::endl;

// Don't forget to close the file when you are done with logging
file.close();
~~~

User types can easily be logged by overloading `operator<<`:
~~~c++
pico::Log& operator<<(Log& log, const UserType& u)
{
        return log << u.a << "," << u.b;
}

UserType u = { "test", 2.5f };
log().d() << "A user type: " << u << std::endl;
~~~

Build the example
-----------------
You can use the Makefile and type `make all` or use a simple g++ command:
~~~
g++ -I. example.cpp -Wall -Wpedantic
~~~

License
-------
picolog uses the [zlib license](https://www.zlib.net/zlib_license.html) that
is shipped with the header file.
