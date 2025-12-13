/**
  ******************************************************************************
  * @file    network.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2025-12-12T19:32:28+0200
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
#define AI_NETWORK_MODEL_SIGNATURE     "0xa6d58b4820c67477c0c94b167e56146b"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     ""
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "2025-12-12T19:32:28+0200"

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
  NULL, NULL, 5, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  nl_21_output_array, AI_ARRAY_FORMAT_S8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 5, AI_STATIC)

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
  NULL, NULL, 320, AI_STATIC)

/* Array#30 */
AI_ARRAY_OBJ_DECLARE(
  gemm_20_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 5, AI_STATIC)

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
  NULL, NULL, 89, AI_STATIC)

/* Array#36 */
AI_ARRAY_OBJ_DECLARE(
  nl_21_scratch0_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 248, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_11_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08246849477291107f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_11_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002492628525942564f, 0.0025087117683142424f, 0.00219863373786211f, 0.002368567744269967f, 0.0025440831668674946f, 0.0022873315028846264f, 0.002488520462065935f, 0.0023111130576580763f, 0.0023329444229602814f, 0.00252024014480412f, 0.0026176085229963064f, 0.00323754595592618f, 0.002257366431877017f, 0.0025682959239929914f, 0.0026848705019801855f, 0.002290181815624237f, 0.0025450480170547962f, 0.00274792336858809f, 0.00278818653896451f, 0.002764172153547406f, 0.002849512966349721f, 0.0024392439518123865f, 0.0027706504333764315f, 0.0025273754727095366f, 0.002115623326972127f, 0.0022097507026046515f, 0.002752346685156226f, 0.0030443170107901096f, 0.0028033265843987465f, 0.0031223855912685394f, 0.0019670871552079916f, 0.003412507241591811f, 0.0023112010676413774f, 0.003076246939599514f, 0.003475752891972661f, 0.0022123518865555525f, 0.0024067244958132505f, 0.0023683207109570503f, 0.002536175074055791f, 0.0021037461701780558f, 0.0021637137979269028f, 0.0026105022989213467f, 0.0026890579611063004f, 0.0028477420564740896f, 0.0024761382956057787f, 0.0025496177840977907f, 0.0024077342823147774f, 0.0024810724426060915f, 0.002334856428205967f, 0.002302254782989621f, 0.0024053810629993677f, 0.002321281237527728f, 0.00252727628685534f, 0.002063525840640068f, 0.0022486625239253044f, 0.002161267679184675f, 0.0022927529644221067f, 0.0029634740203619003f, 0.00254056672565639f, 0.0028140770737081766f, 0.002732699504122138f, 0.002147210296243429f, 0.0025447066873311996f, 0.0023392701987177134f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.048655226826667786f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_16_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 96,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002366205444559455f, 0.0024910501670092344f, 0.002891435520723462f, 0.0028582133818417788f, 0.0020584724843502045f, 0.0022549545392394066f, 0.0021072514355182648f, 0.002569877542555332f, 0.003230511909350753f, 0.002527037635445595f, 0.0024580133613198996f, 0.002900574589148164f, 0.0027672939468175173f, 0.0023676096461713314f, 0.0023679216392338276f, 0.0029870038852095604f, 0.002642597071826458f, 0.002518582157790661f, 0.0027029849588871002f, 0.002564887050539255f, 0.0025594269391149282f, 0.0024204954970628023f, 0.0025942400097846985f, 0.002432991983368993f, 0.002832163590937853f, 0.002440235111862421f, 0.0025730349589139223f, 0.0025339529383927584f, 0.0028380975127220154f, 0.0028181246016174555f, 0.0021807276643812656f, 0.0022386908531188965f, 0.0027107454370707273f, 0.002720569260418415f, 0.0025259056128561497f, 0.0024355945643037558f, 0.0031422742176800966f, 0.0021333061158657074f, 0.002564180875197053f, 0.0037621259689331055f, 0.0030400720424950123f, 0.002397500677034259f, 0.0019829138182103634f, 0.0022672577761113644f, 0.0025888204108923674f, 0.0021755031775683165f, 0.002555843209847808f, 0.0026151908095926046f, 0.002819436602294445f, 0.002726937411352992f, 0.0030635595321655273f, 0.002129854867234826f, 0.002226915443316102f, 0.0024575605057179928f, 0.0025809835642576218f, 0.002397660631686449f, 0.0030686981044709682f, 0.0027162397745996714f, 0.0030944428872317076f, 0.0022568353451788425f, 0.0023733805865049362f, 0.002627098001539707f, 0.0023095037322491407f, 0.002718623261898756f, 0.0028522249776870012f, 0.002770343329757452f, 0.002829186851158738f, 0.0023407801054418087f, 0.0028839297592639923f, 0.0029012856539338827f, 0.00236132531426847f, 0.0022304526064544916f, 0.0027502444572746754f, 0.0029033359605818987f, 0.0023578202817589045f, 0.002478082897141576f, 0.0028285598382353783f, 0.0024467865005135536f, 0.0031928210519254208f, 0.0022554914467036724f, 0.003477894002571702f, 0.0022010779939591885f, 0.0026287161745131016f, 0.0027935111429542303f, 0.002592487493529916f, 0.0024175532162189484f, 0.003491763724014163f, 0.002463767770677805f, 0.0025075313169509172f, 0.00274978531524539f, 0.0026134334038943052f, 0.0023120243567973375f, 0.0022586409468203783f, 0.002663625404238701f, 0.002004152862355113f, 0.0027321483939886093f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.053868409246206284f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.004821412730962038f, 0.005284507758915424f, 0.005058849696069956f, 0.0038495396729558706f, 0.0064059654250741005f, 0.008072346448898315f, 0.004882181994616985f, 0.0051886169239878654f, 0.004861411172896624f, 0.00554020656272769f, 0.004860750399529934f, 0.005897655617445707f, 0.005464198067784309f, 0.003952201921492815f, 0.004568061791360378f, 0.005813957657665014f, 0.0042379992082715034f, 0.004808785859495401f, 0.004736609291285276f, 0.005651689600199461f, 0.004341993946582079f, 0.004753955639898777f, 0.005868591833859682f, 0.00434513483196497f, 0.004811999388039112f, 0.004364912863820791f, 0.004980609752237797f, 0.0057787648402154446f, 0.004070187918841839f, 0.004337254911661148f, 0.004956539254635572f, 0.00593649223446846f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04115728661417961f),
    AI_PACK_INTQ_ZP(14)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_12_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07364504039287567f),
    AI_PACK_INTQ_ZP(-111)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_13_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.07309920340776443f),
    AI_PACK_INTQ_ZP(-110)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_1_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04103567451238632f),
    AI_PACK_INTQ_ZP(14)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_7_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08245918899774551f),
    AI_PACK_INTQ_ZP(-118)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(eltwise_8_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.08022891730070114f),
    AI_PACK_INTQ_ZP(-118)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_19_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.030520237982273102f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_19_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.14333847165107727f, 0.12220998108386993f, 0.07695455849170685f, 0.1338643580675125f, 0.10996931791305542f, 0.10375548899173737f, 0.22419172525405884f, 0.10192655026912689f, 0.08610609918832779f, 0.11446172744035721f, 0.08746061474084854f, 0.07601407170295715f, 0.13083162903785706f, 0.16718140244483948f, 0.07877589762210846f, 0.08490526676177979f, 0.09722565114498138f, 0.10852378606796265f, 0.07131025195121765f, 0.11736533790826797f, 0.0997239202260971f, 0.11413739621639252f, 0.14227740466594696f, 0.08004987984895706f, 0.22850890457630157f, 0.08245153725147247f, 0.09624729305505753f, 0.11962894350290298f, 0.1319451630115509f, 0.11467622965574265f, 0.11708906292915344f, 0.0979384183883667f, 0.122331902384758f, 0.09103120863437653f, 0.12394414097070694f, 0.13324791193008423f, 0.10470230132341385f, 0.13974307477474213f, 0.14845438301563263f, 0.19684581458568573f, 0.10695457458496094f, 0.10881004482507706f, 0.13881605863571167f, 0.1199931725859642f, 0.08393694460391998f, 0.09322459250688553f, 0.1649586409330368f, 0.08882729709148407f, 0.1103253960609436f, 0.13991579413414001f, 0.08747364580631256f, 0.1264507919549942f, 0.08171096444129944f, 0.10388261079788208f, 0.12098284810781479f, 0.15276314318180084f, 0.12951502203941345f, 0.12985649704933167f, 0.09227882325649261f, 0.10304751247167587f, 0.12354940176010132f, 0.13104046881198883f, 0.1323850452899933f, 0.11656209826469421f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_20_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.11034243553876877f),
    AI_PACK_INTQ_ZP(-31)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(gemm_20_weights_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 5,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.006680928170681f, 0.005048595834523439f, 0.00534351821988821f, 0.0036399108357727528f, 0.005979482084512711f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0)))

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
    AI_PACK_INTQ_SCALE(0.008634453639388084f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #18 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(pool_6_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.053868409246206284f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #19 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(serving_default_input_layer0_output_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.05421698838472366f),
    AI_PACK_INTQ_ZP(7)))

/* Int quant #20 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst10_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003273144830018282f),
    AI_PACK_INTQ_ZP(127)))

/* Int quant #21 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst11_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.012789036147296429f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #22 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst14_3D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0003524189523886889f),
    AI_PACK_INTQ_ZP(11)))

/* Int quant #23 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst15_3D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005073641426861286f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #24 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst6_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.005974419880658388f),
    AI_PACK_INTQ_ZP(87)))

/* Int quant #25 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(tfl_pseudo_qconst7_4D_array_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.006154219154268503f),
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
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 4, 4, 20, 20),
  1, &gemm_20_bias_array, NULL)

/* Tensor #25 */
AI_TENSOR_OBJ_DECLARE(
  gemm_20_output, AI_STATIC,
  25, 0x1,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 1, 1, 5, 5),
  1, &gemm_20_output_array, &gemm_20_output_array_intq)

/* Tensor #26 */
AI_TENSOR_OBJ_DECLARE(
  gemm_20_scratch0, AI_STATIC,
  26, 0x0,
  AI_SHAPE_INIT(4, 1, 89, 1, 1), AI_STRIDE_INIT(4, 2, 2, 178, 178),
  1, &gemm_20_scratch0_array, NULL)

/* Tensor #27 */
AI_TENSOR_OBJ_DECLARE(
  gemm_20_weights, AI_STATIC,
  27, 0x1,
  AI_SHAPE_INIT(4, 64, 5, 1, 1), AI_STRIDE_INIT(4, 1, 64, 320, 320),
  1, &gemm_20_weights_array, &gemm_20_weights_array_intq)

/* Tensor #28 */
AI_TENSOR_OBJ_DECLARE(
  nl_21_output, AI_STATIC,
  28, 0x1,
  AI_SHAPE_INIT(4, 1, 5, 1, 1), AI_STRIDE_INIT(4, 1, 1, 5, 5),
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



AI_STATIC_CONST ai_i32 nl_21_nl_params_data[] = { 1895668608, 23, -248 };
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
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 36860, 1, 1),
    36860, NULL, NULL),
  AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
    AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 13760, 1, 1),
    13760, NULL, NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &serving_default_input_layer0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &nl_21_output),
  &eltwise_0_layer, 0x475d4acb, NULL)

#else

AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 36860, 1, 1),
      36860, NULL, NULL)
  ),
  AI_BUFFER_ARRAY_OBJ_INIT_STATIC(
  	AI_FLAG_NONE, 1,
    AI_BUFFER_INIT(AI_FLAG_NONE,  AI_BUFFER_FORMAT_U8,
      AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 13760, 1, 1),
      13760, NULL, NULL)
  ),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_IN_NUM, &serving_default_input_layer0_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_NETWORK_OUT_NUM, &nl_21_output),
  &eltwise_0_layer, 0x475d4acb, NULL)

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
    gemm_20_output_array.data = AI_PTR(g_network_activations_map[0] + 180);
    gemm_20_output_array.data_start = AI_PTR(g_network_activations_map[0] + 180);
    nl_21_scratch0_array.data = AI_PTR(g_network_activations_map[0] + 188);
    nl_21_scratch0_array.data_start = AI_PTR(g_network_activations_map[0] + 188);
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
    gemm_20_bias_array.data = AI_PTR(g_network_weights_map[0] + 36840);
    gemm_20_bias_array.data_start = AI_PTR(g_network_weights_map[0] + 36840);
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
      
      .n_macc            = 1234000,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .params            = AI_STRUCT_INIT,
      .activations       = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x475d4acb,
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
      
      .n_macc            = 1234000,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .map_signature     = AI_MAGIC_SIGNATURE,
      .map_weights       = AI_STRUCT_INIT,
      .map_activations   = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x475d4acb,
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

