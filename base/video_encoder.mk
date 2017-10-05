#------------------------------------------------------------------------------
# Video Encoder Component
#------------------------------------------------------------------------------

BASE_DIR?=.

include $(BASE_DIR)/video_def.mk
include $(BASE_DIR)/encoder_version.mk

LIB_ENCODE_A=$(EXTERNAL_BIN)/liballegro_encode.a
LIB_OMX_ENCODE_SO=$(BIN)/libOMX.allegro.video_encoder.so.$(ENC_VERSION)

ifneq ($(LINK_SHARED_CTRLSW), 1)
	LIBS_OMX_ENCODE+=$(LIB_ENCODE_A)
endif

-include $(BASE_DIR)/ref_enc.mk

$(LIB_OMX_ENCODE_SO):
	@mkdir -p $(dir $@)
	$(Q)$(CXX) $(LDFLAGS) $(INCLUDES) -shared -Wl,-soname,libOMX.allegro.video_encoder.so.$(ENC_MAJOR) -o "$@" $^ $(LIBS)
	@echo "LD $@"
	ln -fs "libOMX.allegro.video_encoder.so.$(ENC_VERSION)" "$(BIN)/libOMX.allegro.video_encoder.so"

TARGETS_OMX_ENC+=$(LIB_OMX_ENCODE_SO)

ifneq ($(LINK_SHARED_CTRLSW), 1)
$(LIB_ENCODE_A):
	ENABLE_64BIT=$(ENABLE_64BIT) \
	CROSS_COMPILE=$(CROSS_COMPILE) \
	ENABLE_STATIC=$(STATIC) \
	BIN=$(EXTERNAL_BIN) \
	$(MAKE) -C $(EXTERNAL_LIB) liballegro_encode
endif

LIB_OMX_ENCODE_SRC:=\
	$(BASE_DIR)/omx_port/omx_port.cpp\
	$(BASE_DIR)/omx_port/omx_buffer_manager.cpp\
	$(BASE_DIR)/omx_wrapper/omx_wrapper.cpp\
	$(BASE_DIR)/omx_wrapper/omx_enc_wrapper.cpp\
	$(BASE_DIR)/omx_checker/omx_checker.cpp\
	$(BASE_DIR)/omx_videocodec/omx_videocodec.cpp\
	$(BASE_DIR)/omx_processtype/omx_process.cpp\
	$(BASE_DIR)/omx_processtype/omx_enc_process.cpp\
	$(BASE_DIR)/omx_processtype/omx_enc_ipdevice.cpp\
	$(BASE_DIR)/omx_buffer/omx_buffer.cpp\
	$(BASE_DIR)/omx_buffer/omx_buffer_meta.cpp\
	$(BASE_DIR)/omx_codectype/omx_hevc_codec.cpp\
	$(BASE_DIR)/omx_codectype/omx_avc_codec.cpp\
	$(BASE_DIR)/omx_codectype/omx_enc_param.cpp\

-include $(BASE_DIR)/module_enc.mk

LIB_OMX_ENCODE_OBJ:=$(LIB_OMX_ENCODE_SRC:%.cpp=$(BIN)/%.cpp.o)

$(LIB_OMX_ENCODE_SO): $(LIB_OMX_ENCODE_OBJ) $(LIBS_OMX_ENCODE)

TARGETS_OMX_ENC+=$(LIB_OMX_ENCODE_SO)

ifneq ($(LINK_SHARED_CTRLSW), 1)
lib_omx_encoder: LIBS:= $(LIBS) -lpthread
lib_omx_encoder: $(LIB_ENCODE_A) $(TARGETS_OMX_ENC)
else
lib_omx_encoder: LIBS:= $(LIBS) -lpthread -lallegro_encode
lib_omx_encoder: $(TARGETS_OMX_ENC)
endif

TARGETS+=lib_omx_encoder
