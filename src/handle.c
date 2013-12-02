#include <string.h>
#include "gmdi.h"
#include "gmdi_structs.h"

/*
 * Initialize gmdi_inte_handle
 */
gmdi_inte_handle gmdi_create_inte_handle(size_t n)
{
    gmdi_multi_dim_inte_param * ret;

    ret = (gmdi_multi_dim_inte_param * ) malloc(sizeof(gmdi_multi_dim_inte_param));
    memset(ret, 0, sizeof(gmdi_multi_dim_inte_param));
    
    ret->n = n;
    ret->oip = (gmdi_one_inte_param *) calloc(n, sizeof(gmdi_one_inte_param));

    return ret;
}

/*
 * Destroy gmdi_inte_handle
 */
void gmdi_destroy_inte_handle(gmdi_inte_handle * handle)
{
    free(((gmdi_multi_dim_inte_param * )handle)->oip);

    free(handle);
}

void gmdi_handle_set_key(gmdi_inte_handle handle, int key, size_t n)
{
    ((gmdi_multi_dim_inte_param *) handle)->oip[n].key = key;
}

void gmdi_handle_set_epsabs(gmdi_inte_handle handle, double epsabs, size_t n)
{
    ((gmdi_multi_dim_inte_param *) handle)->oip[n].epsabs = epsabs;
}

void gmdi_handle_set_epsrel(gmdi_inte_handle handle, double epsrel, size_t n)
{
    ((gmdi_multi_dim_inte_param *) handle)->oip[n].epsrel = epsrel;
}

void gmdi_handle_set_limit(gmdi_inte_handle handle, double limit, size_t n)
{
    ((gmdi_multi_dim_inte_param *) handle)->oip[n].limit = limit;
}

void gmdi_handle_set_inte_func(gmdi_inte_handle handle, GMDI_INTE_FUNCTIONS inte_func, size_t n)
{
    ((gmdi_multi_dim_inte_param *) handle)->oip[n].inte_func = inte_func;
}

void gmdi_handle_set_x0(gmdi_inte_handle handle, const gmdi_function_or_constant * x0, size_t n)
{
    ((gmdi_multi_dim_inte_param *) handle)->oip[n].x0 = *x0;
}

void gmdi_handle_set_x1(gmdi_inte_handle handle, const gmdi_function_or_constant * x1, size_t n)
{
    ((gmdi_multi_dim_inte_param *) handle)->oip[n].x1 = *x1;
}

void gmdi_handle_set_f(gmdi_inte_handle handle, const gmdi_multi_var_function * f, size_t n)
{
    ((gmdi_multi_dim_inte_param *) handle)->oip[n].f = *f;
}

void gmdi_handle_set_kernel(gmdi_inte_handle handle, const gmdi_multi_var_function * f)
{
    gmdi_multi_dim_inte_param * params = (gmdi_multi_dim_inte_param *) handle;
    params->oip[params->n - 1].f = *f;
}

double gmdi_handle_get_result(gmdi_inte_handle handle)
{
    return ((gmdi_multi_dim_inte_param *) handle)->result;
}

double gmdi_handle_get_abserr(gmdi_inte_handle handle)
{
    return ((gmdi_multi_dim_inte_param *) handle)->abserr;
}
