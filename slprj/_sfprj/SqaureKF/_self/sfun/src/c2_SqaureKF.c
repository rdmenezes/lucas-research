/* Include files */

#include "blascompat32.h"
#include "SqaureKF_sfun.h"
#include "c2_SqaureKF.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "SqaureKF_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c2_debug_family_names[15] = { "v", "vw", "omega", "theta",
  "d", "d_upwind", "d_downwind", "nargin", "nargout", "d1", "d2", "d3", "d4",
  "i", "j" };

/* Function Declarations */
static void initialize_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance);
static void initialize_params_c2_SqaureKF(SFc2_SqaureKFInstanceStruct
  *chartInstance);
static void enable_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance);
static void disable_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_SqaureKF(SFc2_SqaureKFInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_SqaureKF(SFc2_SqaureKFInstanceStruct
  *chartInstance);
static void set_sim_state_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance);
static void sf_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance);
static void compInitSubchartSimstructsFcn_c2_SqaureKF
  (SFc2_SqaureKFInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshall(void *chartInstanceVoid, void *c2_u);
static const mxArray *c2_b_sf_marshall(void *chartInstanceVoid, void *c2_u);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[21]);
static const mxArray *c2_c_sf_marshall(void *chartInstanceVoid, void *c2_u);
static real_T c2_emlrt_marshallIn(SFc2_SqaureKFInstanceStruct *chartInstance,
  const mxArray *c2_i, const char_T *c2_name);
static real_T c2_b_emlrt_marshallIn(SFc2_SqaureKFInstanceStruct *chartInstance,
  const mxArray *c2_b_j, const char_T *c2_name);
static uint8_T c2_c_emlrt_marshallIn(SFc2_SqaureKFInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_SqaureKF, const char_T *c2_name);
static void init_dsm_address_info(SFc2_SqaureKFInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_j_not_empty = FALSE;
  chartInstance->c2_is_active_c2_SqaureKF = 0U;
}

static void initialize_params_c2_SqaureKF(SFc2_SqaureKFInstanceStruct
  *chartInstance)
{
}

static void enable_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_SqaureKF(SFc2_SqaureKFInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_SqaureKF(SFc2_SqaureKFInstanceStruct
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
  c2_c_hoistedGlobal = chartInstance->c2_is_active_c2_SqaureKF;
  c2_c_u = c2_c_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c2_y, 2, c2_d_y);
  sf_mex_assign(&c2_st, c2_y);
  return c2_st;
}

static void set_sim_state_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance,
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
  chartInstance->c2_is_active_c2_SqaureKF = c2_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 2)),
    "is_active_c2_SqaureKF");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_SqaureKF(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance)
{
}

static void sf_c2_SqaureKF(SFc2_SqaureKFInstanceStruct *chartInstance)
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
  uint32_T c2_debug_family_var_map[15];
  real_T c2_v;
  real_T c2_vw;
  real_T c2_omega;
  real_T c2_theta;
  real_T c2_d;
  real_T c2_d_upwind;
  real_T c2_d_downwind;
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
  sf_debug_symbol_scope_push_eml(0U, 15U, 15U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_v, c2_b_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c2_vw, c2_b_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c2_omega, c2_b_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c2_theta, c2_b_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c2_d, c2_b_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c2_d_upwind, c2_b_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c2_d_downwind, c2_b_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c2_nargin, c2_b_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c2_nargout, c2_b_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c2_d1, c2_b_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&c2_d2, c2_b_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&c2_d3, c2_b_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c2_d4, c2_b_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(&c2_i, c2_b_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c2_j, c2_sf_marshall, 14U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0, 6);
  if (CV_EML_IF(0, 0, !chartInstance->c2_j_not_empty)) {
    _SFD_EML_CALL(0, 7);
    chartInstance->c2_j = 1.0;
    chartInstance->c2_j_not_empty = TRUE;
  }

  /* d = 40;  */
  _SFD_EML_CALL(0, 11);
  c2_v = 12.0;
  _SFD_EML_CALL(0, 12);
  c2_vw = 5.0;
  _SFD_EML_CALL(0, 13);
  c2_omega = 0.38;
  _SFD_EML_CALL(0, 14);
  c2_theta = 1.5707963267948966;
  _SFD_EML_CALL(0, 15);
  c2_d = 31.578947368421048;
  _SFD_EML_CALL(0, 16);
  c2_d_upwind = 30.0;

  /* (v-vw/2)/omega * tan(theta/2); */
  _SFD_EML_CALL(0, 17);
  c2_d_downwind = 30.0;

  /* (v+vw)/omega * tan(theta/2); */
  _SFD_EML_CALL(0, 20);
  if (CV_EML_COND(0, 0, chartInstance->c2_j == 1.0)) {
    if (CV_EML_COND(0, 1, c2_d1 < c2_d_downwind)) {
      CV_EML_MCDC(0, 0, TRUE);
      CV_EML_IF(0, 1, TRUE);

      /* bodge factor for !90 turn */
      _SFD_EML_CALL(0, 21);
      chartInstance->c2_j = chartInstance->c2_j + 1.0;
      goto label_1;
    }
  }

  CV_EML_MCDC(0, 0, FALSE);
  CV_EML_IF(0, 1, FALSE);
 label_1:
  ;
  _SFD_EML_CALL(0, 24);
  if (CV_EML_COND(0, 2, chartInstance->c2_j == 2.0)) {
    if (CV_EML_COND(0, 3, c2_d2 < c2_d_downwind)) {
      CV_EML_MCDC(0, 1, TRUE);
      CV_EML_IF(0, 2, TRUE);
      _SFD_EML_CALL(0, 25);
      chartInstance->c2_j = chartInstance->c2_j + 1.0;
      goto label_2;
    }
  }

  CV_EML_MCDC(0, 1, FALSE);
  CV_EML_IF(0, 2, FALSE);
 label_2:
  ;
  _SFD_EML_CALL(0, 28);
  if (CV_EML_COND(0, 4, chartInstance->c2_j == 3.0)) {
    if (CV_EML_COND(0, 5, c2_d3 < c2_d_upwind)) {
      CV_EML_MCDC(0, 2, TRUE);
      CV_EML_IF(0, 3, TRUE);
      _SFD_EML_CALL(0, 29);
      chartInstance->c2_j = chartInstance->c2_j + 1.0;
      goto label_3;
    }
  }

  CV_EML_MCDC(0, 2, FALSE);
  CV_EML_IF(0, 3, FALSE);
 label_3:
  ;
  _SFD_EML_CALL(0, 32);
  if (CV_EML_COND(0, 6, chartInstance->c2_j == 4.0)) {
    if (CV_EML_COND(0, 7, c2_d4 < c2_d_upwind)) {
      CV_EML_MCDC(0, 3, TRUE);
      CV_EML_IF(0, 4, TRUE);
      _SFD_EML_CALL(0, 33);
      chartInstance->c2_j = 1.0;
      goto label_4;
    }
  }

  CV_EML_MCDC(0, 3, FALSE);
  CV_EML_IF(0, 4, FALSE);
 label_4:
  ;
  _SFD_EML_CALL(0, 36);
  c2_i = chartInstance->c2_j;
  _SFD_EML_CALL(0, -36);
  sf_debug_symbol_scope_pop();
  *c2_b_i = c2_i;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0);
  _sfEvent_ = c2_previousEvent;
  sf_debug_check_for_state_inconsistency(_SqaureKFMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void compInitSubchartSimstructsFcn_c2_SqaureKF
  (SFc2_SqaureKFInstanceStruct *chartInstance)
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
  SFc2_SqaureKFInstanceStruct *chartInstance;
  chartInstance = (SFc2_SqaureKFInstanceStruct *)chartInstanceVoid;
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
  SFc2_SqaureKFInstanceStruct *chartInstance;
  chartInstance = (SFc2_SqaureKFInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_b_u = *((real_T *)c2_u);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

const mxArray *sf_c2_SqaureKF_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_ResolvedFunctionInfo c2_info[21];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i0;
  c2_ResolvedFunctionInfo *c2_r0;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 21));
  for (c2_i0 = 0; c2_i0 < 21; c2_i0 = c2_i0 + 1) {
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

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[21])
{
  c2_info[0].context = "";
  c2_info[0].name = "pi";
  c2_info[0].dominantType = "";
  c2_info[0].resolved = "[B]pi";
  c2_info[0].fileLength = 0U;
  c2_info[0].fileTime1 = 0U;
  c2_info[0].fileTime2 = 0U;
  c2_info[1].context = "";
  c2_info[1].name = "mrdivide";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[1].fileLength = 432U;
  c2_info[1].fileTime1 = 1277751822U;
  c2_info[1].fileTime2 = 0U;
  c2_info[2].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[2].name = "nargin";
  c2_info[2].dominantType = "";
  c2_info[2].resolved = "[B]nargin";
  c2_info[2].fileLength = 0U;
  c2_info[2].fileTime1 = 0U;
  c2_info[2].fileTime2 = 0U;
  c2_info[3].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[3].name = "ge";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved = "[B]ge";
  c2_info[3].fileLength = 0U;
  c2_info[3].fileTime1 = 0U;
  c2_info[3].fileTime2 = 0U;
  c2_info[4].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[4].name = "isscalar";
  c2_info[4].dominantType = "double";
  c2_info[4].resolved = "[B]isscalar";
  c2_info[4].fileLength = 0U;
  c2_info[4].fileTime1 = 0U;
  c2_info[4].fileTime2 = 0U;
  c2_info[5].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c2_info[5].name = "rdivide";
  c2_info[5].dominantType = "double";
  c2_info[5].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[5].fileLength = 403U;
  c2_info[5].fileTime1 = 1245106020U;
  c2_info[5].fileTime2 = 0U;
  c2_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[6].name = "gt";
  c2_info[6].dominantType = "double";
  c2_info[6].resolved = "[B]gt";
  c2_info[6].fileLength = 0U;
  c2_info[6].fileTime1 = 0U;
  c2_info[6].fileTime2 = 0U;
  c2_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[7].name = "isa";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved = "[B]isa";
  c2_info[7].fileLength = 0U;
  c2_info[7].fileTime1 = 0U;
  c2_info[7].fileTime2 = 0U;
  c2_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c2_info[8].name = "eml_div";
  c2_info[8].dominantType = "double";
  c2_info[8].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[8].fileLength = 4918U;
  c2_info[8].fileTime1 = 1267067010U;
  c2_info[8].fileTime2 = 0U;
  c2_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c2_info[9].name = "isinteger";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved = "[B]isinteger";
  c2_info[9].fileLength = 0U;
  c2_info[9].fileTime1 = 0U;
  c2_info[9].fileTime2 = 0U;
  c2_info[10].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m!eml_fldiv";
  c2_info[10].name = "isreal";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved = "[B]isreal";
  c2_info[10].fileLength = 0U;
  c2_info[10].fileTime1 = 0U;
  c2_info[10].fileTime2 = 0U;
  c2_info[11].context = "";
  c2_info[11].name = "tan";
  c2_info[11].dominantType = "double";
  c2_info[11].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tan.m";
  c2_info[11].fileLength = 324U;
  c2_info[11].fileTime1 = 1203451646U;
  c2_info[11].fileTime2 = 0U;
  c2_info[12].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/tan.m";
  c2_info[12].name = "eml_scalar_tan";
  c2_info[12].dominantType = "double";
  c2_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_tan.m";
  c2_info[12].fileLength = 487U;
  c2_info[12].fileTime1 = 1203451616U;
  c2_info[12].fileTime2 = 0U;
  c2_info[13].context = "";
  c2_info[13].name = "mtimes";
  c2_info[13].dominantType = "double";
  c2_info[13].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[13].fileLength = 3425U;
  c2_info[13].fileTime1 = 1251035472U;
  c2_info[13].fileTime2 = 0U;
  c2_info[14].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[14].name = "strcmp";
  c2_info[14].dominantType = "char";
  c2_info[14].resolved = "[B]strcmp";
  c2_info[14].fileLength = 0U;
  c2_info[14].fileTime1 = 0U;
  c2_info[14].fileTime2 = 0U;
  c2_info[15].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[15].name = "size";
  c2_info[15].dominantType = "double";
  c2_info[15].resolved = "[B]size";
  c2_info[15].fileLength = 0U;
  c2_info[15].fileTime1 = 0U;
  c2_info[15].fileTime2 = 0U;
  c2_info[16].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[16].name = "eq";
  c2_info[16].dominantType = "double";
  c2_info[16].resolved = "[B]eq";
  c2_info[16].fileLength = 0U;
  c2_info[16].fileTime1 = 0U;
  c2_info[16].fileTime2 = 0U;
  c2_info[17].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[17].name = "class";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved = "[B]class";
  c2_info[17].fileLength = 0U;
  c2_info[17].fileTime1 = 0U;
  c2_info[17].fileTime2 = 0U;
  c2_info[18].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[18].name = "not";
  c2_info[18].dominantType = "logical";
  c2_info[18].resolved = "[B]not";
  c2_info[18].fileLength = 0U;
  c2_info[18].fileTime1 = 0U;
  c2_info[18].fileTime2 = 0U;
  c2_info[19].context = "";
  c2_info[19].name = "lt";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved = "[B]lt";
  c2_info[19].fileLength = 0U;
  c2_info[19].fileTime1 = 0U;
  c2_info[19].fileTime2 = 0U;
  c2_info[20].context = "";
  c2_info[20].name = "plus";
  c2_info[20].dominantType = "double";
  c2_info[20].resolved = "[B]plus";
  c2_info[20].fileLength = 0U;
  c2_info[20].fileTime1 = 0U;
  c2_info[20].fileTime2 = 0U;
}

static const mxArray *c2_c_sf_marshall(void *chartInstanceVoid, void *c2_u)
{
  const mxArray *c2_y = NULL;
  boolean_T c2_b_u;
  const mxArray *c2_b_y = NULL;
  SFc2_SqaureKFInstanceStruct *chartInstance;
  chartInstance = (SFc2_SqaureKFInstanceStruct *)chartInstanceVoid;
  c2_y = NULL;
  c2_b_u = *((boolean_T *)c2_u);
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c2_y, c2_b_y);
  return c2_y;
}

static real_T c2_emlrt_marshallIn(SFc2_SqaureKFInstanceStruct *chartInstance,
  const mxArray *c2_i, const char_T *c2_name)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_name, sf_mex_dup(c2_i), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_i);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_SqaureKFInstanceStruct *chartInstance,
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

static uint8_T c2_c_emlrt_marshallIn(SFc2_SqaureKFInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_SqaureKF, const
  char_T *c2_name)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_name, sf_mex_dup(c2_b_is_active_c2_SqaureKF), &c2_u0, 1, 3,
                0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_b_is_active_c2_SqaureKF);
  return c2_y;
}

static void init_dsm_address_info(SFc2_SqaureKFInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_SqaureKF_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2492613893U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1684665624U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1635731303U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3130311500U);
}

mxArray *sf_c2_SqaureKF_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(3921987259U);
    pr[1] = (double)(3108834861U);
    pr[2] = (double)(1633653103U);
    pr[3] = (double)(1706633563U);
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

static mxArray *sf_get_sim_state_info_c2_SqaureKF(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"i\",},{M[4],M[0],T\"j\",S'l','i','p'{{M1x2[51 52],M[0],}}},{M[8],M[0],T\"is_active_c2_SqaureKF\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_SqaureKF_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_SqaureKFInstanceStruct *chartInstance;
    chartInstance = (SFc2_SqaureKFInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_SqaureKFMachineNumber_,
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
          init_script_number_translation(_SqaureKFMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_SqaureKFMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_SqaureKFMachineNumber_,
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
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,473);
        _SFD_CV_INIT_EML_IF(0,0,55,68,-1,83);
        _SFD_CV_INIT_EML_IF(0,1,260,286,-1,332);
        _SFD_CV_INIT_EML_IF(0,2,334,360,-1,379);
        _SFD_CV_INIT_EML_IF(0,3,381,405,-1,424);
        _SFD_CV_INIT_EML_IF(0,4,426,450,-1,465);

        {
          static int condStart[] = { 263, 271 };

          static int condEnd[] = { 267, 286 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,0,263,286,2,0,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 337, 345 };

          static int condEnd[] = { 341, 360 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,337,360,2,2,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 384, 392 };

          static int condEnd[] = { 388, 405 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,2,384,405,2,4,&(condStart[0]),&(condEnd[0]),3,
                                &(pfixExpr[0]));
        }

        {
          static int condStart[] = { 429, 437 };

          static int condEnd[] = { 433, 450 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,3,429,450,2,6,&(condStart[0]),&(condEnd[0]),3,
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
      sf_debug_reset_current_state_configuration(_SqaureKFMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c2_SqaureKF(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_SqaureKFInstanceStruct*) chartInstanceVar)
    ->S,0);
  initialize_params_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*) chartInstanceVar);
  initialize_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_SqaureKF(void *chartInstanceVar)
{
  enable_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_SqaureKF(void *chartInstanceVar)
{
  disable_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_SqaureKF(void *chartInstanceVar)
{
  sf_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*) chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c2_SqaureKF(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c2_SqaureKF();/* state var info */
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

static void sf_internal_set_sim_state_c2_SqaureKF(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_SqaureKF();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c2_SqaureKF(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_SqaureKF(S);
}

static void sf_opaque_set_sim_state_c2_SqaureKF(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_SqaureKF(S, st);
}

static void sf_opaque_terminate_c2_SqaureKF(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_SqaureKFInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_SqaureKF(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_SqaureKF((SFc2_SqaureKFInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_SqaureKF(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"SqaureKF","SqaureKF",2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"SqaureKF","SqaureKF",2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"SqaureKF","SqaureKF",2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"SqaureKF","SqaureKF",2,4);
      sf_mark_chart_reusable_outputs(S,"SqaureKF","SqaureKF",2,1);
    }

    sf_set_rtw_dwork_info(S,"SqaureKF","SqaureKF",2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(4044075232U));
  ssSetChecksum1(S,(873936769U));
  ssSetChecksum2(S,(1622682478U));
  ssSetChecksum3(S,(1784683580U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_SqaureKF(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "SqaureKF", "SqaureKF",2);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_SqaureKF(SimStruct *S)
{
  SFc2_SqaureKFInstanceStruct *chartInstance;
  chartInstance = (SFc2_SqaureKFInstanceStruct *)malloc(sizeof
    (SFc2_SqaureKFInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_SqaureKFInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_SqaureKF;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_SqaureKF;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_SqaureKF;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_SqaureKF;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_SqaureKF;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_SqaureKF;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_SqaureKF;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_SqaureKF;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_SqaureKF;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_SqaureKF;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_SqaureKF;
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

void c2_SqaureKF_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_SqaureKF(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_SqaureKF(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_SqaureKF(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_SqaureKF_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
