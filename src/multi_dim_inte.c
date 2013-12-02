#include <stdio.h>
#include <string.h>
#include <gsl/gsl_integration.h>
#include "gmdi.h"
#include "gmdi_structs.h"

#define CALL_GSL_FUNCTION(gf, x)                    gf.function((x), gf.params)
#define CALL_GMDI_MULTI_VAR_FUNCTION(gmvf, x)       gmvf.function((x), gmvf.n, gmvf.params)

static double call_gmdi_function_or_constant(gmdi_function_or_constant * gfc, const double * x)
{
    switch (gfc->type)
    {
    case GMDI_FUNCTION_OR_CONSTANT_TYPE_CONSTANT:
        return gfc->content.c;
    case GMDI_FUNCTION_OR_CONSTANT_TYPE_FUNCTION:
        return CALL_GSL_FUNCTION(gfc->content.gf, *x);
    case GMDI_FUNCTION_OR_CONSTANT_TYPE_MULTI_VAR_FUNCTION:
        return CALL_GMDI_MULTI_VAR_FUNCTION(gfc->content.mf, x);
    }
}

static double big_g(double y, void* p);

/*
 * call the integration function according to the parameters.
 */
static int call_integration_func(gmdi_multi_dim_inte_param* params)
{
    gmdi_one_inte_param *               oip = params->oip + params->intern.dim;

    int                                 ret;

    double                              inte_limit_low  = call_gmdi_function_or_constant(&oip->x0, params->intern.x);
    double                              inte_limit_high = call_gmdi_function_or_constant(&oip->x1, params->intern.x);

    gsl_function                        gf;

    gf.function = big_g;
    gf.params = params;

    switch (oip->inte_func)
    {
    case GMDI_INTE_FUNCTIONS_QNG:

        break;
    case GMDI_INTE_FUNCTIONS_QAG:

        ret = gsl_integration_qag(&gf,
                inte_limit_low,
                inte_limit_high,
                oip->epsabs,
                oip->epsrel,
                oip->limit,
                oip->key,
                oip->intern.giw,
                params->intern.results + params->intern.dim,
                params->intern.abserrs + params->intern.dim);
        break;
    }

    return ret;
}

static double big_g(double x, void * p)
{
    double                              result = 1.0;
    gmdi_multi_dim_inte_param *         params = (gmdi_multi_dim_inte_param *) p;
    gmdi_one_inte_param *               oip;

    oip = params->oip + params->intern.dim;

    params->intern.x[params->intern.dim] = x;

    if (params->intern.dim < params->n - 1)
    {
        ++ params->intern.dim;

        call_integration_func(params);
        result = params->intern.results[params->intern.dim];

        -- params->intern.dim;
    }

    if (oip->f.function)
        result *= CALL_GMDI_MULTI_VAR_FUNCTION(oip->f, params->intern.x);

    return result;
}

int gmdi_multi_dimensional_integration(gmdi_inte_handle handle)
{
    int                                         ret, i;
    gmdi_multi_dim_inte_param *                 params = (gmdi_multi_dim_inte_param *) handle;

    params->intern.x = calloc(params->n, sizeof(double));
    params->intern.results = calloc(params->n, sizeof(double));
    params->intern.abserrs = calloc(params->n, sizeof(double));
    params->intern.dim = 0;

    for (i = 0; i < params->n; ++ i)
    {
        params->oip[i].intern.giw = gsl_integration_workspace_alloc(params->oip[i].limit);
        params->oip[i].f.n = i + 1;

        if (params->oip[i].x0.type == GMDI_FUNCTION_OR_CONSTANT_TYPE_MULTI_VAR_FUNCTION)
            params->oip[i].x0.content.mf.n = i;
        if (params->oip[i].x1.type == GMDI_FUNCTION_OR_CONSTANT_TYPE_MULTI_VAR_FUNCTION)
            params->oip[i].x1.content.mf.n = i;
    }

    ret = call_integration_func(params);

    params->result = params->intern.results[0];
    params->abserr = params->intern.abserrs[0];

    for (i = 0; i < params->n; ++ i)
        gsl_integration_workspace_free(params->oip[i].intern.giw);

    free(params->intern.x);
    free(params->intern.results);
    free(params->intern.abserrs);

    return ret;
}

