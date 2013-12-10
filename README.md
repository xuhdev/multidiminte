MultiDimInte
============

MultiDimInte is a library which does multi-dimensional numerical integral by applying GSL one-dimensional integration
function repeatedly. No special trick is used in this library -- this is just a convenient wrapper to write such
integral easily.

Before you decide to use this library, I recommend you to look into [Cuba][] and [Monte Carlo Integration in
GSL][GSLMC]. If they don't work out for you, this library might be good for you.

Currently only the use of `gsl_integration_qag` and `gsl_integration_qng` functions is implemented.

## Installation

This project is based on [cmake][] build system. First install cmake and GSL. Then:

    cd /path/to/multidiminte
    mkdir build
    cd build
    cmake ..
    make && make install

## License

Copyright (C) 2013 Hong Xu

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


[cmake]: http://www.cmake.org
[Cuba]: http://www.feynarts.de/cuba/
[GSLMC]: http://www.gnu.org/software/gsl/manual/html_node/Monte-Carlo-Integration.html
