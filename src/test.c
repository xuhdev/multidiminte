/*
 * Copyright (C) 2013 Hong Xu
 * All rights reserved.
 * 
 * This file is part of MultiDimInte.
 *
 * MultiDimInte is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
 * version.
 * 
 * MultiDimInte is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with MultiDimInte.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/*
 * This is the testing file.
 */
#include <stdio.h>
#include "gmdi.h"

static double test_1_f(const double* x, size_t n, void* p)
{
    return x[n - 1] * x[n - 1];
}

#define test_2_f test_1_f

/*
 * \int_0^2 dy \int_0^1 dx x^2
 *
 * Using gsl_integration_qag and gsl_integration_qng
 */
static int test_1(void)
{
    gmdi_inte_handle            handle = gmdi_create_inte_handle(2);
    gmdi_function_or_constant   fc;
    gmdi_multi_var_function     mvf;
    double                      result;
    int                         ret = 0;

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

    puts("test_1: \\int_0^2 dy \\int_0^1 dx x^2");
    puts("The result should be 2/3");

    gmdi_multi_dimensional_integration(handle);
    puts("Method: gsl_integration_qag");
    printf("result: %e\n", gmdi_handle_get_result(handle));
    printf("abserr: %e\n", gmdi_handle_get_abserr(handle));
    if (fabs(gmdi_handle_get_result(handle) - 2.0/3) >= 1e-7)
    {
        puts("Test failed");
        ret = 1;
    }
    else
        puts("Test passed");

    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 0);
    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 1);

    gmdi_multi_dimensional_integration(handle);
    puts("Method: gsl_integration_qng");
    printf("result: %e\n", gmdi_handle_get_result(handle));
    printf("abserr: %e\n", gmdi_handle_get_abserr(handle));
    if (fabs(gmdi_handle_get_result(handle) - 2.0/3) >= 1e-7)
    {
        puts("Test failed");
        ret = 1;
    }
    else
        puts("Test passed");

    puts("");

    gmdi_free_inte_handle(handle);

    return ret;
}

static double test_2_x1(const double* x, size_t n, void * p)
{
    return *x;
}

/*
 * \int_0^2 dy \int_0^y dx x^2
 */
static int test_2(void)
{
    gmdi_inte_handle            handle = gmdi_create_inte_handle(2);
    gmdi_function_or_constant   fc;
    gmdi_multi_var_function     mvf;
    int                         ret = 0;

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

    printf("Test 2: \\int_0^2 dy \\int_0^y dx x^2\n");
    puts("The result should be 4/3");
    puts("Method: gsl_integration_qag");
    printf("result: %e\n", gmdi_handle_get_result(handle));
    printf("abserr: %e\n", gmdi_handle_get_abserr(handle));

    if (fabs(gmdi_handle_get_result(handle) - 4.0/3) >= 1e-7)
    {
        puts("Test failed");
        ret = 1;
    }
    else
        puts("Test passed");

    puts("");

    gmdi_free_inte_handle(handle);

    return ret;
}


#define test_3_f test_1_f

static double test_3_x1(const double* x, size_t n, void * p)
{
    return *(x + 1);
}


/*
 * \int_1^3 dz \int_0^2 dy \int_0^y dx x^2
 */
static int test_3(void)
{
    gmdi_inte_handle            handle = gmdi_create_inte_handle(3);
    gmdi_function_or_constant   fc;
    gmdi_multi_var_function     mvf;
    int                         ret = 0;

    gmdi_handle_set_key(handle, GSL_INTEG_GAUSS61, 0);
    gmdi_handle_set_key(handle, GSL_INTEG_GAUSS61, 1);
    gmdi_handle_set_key(handle, GSL_INTEG_GAUSS61, 2);
    gmdi_handle_set_epsabs(handle, 0, 0);
    gmdi_handle_set_epsabs(handle, 0, 1);
    gmdi_handle_set_epsabs(handle, 0, 2);
    gmdi_handle_set_epsrel(handle, 1e-7, 0);
    gmdi_handle_set_epsrel(handle, 1e-7, 1);
    gmdi_handle_set_epsrel(handle, 1e-7, 2);
    gmdi_handle_set_limit(handle, 100000, 0);
    gmdi_handle_set_limit(handle, 100000, 1);
    gmdi_handle_set_limit(handle, 100000, 2);
    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 0);
    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 1);
    gmdi_handle_set_inte_func(handle, GMDI_INTE_FUNCTIONS_QAG, 2);

    gmdi_handle_set_x0_constant(handle, 1, 0);
    gmdi_handle_set_x0_constant(handle, 0, 1);
    gmdi_handle_set_x0_constant(handle, 0, 2);

    gmdi_handle_set_x1_constant(handle, 3, 0);
    gmdi_handle_set_x1_constant(handle, 2, 1);

    fc.type = GMDI_FUNCTION_OR_CONSTANT_TYPE_MULTI_VAR_FUNCTION;
    fc.content.mf.function = test_3_x1;
    fc.content.mf.params = NULL;
    gmdi_handle_set_x1(handle, &fc, 2);

    mvf.n = 1;
    mvf.function = test_3_f;
    mvf.params = NULL;
    gmdi_handle_set_kernel(handle, &mvf);

    gmdi_multi_dimensional_integration(handle);

    printf("Test 3: \\int_1^3 dz \\int_0^2 dy \\int_0^y dx x^2\n");
    puts("The result should be 8/3");
    puts("Method: gsl_integration_qag");
    printf("result: %e\n", gmdi_handle_get_result(handle));
    printf("abserr: %e\n", gmdi_handle_get_abserr(handle));

    if (fabs(gmdi_handle_get_result(handle) - 8.0/3) >= 1e-7)
    {
        puts("Test failed");
        ret = 1;
    }
    else
        puts("Test passed");

    puts("");

    gmdi_free_inte_handle(handle);

    return ret;
}

int main(int argc, const char *argv[])
{
    return test_1() || test_2() || test_3();
}
