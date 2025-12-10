/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-12-10T22:07:28+0200
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
#define AI_NETWORK_MODEL_SIGNATURE     "0x6641486b2180088aa476006e4b29e3da"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2025-12-10T22:07:28+0200"

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
  NULL, NULL, 248, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_11_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0828041359782219f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_11_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0024957149289548397f, 0.0019553478341549635f, 0.0020887108985334635f, 0.0018777153454720974f, 0.002110313158482313f, 0.002286995528265834f, 0.0022147679701447487f, 0.0022292251233011484f, 0.001890431041829288f, 0.0022244760766625404f, 0.002692221896722913f, 0.002288001123815775f, 0.0020799648482352495f, 0.0022510304115712643f, 0.002173843327909708f, 0.002280728192999959f, 0.0028737341053783894f, 0.002037476748228073f, 0.002766874385997653f, 0.0030293832533061504f, 0.0020775918383151293f, 0.0019783780444413424f, 0.00212995451875031f, 0.002075875410810113f, 0.0020666327327489853f, 0.0020321724005043507f, 0.0019683365244418383f, 0.002300841733813286f, 0.002174339024350047f, 0.002880165819078684f, 0.0021823851857334375f, 0.002017098478972912f, 0.002218505134806037f, 0.002097369870170951f, 0.0017301180632784963f, 0.0021126149222254753f, 0.0021555316634476185f, 0.0019511786522343755f, 0.002510379534214735f, 0.0022999567445367575f, 0.0031718802638351917f, 0.0026466900017112494f, 0.002083737403154373f, 0.0024975177366286516f, 0.00236452161334455f, 0.0018099952721968293f, 0.0021600413601845503f, 0.002387857995927334f, 0.0021118123549968004f, 0.00257839635014534f, 0.0024352315813302994f, 0.002026109956204891f, 0.002755650319159031f, 0.0036333249881863594f, 0.0024259232450276613f, 0.002293184632435441f, 0.0026095793582499027f, 0.0020339107140898705f, 0.001925873919390142f, 0.0019555208273231983f, 0.0028464391361922026f, 0.002007134724408388f, 0.002060595201328397f, 0.0019754741806536913f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05533688887953758f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 96,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0019941485952585936f, 0.0021550736855715513f, 0.0021326756104826927f, 0.002025287365540862f, 0.002051437273621559f, 0.0021045859903097153f, 0.0018574032001197338f, 0.0029993378557264805f, 0.0026924614794552326f, 0.0031311381608247757f, 0.002078533871099353f, 0.0022448759991675615f, 0.0022747402545064688f, 0.0023879215586930513f, 0.002219113986939192f, 0.002112479880452156f, 0.0026924426201730967f, 0.0019576011691242456f, 0.0025433183182030916f, 0.0022703944705426693f, 0.002293907105922699f, 0.001970184501260519f, 0.002733534201979637f, 0.0022297613322734833f, 0.0021635296288877726f, 0.0020832139998674393f, 0.002078712685033679f, 0.0023001711815595627f, 0.0022886714432388544f, 0.002052851254120469f, 0.0022027476225048304f, 0.002330184681341052f, 0.0027459817938506603f, 0.002375776646658778f, 0.002578414510935545f, 0.0020904839038848877f, 0.0022645548451691866f, 0.002287871902808547f, 0.002274556318297982f, 0.0019366563064977527f, 0.002484563970938325f, 0.0026501857209950686f, 0.0021603007335215807f, 0.0022570830769836903f, 0.0025563316885381937f, 0.002749685663729906f, 0.001992808422073722f, 0.001922544208355248f, 0.0020233825780451298f, 0.0026849915739148855f, 0.0024601402692496777f, 0.002737954957410693f, 0.0022131477016955614f, 0.0020991493947803974f, 0.0025650658644735813f, 0.0022815479896962643f, 0.0022829801309853792f, 0.0018830059561878443f, 0.0017274155979976058f, 0.0019667879678308964f, 0.0026601918507367373f, 0.0033604444470256567f, 0.002096720738336444f, 0.0025048323441296816f, 0.002115986542776227f, 0.0021507199853658676f, 0.0018291739979758859f, 0.003227870911359787f, 0.0022354936227202415f, 0.0021080649457871914f, 0.0022078626789152622f, 0.002248685108497739f, 0.002040398772805929f, 0.0021002276334911585f, 0.0028621123638004065f, 0.002242402173578739f, 0.002548214513808489f, 0.001934404019266367f, 0.002009171526879072f, 0.0019835212733596563f, 0.00215497356839478f, 0.002165884943678975f, 0.002171690808609128f, 0.002040168270468712f, 0.0024229269474744797f, 0.002262947615236044f, 0.0020476565696299076f, 0.0024479113053530455f, 0.0025118491612374783f, 0.002114079659804702f, 0.0020958748646080494f, 0.0020250948145985603f, 0.002620553132146597f, 0.0021637578029185534f, 0.001997490646317601f, 0.002679739845916629f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.060914959758520126f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004699139390140772f, 0.004046765621751547f, 0.004916546866297722f, 0.005240487400442362f, 0.004849424120038748f, 0.0051909699104726315f, 0.0049764374271035194f, 0.004670529160648584f, 0.004735712427645922f, 0.005064614582806826f, 0.0043556587770581245f, 0.004136044532060623f, 0.004934275988489389f, 0.004885726608335972f, 0.00430604163557291f, 0.004754232708364725f, 0.0048787640407681465f, 0.0061007230542600155f, 0.005012075416743755f, 0.0055701551027596f, 0.0051109944470226765f, 0.004586942493915558f, 0.00468724500387907f, 0.004945520777255297f, 0.004168510902673006f, 0.004323047585785389f, 0.003920239396393299f, 0.005556039046496153f, 0.005128313321620226f, 0.004864933900535107f, 0.005018812604248524f, 0.0050381324253976345f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04054715111851692f),
    AI_PACK_INTQ_ZP(4)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_12_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0764584168791771f),
    AI_PACK_INTQ_ZP(-112)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_13_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0764584168791771f),
    AI_PACK_INTQ_ZP(-112)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_1_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04034842178225517f),
    AI_PACK_INTQ_ZP(5)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_7_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08449401706457138f),
    AI_PACK_INTQ_ZP(-117)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_8_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0834125429391861f),
    AI_PACK_INTQ_ZP(-116)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_19_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.03719619661569595f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_19_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07033205777406693f, 0.0770677924156189f, 0.06928287446498871f, 0.06091494485735893f, 0.09221839159727097f, 0.0983424112200737f, 0.05447923764586449f, 0.0721464529633522f, 0.09371397644281387f, 0.1029602661728859f, 0.06443124264478683f, 0.07278507947921753f, 0.08138365298509598f, 0.0839635580778122f, 0.06677942723035812f, 0.07791758328676224f, 0.09233464300632477f, 0.09361019730567932f, 0.0636470764875412f, 0.07823498547077179f, 0.0427495501935482f, 0.059915073215961456f, 0.10001218318939209f, 0.10612253844738007f, 0.1362573802471161f, 0.0847788155078888f, 0.07941820472478867f, 0.07497948408126831f, 0.09945568442344666f, 0.08193599432706833f, 0.06276509165763855f, 0.0939716100692749f, 0.06716921180486679f, 0.09530951082706451f, 0.09073818475008011f, 0.09240508079528809f, 0.062161680310964584f, 0.0681024044752121f, 0.13049565255641937f, 0.06441296637058258f, 0.10284383594989777f, 0.07767345756292343f, 0.09541750699281693f, 0.06237727031111717f, 0.056938473135232925f, 0.08012815564870834f, 0.05258312076330185f, 0.10999049246311188f, 0.09488321095705032f, 0.06482100486755371f, 0.068696528673172f, 0.06075567007064819f, 0.0503084696829319f, 0.06482107937335968f, 0.06474688649177551f, 0.0715491995215416f, 0.11715535819530487f, 0.061285071074962616f, 0.07331886887550354f, 0.09086020290851593f, 0.0663365051150322f, 0.055448099970817566f, 0.07983925193548203f, 0.08209134638309479f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_20_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.09440281987190247f),
    AI_PACK_INTQ_ZP(-40)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_20_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 7,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005249878391623497f, 0.003448191564530134f, 0.004102274309843779f, 0.004186207894235849f, 0.0037703095003962517f, 0.0033030647318810225f, 0.003267494263127446f),
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
    AI_PACK_INTQ_SCALE(0.014469647780060768f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_6_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.060914959758520126f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_input_layer0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.052613284438848495f),
    AI_PACK_INTQ_ZP(3)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst10_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003792748786509037f),
    AI_PACK_INTQ_ZP(127)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst11_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.012110224924981594f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst14_3D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00035838005715049803f),
    AI_PACK_INTQ_ZP(13)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst15_3D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004641900770366192f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #24 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst6_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005373277701437473f),
    AI_PACK_INTQ_ZP(105)))

/* Int quant #25 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst7_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.008382037281990051f),
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
  AI_SHAPE_INIT(4, 1, 248, 1, 1), AI_STRIDE_INIT(4, 4, 4, 992, 992),
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



AI_STATIC_CONST ai_i32 nl_21_nl_params_data[] = { 1621828096, 23, -248 };
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
  &eltwise_0_layer, 0x30c02444, NULL)

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
  &eltwise_0_layer, 0x30c02444, NULL)

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
    nl_21_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 208);
    nl_21_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 208);
    nl_21_output_array.data = AI_PTR(g_network_activations_map[0] + 0);
    nl_21_output_array.data_start = AI_PTR(g_network_activations_map[0] + 0);
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
      .signature         = 0x30c02444,
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
      .signature         = 0x30c02444,
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

