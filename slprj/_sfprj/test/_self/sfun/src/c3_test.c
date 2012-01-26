/* Include files */

#include "blascompat32.h"
#include "test_sfun.h"
#include "c3_test.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "test_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c3_debug_family_names[17] = { "ellA", "ellB", "dLat", "dLng",
  "a", "c", "r", "nargin", "nargout", "lat1", "lng1", "lat2", "lng2", "N", "E",
  "d", "theta" };

/* Function Declarations */
static void initialize_c3_test(SFc3_testInstanceStruct *chartInstance);
static void initialize_params_c3_test(SFc3_testInstanceStruct *chartInstance);
static void enable_c3_test(SFc3_testInstanceStruct *chartInstance);
static void disable_c3_test(SFc3_testInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_test(SFc3_testInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_test(SFc3_testInstanceStruct
  *chartInstance);
static void set_sim_state_c3_test(SFc3_testInstanceStruct *chartInstance, const
  mxArray *c3_st);
static void finalize_c3_test(SFc3_testInstanceStruct *chartInstance);
static void sf_c3_test(SFc3_testInstanceStruct *chartInstance);
static void c3_c3_test(SFc3_testInstanceStruct *chartInstance);
static void compInitSubchartSimstructsFcn_c3_test(SFc3_testInstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber);
static void c3_eml_error(SFc3_testInstanceStruct *chartInstance);
static real_T c3_atan2(SFc3_testInstanceStruct *chartInstance, real_T c3_y,
  real_T c3_x);
static void c3_eml_scalar_eg(SFc3_testInstanceStruct *chartInstance);
static real_T c3_mpower(SFc3_testInstanceStruct *chartInstance, real_T c3_a);
static const mxArray *c3_sf_marshall(void *chartInstanceVoid, void *c3_u);
static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[39]);
static const mxArray *c3_b_sf_marshall(void *chartInstanceVoid, void *c3_u);
static real_T c3_emlrt_marshallIn(SFc3_testInstanceStruct *chartInstance, const
  mxArray *c3_E, const char_T *c3_name);
static uint8_T c3_b_emlrt_marshallIn(SFc3_testInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_test, const char_T *c3_name);
static void init_dsm_address_info(SFc3_testInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_test(SFc3_testInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c3_is_active_c3_test = 0U;
}

static void initialize_params_c3_test(SFc3_testInstanceStruct *chartInstance)
{
}

static void enable_c3_test(SFc3_testInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c3_test(SFc3_testInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c3_update_debugger_state_c3_test(SFc3_testInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c3_test(SFc3_testInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st = NULL;
  const mxArray *c3_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_u;
  const mxArray *c3_b_y = NULL;
  real_T c3_b_hoistedGlobal;
  real_T c3_b_u;
  const mxArray *c3_c_y = NULL;
  real_T c3_c_hoistedGlobal;
  real_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  real_T c3_d_hoistedGlobal;
  real_T c3_d_u;
  const mxArray *c3_e_y = NULL;
  uint8_T c3_e_hoistedGlobal;
  uint8_T c3_e_u;
  const mxArray *c3_f_y = NULL;
  real_T *c3_E;
  real_T *c3_N;
  real_T *c3_d;
  real_T *c3_theta;
  c3_theta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_d = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c3_E = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_N = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellarray(5));
  c3_hoistedGlobal = *c3_E;
  c3_u = c3_hoistedGlobal;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 0, c3_b_y);
  c3_b_hoistedGlobal = *c3_N;
  c3_b_u = c3_b_hoistedGlobal;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_c_hoistedGlobal = *c3_d;
  c3_c_u = c3_c_hoistedGlobal;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 2, c3_d_y);
  c3_d_hoistedGlobal = *c3_theta;
  c3_d_u = c3_d_hoistedGlobal;
  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_d_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 3, c3_e_y);
  c3_e_hoistedGlobal = chartInstance->c3_is_active_c3_test;
  c3_e_u = c3_e_hoistedGlobal;
  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", &c3_e_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c3_y, 4, c3_f_y);
  sf_mex_assign(&c3_st, c3_y);
  return c3_st;
}

static void set_sim_state_c3_test(SFc3_testInstanceStruct *chartInstance, const
  mxArray *c3_st)
{
  const mxArray *c3_u;
  real_T *c3_E;
  real_T *c3_N;
  real_T *c3_d;
  real_T *c3_theta;
  c3_theta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_d = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c3_E = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_N = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = TRUE;
  c3_u = sf_mex_dup(c3_st);
  *c3_E = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 0)),
    "E");
  *c3_N = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
    "N");
  *c3_d = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 2)),
    "d");
  *c3_theta = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u,
    3)), "theta");
  chartInstance->c3_is_active_c3_test = c3_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 4)), "is_active_c3_test");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_test(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_test(SFc3_testInstanceStruct *chartInstance)
{
}

static void sf_c3_test(SFc3_testInstanceStruct *chartInstance)
{
  int32_T c3_previousEvent;
  real_T *c3_N;
  real_T *c3_lat1;
  real_T *c3_lng1;
  real_T *c3_E;
  real_T *c3_lat2;
  real_T *c3_lng2;
  real_T *c3_d;
  real_T *c3_theta;
  c3_theta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_d = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c3_lng2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_lat2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_E = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_lng1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c3_lat1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c3_N = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0);
  _SFD_DATA_RANGE_CHECK(*c3_N, 0U);
  _SFD_DATA_RANGE_CHECK(*c3_lat1, 1U);
  _SFD_DATA_RANGE_CHECK(*c3_lng1, 2U);
  _SFD_DATA_RANGE_CHECK(*c3_E, 3U);
  _SFD_DATA_RANGE_CHECK(*c3_lat2, 4U);
  _SFD_DATA_RANGE_CHECK(*c3_lng2, 5U);
  _SFD_DATA_RANGE_CHECK(*c3_d, 6U);
  _SFD_DATA_RANGE_CHECK(*c3_theta, 7U);
  c3_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  c3_c3_test(chartInstance);
  _sfEvent_ = c3_previousEvent;
  sf_debug_check_for_state_inconsistency(_testMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c3_c3_test(SFc3_testInstanceStruct *chartInstance)
{
  real_T c3_hoistedGlobal;
  real_T c3_b_hoistedGlobal;
  real_T c3_c_hoistedGlobal;
  real_T c3_d_hoistedGlobal;
  real_T c3_lat1;
  real_T c3_lng1;
  real_T c3_lat2;
  real_T c3_lng2;
  uint32_T c3_debug_family_var_map[17];
  real_T c3_ellA;
  real_T c3_ellB;
  real_T c3_dLat;
  real_T c3_dLng;
  real_T c3_a;
  real_T c3_c;
  real_T c3_r;
  real_T c3_nargin = 4.0;
  real_T c3_nargout = 4.0;
  real_T c3_N;
  real_T c3_E;
  real_T c3_d;
  real_T c3_theta;
  real_T c3_b_a;
  real_T c3_y;
  real_T c3_A;
  real_T c3_x;
  real_T c3_b_x;
  real_T c3_c_x;
  real_T c3_c_a;
  real_T c3_b_y;
  real_T c3_b_A;
  real_T c3_d_x;
  real_T c3_e_x;
  real_T c3_f_x;
  real_T c3_d_a;
  real_T c3_c_y;
  real_T c3_c_A;
  real_T c3_g_x;
  real_T c3_h_x;
  real_T c3_i_x;
  real_T c3_e_a;
  real_T c3_d_y;
  real_T c3_d_A;
  real_T c3_j_x;
  real_T c3_k_x;
  real_T c3_l_x;
  real_T c3_e_A;
  real_T c3_m_x;
  real_T c3_n_x;
  real_T c3_o_x;
  real_T c3_e_y;
  real_T c3_p_x;
  real_T c3_q_x;
  real_T c3_r_x;
  real_T c3_f_A;
  real_T c3_s_x;
  real_T c3_t_x;
  real_T c3_u_x;
  real_T c3_f_y;
  real_T c3_v_x;
  real_T c3_w_x;
  real_T c3_x_x;
  real_T c3_f_a;
  real_T c3_b;
  real_T c3_g_y;
  real_T c3_y_x;
  real_T c3_ab_x;
  real_T c3_bb_x;
  real_T c3_cb_x;
  real_T c3_db_x;
  real_T c3_eb_x;
  real_T c3_g_a;
  real_T c3_b_b;
  real_T c3_h_y;
  real_T c3_g_A;
  real_T c3_fb_x;
  real_T c3_gb_x;
  real_T c3_hb_x;
  real_T c3_i_y;
  real_T c3_ib_x;
  real_T c3_jb_x;
  real_T c3_kb_x;
  real_T c3_h_a;
  real_T c3_c_b;
  real_T c3_j_y;
  real_T c3_h_A;
  real_T c3_lb_x;
  real_T c3_mb_x;
  real_T c3_nb_x;
  real_T c3_k_y;
  real_T c3_ob_x;
  real_T c3_pb_x;
  real_T c3_qb_x;
  real_T c3_i_a;
  real_T c3_d_b;
  real_T c3_l_y;
  real_T c3_rb_x;
  real_T c3_sb_x;
  real_T c3_tb_x;
  real_T c3_ub_x;
  real_T c3_vb_x;
  real_T c3_wb_x;
  real_T c3_e_b;
  real_T c3_i_A;
  real_T c3_xb_x;
  real_T c3_yb_x;
  real_T c3_ac_x;
  real_T c3_m_y;
  real_T c3_bc_x;
  real_T c3_cc_x;
  real_T c3_dc_x;
  real_T c3_f_b;
  real_T c3_n_y;
  real_T c3_j_A;
  real_T c3_ec_x;
  real_T c3_fc_x;
  real_T c3_gc_x;
  real_T c3_o_y;
  real_T c3_hc_x;
  real_T c3_ic_x;
  real_T c3_jc_x;
  real_T c3_g_b;
  real_T c3_p_y;
  real_T c3_kc_x;
  real_T c3_lc_x;
  real_T c3_mc_x;
  real_T c3_B;
  real_T c3_q_y;
  real_T c3_r_y;
  real_T c3_s_y;
  real_T c3_j_a;
  real_T c3_h_b;
  real_T c3_nc_x;
  real_T c3_oc_x;
  real_T c3_pc_x;
  real_T c3_qc_x;
  real_T c3_rc_x;
  real_T c3_sc_x;
  real_T c3_k_a;
  real_T c3_i_b;
  real_T c3_t_y;
  real_T c3_tc_x;
  real_T c3_uc_x;
  real_T c3_vc_x;
  real_T c3_wc_x;
  real_T c3_xc_x;
  real_T c3_yc_x;
  real_T c3_l_a;
  real_T c3_j_b;
  real_T c3_u_y;
  real_T c3_ad_x;
  real_T c3_bd_x;
  real_T c3_cd_x;
  real_T c3_dd_x;
  real_T c3_ed_x;
  real_T c3_fd_x;
  real_T c3_m_a;
  real_T c3_k_b;
  real_T c3_v_y;
  real_T c3_gd_x;
  real_T c3_hd_x;
  real_T c3_id_x;
  real_T c3_n_a;
  real_T c3_l_b;
  real_T c3_w_y;
  real_T c3_jd_x;
  real_T c3_kd_x;
  real_T c3_ld_x;
  real_T c3_o_a;
  real_T c3_m_b;
  real_T c3_md_x;
  real_T c3_nd_x;
  real_T c3_od_x;
  real_T c3_p_a;
  real_T c3_n_b;
  real_T *c3_b_lat1;
  real_T *c3_b_lng1;
  real_T *c3_b_lat2;
  real_T *c3_b_lng2;
  real_T *c3_b_N;
  real_T *c3_b_E;
  real_T *c3_b_d;
  real_T *c3_b_theta;
  c3_b_theta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_b_d = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c3_b_lng2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_b_lat2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c3_b_E = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_lng1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c3_b_lat1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c3_b_N = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0);
  c3_hoistedGlobal = *c3_b_lat1;
  c3_b_hoistedGlobal = *c3_b_lng1;
  c3_c_hoistedGlobal = *c3_b_lat2;
  c3_d_hoistedGlobal = *c3_b_lng2;
  c3_lat1 = c3_hoistedGlobal;
  c3_lng1 = c3_b_hoistedGlobal;
  c3_lat2 = c3_c_hoistedGlobal;
  c3_lng2 = c3_d_hoistedGlobal;
  sf_debug_symbol_scope_push_eml(0U, 17U, 17U, c3_debug_family_names,
    c3_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c3_ellA, c3_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c3_ellB, c3_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c3_dLat, c3_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c3_dLng, c3_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c3_a, c3_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c3_c, c3_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c3_r, c3_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c3_nargin, c3_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c3_nargout, c3_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&c3_lat1, c3_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&c3_lng1, c3_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&c3_lat2, c3_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&c3_lng2, c3_sf_marshall, 12U);
  sf_debug_symbol_scope_add_eml(&c3_N, c3_sf_marshall, 13U);
  sf_debug_symbol_scope_add_eml(&c3_E, c3_sf_marshall, 14U);
  sf_debug_symbol_scope_add_eml(&c3_d, c3_sf_marshall, 15U);
  sf_debug_symbol_scope_add_eml(&c3_theta, c3_sf_marshall, 16U);
  CV_EML_FCN(0, 0);

  /*  This block supports the Embedded MATLAB subset. */
  _SFD_EML_CALL(0, 5);
  c3_ellA = 6.378137E+6;

  /* //Earths Equatorial Radius */
  _SFD_EML_CALL(0, 6);
  c3_ellB = 6.3567523E+6;

  /* //Earths Polar Radius */
  /* pi = 3.1415926535897932384626433832795028; */
  _SFD_EML_CALL(0, 8);
  c3_b_a = c3_lat1;
  c3_y = c3_b_a * 3.1415926535897931;
  c3_A = c3_y;
  c3_x = c3_A;
  c3_b_x = c3_x;
  c3_c_x = c3_b_x;
  c3_lat1 = c3_c_x / 180.0;
  _SFD_EML_CALL(0, 9);
  c3_c_a = c3_lat2;
  c3_b_y = c3_c_a * 3.1415926535897931;
  c3_b_A = c3_b_y;
  c3_d_x = c3_b_A;
  c3_e_x = c3_d_x;
  c3_f_x = c3_e_x;
  c3_lat2 = c3_f_x / 180.0;
  _SFD_EML_CALL(0, 10);
  c3_d_a = c3_lng1;
  c3_c_y = c3_d_a * 3.1415926535897931;
  c3_c_A = c3_c_y;
  c3_g_x = c3_c_A;
  c3_h_x = c3_g_x;
  c3_i_x = c3_h_x;
  c3_lng1 = c3_i_x / 180.0;
  _SFD_EML_CALL(0, 11);
  c3_e_a = c3_lng2;
  c3_d_y = c3_e_a * 3.1415926535897931;
  c3_d_A = c3_d_y;
  c3_j_x = c3_d_A;
  c3_k_x = c3_j_x;
  c3_l_x = c3_k_x;
  c3_lng2 = c3_l_x / 180.0;
  _SFD_EML_CALL(0, 13);
  c3_dLat = c3_lat2 - c3_lat1;
  _SFD_EML_CALL(0, 14);
  c3_dLng = c3_lng2 - c3_lng1;
  _SFD_EML_CALL(0, 15);
  c3_e_A = c3_dLat;
  c3_m_x = c3_e_A;
  c3_n_x = c3_m_x;
  c3_o_x = c3_n_x;
  c3_e_y = c3_o_x / 2.0;
  c3_p_x = c3_e_y;
  c3_q_x = c3_p_x;
  c3_r_x = c3_q_x;
  c3_q_x = c3_r_x;
  c3_q_x = muDoubleScalarSin(c3_q_x);
  c3_f_A = c3_dLat;
  c3_s_x = c3_f_A;
  c3_t_x = c3_s_x;
  c3_u_x = c3_t_x;
  c3_f_y = c3_u_x / 2.0;
  c3_v_x = c3_f_y;
  c3_w_x = c3_v_x;
  c3_x_x = c3_w_x;
  c3_w_x = c3_x_x;
  c3_w_x = muDoubleScalarSin(c3_w_x);
  c3_f_a = c3_q_x;
  c3_b = c3_w_x;
  c3_g_y = c3_f_a * c3_b;
  c3_y_x = c3_lat1;
  c3_ab_x = c3_y_x;
  c3_bb_x = c3_ab_x;
  c3_ab_x = c3_bb_x;
  c3_ab_x = muDoubleScalarCos(c3_ab_x);
  c3_cb_x = c3_lat2;
  c3_db_x = c3_cb_x;
  c3_eb_x = c3_db_x;
  c3_db_x = c3_eb_x;
  c3_db_x = muDoubleScalarCos(c3_db_x);
  c3_g_a = c3_ab_x;
  c3_b_b = c3_db_x;
  c3_h_y = c3_g_a * c3_b_b;
  c3_g_A = c3_dLng;
  c3_fb_x = c3_g_A;
  c3_gb_x = c3_fb_x;
  c3_hb_x = c3_gb_x;
  c3_i_y = c3_hb_x / 2.0;
  c3_ib_x = c3_i_y;
  c3_jb_x = c3_ib_x;
  c3_kb_x = c3_jb_x;
  c3_jb_x = c3_kb_x;
  c3_jb_x = muDoubleScalarSin(c3_jb_x);
  c3_h_a = c3_h_y;
  c3_c_b = c3_jb_x;
  c3_j_y = c3_h_a * c3_c_b;
  c3_h_A = c3_dLng;
  c3_lb_x = c3_h_A;
  c3_mb_x = c3_lb_x;
  c3_nb_x = c3_mb_x;
  c3_k_y = c3_nb_x / 2.0;
  c3_ob_x = c3_k_y;
  c3_pb_x = c3_ob_x;
  c3_qb_x = c3_pb_x;
  c3_pb_x = c3_qb_x;
  c3_pb_x = muDoubleScalarSin(c3_pb_x);
  c3_i_a = c3_j_y;
  c3_d_b = c3_pb_x;
  c3_l_y = c3_i_a * c3_d_b;
  c3_a = c3_g_y + c3_l_y;
  _SFD_EML_CALL(0, 16);
  c3_rb_x = c3_a;
  c3_sb_x = c3_rb_x;
  if (c3_sb_x < 0.0) {
    c3_eml_error(chartInstance);
  }

  c3_tb_x = c3_sb_x;
  c3_sb_x = c3_tb_x;
  c3_sb_x = muDoubleScalarSqrt(c3_sb_x);
  c3_ub_x = 1.0 - c3_a;
  c3_vb_x = c3_ub_x;
  if (c3_vb_x < 0.0) {
    c3_eml_error(chartInstance);
  }

  c3_wb_x = c3_vb_x;
  c3_vb_x = c3_wb_x;
  c3_vb_x = muDoubleScalarSqrt(c3_vb_x);
  c3_e_b = c3_atan2(chartInstance, c3_sb_x, c3_vb_x);
  c3_c = 2.0 * c3_e_b;
  _SFD_EML_CALL(0, 18);
  c3_i_A = c3_lat1 + c3_lat2;
  c3_xb_x = c3_i_A;
  c3_yb_x = c3_xb_x;
  c3_ac_x = c3_yb_x;
  c3_m_y = c3_ac_x / 2.0;
  c3_bc_x = c3_m_y;
  c3_cc_x = c3_bc_x;
  c3_dc_x = c3_cc_x;
  c3_cc_x = c3_dc_x;
  c3_cc_x = muDoubleScalarCos(c3_cc_x);
  c3_f_b = c3_cc_x;
  c3_n_y = 6.3567523E+6 * c3_f_b;
  c3_j_A = c3_lat1 + c3_lat2;
  c3_ec_x = c3_j_A;
  c3_fc_x = c3_ec_x;
  c3_gc_x = c3_fc_x;
  c3_o_y = c3_gc_x / 2.0;
  c3_hc_x = c3_o_y;
  c3_ic_x = c3_hc_x;
  c3_jc_x = c3_ic_x;
  c3_ic_x = c3_jc_x;
  c3_ic_x = muDoubleScalarSin(c3_ic_x);
  c3_g_b = c3_ic_x;
  c3_p_y = 6.378137E+6 * c3_g_b;
  c3_kc_x = c3_mpower(chartInstance, c3_n_y) + c3_mpower(chartInstance, c3_p_y);
  c3_lc_x = c3_kc_x;
  if (c3_lc_x < 0.0) {
    c3_eml_error(chartInstance);
  }

  c3_mc_x = c3_lc_x;
  c3_lc_x = c3_mc_x;
  c3_lc_x = muDoubleScalarSqrt(c3_lc_x);
  c3_B = c3_lc_x;
  c3_q_y = c3_B;
  c3_r_y = c3_q_y;
  c3_s_y = c3_r_y;
  c3_r = 4.05442370444651E+13 / c3_s_y;
  _SFD_EML_CALL(0, 19);
  c3_j_a = c3_r;
  c3_h_b = c3_c;
  c3_d = c3_j_a * c3_h_b;
  _SFD_EML_CALL(0, 20);
  c3_nc_x = c3_dLng;
  c3_oc_x = c3_nc_x;
  c3_pc_x = c3_oc_x;
  c3_oc_x = c3_pc_x;
  c3_oc_x = muDoubleScalarSin(c3_oc_x);
  c3_qc_x = c3_lat2;
  c3_rc_x = c3_qc_x;
  c3_sc_x = c3_rc_x;
  c3_rc_x = c3_sc_x;
  c3_rc_x = muDoubleScalarCos(c3_rc_x);
  c3_k_a = c3_oc_x;
  c3_i_b = c3_rc_x;
  c3_t_y = c3_k_a * c3_i_b;
  c3_tc_x = c3_lat1;
  c3_uc_x = c3_tc_x;
  c3_vc_x = c3_uc_x;
  c3_uc_x = c3_vc_x;
  c3_uc_x = muDoubleScalarCos(c3_uc_x);
  c3_wc_x = c3_lat2;
  c3_xc_x = c3_wc_x;
  c3_yc_x = c3_xc_x;
  c3_xc_x = c3_yc_x;
  c3_xc_x = muDoubleScalarSin(c3_xc_x);
  c3_l_a = c3_uc_x;
  c3_j_b = c3_xc_x;
  c3_u_y = c3_l_a * c3_j_b;
  c3_ad_x = c3_lat1;
  c3_bd_x = c3_ad_x;
  c3_cd_x = c3_bd_x;
  c3_bd_x = c3_cd_x;
  c3_bd_x = muDoubleScalarSin(c3_bd_x);
  c3_dd_x = c3_lat2;
  c3_ed_x = c3_dd_x;
  c3_fd_x = c3_ed_x;
  c3_ed_x = c3_fd_x;
  c3_ed_x = muDoubleScalarCos(c3_ed_x);
  c3_m_a = c3_bd_x;
  c3_k_b = c3_ed_x;
  c3_v_y = c3_m_a * c3_k_b;
  c3_gd_x = c3_dLng;
  c3_hd_x = c3_gd_x;
  c3_id_x = c3_hd_x;
  c3_hd_x = c3_id_x;
  c3_hd_x = muDoubleScalarCos(c3_hd_x);
  c3_n_a = c3_v_y;
  c3_l_b = c3_hd_x;
  c3_w_y = c3_n_a * c3_l_b;
  c3_theta = c3_atan2(chartInstance, c3_t_y, c3_u_y - c3_w_y);
  _SFD_EML_CALL(0, 21);
  c3_jd_x = c3_theta;
  c3_kd_x = c3_jd_x;
  c3_ld_x = c3_kd_x;
  c3_kd_x = c3_ld_x;
  c3_kd_x = muDoubleScalarCos(c3_kd_x);
  c3_o_a = c3_d;
  c3_m_b = c3_kd_x;
  c3_N = c3_o_a * c3_m_b;
  _SFD_EML_CALL(0, 22);
  c3_md_x = c3_theta;
  c3_nd_x = c3_md_x;
  c3_od_x = c3_nd_x;
  c3_nd_x = c3_od_x;
  c3_nd_x = muDoubleScalarSin(c3_nd_x);
  c3_p_a = c3_d;
  c3_n_b = c3_nd_x;
  c3_E = c3_p_a * c3_n_b;
  _SFD_EML_CALL(0, -22);
  sf_debug_symbol_scope_pop();
  *c3_b_N = c3_N;
  *c3_b_E = c3_E;
  *c3_b_d = c3_d;
  *c3_b_theta = c3_theta;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0);
}

static void compInitSubchartSimstructsFcn_c3_test(SFc3_testInstanceStruct
  *chartInstance)
{
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber)
{
}

static void c3_eml_error(SFc3_testInstanceStruct *chartInstance)
{
  int32_T c3_i0;
  static char_T c3_cv0[31] = { 'E', 'm', 'b', 'e', 'd', 'd', 'e', 'd', 'M', 'A',
    'T', 'L', 'A', 'B', ':', 's', 'q', 'r', 't', ':', 'd'
    , 'o', 'm', 'a', 'i', 'n', 'E', 'r', 'r', 'o', 'r' };

  char_T c3_u[31];
  const mxArray *c3_y = NULL;
  int32_T c3_i1;
  static char_T c3_cv1[77] = { 'D', 'o', 'm', 'a', 'i', 'n', ' ', 'e', 'r', 'r',
    'o', 'r', '.', ' ', 'T', 'o', ' ', 'c', 'o', 'm', 'p'
    , 'u', 't', 'e', ' ', 'c', 'o', 'm', 'p', 'l', 'e', 'x', ' ', 'r', 'e', 's',
    'u', 'l', 't', 's', ' ',
    'f', 'r', 'o', 'm', ' ', 'r', 'e', 'a', 'l', ' ', 'x', ',', ' ', 'u', 's',
    'e', ' ', '\'', 's', 'q',
    'r', 't', '(', 'c', 'o', 'm', 'p', 'l', 'e', 'x', '(', 'x', ')', ')', '\'',
    '.' };

  char_T c3_b_u[77];
  const mxArray *c3_b_y = NULL;
  for (c3_i0 = 0; c3_i0 < 31; c3_i0 = c3_i0 + 1) {
    c3_u[c3_i0] = c3_cv0[c3_i0];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 10, 0U, 1U, 0U, 2, 1, 31));
  for (c3_i1 = 0; c3_i1 < 77; c3_i1 = c3_i1 + 1) {
    c3_b_u[c3_i1] = c3_cv1[c3_i1];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_b_u, 10, 0U, 1U, 0U, 2, 1, 77));
  sf_mex_call_debug("error", 0U, 2U, 14, c3_y, 14, c3_b_y);
}

static real_T c3_atan2(SFc3_testInstanceStruct *chartInstance, real_T c3_y,
  real_T c3_x)
{
  real_T c3_b_y;
  real_T c3_b_x;
  c3_eml_scalar_eg(chartInstance);
  c3_b_y = c3_y;
  c3_b_x = c3_x;
  return muDoubleScalarAtan2(c3_b_y, c3_b_x);
}

static void c3_eml_scalar_eg(SFc3_testInstanceStruct *chartInstance)
{
}

static real_T c3_mpower(SFc3_testInstanceStruct *chartInstance, real_T c3_a)
{
  real_T c3_b_a;
  real_T c3_ak;
  c3_b_a = c3_a;
  c3_eml_scalar_eg(chartInstance);
  c3_ak = c3_b_a;
  return muDoubleScalarPower(c3_ak, 2.0);
}

static const mxArray *c3_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  real_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_testInstanceStruct *chartInstance;
  chartInstance = (SFc3_testInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_b_u = *((real_T *)c3_u);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

const mxArray *sf_c3_test_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_ResolvedFunctionInfo c3_info[39];
  const mxArray *c3_m0 = NULL;
  int32_T c3_i2;
  c3_ResolvedFunctionInfo *c3_r0;
  c3_nameCaptureInfo = NULL;
  c3_info_helper(c3_info);
  sf_mex_assign(&c3_m0, sf_mex_createstruct("nameCaptureInfo", 1, 39));
  for (c3_i2 = 0; c3_i2 < 39; c3_i2 = c3_i2 + 1) {
    c3_r0 = &c3_info[c3_i2];
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->context)), "context",
                    "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c3_r0->name)), "name",
                    "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c3_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", c3_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c3_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c3_i2);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo", c3_i2);
    sf_mex_addfield(c3_m0, sf_mex_create("nameCaptureInfo", &c3_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo", c3_i2);
  }

  sf_mex_assign(&c3_nameCaptureInfo, c3_m0);
  return c3_nameCaptureInfo;
}

static void c3_info_helper(c3_ResolvedFunctionInfo c3_info[39])
{
  c3_info[0].context = "";
  c3_info[0].name = "pi";
  c3_info[0].dominantType = "";
  c3_info[0].resolved = "[B]pi";
  c3_info[0].fileLength = 0U;
  c3_info[0].fileTime1 = 0U;
  c3_info[0].fileTime2 = 0U;
  c3_info[1].context = "";
  c3_info[1].name = "mtimes";
  c3_info[1].dominantType = "double";
  c3_info[1].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[1].fileLength = 3425U;
  c3_info[1].fileTime1 = 1251035472U;
  c3_info[1].fileTime2 = 0U;
  c3_info[2].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[2].name = "nargin";
  c3_info[2].dominantType = "";
  c3_info[2].resolved = "[B]nargin";
  c3_info[2].fileLength = 0U;
  c3_info[2].fileTime1 = 0U;
  c3_info[2].fileTime2 = 0U;
  c3_info[3].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[3].name = "gt";
  c3_info[3].dominantType = "double";
  c3_info[3].resolved = "[B]gt";
  c3_info[3].fileLength = 0U;
  c3_info[3].fileTime1 = 0U;
  c3_info[3].fileTime2 = 0U;
  c3_info[4].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[4].name = "isa";
  c3_info[4].dominantType = "double";
  c3_info[4].resolved = "[B]isa";
  c3_info[4].fileLength = 0U;
  c3_info[4].fileTime1 = 0U;
  c3_info[4].fileTime2 = 0U;
  c3_info[5].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[5].name = "isinteger";
  c3_info[5].dominantType = "double";
  c3_info[5].resolved = "[B]isinteger";
  c3_info[5].fileLength = 0U;
  c3_info[5].fileTime1 = 0U;
  c3_info[5].fileTime2 = 0U;
  c3_info[6].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[6].name = "isscalar";
  c3_info[6].dominantType = "double";
  c3_info[6].resolved = "[B]isscalar";
  c3_info[6].fileLength = 0U;
  c3_info[6].fileTime1 = 0U;
  c3_info[6].fileTime2 = 0U;
  c3_info[7].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[7].name = "strcmp";
  c3_info[7].dominantType = "char";
  c3_info[7].resolved = "[B]strcmp";
  c3_info[7].fileLength = 0U;
  c3_info[7].fileTime1 = 0U;
  c3_info[7].fileTime2 = 0U;
  c3_info[8].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[8].name = "size";
  c3_info[8].dominantType = "double";
  c3_info[8].resolved = "[B]size";
  c3_info[8].fileLength = 0U;
  c3_info[8].fileTime1 = 0U;
  c3_info[8].fileTime2 = 0U;
  c3_info[9].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[9].name = "eq";
  c3_info[9].dominantType = "double";
  c3_info[9].resolved = "[B]eq";
  c3_info[9].fileLength = 0U;
  c3_info[9].fileTime1 = 0U;
  c3_info[9].fileTime2 = 0U;
  c3_info[10].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[10].name = "class";
  c3_info[10].dominantType = "double";
  c3_info[10].resolved = "[B]class";
  c3_info[10].fileLength = 0U;
  c3_info[10].fileTime1 = 0U;
  c3_info[10].fileTime2 = 0U;
  c3_info[11].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c3_info[11].name = "not";
  c3_info[11].dominantType = "logical";
  c3_info[11].resolved = "[B]not";
  c3_info[11].fileLength = 0U;
  c3_info[11].fileTime1 = 0U;
  c3_info[11].fileTime2 = 0U;
  c3_info[12].context = "";
  c3_info[12].name = "mrdivide";
  c3_info[12].dominantType = "double";
  c3_info[12].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[12].fileLength = 432U;
  c3_info[12].fileTime1 = 1277751822U;
  c3_info[12].fileTime2 = 0U;
  c3_info[13].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[13].name = "ge";
  c3_info[13].dominantType = "double";
  c3_info[13].resolved = "[B]ge";
  c3_info[13].fileLength = 0U;
  c3_info[13].fileTime1 = 0U;
  c3_info[13].fileTime2 = 0U;
  c3_info[14].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p";
  c3_info[14].name = "rdivide";
  c3_info[14].dominantType = "double";
  c3_info[14].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[14].fileLength = 403U;
  c3_info[14].fileTime1 = 1245106020U;
  c3_info[14].fileTime2 = 0U;
  c3_info[15].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m";
  c3_info[15].name = "eml_div";
  c3_info[15].dominantType = "double";
  c3_info[15].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m";
  c3_info[15].fileLength = 4918U;
  c3_info[15].fileTime1 = 1267067010U;
  c3_info[15].fileTime2 = 0U;
  c3_info[16].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m!eml_fldiv";
  c3_info[16].name = "isreal";
  c3_info[16].dominantType = "double";
  c3_info[16].resolved = "[B]isreal";
  c3_info[16].fileLength = 0U;
  c3_info[16].fileTime1 = 0U;
  c3_info[16].fileTime2 = 0U;
  c3_info[17].context = "";
  c3_info[17].name = "minus";
  c3_info[17].dominantType = "double";
  c3_info[17].resolved = "[B]minus";
  c3_info[17].fileLength = 0U;
  c3_info[17].fileTime1 = 0U;
  c3_info[17].fileTime2 = 0U;
  c3_info[18].context = "";
  c3_info[18].name = "sin";
  c3_info[18].dominantType = "double";
  c3_info[18].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c3_info[18].fileLength = 324U;
  c3_info[18].fileTime1 = 1203451642U;
  c3_info[18].fileTime2 = 0U;
  c3_info[19].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m";
  c3_info[19].name = "eml_scalar_sin";
  c3_info[19].dominantType = "double";
  c3_info[19].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c3_info[19].fileLength = 601U;
  c3_info[19].fileTime1 = 1209334390U;
  c3_info[19].fileTime2 = 0U;
  c3_info[20].context = "";
  c3_info[20].name = "cos";
  c3_info[20].dominantType = "double";
  c3_info[20].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c3_info[20].fileLength = 324U;
  c3_info[20].fileTime1 = 1203451550U;
  c3_info[20].fileTime2 = 0U;
  c3_info[21].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m";
  c3_info[21].name = "eml_scalar_cos";
  c3_info[21].dominantType = "double";
  c3_info[21].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c3_info[21].fileLength = 602U;
  c3_info[21].fileTime1 = 1209334386U;
  c3_info[21].fileTime2 = 0U;
  c3_info[22].context = "";
  c3_info[22].name = "plus";
  c3_info[22].dominantType = "double";
  c3_info[22].resolved = "[B]plus";
  c3_info[22].fileLength = 0U;
  c3_info[22].fileTime1 = 0U;
  c3_info[22].fileTime2 = 0U;
  c3_info[23].context = "";
  c3_info[23].name = "sqrt";
  c3_info[23].dominantType = "double";
  c3_info[23].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c3_info[23].fileLength = 572U;
  c3_info[23].fileTime1 = 1203451644U;
  c3_info[23].fileTime2 = 0U;
  c3_info[24].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c3_info[24].name = "lt";
  c3_info[24].dominantType = "double";
  c3_info[24].resolved = "[B]lt";
  c3_info[24].fileLength = 0U;
  c3_info[24].fileTime1 = 0U;
  c3_info[24].fileTime2 = 0U;
  c3_info[25].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c3_info[25].name = "eml_error";
  c3_info[25].dominantType = "char";
  c3_info[25].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m";
  c3_info[25].fileLength = 315U;
  c3_info[25].fileTime1 = 1213930344U;
  c3_info[25].fileTime2 = 0U;
  c3_info[26].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sqrt.m";
  c3_info[26].name = "eml_scalar_sqrt";
  c3_info[26].dominantType = "double";
  c3_info[26].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sqrt.m";
  c3_info[26].fileLength = 664U;
  c3_info[26].fileTime1 = 1209334394U;
  c3_info[26].fileTime2 = 0U;
  c3_info[27].context = "";
  c3_info[27].name = "atan2";
  c3_info[27].dominantType = "double";
  c3_info[27].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c3_info[27].fileLength = 605U;
  c3_info[27].fileTime1 = 1236260854U;
  c3_info[27].fileTime2 = 0U;
  c3_info[28].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c3_info[28].name = "eml_scalar_eg";
  c3_info[28].dominantType = "double";
  c3_info[28].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[28].fileLength = 3068U;
  c3_info[28].fileTime1 = 1240265610U;
  c3_info[28].fileTime2 = 0U;
  c3_info[29].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m!any_enums";
  c3_info[29].name = "false";
  c3_info[29].dominantType = "";
  c3_info[29].resolved = "[B]false";
  c3_info[29].fileLength = 0U;
  c3_info[29].fileTime1 = 0U;
  c3_info[29].fileTime2 = 0U;
  c3_info[30].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c3_info[30].name = "isstruct";
  c3_info[30].dominantType = "double";
  c3_info[30].resolved = "[B]isstruct";
  c3_info[30].fileLength = 0U;
  c3_info[30].fileTime1 = 0U;
  c3_info[30].fileTime2 = 0U;
  c3_info[31].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m!zerosum";
  c3_info[31].name = "cast";
  c3_info[31].dominantType = "double";
  c3_info[31].resolved = "[B]cast";
  c3_info[31].fileLength = 0U;
  c3_info[31].fileTime1 = 0U;
  c3_info[31].fileTime2 = 0U;
  c3_info[32].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c3_info[32].name = "eml_scalexp_alloc";
  c3_info[32].dominantType = "double";
  c3_info[32].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c3_info[32].fileLength = 932U;
  c3_info[32].fileTime1 = 1261955470U;
  c3_info[32].fileTime2 = 0U;
  c3_info[33].context =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/atan2.m";
  c3_info[33].name = "eml_scalar_atan2";
  c3_info[33].dominantType = "double";
  c3_info[33].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_atan2.m";
  c3_info[33].fileLength = 964U;
  c3_info[33].fileTime1 = 1209334386U;
  c3_info[33].fileTime2 = 0U;
  c3_info[34].context = "";
  c3_info[34].name = "mpower";
  c3_info[34].dominantType = "double";
  c3_info[34].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c3_info[34].fileLength = 3710U;
  c3_info[34].fileTime1 = 1238437888U;
  c3_info[34].fileTime2 = 0U;
  c3_info[35].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c3_info[35].name = "ndims";
  c3_info[35].dominantType = "double";
  c3_info[35].resolved = "[B]ndims";
  c3_info[35].fileLength = 0U;
  c3_info[35].fileTime1 = 0U;
  c3_info[35].fileTime2 = 0U;
  c3_info[36].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m";
  c3_info[36].name = "power";
  c3_info[36].dominantType = "double";
  c3_info[36].resolved = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c3_info[36].fileLength = 5380U;
  c3_info[36].fileTime1 = 1228097498U;
  c3_info[36].fileTime2 = 0U;
  c3_info[37].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c3_info[37].name = "eml_scalar_floor";
  c3_info[37].dominantType = "double";
  c3_info[37].resolved =
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m";
  c3_info[37].fileLength = 260U;
  c3_info[37].fileTime1 = 1209334390U;
  c3_info[37].fileTime2 = 0U;
  c3_info[38].context = "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m";
  c3_info[38].name = "ne";
  c3_info[38].dominantType = "double";
  c3_info[38].resolved = "[B]ne";
  c3_info[38].fileLength = 0U;
  c3_info[38].fileTime1 = 0U;
  c3_info[38].fileTime2 = 0U;
}

static const mxArray *c3_b_sf_marshall(void *chartInstanceVoid, void *c3_u)
{
  const mxArray *c3_y = NULL;
  boolean_T c3_b_u;
  const mxArray *c3_b_y = NULL;
  SFc3_testInstanceStruct *chartInstance;
  chartInstance = (SFc3_testInstanceStruct *)chartInstanceVoid;
  c3_y = NULL;
  c3_b_u = *((boolean_T *)c3_u);
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c3_y, c3_b_y);
  return c3_y;
}

static real_T c3_emlrt_marshallIn(SFc3_testInstanceStruct *chartInstance, const
  mxArray *c3_E, const char_T *c3_name)
{
  real_T c3_y;
  real_T c3_d0;
  sf_mex_import(c3_name, sf_mex_dup(c3_E), &c3_d0, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d0;
  sf_mex_destroy(&c3_E);
  return c3_y;
}

static uint8_T c3_b_emlrt_marshallIn(SFc3_testInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_test, const char_T *
  c3_name)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  sf_mex_import(c3_name, sf_mex_dup(c3_b_is_active_c3_test), &c3_u0, 1, 3, 0U, 0,
                0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_b_is_active_c3_test);
  return c3_y;
}

static void init_dsm_address_info(SFc3_testInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c3_test_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3998091923U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1443160703U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4009188783U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1830858680U);
}

mxArray *sf_c3_test_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(1133245694U);
    pr[1] = (double)(3689236926U);
    pr[2] = (double)(3203190739U);
    pr[3] = (double)(1009485152U);
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  return(mxAutoinheritanceInfo);
}

static mxArray *sf_get_sim_state_info_c3_test(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x5'type','srcId','name','auxInfo'{{M[1],M[12],T\"E\",},{M[1],M[4],T\"N\",},{M[1],M[17],T\"d\",},{M[1],M[18],T\"theta\",},{M[8],M[0],T\"is_active_c3_test\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 5, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_test_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_testInstanceStruct *chartInstance;
    chartInstance = (SFc3_testInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_testMachineNumber_,
          3,
          1,
          1,
          8,
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
          init_script_number_translation(_testMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_testMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_testMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"N");
          _SFD_SET_DATA_PROPS(1,1,1,0,"lat1");
          _SFD_SET_DATA_PROPS(2,1,1,0,"lng1");
          _SFD_SET_DATA_PROPS(3,2,0,1,"E");
          _SFD_SET_DATA_PROPS(4,1,1,0,"lat2");
          _SFD_SET_DATA_PROPS(5,1,1,0,"lng2");
          _SFD_SET_DATA_PROPS(6,2,0,1,"d");
          _SFD_SET_DATA_PROPS(7,2,0,1,"theta");
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
        _SFD_CV_INIT_EML(0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,746);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_sf_marshall);

        {
          real_T *c3_N;
          real_T *c3_lat1;
          real_T *c3_lng1;
          real_T *c3_E;
          real_T *c3_lat2;
          real_T *c3_lng2;
          real_T *c3_d;
          real_T *c3_theta;
          c3_theta = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c3_d = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c3_lng2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c3_lat2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c3_E = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c3_lng1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c3_lat1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c3_N = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c3_N);
          _SFD_SET_DATA_VALUE_PTR(1U, c3_lat1);
          _SFD_SET_DATA_VALUE_PTR(2U, c3_lng1);
          _SFD_SET_DATA_VALUE_PTR(3U, c3_E);
          _SFD_SET_DATA_VALUE_PTR(4U, c3_lat2);
          _SFD_SET_DATA_VALUE_PTR(5U, c3_lng2);
          _SFD_SET_DATA_VALUE_PTR(6U, c3_d);
          _SFD_SET_DATA_VALUE_PTR(7U, c3_theta);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_testMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c3_test(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_testInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c3_test((SFc3_testInstanceStruct*) chartInstanceVar);
  initialize_c3_test((SFc3_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_test(void *chartInstanceVar)
{
  enable_c3_test((SFc3_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_test(void *chartInstanceVar)
{
  disable_c3_test((SFc3_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_test(void *chartInstanceVar)
{
  sf_c3_test((SFc3_testInstanceStruct*) chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c3_test(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_test((SFc3_testInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c3_test();/* state var info */
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

static void sf_internal_set_sim_state_c3_test(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_test();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_test((SFc3_testInstanceStruct*)chartInfo->chartInstance,
                        mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c3_test(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_test(S);
}

static void sf_opaque_set_sim_state_c3_test(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_test(S, st);
}

static void sf_opaque_terminate_c3_test(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_testInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c3_test((SFc3_testInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  compInitSubchartSimstructsFcn_c3_test((SFc3_testInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_test(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c3_test((SFc3_testInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_test(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,"test","test",3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,"test","test",3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,"test","test",3,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"test","test",3,4);
      sf_mark_chart_reusable_outputs(S,"test","test",3,4);
    }

    sf_set_rtw_dwork_info(S,"test","test",3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1127358278U));
  ssSetChecksum1(S,(3201287371U));
  ssSetChecksum2(S,(1143650963U));
  ssSetChecksum3(S,(3514023288U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c3_test(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "test", "test",3);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_test(SimStruct *S)
{
  SFc3_testInstanceStruct *chartInstance;
  chartInstance = (SFc3_testInstanceStruct *)malloc(sizeof
    (SFc3_testInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_testInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_test;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_test;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_test;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_test;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_test;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_test;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_test;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_test;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_test;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_test;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_test;
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

void c3_test_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_test(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_test(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_test(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_test_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}