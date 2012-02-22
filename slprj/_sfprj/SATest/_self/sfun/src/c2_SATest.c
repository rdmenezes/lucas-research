/* Include files */

#include "blascompat32.h"
#include "SATest_sfun.h"
#include "c2_SATest.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "SATest_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c2_debug_family_names[8] = { "nargin", "nargout", "d1", "d2",
  "d3", "d4", "i", "j" };

/* Function Declarations */
static void initialize_c2_SATest(SFc2_SATestInstanceStruct *chartInstance);
static void initialize_params_c2_SATest(SFc2_SATestInstanceStruct *chartInstance);
static void enable_c2_SATest(SFc2_SATestInstanceStruct *chartInstance);
static void disable_c2_SATest(SFc2_SATestInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_SATest(SFc2_SATestInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_SATest(SFc2_SATestInstanceStruct
  *chartInstance);
static void set_sim_state_c2_SATest(SFc2_SATestInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_SATest(SFc2_SATestInstanceStruct *chartInstance);
static void sf_c2_SATest(SFc2_SATestInstanceStruct *chartInstance);
static void compInitSubchartSimstructsFcn_c2_SATest(SFc2_SATestInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_b_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_c_sf_marshall(void *chartInstanceVoid, void *c2_u);
static real_T c2_emlrt_marshallIn(SFc2_SATestInstanceStruct *chartInstance,
  const mxArray *c2_i, const char_T *c2_name);
static real_T c2_b_emlrt_marshallIn(SFc2_SATestInstanceStruct *chartInstance,
  const mxArray *c2_b_j, const char_T *c2_name);
static uint8_T c2_c_emlrt_marshallIn(SFc2_SATestInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_SATest, const char_T *c2_name);
static void init_dsm_address_info(SFc2_SATestInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_SATest(SFc2_SATestInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_j_not_empty = FALSE;
  chartInstance->c2_is_active_c2_SATest = 0U;
}

static void initialize_params_c2_SATest(SFc2_SATestInstanceStruct *chartInstance)
{
}

static void enable_c2_SATest(SFc2_SATestInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_SATest(SFc2_SATestInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_SATest(SFc2_SATestInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_SATest(SFc2_SATestInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st = NULL;
  const mxArray *c2_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  uint8_T c2_c_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  real_T *c2_i;
  c2_i = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(3));
  c2_hoistedGlobal = *c2_i;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = chartInstance->c2_j;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  if (!chartInstance->c2_j_not_empty) {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_hoistedGlobal = chartInstance->c2_is_active_c2_SATest;
  c2_c_u = c2_c_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 2, c2_d_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_SATest(SFc2_SATestInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  real_T *c2_i;
  c2_i = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  *c2_i = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)),
    "i");
  chartInstance->c2_j = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 1)), "j");
  chartInstance->c2_is_active_c2_SATest = c2_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 2)),
    "is_active_c2_SATest");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_SATest(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_SATest(SFc2_SATestInstanceStruct *chartInstance)
{
}

static void sf_c2_SATest(SFc2_SATestInstanceStruct *chartInstance)
{
  int32_T c2_previousEvent;
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  real_T c2_d_hoistedGlobal;
  real_T c2_d1;
  real_T c2_d2;
  real_T c2_d3;
  real_T c2_d4;
  uint32_T c2_debug_family_var_map[8];
  real_T c2_nargin = 4.0;
  real_T c2_nargout = 1.0;
  real_T c2_i;
  real_T *c2_b_d1;
  real_T *c2_b_i;
  real_T *c2_b_d2;
  real_T *c2_b_d3;
  real_T *c2_b_d4;
  c2_b_d4 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c2_b_d3 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c2_b_d2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_b_i = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_b_d1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0);
  _SFD_DATA_RANGE_CHECK(*c2_b_d1, 0U);
  _SFD_DATA_RANGE_CHECK(*c2_b_i, 1U);
  _SFD_DATA_RANGE_CHECK(*c2_b_d2, 2U);
  _SFD_DATA_RANGE_CHECK(*c2_b_d3, 3U);
  _SFD_DATA_RANGE_CHECK(*c2_b_d4, 4U);
  c2_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0);
  c2_hoistedGlobal = *c2_b_d1;
  c2_b_hoistedGlobal = *c2_b_d2;
  c2_c_hoistedGlobal = *c2_b_d3;
  c2_d_hoistedGlobal = *c2_b_d4;
  c2_d1 = c2_hoistedGlobal;
  c2_d2 = c2_b_hoistedGlobal;
  c2_d3 = c2_c_hoistedGlobal;
  c2_d4 = c2_d_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 8U, 8U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_nargin, c2_b_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c2_nargout, c2_b_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c2_d1, c2_b_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c2_d2, c2_b_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c2_d3, c2_b_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c2_d4, c2_b_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c2_i, c2_b_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c2_j, c2_sf_marshall, 7U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0, 6);
  if (CV_EML_IF(0, 0, !chartInstance->c2_j_not_empty)) {
    _SFD_EML_CALL(0, 7);
    chartInstance->c2_j = 1.0;
    chartInstance->c2_j_not_empty = TRUE;
  }

  _SFD_EML_CALL(0, 10);
  if (CV_EML_COND(0, 0, chartInstance->c2_j == 1.0)) {
    if (CV_EML_COND(0, 1, c2_d1 < 20.0)) {
      CV_EML_MCDC(0, 0, TRUE);
      CV_EML_IF(0, 1, TRUE);
      _SFD_EML_CALL(0, 11);
      chartInstance->c2_j = chartInstance->c2_j + 1.0;
      goto label_1;
    }
  }

  CV_EML_MCDC(0, 0, FALSE);
  CV_EML_IF(0, 1, FALSE);
 label_1:
  ;
  _SFD_EML_CALL(0, 14);
  if (CV_EML_COND(0, 2, chartInstance->c2_j == 2.0)) {
    if (CV_EML_COND(0, 3, c2_d2 < 20.0)) {
      CV_EML_MCDC(0, 1, TRUE);
      CV_EML_IF(0, 2, TRUE);
      _SFD_EML_CALL(0, 15);
      chartInstance->c2_j = chartInstance->c2_j + 1.0;
      goto label_2;
    }
  }

  CV_EML_MCDC(0, 1, FALSE);
  CV_EML_IF(0, 2, FALSE);
 label_2:
  ;
  _SFD_EML_CALL(0, 18);
  if (CV_EML_COND(0, 4, chartInstance->c2_j == 3.0)) {
    if (CV_EML_COND(0, 5, c2_d3 < 20.0)) {
      CV_EML_MCDC(0, 2, TRUE);
      CV_EML_IF(0, 3, TRUE);
      _SFD_EML_CALL(0, 19);
      chartInstance->c2_j = chartInstance->c2_j + 1.0;
      goto label_3;
    }
  }

  CV_EML_MCDC(0, 2, FALSE);
  CV_EML_IF(0, 3, FALSE);
 label_3:
  ;
  _SFD_EML_CALL(0, 22);
  if (CV_EML_COND(0, 6, chartInstance->c2_j == 4.0)) {
    if (CV_EML_COND(0, 7, c2_d4 < 20.0)) {
      CV_EML_MCDC(0, 3, TRUE);
      CV_EML_IF(0, 4, TRUE);
      _SFD_EML_CALL(0, 23);
      chartInstance->c2_j = 1.0;
      goto label_4;
    }
  }

  CV_EML_MCDC(0, 3, FALSE);
  CV_EML_IF(0, 4, FALSE);
 label_4:
  ;
  _SFD_EML_CALL(0, 26);
  c2_i = chartInstance->c2_j;
  _SFD_EML_CALL(0, -26);
  sf_debug_symbol_scope_pop();
  *c2_b_i = c2_i;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0);
  _sfEvent_ = c2_previousEvent;
  sf_debug_check_for_state_inconsistency(_SATestMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void compInitSubchartSimstructsFcn_c2_SATest(SFc2_SATestInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_SATestInstanceStruct *chartInstance;
  chartInstance = (SFc2_SATestInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_b_u = *((real_T *)c2_u);
  c2_b_y = NULL;
  if (!chartInstance->c2_j_not_empty) {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static const mxArray *c2_b_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  real_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_SATestInstanceStruct *chartInstance;
  chartInstance = (SFc2_SATestInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_b_u = *((real_T *)c2_u);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

const mxArray *sf_c2_SATest_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_ResolvedFunctionInfo c2_info[3];
  c2_ResolvedFunctionInfo (*c2_b_info)[3];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i0;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_b_info = (c2_ResolvedFunctionInfo (*)[3])c2_info;
  (*c2_b_info)[0].context = "";
  (*c2_b_info)[0].name = "eq";
  (*c2_b_info)[0].dominantType = "double";
  (*c2_b_info)[0].resolved = "[B]eq";
  (*c2_b_info)[0].fileLength = 0U;
  (*c2_b_info)[0].fileTime1 = 0U;
  (*c2_b_info)[0].fileTime2 = 0U;
  (*c2_b_info)[1].context = "";
  (*c2_b_info)[1].name = "lt";
  (*c2_b_info)[1].dominantType = "double";
  (*c2_b_info)[1].resolved = "[B]lt";
  (*c2_b_info)[1].fileLength = 0U;
  (*c2_b_info)[1].fileTime1 = 0U;
  (*c2_b_info)[1].fileTime2 = 0U;
  (*c2_b_info)[2].context = "";
  (*c2_b_info)[2].name = "plus";
  (*c2_b_info)[2].dominantType = "double";
  (*c2_b_info)[2].resolved = "[B]plus";
  (*c2_b_info)[2].fileLength = 0U;
  (*c2_b_info)[2].fileTime1 = 0U;
  (*c2_b_info)[2].fileTime2 = 0U;
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 3));
  for (c2_i0 = 0; c2_i0 < 3; c2_i0 = c2_i0 + 1) {
    c2_r0 = &c2_info[c2_i0];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->context)), "context",
                    "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r0->name)), "name",
                    "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo", c2_i0);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo", c2_i0);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0);
  return c2_nameCaptureInfo;
}

static const mxArray *c2_c_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  boolean_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_SATestInstanceStruct *chartInstance;
  chartInstance = (SFc2_SATestInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_b_u = *((boolean_T *)c2_u);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static real_T c2_emlrt_marshallIn(SFc2_SATestInstanceStruct *chartInstance,
  const mxArray *c2_i, const char_T *c2_name)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_name, sf_mex_dup(c2_i), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_i);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_SATestInstanceStruct *chartInstance,
  const mxArray *c2_b_j, const char_T *c2_name)
{
  real_T c2_y;
  real_T c2_d1;
  if (mxIsEmpty(c2_b_j)) {
    chartInstance->c2_j_not_empty = FALSE;
  } else {
    chartInstance->c2_j_not_empty = TRUE;
    sf_mex_import(c2_name, sf_mex_dup(c2_b_j), &c2_d1, 1, 0, 0U, 0, 0U, 0);
    c2_y = c2_d1;
  }

  sf_mex_destroy(&c2_b_j);
  return c2_y;
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_SATestInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_SATest, const char_T
  *c2_name)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_name, sf_mex_dup(c2_b_is_active_c2_SATest), &c2_u0, 1, 3, 0U,
                0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_b_is_active_c2_SATest);
  return c2_y;
}

static void init_dsm_address_info(SFc2_SATestInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_SATest_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1989141204U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3318209036U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4264150298U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3115814821U);
}

mxArray *sf_c2_SATest_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(103058585U);
    pr[1] = (double)(3632543791U);
    pr[2] = (double)(4050578879U);
    pr[3] = (double)(1052323326U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  return(mxAutoinheritanceInfo);
}

static mxArray *sf_get_sim_state_info_c2_SATest(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"i\",},{M[4],M[0],T\"j\",S'l','i','p'{{M1x2[51 52],M[0],}}},{M[8],M[0],T\"is_active_c2_SATest\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_SATest_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_SATestInstanceStruct *chartInstance;
    chartInstance = (SFc2_SATestInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_SATestMachineNumber_,
          2,
          1,
          1,
          5,
          0,
          0,
          0,
          0,
          0,
          &(chartInstance->chartNumber),
          &(chartInstance->instanceNumber),
          ssGetPath(S),
          (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_SATestMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_SATestMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_SATestMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"d1");
          _SFD_SET_DATA_PROPS(1,2,0,1,"i");
          _SFD_SET_DATA_PROPS(2,1,1,0,"d2");
          _SFD_SET_DATA_PROPS(3,1,1,0,"d3");
          _SFD_SET_DATA_PROPS(4,1,1,0,"d4");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of EML Model Coverage */
        _SFD_CV_INIT_EML(0,1,5,0,0,0,0,8,4);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,243);
        _SFD_CV_INIT_EML_IF(0,0,55,68,-1,83);
        _SFD_CV_INIT_EML_IF(0,1,85,103,-1,122);
        _SFD_CV_INIT_EML_IF(0,2,124,142,-1,161);
        _SFD_CV_INIT_EML_IF(0,3,163,181,-1,200);
        _SFD_CV_INIT_EML_IF(0,4,202,220,-1,235);

        {
          static int condStart[] = { 88, 96 };

          static int condEnd[] = { 92, 103 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,0,88,103,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 127, 135 };

          static int condEnd[] = { 131, 142 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,127,142,2,2,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 166, 174 };

          static int condEnd[] = { 170, 181 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,2,166,181,2,4,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 205, 213 };

          static int condEnd[] = { 209, 220 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,3,205,220,2,6,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_b_sf_marshall);

        {
          real_T *c2_d1;
          real_T *c2_i;
          real_T *c2_d2;
          real_T *c2_d3;
          real_T *c2_d4;
          c2_d4 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c2_d3 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c2_d2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c2_i = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c2_d1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c2_d1);
          _SFD_SET_DATA_VALUE_PTR(1U, c2_i);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_d2);
          _SFD_SET_DATA_VALUE_PTR(3U, c2_d3);
          _SFD_SET_DATA_VALUE_PTR(4U, c2_d4);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_SATestMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c2_SATest(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_SATestInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c2_SATest((SFc2_SATestInstanceStruct*) chartInstanceVar);
  initialize_c2_SATest((SFc2_SATestInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_SATest(void *chartInstanceVar)
{
  enable_c2_SATest((SFc2_SATestInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_SATest(void *chartInstanceVar)
{
  disable_c2_SATest((SFc2_SATestInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_SATest(void *chartInstanceVar)
{
  sf_c2_SATest((SFc2_SATestInstanceStruct*) chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c2_SATest(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_SATest((SFc2_SATestInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c2_SATest();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

static void sf_internal_set_sim_state_c2_SATest(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_SATest();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_SATest((SFc2_SATestInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c2_SATest(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_SATest(S);
}

static void sf_opaque_set_sim_state_c2_SATest(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_SATest(S, st);
}

static void sf_opaque_terminate_c2_SATest(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_SATestInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_SATest((SFc2_SATestInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c2_SATest((SFc2_SATestInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_SATest(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_SATest((SFc2_SATestInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_SATest(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"SATest","SATest",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"SATest","SATest",2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"SATest","SATest",2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"SATest","SATest",2,4);
      sf_mark_chart_reusable_outputs(S,"SATest","SATest",2,1);
    }

    sf_set_rtw_dwork_info(S,"SATest","SATest",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(463501616U));
  ssSetChecksum1(S,(1205019772U));
  ssSetChecksum2(S,(850057429U));
  ssSetChecksum3(S,(757322635U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_SATest(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "SATest", "SATest",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_SATest(SimStruct *S)
{
  SFc2_SATestInstanceStruct *chartInstance;
  chartInstance = (SFc2_SATestInstanceStruct *)malloc(sizeof
    (SFc2_SATestInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_SATestInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_SATest;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_SATest;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_SATest;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_SATest;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_SATest;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_SATest;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_SATest;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_SATest;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_SATest;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_SATest;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_SATest;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_SATest_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_SATest(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_SATest(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_SATest(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_SATest_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
