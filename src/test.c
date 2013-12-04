#include <stdio.h>
#include "gmdi.h"

static double test_1_f(const double* x, size_t n, void* p)
{
    return x[n - 1] * x[n - 1];
}

#define test_2_f test_1_f

static double test_2_x1(const double* x, size_t n, void * p)
{
    return *x;
}

static void test_1(void)
{
    gmdi_inte_handle            handle = gmdi_create_inte_handle(2);
    gmdi_function_or_constant   fc;
    gmdi_multi_var_function     mvf;

    gmdi_handle_set_key(handle, GSL_INTEG_GAUSS61, 0);
    gmdi_handle_set_key(handle, GSL_INTEG_GAUSS61, 1);
    gmdi_handle_set_epsabs(handle, 0, 0);
    gmdi_handle_set_epsabs(handle, 0, 1);
    gmdi_handle_set_epsrel(handle, 1e-7, 0);
    gmdi_handle_set_epsrel(handle, 1e-7, 1);
    gmdi_handle_set_limit(handle, 100000, 0);
    gmdi_handle_set_limit(handle, 100000, 1);
    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 0);
    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 1);

    fc.type = GMDI_FUNCTION_OR_CONSTANT_TYPE_CONSTANT;
    fc.content.c = 0;
    gmdi_handle_set_x0(handle, &fc, 0);
    gmdi_handle_set_x0(handle, &fc, 1);

    fc.content.c = 1;
    gmdi_handle_set_x1(handle, &fc, 1);

    fc.content.c = 2;
    gmdi_handle_set_x1(handle, &fc, 0);

    mvf.n = 1;
    mvf.function = test_1_f;
    mvf.params = NULL;
    gmdi_handle_set_kernel(handle, &mvf);

    gmdi_multi_dimensional_integration(handle);
    printf("result: %e\n", gmdi_handle_get_result(handle));
    printf("abserr: %e\n", gmdi_handle_get_abserr(handle));

    gmdi_free_inte_handle(handle);
}

static void test_2(void)
{
    gmdi_inte_handle            handle = gmdi_create_inte_handle(2);
    gmdi_function_or_constant   fc;
    gmdi_multi_var_function     mvf;

    gmdi_handle_set_key(handle, GSL_INTEG_GAUSS61, 0);
    gmdi_handle_set_key(handle, GSL_INTEG_GAUSS61, 1);
    gmdi_handle_set_epsabs(handle, 0, 0);
    gmdi_handle_set_epsabs(handle, 0, 1);
    gmdi_handle_set_epsrel(handle, 1e-7, 0);
    gmdi_handle_set_epsrel(handle, 1e-7, 1);
    gmdi_handle_set_limit(handle, 100000, 0);
    gmdi_handle_set_limit(handle, 100000, 1);
    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 0);
    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 1);

    fc.type = GMDI_FUNCTION_OR_CONSTANT_TYPE_CONSTANT;
    fc.content.c = 0;
    gmdi_handle_set_x0(handle, &fc, 0);
    gmdi_handle_set_x0(handle, &fc, 1);

    fc.content.c = 2;
    gmdi_handle_set_x1(handle, &fc, 0);

    fc.type = GMDI_FUNCTION_OR_CONSTANT_TYPE_MULTI_VAR_FUNCTION;
    fc.content.mf.function = test_2_x1;
    fc.content.mf.params = NULL;
    gmdi_handle_set_x1(handle, &fc, 1);

    mvf.n = 1;
    mvf.function = test_2_f;
    mvf.params = NULL;
    gmdi_handle_set_kernel(handle, &mvf);

    gmdi_multi_dimensional_integration(handle);
    printf("result: %e\n", gmdi_handle_get_result(handle));
    printf("abserr: %e\n", gmdi_handle_get_abserr(handle));

    gmdi_free_inte_handle(handle);
}

int main(int argc, const char *argv[])
{
    test_1();
    test_2();

    return 0;
}
