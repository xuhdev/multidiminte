#ifndef GMDI_H_
# define GMDI_H_

#include <gsl/gsl_integration.h>

typedef enum ENUM_GMDI_INTE_FUNCTIONS
{
    GMDI_INTE_FUNCTIONS_QNG = 1,
    GMDI_INTE_FUNCTIONS_QAG,
} GMDI_INTE_FUNCTIONS;

typedef enum ENUM_GMDI_FUNCTION_OR_CONSTANT_TYPE
{
    GMDI_FUNCTION_OR_CONSTANT_TYPE_CONSTANT = 1,
    GMDI_FUNCTION_OR_CONSTANT_TYPE_FUNCTION,
    GMDI_FUNCTION_OR_CONSTANT_TYPE_MULTI_VAR_FUNCTION,
} GMDI_FUNCTION_OR_CONSTANT_TYPE;

typedef struct struct_gmdi_multi_var_function
{
    double (*function) (const double* v, size_t n, void* p);
    size_t   n;
    void*    params;
} gmdi_multi_var_function;

typedef struct struct_gmdi_function_or_constant
{
    GMDI_FUNCTION_OR_CONSTANT_TYPE  type;
    union
    {
        gsl_function                gf;
        gmdi_multi_var_function     mf;
        double                      c;
    } content;
} gmdi_function_or_constant;

typedef void *      gmdi_inte_handle;

gmdi_inte_handle gmdi_create_inte_handle(size_t n);
void gmdi_destroy_inte_handle(gmdi_inte_handle * handle);
int gmdi_multi_dimensional_integration(gmdi_inte_handle handle);
void gmdi_handle_set_key(gmdi_inte_handle handle, int key, size_t n);
void gmdi_handle_set_epsabs(gmdi_inte_handle handle, double epsabs, size_t n);
void gmdi_handle_set_epsrel(gmdi_inte_handle handle, double epsrel, size_t n);
void gmdi_handle_set_limit(gmdi_inte_handle handle, double limit, size_t n);
void gmdi_handle_set_inte_func(gmdi_inte_handle handle, GMDI_INTE_FUNCTIONS inte_func, size_t n);
void gmdi_handle_set_x0(gmdi_inte_handle handle, const gmdi_function_or_constant * x0, size_t n);
void gmdi_handle_set_x1(gmdi_inte_handle handle, const gmdi_function_or_constant * x1, size_t n);
void gmdi_handle_set_f(gmdi_inte_handle handle, const gmdi_multi_var_function * f, size_t n);
void gmdi_handle_set_kernel(gmdi_inte_handle handle, const gmdi_multi_var_function * f);
double gmdi_handle_get_result(gmdi_inte_handle handle);
double gmdi_handle_get_abserr(gmdi_inte_handle handle);

#endif /* GMDI_H_ */
