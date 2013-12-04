#ifndef GMDI_H_
# define GMDI_H_

#include <gsl/gsl_integration.h>

/*  used for specify the integration function of each dimension of the integration. */
typedef enum ENUM_GMDI_INTE_FUNCTIONS
{
    GMDI_INTE_FUNCTIONS_QNG = 1, /* gsl_integration_qng */
    GMDI_INTE_FUNCTIONS_QAG, /* gsl_integration_qag */
} GMDI_INTE_FUNCTIONS;

/* the type of gmdi_function_or_constant::type */
typedef enum ENUM_GMDI_FUNCTION_OR_CONSTANT_TYPE
{
    GMDI_FUNCTION_OR_CONSTANT_TYPE_CONSTANT = 1,
    GMDI_FUNCTION_OR_CONSTANT_TYPE_FUNCTION,
    GMDI_FUNCTION_OR_CONSTANT_TYPE_MULTI_VAR_FUNCTION,
} GMDI_FUNCTION_OR_CONSTANT_TYPE;

/* Multivariate function. Similar to gsl_function, but for multivariate function. */
typedef struct struct_gmdi_multi_var_function
{
    double (*function) (const double* v, size_t n, void* p); /* The function itself. */
    size_t   n;     /* Number of variables */
    void*    params; /* parameters */
} gmdi_multi_var_function;

/* Used to specify a function or a constant. */
typedef struct struct_gmdi_function_or_constant
{
    GMDI_FUNCTION_OR_CONSTANT_TYPE  type; /* Constant, Function or Multivariate Function? */
    union
    {
        gsl_function                gf; /* function */
        gmdi_multi_var_function     mf; /* multivariate function */
        double                      c;  /* constant */
    } content;
} gmdi_function_or_constant;

typedef void *      gmdi_inte_handle;       /* handle of an integration */

/* Create an handle */
gmdi_inte_handle gmdi_create_inte_handle(size_t n);

/* Free the handle */
void gmdi_free_inte_handle(gmdi_inte_handle * handle);

/* Do the integration */
int gmdi_multi_dimensional_integration(gmdi_inte_handle handle);

/* Set the key of the integration of the nth dimension */
void gmdi_handle_set_key(gmdi_inte_handle handle, int key, size_t n);

/* Set the epsabs of the integration of the nth dimension */
void gmdi_handle_set_epsabs(gmdi_inte_handle handle, double epsabs, size_t n);

/* Set the epsrel of the integration of the nth dimension */
void gmdi_handle_set_epsrel(gmdi_inte_handle handle, double epsrel, size_t n);

/* Set the limit of the integration of the nth dimension */
void gmdi_handle_set_limit(gmdi_inte_handle handle, double limit, size_t n);

/* Set the inte_func of the integration of the nth dimension */
void gmdi_handle_set_inte_func(gmdi_inte_handle handle, GMDI_INTE_FUNCTIONS inte_func, size_t n);

/* Set the x0 of the integration of the nth dimension */
void gmdi_handle_set_x0(gmdi_inte_handle handle, const gmdi_function_or_constant * x0, size_t n);

/* Set the x1 of the integration of the nth dimension */
void gmdi_handle_set_x1(gmdi_inte_handle handle, const gmdi_function_or_constant * x1, size_t n);

/* Set the f of the integration of the nth dimension */
void gmdi_handle_set_f(gmdi_inte_handle handle, const gmdi_multi_var_function * f, size_t n);

/* Set the main integration kernel of the integration */
void gmdi_handle_set_kernel(gmdi_inte_handle handle, const gmdi_multi_var_function * f);

/* Obtain the result */
double gmdi_handle_get_result(gmdi_inte_handle handle);

/* Obtain the abserr */
double gmdi_handle_get_abserr(gmdi_inte_handle handle);

#endif /* GMDI_H_ */
