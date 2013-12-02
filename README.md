MultiDimInte is a library which does multi-dimensional numerical integral by applying GSL one-dimensional integration
function repeatedly. No special trick is used in this library -- this is just a convenient wrapper to write such
integral easily.

Before you decide to use this library, I recommend you to look into [Cuba][] and [Monte Carlo Integration in
GSL][GSLMC]. If they don't work out for you, this library might be good for you.

Currently this project is still under construction. Only the use of `gsl_integration_qag` function is implemented and
further documentation is needed. Despite the mess here, your interest is still welcome.


[Cuba]: http://www.feynarts.de/cuba/
[GSLMC]: http://www.gnu.org/software/gsl/manual/html_node/Monte-Carlo-Integration.html
