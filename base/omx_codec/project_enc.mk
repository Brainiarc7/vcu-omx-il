THIS.omx_codec_enc:=$(call get-my-dir)

OMX_CODEC_ENC_SRCS+=\
	$(THIS.omx_codec_enc)/omx_codec_enc.cpp\
	$(THIS.omx_codec_enc)/omx_expertise_enc_avc.cpp\
	$(THIS.omx_codec_enc)/omx_expertise_enc_hevc.cpp\

UNITTESTS+=$(OMX_CODEC_ENC_SRCS)
