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

#include "omx_mediatype_enc_avc.h"

EncMediatypeAVC::EncMediatypeAVC()
{
  Reset();
}

EncMediatypeAVC::~EncMediatypeAVC()
{
}

void EncMediatypeAVC::Reset()
{
  AL_Settings_SetDefaults(&settings);
  auto& chan = settings.tChParam;
  chan.eProfile = AL_PROFILE_AVC_BASELINE;
  AL_Settings_SetDefaultParam(&settings);
  chan.uLevel = 10;
}

CompressionType EncMediatypeAVC::Compression() const
{
  return COMPRESSION_AVC;
}

std::string EncMediatypeAVC::Mime() const
{
  return "video/x-h264";
}

std::vector<ProfileLevelType> EncMediatypeAVC::ProfileLevelSupported() const
{
  std::vector<ProfileLevelType> vector;

  for(auto const& profile : profiles)
    for(auto const & level : levels)
    {
      ProfileLevelType tmp;
      tmp.profile.avc = profile;
      tmp.level = level;
      vector.push_back(tmp);
    }

  return vector;
}

static AVCProfileType ToProfile(AL_EProfile const& profile)
{
  if(!AL_IS_AVC(profile))
    return AVC_PROFILE_MAX;
  switch(profile)
  {
  case AL_PROFILE_AVC_BASELINE: return AVC_PROFILE_BASELINE;
  case AL_PROFILE_AVC_MAIN: return AVC_PROFILE_MAIN;
  case AL_PROFILE_AVC_HIGH: return AVC_PROFILE_HIGH;
  case AL_PROFILE_AVC_HIGH10: return AVC_PROFILE_HIGH10;
  case AL_PROFILE_AVC_HIGH_422: return AVC_PROFILE_HIGH422;
  default:
    return AVC_PROFILE_MAX;
  }

  return AVC_PROFILE_MAX;
}

ProfileLevelType EncMediatypeAVC::ProfileLevel() const
{
  auto const chan = settings.tChParam;
  ProfileLevelType p;
  p.profile.avc = ToProfile(chan.eProfile);
  p.level = chan.uLevel;
  return p;
}

static AL_EProfile ToProfile(AVCProfileType const& profile)
{
  switch(profile)
  {
  case AVC_PROFILE_BASELINE: return AL_PROFILE_AVC_BASELINE;
  case AVC_PROFILE_MAIN: return AL_PROFILE_AVC_MAIN;
  case AVC_PROFILE_HIGH: return AL_PROFILE_AVC_HIGH;
  case AVC_PROFILE_HIGH10: return AL_PROFILE_AVC_HIGH10;
  case AVC_PROFILE_HIGH422: return AL_PROFILE_AVC_HIGH_422;
  case AVC_PROFILE_MAX:
  default: return AL_PROFILE_AVC;
  }

  return AL_PROFILE_AVC;
}

bool EncMediatypeAVC::IsInProfilesSupported(AVCProfileType const& profile)
{
  for(auto const& p : profiles)
  {
    if(p == profile)
      return true;
  }

  return false;
}

bool EncMediatypeAVC::IsInLevelsSupported(int const& level)
{
  for(auto const& l : levels)
  {
    if(l == level)
      return true;
  }

  return false;
}

bool EncMediatypeAVC::SetProfileLevel(ProfileLevelType const& profileLevel)
{
  if(!IsInProfilesSupported(profileLevel.profile.avc))
    return false;

  if(!IsInLevelsSupported(profileLevel.level))
    return false;

  auto const profile = ToProfile(profileLevel.profile.avc);

  if(profile == AL_PROFILE_AVC)
    return false;

  auto& chan = settings.tChParam;
  chan.eProfile = profile;
  chan.uLevel = profileLevel.level;
  return true;
}

static EntropyCodingType ToEntropyCoding(AL_EEntropyMode const& mode)
{
  switch(mode)
  {
  case AL_MODE_CABAC: return ENTROPY_CODING_CABAC;
  case AL_MODE_CAVLC: return ENTROPY_CODING_CAVLC;
  default: return ENTROPY_CODING_MAX;
  }

  return ENTROPY_CODING_MAX;
}

EntropyCodingType EncMediatypeAVC::EntropyCoding() const
{
  auto const chan = settings.tChParam;
  return ToEntropyCoding(chan.eEntropyMode);
}

static AL_EEntropyMode ToEntropyCoding(EntropyCodingType const& mode)
{
  switch(mode)
  {
  case ENTROPY_CODING_CABAC: return AL_MODE_CABAC;
  case ENTROPY_CODING_CAVLC: return AL_MODE_CAVLC;
  case ENTROPY_CODING_MAX:
  default: return AL_MODE_CABAC;
  }

  return AL_MODE_CABAC;
}

bool EncMediatypeAVC::SetEntropyCoding(EntropyCodingType const& entropyCoding)
{
  auto& chan = settings.tChParam;
  chan.eEntropyMode = ToEntropyCoding(entropyCoding);
  return true;
}

bool EncMediatypeAVC::IsConstrainedIntraPrediction() const
{
  auto const chan = settings.tChParam;
  return chan.eOptions & AL_OPT_CONST_INTRA_PRED;
}

bool EncMediatypeAVC::SetConstrainedIntraPrediction(bool const& constrainedIntraPrediction)
{
  auto& opt = settings.tChParam.eOptions;

  if(constrainedIntraPrediction)
    opt = static_cast<AL_EChEncOption>(opt | AL_OPT_CONST_INTRA_PRED);

  return true;
}

static inline LoopFilterType ToLoopFilter(AL_EChEncOption const& opt)
{
  if(opt & (AL_OPT_LF_X_SLICE | AL_OPT_LF))
    return LOOP_FILTER_ENABLE_CROSS_SLICE;

  if(opt & AL_OPT_LF)
    return LOOP_FILTER_ENABLE;

  return LOOP_FILTER_DISABLE;
}

LoopFilterType EncMediatypeAVC::LoopFilter() const
{
  auto const chan = settings.tChParam;
  return ToLoopFilter(chan.eOptions);
}

bool EncMediatypeAVC::SetLoopFilter(LoopFilterType const& loopFilter)
{
  auto& opt = settings.tChParam.eOptions;

  if(loopFilter == LOOP_FILTER_MAX)
    return false;

  if(loopFilter == LOOP_FILTER_DISABLE)
    opt = static_cast<AL_EChEncOption>(opt & ~(AL_OPT_LF | AL_OPT_LF_X_SLICE));
  else // LoopFilter is enable
  {
    opt = static_cast<AL_EChEncOption>(opt | AL_OPT_LF);

    if(loopFilter == LOOP_FILTER_ENABLE_CROSS_SLICE)
      opt = static_cast<AL_EChEncOption>(opt | AL_OPT_LF_X_SLICE);
  }

  return true;
}

bool EncMediatypeAVC::IsEnableLowBandwidth() const
{
  auto const chan = settings.tChParam;
  return chan.pMeRange[SLICE_P][1] == 8;
}

bool EncMediatypeAVC::SetEnableLowBandwidth(bool const& enable)
{
  auto& chan = settings.tChParam;
  auto bw = enable ? 8 : 16;
  chan.pMeRange[SLICE_P][1] = bw;
  return true;
}

