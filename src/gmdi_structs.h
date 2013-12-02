#ifndef GMDI_STRUCTS_H_

#define GMDI_STRUCTS_H_

#include <gsl/gsl_integration.h>
#include "gmdi.h"

/* The param of one integral */
typedef struct struct_gmdi_one_inte_param
{
    gmdi_function_or_constant           x0;     /* Integration low limit */
    gmdi_function_or_constant           x1;     /* Integration high limit */
    double                              limit;
    double                              epsrel; /* relative tolerance */
    double                              epsabs; /* absolute tolerance */
    int                                 key;
    GMDI_INTE_FUNCTIONS                 inte_func;  /* Which GSL integration function to use? */
    gmdi_multi_var_function             f;          /* function to be integrated */

    /* used internally. */
    struct
    {
        gsl_integration_workspace *         giw;
    } intern;

} gmdi_one_inte_param;

typedef struct struct_gmdi_multi_dim_inte_param
{
    size_t                              n; /* integral dimension */

    gmdi_one_inte_param *               oip;

    /* output result */
    double                              result;
    double                              abserr;
    size_t                              neval;

    /* used internally */
    struct
    {
        size_t                              dim;            /* which dim are we working on now? */
        double*                             x;              /* Value of the high dimensional x */
        double*                             results;
        double*                             abserrs;
    } intern;
} gmdi_multi_dim_inte_param;


#endif /* GMDI_STRUCTS_H_ */
