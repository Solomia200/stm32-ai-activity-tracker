/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-12-10T15:07:22+0200
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */


#include "network.h"
#include "network_data.h"

#include "ai_platform.h"
#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "core_convert.h"

#include "layers.h"



#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_network
 
#undef AI_NETWORK_MODEL_SIGNATURE
#define AI_NETWORK_MODEL_SIGNATURE     "0x1a129778f99b6502dbefac254a2067cb"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2025-12-10T15:07:22+0200"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_NETWORK_N_BATCHES
#define AI_NETWORK_N_BATCHES         (1)

static ai_ptr g_network_activations_map[1] = AI_C_ARRAY_INIT;
static ai_ptr g_network_weights_map[1] = AI_C_ARRAY_INIT;



/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  serving_default_input_layer0_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 288, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 288, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2944, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  pool_6_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1472, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_7_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1472, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_8_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1472, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_11_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2688, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_12_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2688, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  eltwise_13_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2688, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_16_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3840, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  pool_18_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 96, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  gemm_19_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  gemm_20_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  nl_21_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 7, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst15_3D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst14_3D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst11_4D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst10_4D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst7_4D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#20 */
AI_ARRAY_OBJ_DECLARE(
  tfl_pseudo_qconst6_4D_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#21 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 480, AI_STATIC)

/* Array#22 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#23 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_11_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 10240, AI_STATIC)

/* Array#24 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_11_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#25 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_16_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 18432, AI_STATIC)

/* Array#26 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_16_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 96, AI_STATIC)

/* Array#27 */
AI_ARRAY_OBJ_DECLARE(
  gemm_19_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6144, AI_STATIC)

/* Array#28 */
AI_ARRAY_OBJ_DECLARE(
  gemm_19_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#29 */
AI_ARRAY_OBJ_DECLARE(
  gemm_20_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 448, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  gemm_20_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 7, AI_STATIC)

/* Array#31 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 1468, AI_STATIC)

/* Array#32 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_11_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 6656, AI_STATIC)

/* Array#33 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_16_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7232, AI_STATIC)

/* Array#34 */
AI_ARRAY_OBJ_DECLARE(
  gemm_19_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 416, AI_STATIC)

/* Array#35 */
AI_ARRAY_OBJ_DECLARE(
  gemm_20_scratch0_array, AI_ARRAY_FORMAT_S16,
  NULL, NULL, 99, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  nl_21_scratch0_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 3, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_11_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.3812257647514343f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_11_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002128778025507927f, 0.0020551758352667093f, 0.002121475525200367f, 0.0035819767508655787f, 0.002269975608214736f, 0.0021243568044155836f, 0.002095976611599326f, 0.0021780633833259344f, 0.0022949944250285625f, 0.0021953617688268423f, 0.0025377802085131407f, 0.0020213511306792498f, 0.00194769527297467f, 0.0021095657721161842f, 0.0021238140761852264f, 0.0020521304104477167f, 0.0018121477914974093f, 0.0027216682210564613f, 0.0022436846047639847f, 0.002276534214615822f, 0.0021192384883761406f, 0.0018452975200489163f, 0.002171770902350545f, 0.002569079864770174f, 0.003236514050513506f, 0.002220507711172104f, 0.0024388052988797426f, 0.0021465825848281384f, 0.00210953364148736f, 0.0017866393318399787f, 0.0021977012511342764f, 0.0021485090255737305f, 0.002263290574774146f, 0.0021639533806592226f, 0.0021773953922092915f, 0.0020386315882205963f, 0.0019995332695543766f, 0.0018433191580697894f, 0.0020880254451185465f, 0.0022813209798187017f, 0.0019187742145732045f, 0.0025677175726741552f, 0.002700657583773136f, 0.0028673449996858835f, 0.002193125896155834f, 0.002267469884827733f, 0.0030642999336123466f, 0.0023069896269589663f, 0.002212589606642723f, 0.0026339564938098192f, 0.002550039440393448f, 0.0020463597029447556f, 0.0019907394889742136f, 0.0024041892029345036f, 0.0022931869607418776f, 0.00363204930908978f, 0.002374058123677969f, 0.0019914687145501375f, 0.0029765316285192966f, 0.002463829005137086f, 0.0018320925300940871f, 0.0028002357576042414f, 0.002049091039225459f, 0.002124781720340252f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.3036007881164551f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 96,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0019370445515960455f, 0.001821790006943047f, 0.002065452979877591f, 0.001771572744473815f, 0.002170521067455411f, 0.0022279422264546156f, 0.0022071555722504854f, 0.0017508994787931442f, 0.0022670873440802097f, 0.0019175322959199548f, 0.001815601484850049f, 0.002119048498570919f, 0.0023175820242613554f, 0.0019504210213199258f, 0.002134528709575534f, 0.002563279354944825f, 0.0022504786029458046f, 0.00192577566485852f, 0.002235234249383211f, 0.0026896456256508827f, 0.0027466241735965014f, 0.002227823482826352f, 0.0023242137394845486f, 0.002799123292788863f, 0.002316995058208704f, 0.0019807920325547457f, 0.001963950926437974f, 0.002624091226607561f, 0.0019954931922256947f, 0.0026863354723900557f, 0.0020002867095172405f, 0.0020467243157327175f, 0.0019632589537650347f, 0.0026799242477864027f, 0.001950206235051155f, 0.0021203113719820976f, 0.002418395597487688f, 0.0022283627185970545f, 0.0020776742603629827f, 0.002018748549744487f, 0.002598884515464306f, 0.001926607801578939f, 0.002182798692956567f, 0.0022513638250529766f, 0.001766370958648622f, 0.0021800214890390635f, 0.0021350949537009f, 0.002042616019025445f, 0.002186628058552742f, 0.00236362311989069f, 0.002161332406103611f, 0.002845178125426173f, 0.002068430418148637f, 0.0021530899684876204f, 0.002229713834822178f, 0.001976874889805913f, 0.0021651897113770247f, 0.0028996209148317575f, 0.0017462337855249643f, 0.002214117208495736f, 0.0021737695205956697f, 0.002457527443766594f, 0.002310585230588913f, 0.0023553892970085144f, 0.0024822382256388664f, 0.0019363653846085072f, 0.001975913066416979f, 0.0021440114360302687f, 0.0022519156336784363f, 0.0027276913169771433f, 0.002162214834243059f, 0.002168706152588129f, 0.0022661960683763027f, 0.0022707204334437847f, 0.002091151662170887f, 0.002154781250283122f, 0.002340778009966016f, 0.002308364724740386f, 0.0029232122469693422f, 0.002254394581541419f, 0.00196858961135149f, 0.002223420422524214f, 0.002948455512523651f, 0.0022451477125287056f, 0.002411492634564638f, 0.002121525816619396f, 0.0020856184419244528f, 0.0022642086260020733f, 0.0021583836060017347f, 0.002078703138977289f, 0.002756612142547965f, 0.0024342103861272335f, 0.002083113882690668f, 0.0026151847559958696f, 0.00203825905919075f, 0.0030604342464357615f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.25666794180870056f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004885795526206493f, 0.00498955650255084f, 0.006108285393565893f, 0.003989498130977154f, 0.005591082852333784f, 0.004945919383317232f, 0.0056870304979383945f, 0.005136863328516483f, 0.0047019231133162975f, 0.00506956223398447f, 0.004681799095124006f, 0.0041578179225325584f, 0.0048308828845620155f, 0.005212406162172556f, 0.00468871183693409f, 0.00509985163807869f, 0.004940570332109928f, 0.004747213330119848f, 0.004568865057080984f, 0.005092296749353409f, 0.005312806461006403f, 0.005075023975223303f, 0.004965401720255613f, 0.005050760693848133f, 0.004347426816821098f, 0.0049582733772695065f, 0.004772385582327843f, 0.005395985208451748f, 0.004783162381500006f, 0.005262622144073248f, 0.004418639931827784f, 0.004521812777966261f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.19221116602420807f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_12_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.36317339539527893f),
    AI_PACK_INTQ_ZP(-124)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_13_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.36167988181114197f),
    AI_PACK_INTQ_ZP(-124)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_1_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.19200894236564636f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_7_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.42732349038124084f),
    AI_PACK_INTQ_ZP(-126)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_8_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.42481833696365356f),
    AI_PACK_INTQ_ZP(-126)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_19_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(2.535872459411621f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_19_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.06493677198886871f, 0.06388334184885025f, 0.04976164549589157f, 0.05898159369826317f, 0.07322482019662857f, 0.1174999251961708f, 0.06381872296333313f, 0.07031276077032089f, 0.05741284415125847f, 0.06538226455450058f, 0.08935460448265076f, 0.0919649675488472f, 0.0545615516602993f, 0.08079231530427933f, 0.09180635958909988f, 0.06197897717356682f, 0.06534386426210403f, 0.06675542891025543f, 0.1767086535692215f, 0.08288860321044922f, 0.09198623150587082f, 0.10336064547300339f, 0.11217968165874481f, 0.09395832568407059f, 0.06399553269147873f, 0.06782592087984085f, 0.06517009437084198f, 0.04734746739268303f, 0.0948915034532547f, 0.09597475826740265f, 0.06592175364494324f, 0.11915581673383713f, 0.059989433735609055f, 0.06636855751276016f, 0.0417044460773468f, 0.04874085262417793f, 0.07014662027359009f, 0.1307215541601181f, 0.060332708060741425f, 0.0923703983426094f, 0.08523228019475937f, 0.10178845375776291f, 0.05270318686962128f, 0.10221866518259048f, 0.06243366375565529f, 0.054584261029958725f, 0.09115967154502869f, 0.04844684153795242f, 0.07984712719917297f, 0.09152569621801376f, 0.11374849081039429f, 0.053624555468559265f, 0.06162859499454498f, 0.08681521564722061f, 0.07714532315731049f, 0.06534599512815475f, 0.07712201029062271f, 0.1670781522989273f, 0.08423595130443573f, 0.07546081393957138f, 0.10542570054531097f, 0.07425254583358765f, 0.07911395281553268f, 0.08927842229604721f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_20_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(4.604755878448486f),
    AI_PACK_INTQ_ZP(-3)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_20_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 7,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0039736432954669f, 0.003736883169040084f, 0.002993731526657939f, 0.0028684623539447784f, 0.005168902687728405f, 0.0041497074998915195f, 0.003155715065076947f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_21_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_18_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.19468778371810913f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_6_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.25666794180870056f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_input_layer0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.15379458665847778f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst10_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003041911404579878f),
    AI_PACK_INTQ_ZP(127)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst11_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.014606776647269726f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst14_3D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0004534307518042624f),
    AI_PACK_INTQ_ZP(-14)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst15_3D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0048960610292851925f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #24 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst6_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005511641968041658f),
    AI_PACK_INTQ_ZP(114)))

/* Int quant #25 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst7_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00844868179410696f),
    AI_PACK_INTQ_ZP(-128)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_11_bias, AI_STATIC,
  0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_11_bias_array, NULL)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_11_output, AI_STATIC,
  1, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 42, 1), AI_STRIDE_INIT(4, 1, 1, 64, 2688),
  1, &conv2d_11_output_array, &conv2d_11_output_array_intq)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_11_scratch0, AI_STATIC,
  2, 0x0,
  AI_SHAPE_INIT(4, 1, 6656, 1, 1), AI_STRIDE_INIT(4, 1, 1, 6656, 6656),
  1, &conv2d_11_scratch0_array, NULL)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_11_weights, AI_STATIC,
  3, 0x1,
  AI_SHAPE_INIT(4, 32, 5, 1, 64), AI_STRIDE_INIT(4, 1, 32, 2048, 10240),
  1, &conv2d_11_weights_array, &conv2d_11_weights_array_intq)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_16_bias, AI_STATIC,
  4, 0x0,
  AI_SHAPE_INIT(4, 1, 96, 1, 1), AI_STRIDE_INIT(4, 4, 4, 384, 384),
  1, &conv2d_16_bias_array, NULL)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_16_output, AI_STATIC,
  5, 0x1,
  AI_SHAPE_INIT(4, 1, 96, 40, 1), AI_STRIDE_INIT(4, 1, 1, 96, 3840),
  1, &conv2d_16_output_array, &conv2d_16_output_array_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_16_output0, AI_STATIC,
  6, 0x1,
  AI_SHAPE_INIT(4, 1, 96, 1, 40), AI_STRIDE_INIT(4, 1, 1, 96, 96),
  1, &conv2d_16_output_array, &conv2d_16_output_array_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_16_scratch0, AI_STATIC,
  7, 0x0,
  AI_SHAPE_INIT(4, 1, 7232, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7232, 7232),
  1, &conv2d_16_scratch0_array, NULL)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_16_weights, AI_STATIC,
  8, 0x1,
  AI_SHAPE_INIT(4, 64, 3, 1, 96), AI_STRIDE_INIT(4, 1, 64, 6144, 18432),
  1, &conv2d_16_weights_array, &conv2d_16_weights_array_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  9, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_3_bias_array, NULL)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  10, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 92, 1), AI_STRIDE_INIT(4, 1, 1, 32, 2944),
  1, &conv2d_3_output_array, &conv2d_3_output_array_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch0, AI_STATIC,
  11, 0x0,
  AI_SHAPE_INIT(4, 1, 1468, 1, 1), AI_STRIDE_INIT(4, 1, 1, 1468, 1468),
  1, &conv2d_3_scratch0_array, NULL)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  12, 0x1,
  AI_SHAPE_INIT(4, 3, 5, 1, 32), AI_STRIDE_INIT(4, 1, 3, 96, 480),
  1, &conv2d_3_weights_array, &conv2d_3_weights_array_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_0_output, AI_STATIC,
  13, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 1, 96), AI_STRIDE_INIT(4, 1, 1, 3, 3),
  1, &eltwise_0_output_array, &eltwise_0_output_array_intq)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_12_output, AI_STATIC,
  14, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 42, 1), AI_STRIDE_INIT(4, 1, 1, 64, 2688),
  1, &eltwise_12_output_array, &eltwise_12_output_array_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_13_output, AI_STATIC,
  15, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 42, 1), AI_STRIDE_INIT(4, 1, 1, 64, 2688),
  1, &eltwise_13_output_array, &eltwise_13_output_array_intq)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_1_output, AI_STATIC,
  16, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 1, 96), AI_STRIDE_INIT(4, 1, 1, 3, 3),
  1, &eltwise_1_output_array, &eltwise_1_output_array_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_1_output0, AI_STATIC,
  17, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 96, 1), AI_STRIDE_INIT(4, 1, 1, 3, 288),
  1, &eltwise_1_output_array, &eltwise_1_output_array_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_7_output, AI_STATIC,
  18, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 46, 1), AI_STRIDE_INIT(4, 1, 1, 32, 1472),
  1, &eltwise_7_output_array, &eltwise_7_output_array_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  eltwise_8_output, AI_STATIC,
  19, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 46, 1), AI_STRIDE_INIT(4, 1, 1, 32, 1472),
  1, &eltwise_8_output_array, &eltwise_8_output_array_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  gemm_19_bias, AI_STATIC,
  20, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &gemm_19_bias_array, NULL)

/* Tensor #21 */
AI_TENSOR_OBJ_DECLARE(
  gemm_19_output, AI_STATIC,
  21, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &gemm_19_output_array, &gemm_19_output_array_intq)

/* Tensor #22 */
AI_TENSOR_OBJ_DECLARE(
  gemm_19_scratch0, AI_STATIC,
  22, 0x0,
  AI_SHAPE_INIT(4, 1, 416, 1, 1), AI_STRIDE_INIT(4, 2, 2, 832, 832),
  1, &gemm_19_scratch0_array, NULL)

/* Tensor #23 */
AI_TENSOR_OBJ_DECLARE(
  gemm_19_weights, AI_STATIC,
  23, 0x1,
  AI_SHAPE_INIT(4, 96, 64, 1, 1), AI_STRIDE_INIT(4, 1, 96, 6144, 6144),
  1, &gemm_19_weights_array, &gemm_19_weights_array_intq)

/* Tensor #24 */
AI_TENSOR_OBJ_DECLARE(
  gemm_20_bias, AI_STATIC,
  24, 0x0,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 4, 4, 28, 28),
  1, &gemm_20_bias_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  gemm_20_output, AI_STATIC,
  25, 0x1,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7, 7),
  1, &gemm_20_output_array, &gemm_20_output_array_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  gemm_20_scratch0, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 99, 1, 1), AI_STRIDE_INIT(4, 2, 2, 198, 198),
  1, &gemm_20_scratch0_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  gemm_20_weights, AI_STATIC,
  27, 0x1,
  AI_SHAPE_INIT(4, 64, 7, 1, 1), AI_STRIDE_INIT(4, 1, 64, 448, 448),
  1, &gemm_20_weights_array, &gemm_20_weights_array_intq)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  nl_21_output, AI_STATIC,
  28, 0x1,
  AI_SHAPE_INIT(4, 1, 7, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7, 7),
  1, &nl_21_output_array, &nl_21_output_array_intq)

/* Tensor #29 */
AI_TENSOR_OBJ_DECLARE(
  nl_21_scratch0, AI_STATIC,
  29, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 4, 4, 12, 12),
  1, &nl_21_scratch0_array, NULL)

/* Tensor #30 */
AI_TENSOR_OBJ_DECLARE(
  pool_18_output, AI_STATIC,
  30, 0x1,
  AI_SHAPE_INIT(4, 1, 96, 1, 1), AI_STRIDE_INIT(4, 1, 1, 96, 96),
  1, &pool_18_output_array, &pool_18_output_array_intq)

/* Tensor #31 */
AI_TENSOR_OBJ_DECLARE(
  pool_6_output, AI_STATIC,
  31, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 46, 1), AI_STRIDE_INIT(4, 1, 1, 32, 1472),
  1, &pool_6_output_array, &pool_6_output_array_intq)

/* Tensor #32 */
AI_TENSOR_OBJ_DECLARE(
  serving_default_input_layer0_output, AI_STATIC,
  32, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 1, 96), AI_STRIDE_INIT(4, 1, 1, 3, 3),
  1, &serving_default_input_layer0_output_array, &serving_default_input_layer0_output_array_intq)

/* Tensor #33 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst10_4D, AI_STATIC,
  33, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 1, 1, 32, 32),
  1, &tfl_pseudo_qconst10_4D_array, &tfl_pseudo_qconst10_4D_array_intq)

/* Tensor #34 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst11_4D, AI_STATIC,
  34, 0x1,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 1, 1, 32, 32),
  1, &tfl_pseudo_qconst11_4D_array, &tfl_pseudo_qconst11_4D_array_intq)

/* Tensor #35 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst14_3D, AI_STATIC,
  35, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 1, 1, 3, 3),
  1, &tfl_pseudo_qconst14_3D_array, &tfl_pseudo_qconst14_3D_array_intq)

/* Tensor #36 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst15_3D, AI_STATIC,
  36, 0x1,
  AI_SHAPE_INIT(4, 1, 3, 1, 1), AI_STRIDE_INIT(4, 1, 1, 3, 3),
  1, &tfl_pseudo_qconst15_3D_array, &tfl_pseudo_qconst15_3D_array_intq)

/* Tensor #37 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst6_4D, AI_STATIC,
  37, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &tfl_pseudo_qconst6_4D_array, &tfl_pseudo_qconst6_4D_array_intq)

/* Tensor #38 */
AI_TENSOR_OBJ_DECLARE(
  tfl_pseudo_qconst7_4D, AI_STATIC,
  38, 0x1,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 1, 1, 64, 64),
  1, &tfl_pseudo_qconst7_4D_array, &tfl_pseudo_qconst7_4D_array_intq)



/**  Layer declarations section  **********************************************/



AI_STATIC_CONST ai_i32 nl_21_nl_params_data[] = { 1236079744, 29, -3 };
AI_ARRAY_OBJ_DECLARE(
    nl_21_nl_params, AI_ARRAY_FORMAT_S32,
    nl_21_nl_params_data, nl_21_nl_params_data, 3, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_21_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_20_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_21_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_21_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  nl_21_layer, 21,
  SM_TYPE, 0x0, NULL,
  sm, forward_sm_integer,
  &nl_21_chain,
  NULL, &nl_21_layer, AI_STATIC, 
  .nl_params = &nl_21_nl_params, 
  .axis = AI_SHAPE_CHANNEL, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_20_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_19_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_20_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_20_weights, &gemm_20_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_20_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_20_layer, 20,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_20_chain,
  NULL, &nl_21_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  gemm_19_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_18_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_19_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &gemm_19_weights, &gemm_19_bias),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &gemm_19_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  gemm_19_layer, 19,
  DENSE_TYPE, 0x0, NULL,
  dense, forward_dense_integer_SSSA_ch,
  &gemm_19_chain,
  NULL, &gemm_20_layer, AI_STATIC, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_18_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_18_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_18_layer, 18,
  POOL_TYPE, 0x0, NULL,
  pool, forward_ap_integer_INT8,
  &pool_18_chain,
  NULL, &gemm_19_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(1, 40), 
  .pool_stride = AI_SHAPE_2D_INIT(1, 40), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_16_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_13_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_16_weights, &conv2d_16_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_16_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_16_layer, 16,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_deep_sssa8_ch,
  &conv2d_16_chain,
  NULL, &pool_18_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_13_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_12_output, &tfl_pseudo_qconst6_4D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_13_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_13_layer, 13,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_13_chain,
  NULL, &conv2d_16_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_12_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_11_output, &tfl_pseudo_qconst7_4D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_12_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_12_layer, 12,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_12_chain,
  NULL, &eltwise_13_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_11_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_11_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_11_weights, &conv2d_11_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_11_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_11_layer, 11,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_deep_sssa8_ch,
  &conv2d_11_chain,
  NULL, &eltwise_12_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_8_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_7_output, &tfl_pseudo_qconst10_4D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_8_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_8_layer, 8,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_8_chain,
  NULL, &conv2d_11_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &pool_6_output, &tfl_pseudo_qconst11_4D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_7_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_7_layer, 7,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_7_chain,
  NULL, &eltwise_8_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  pool_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &pool_6_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  pool_6_layer, 6,
  POOL_TYPE, 0x0, NULL,
  pool, forward_mp_integer_INT8,
  &pool_6_chain,
  NULL, &eltwise_7_layer, AI_STATIC, 
  .pool_size = AI_SHAPE_2D_INIT(2, 1), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 1), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_1_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_scratch0)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 3,
  CONV2D_TYPE, 0x0, NULL,
  conv2d, forward_conv2d_sssa8_ch,
  &conv2d_3_chain,
  NULL, &pool_6_layer, AI_STATIC, 
  .groups = 1, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .in_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
  .out_ch_format = AI_LAYER_FORMAT_CHANNEL_LAST_VALID, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &eltwise_0_output, &tfl_pseudo_qconst14_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_1_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_1_layer, 1,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_1_chain,
  NULL, &conv2d_3_layer, AI_STATIC, 
  .operation = ai_sum_f32, 
  .buffer_operation = ai_sum_buffer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  eltwise_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &serving_default_input_layer0_output, &tfl_pseudo_qconst15_3D),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &eltwise_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  eltwise_0_layer, 0,
  ELTWISE_INTEGER_TYPE, 0x0, NULL,
  eltwise_integer, forward_eltwise_integer_INT8,
  &eltwise_0_chain,
  NULL, &eltwise_1_layer, AI_STATIC, 
  .operation = ai_mul_f32, 
  .buffer_operation = ai_mul_buffer_INT8, 
)


#if (AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 36996, 1, 1),
    36996, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 13760, 1, 1),
    13760, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &serving_default_input_layer0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &nl_21_output),
  &eltwise_0_layer, 0xcede1ed1, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 36996, 1, 1),
      36996, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 13760, 1, 1),
      13760, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &serving_default_input_layer0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &nl_21_output),
  &eltwise_0_layer, 0xcede1ed1, NULL)

#endif	/*(AI_TOOLS_API_VERSION < AI_TOOLS_API_VERSION_1_5)*/



/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_activations(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_activations_map(g_network_activations_map, 1, params)) {
    /* Updating activations (byte) offsets */
    
    serving_default_input_layer0_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    serving_default_input_layer0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_0_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_0_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_1_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_1_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    conv2d_3_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 1440);
    conv2d_3_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 1440);
    conv2d_3_output_array.data = AI_PTR(g_network_activations_map[0] + 2908);
    conv2d_3_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2908);
    pool_6_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    pool_6_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_7_output_array.data = AI_PTR(g_network_activations_map[0] + 2624);
    eltwise_7_output_array.data_start = AI_PTR(g_network_activations_map[0] + 2624);
    eltwise_8_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_8_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    conv2d_11_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 2624);
    conv2d_11_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 2624);
    conv2d_11_output_array.data = AI_PTR(g_network_activations_map[0] + 9280);
    conv2d_11_output_array.data_start = AI_PTR(g_network_activations_map[0] + 9280);
    eltwise_12_output_array.data = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_12_output_array.data_start = AI_PTR(g_network_activations_map[0] + 1152);
    eltwise_13_output_array.data = AI_PTR(g_network_activations_map[0] + 3840);
    eltwise_13_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3840);
    conv2d_16_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 6528);
    conv2d_16_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 6528);
    conv2d_16_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    conv2d_16_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    pool_18_output_array.data = AI_PTR(g_network_activations_map[0] + 3840);
    pool_18_output_array.data_start = AI_PTR(g_network_activations_map[0] + 3840);
    gemm_19_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    gemm_19_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    gemm_19_output_array.data = AI_PTR(g_network_activations_map[0] + 832);
    gemm_19_output_array.data_start = AI_PTR(g_network_activations_map[0] + 832);
    gemm_20_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    gemm_20_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    gemm_20_output_array.data = AI_PTR(g_network_activations_map[0] + 200);
    gemm_20_output_array.data_start = AI_PTR(g_network_activations_map[0] + 200);
    nl_21_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_21_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
    nl_21_output_array.data = AI_PTR(g_network_activations_map[0] + 12);
    nl_21_output_array.data_start = AI_PTR(g_network_activations_map[0] + 12);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_ACTIVATIONS);
  return false;
}




/******************************************************************************/
AI_DECLARE_STATIC
ai_bool network_configure_weights(
  ai_network* net_ctx, const ai_network_params* params)
{
  AI_ASSERT(net_ctx)

  if (ai_platform_get_weights_map(g_network_weights_map, 1, params)) {
    /* Updating weights (byte) offsets */
    
    tfl_pseudo_qconst15_3D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst15_3D_array.data = AI_PTR(g_network_weights_map[0] + 0);
    tfl_pseudo_qconst15_3D_array.data_start = AI_PTR(g_network_weights_map[0] + 0);
    tfl_pseudo_qconst14_3D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst14_3D_array.data = AI_PTR(g_network_weights_map[0] + 4);
    tfl_pseudo_qconst14_3D_array.data_start = AI_PTR(g_network_weights_map[0] + 4);
    tfl_pseudo_qconst11_4D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst11_4D_array.data = AI_PTR(g_network_weights_map[0] + 8);
    tfl_pseudo_qconst11_4D_array.data_start = AI_PTR(g_network_weights_map[0] + 8);
    tfl_pseudo_qconst10_4D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst10_4D_array.data = AI_PTR(g_network_weights_map[0] + 40);
    tfl_pseudo_qconst10_4D_array.data_start = AI_PTR(g_network_weights_map[0] + 40);
    tfl_pseudo_qconst7_4D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst7_4D_array.data = AI_PTR(g_network_weights_map[0] + 72);
    tfl_pseudo_qconst7_4D_array.data_start = AI_PTR(g_network_weights_map[0] + 72);
    tfl_pseudo_qconst6_4D_array.format |= AI_FMT_FLAG_CONST;
    tfl_pseudo_qconst6_4D_array.data = AI_PTR(g_network_weights_map[0] + 136);
    tfl_pseudo_qconst6_4D_array.data_start = AI_PTR(g_network_weights_map[0] + 136);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(g_network_weights_map[0] + 200);
    conv2d_3_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 200);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(g_network_weights_map[0] + 680);
    conv2d_3_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 680);
    conv2d_11_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_11_weights_array.data = AI_PTR(g_network_weights_map[0] + 808);
    conv2d_11_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 808);
    conv2d_11_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_11_bias_array.data = AI_PTR(g_network_weights_map[0] + 11048);
    conv2d_11_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 11048);
    conv2d_16_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_16_weights_array.data = AI_PTR(g_network_weights_map[0] + 11304);
    conv2d_16_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 11304);
    conv2d_16_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_16_bias_array.data = AI_PTR(g_network_weights_map[0] + 29736);
    conv2d_16_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 29736);
    gemm_19_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_19_weights_array.data = AI_PTR(g_network_weights_map[0] + 30120);
    gemm_19_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 30120);
    gemm_19_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_19_bias_array.data = AI_PTR(g_network_weights_map[0] + 36264);
    gemm_19_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 36264);
    gemm_20_weights_array.format |= AI_FMT_FLAG_CONST;
    gemm_20_weights_array.data = AI_PTR(g_network_weights_map[0] + 36520);
    gemm_20_weights_array.data_start = AI_PTR(g_network_weights_map[0] + 36520);
    gemm_20_bias_array.format |= AI_FMT_FLAG_CONST;
    gemm_20_bias_array.data = AI_PTR(g_network_weights_map[0] + 36968);
    gemm_20_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 36968);
    return true;
  }
  AI_ERROR_TRAP(net_ctx, INIT_FAILED, NETWORK_WEIGHTS);
  return false;
}


/**  PUBLIC APIs SECTION  *****************************************************/



AI_DEPRECATED
AI_API_ENTRY
ai_bool ai_network_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1234160,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0xcede1ed1,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}



AI_API_ENTRY
ai_bool ai_network_get_report(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if (report && net_ctx)
  {
    ai_network_report r = {
      .model_name        = AI_NETWORK_MODEL_NAME,
      .model_signature   = AI_NETWORK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = AI_STRUCT_INIT,

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 1234160,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0xcede1ed1,
    };

    if (!ai_platform_api_get_network_report(network, &r)) return false;

    *report = r;
    return true;
  }
  return false;
}


AI_API_ENTRY
ai_error ai_network_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}


AI_API_ENTRY
ai_error ai_network_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    AI_CONTEXT_OBJ(&AI_NET_OBJ_INSTANCE),
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}


AI_API_ENTRY
ai_error ai_network_create_and_init(
  ai_handle* network, const ai_handle activations[], const ai_handle weights[])
{
  ai_error err;
  ai_network_params params;

  err = ai_network_create(network, AI_NETWORK_DATA_CONFIG);
  if (err.type != AI_ERROR_NONE) {
    return err;
  }
  
  if (ai_network_data_params_get(&params) != true) {
    err = ai_network_get_error(*network);
    return err;
  }
#if defined(AI_NETWORK_DATA_ACTIVATIONS_COUNT)
  /* set the addresses of the activations buffers */
  for (ai_u16 idx=0; activations && idx<params.map_activations.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_activations, idx, activations[idx]);
  }
#endif
#if defined(AI_NETWORK_DATA_WEIGHTS_COUNT)
  /* set the addresses of the weight buffers */
  for (ai_u16 idx=0; weights && idx<params.map_weights.size; idx++) {
    AI_BUFFER_ARRAY_ITEM_SET_ADDRESS(&params.map_weights, idx, weights[idx]);
  }
#endif
  if (ai_network_init(*network, &params) != true) {
    err = ai_network_get_error(*network);
  }
  return err;
}


AI_API_ENTRY
ai_buffer* ai_network_inputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_inputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_buffer* ai_network_outputs_get(ai_handle network, ai_u16 *n_buffer)
{
  if (network == AI_HANDLE_NULL) {
    network = (ai_handle)&AI_NET_OBJ_INSTANCE;
    AI_NETWORK_OBJ(network)->magic = AI_MAGIC_CONTEXT_TOKEN;
  }
  return ai_platform_outputs_get(network, n_buffer);
}


AI_API_ENTRY
ai_handle ai_network_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}


AI_API_ENTRY
ai_bool ai_network_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = AI_NETWORK_OBJ(ai_platform_network_init(network, params));
  ai_bool ok = true;

  if (!net_ctx) return false;
  ok &= network_configure_weights(net_ctx, params);
  ok &= network_configure_activations(net_ctx, params);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_network_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}


AI_API_ENTRY
ai_i32 ai_network_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}



#undef AI_NETWORK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

