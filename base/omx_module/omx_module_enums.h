/******************************************************************************
*
* Copyright (C) 2017 Allegro DVT2.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX OR ALLEGRO DVT2 BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of  Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
*
* Except as contained in this notice, the name of Allegro DVT2 shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Allegro DVT2.
*
******************************************************************************/

#pragma once

enum CompressionType
{
  COMPRESSION_UNUSED,
  COMPRESSION_HEVC,
  COMPRESSION_AVC,
  COMPRESSION_VP9,
  COMPRESSION_JPEG,
  COMPRESSION_MAX,
};

enum ColorType
{
  COLOR_MONO,
  COLOR_420,
  COLOR_422,
  COLOR_444,
  COLOR_MAX,
};

enum AVCProfileType
{
  AVC_PROFILE_BASELINE,
  AVC_PROFILE_MAIN,
  AVC_PROFILE_HIGH,
  AVC_PROFILE_HIGH10,
  AVC_PROFILE_HIGH422,
  AVC_PROFILE_MAX,
};

enum HEVCProfileType
{
  HEVC_PROFILE_MAIN,
  HEVC_PROFILE_MAIN10,
  HEVC_PROFILE_MAIN422,
  HEVC_PROFILE_MAIN422_10,
  HEVC_PROFILE_MAINSTILL,
  HEVC_PROFILE_MAIN_HIGH_TIER,
  HEVC_PROFILE_MAIN10_HIGH_TIER,
  HEVC_PROFILE_MAIN422_HIGH_TIER,
  HEVC_PROFILE_MAIN422_10_HIGH_TIER,
  HEVC_PROFILE_MAINSTILL_HIGH_TIER,
  HEVC_PROFILE_MAX,
};

enum VP9ProfileType
{
  VP9_PROFILE_MAX,
};

enum JPEGProfileType
{
  JPEG_PROFILE_MAX,
};

union ProfileType
{
  AVCProfileType avc;
  HEVCProfileType hevc;
  VP9ProfileType vp9;
  JPEGProfileType jpeg;
};

enum RateControlType
{
  RATE_CONTROL_CONSTANT_QUANTIZATION,
  RATE_CONTROL_VARIABLE_BITRATE,
  RATE_CONTROL_CONSTANT_BITRATE,
  RATE_CONTROL_LOW_LATENCY,
  RATE_CONTROL_MAX,
};

enum RateControlOptionType
{
  RATE_CONTROL_OPTION_NONE,
  RATE_CONTROL_OPTION_SCENE_CHANGE_RESILIENCE,
  RATE_CONTROL_OPTION_MAX,
};

enum AspectRatioType
{
  ASPECT_RATIO_NONE,
  ASPECT_RATIO_4_3,
  ASPECT_RATIO_16_9,
  ASPECT_RATIO_AUTO,
  ASPECT_RATIO_MAX,
};

enum GopControlType
{
  GOP_CONTROL_DEFAULT,
  GOP_CONTROL_PYRAMIDAL,
  GOP_CONTROL_LOW_DELAY_P,
  GOP_CONTROL_LOW_DELAY_B,
  GOP_CONTROL_MAX,
};

enum GdrType
{
  GDR_OFF,
  GDR_VERTICAL,
  GDR_HORTIZONTAL,
  GDR_MAX,
};

enum QPControlType
{
  QP_UNIFORM,
  QP_AUTO,
  QP_ROI,
  QP_MAX,
};

enum ScalingListType
{
  SCALING_LIST_DEFAULT,
  SCALING_LIST_FLAT,
  SCALING_LIST_MAX,
};

enum DecodedPictureBufferType
{
  DECODED_PICTURE_BUFFER_NORMAL,
  DECODED_PICTURE_BUFFER_LOW_REFERENCE,
  DECODED_PICTURE_BUFFER_MAX,
};

enum DecodeUnitType
{
  DECODE_UNIT_FRAME, // ACCESS UNIT
  DECODE_UNIT_SLICE, // VCL NAL
  DECODE_UNIT_MAX,
};

enum EntropyCodingType
{
  ENTROPY_CODING_CABAC,
  ENTROPY_CODING_CAVLC,
  ENTROPY_CODING_MAX,
};

enum LoopFilterType
{
  LOOP_FILTER_DISABLE,
  LOOP_FILTER_ENABLE,
  LOOP_FILTER_ENABLE_CROSS_TILE,
  LOOP_FILTER_ENABLE_CROSS_SLICE,
  LOOP_FILTER_ENABLE_CROSS_TILE_AND_SLICE,
  LOOP_FILTER_MAX,
};

enum BufferModeType
{
  BUFFER_MODE_FRAME,
  BUFFER_MODE_FRAME_NO_REORDERING,
  BUFFER_MODE_SLICE,
  BUFFER_MODE_MAX,
};

enum BufferHandleType
{
  BUFFER_HANDLE_CHAR_PTR,
  BUFFER_HANDLE_FD,
  BUFFER_HANDLE_MAX,
};

enum QualityType
{
  REGION_OF_INTEREST_QUALITY_HIGH,
  REGION_OF_INTEREST_QUALITY_MEDIUM,
  REGION_OF_INTEREST_QUALITY_LOW,
  REGION_OF_INTEREST_QUALITY_DONT_CARE,
  REGION_OF_INTEREST_QUALITY_STATIC,
};

