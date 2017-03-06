// ----------------------------------------------------------------------------
// AL_EXT_STATIC_BUFFER
// ----------------------------------------------------------------------------

AL_IMPORT(alBufferDataStatic, PFNALBUFFERDATASTATICPROC);

// ----------------------------------------------------------------------------
// AL_SOFT_buffer_sub_data
// ----------------------------------------------------------------------------

AL_IMPORT(alBufferSubDataSOFT, PFNALBUFFERSUBDATASOFTPROC);

// ----------------------------------------------------------------------------
// AL_EXT_FOLDBACK
// ----------------------------------------------------------------------------

AL_IMPORT(alRequestFoldbackStart, LPALREQUESTFOLDBACKSTART);
AL_IMPORT(alRequestFoldbackStop, LPALREQUESTFOLDBACKSTOP);

// ----------------------------------------------------------------------------
// AL_SOFT_buffer_samples Extension
// ----------------------------------------------------------------------------

AL_IMPORT(alBufferSamplesSOFT, LPALBUFFERSAMPLESSOFT);
AL_IMPORT(alBufferSubSamplesSOFT, LPALBUFFERSUBSAMPLESSOFT);
AL_IMPORT(alGetBufferSamplesSOFT, LPALGETBUFFERSAMPLESSOFT);
AL_IMPORT(alIsBufferFormatSupportedSOFT, LPALISBUFFERFORMATSUPPORTEDSOFT);

// ----------------------------------------------------------------------------
// AL_SOFT_source_latency
// ----------------------------------------------------------------------------

AL_IMPORT(alSourcedSOFT, LPALSOURCEDSOFT);
AL_IMPORT(alSource3dSOFT, LPALSOURCE3DSOFT);
AL_IMPORT(alSourcedvSOFT, LPALSOURCEDVSOFT);
AL_IMPORT(alGetSourcedSOFT, LPALGETSOURCEDSOFT);
AL_IMPORT(alGetSource3dSOFT, LPALGETSOURCE3DSOFT);
AL_IMPORT(alGetSourcedvSOFT, LPALGETSOURCEDVSOFT);
AL_IMPORT(alSourcei64SOFT, LPALSOURCEI64SOFT);
AL_IMPORT(alSource3i64SOFT, LPALSOURCE3I64SOFT);
AL_IMPORT(alSourcei64vSOFT, LPALSOURCEI64VSOFT);
AL_IMPORT(alGetSourcei64SOFT, LPALGETSOURCEI64SOFT);
AL_IMPORT(alGetSource3i64SOFT, LPALGETSOURCE3I64SOFT);
AL_IMPORT(alGetSourcei64vSOFT, LPALGETSOURCEI64VSOFT);

// ----------------------------------------------------------------------------
// AL_SOFT_deferred_updates
// ----------------------------------------------------------------------------

AL_IMPORT(alDeferUpdatesSOFT, LPALDEFERUPDATESSOFT);
AL_IMPORT(alProcessUpdatesSOFT, LPALPROCESSUPDATESSOFT);

// ----------------------------------------------------------------------------
// ALC_EXT_EFX
// ----------------------------------------------------------------------------

AL_IMPORT(alGenEffects, LPALGENEFFECTS);
AL_IMPORT(alDeleteEffects, LPALDELETEEFFECTS);
AL_IMPORT(alIsEffect, LPALISEFFECT);
AL_IMPORT(alEffecti, LPALEFFECTI);
AL_IMPORT(alEffectiv, LPALEFFECTIV);
AL_IMPORT(alEffectf, LPALEFFECTF);
AL_IMPORT(alEffectfv, LPALEFFECTFV);
AL_IMPORT(alGetEffecti, LPALGETEFFECTI);
AL_IMPORT(alGetEffectiv, LPALGETEFFECTIV);
AL_IMPORT(alGetEffectf, LPALGETEFFECTF);
AL_IMPORT(alGetEffectfv, LPALGETEFFECTFV);

AL_IMPORT(alGenFilters, LPALGENFILTERS);
AL_IMPORT(alDeleteFilters, LPALDELETEFILTERS);
AL_IMPORT(alIsFilter, LPALISFILTER);
AL_IMPORT(alFilteri, LPALFILTERI);
AL_IMPORT(alFilteriv, LPALFILTERIV);
AL_IMPORT(alFilterf, LPALFILTERF);
AL_IMPORT(alFilterfv, LPALFILTERFV);
AL_IMPORT(alGetFilteri, LPALGETFILTERI);
AL_IMPORT(alGetFilteriv, LPALGETFILTERIV);
AL_IMPORT(alGetFilterf, LPALGETFILTERF);
AL_IMPORT(alGetFilterfv, LPALGETFILTERFV);

AL_IMPORT(alGenAuxiliaryEffectSlots, LPALGENAUXILIARYEFFECTSLOTS);
AL_IMPORT(alDeleteAuxiliaryEffectSlots, LPALDELETEAUXILIARYEFFECTSLOTS);
AL_IMPORT(alIsAuxiliaryEffectSlot, LPALISAUXILIARYEFFECTSLOT);
AL_IMPORT(alAuxiliaryEffectSloti, LPALAUXILIARYEFFECTSLOTI);
AL_IMPORT(alAuxiliaryEffectSlotiv, LPALAUXILIARYEFFECTSLOTIV);
AL_IMPORT(alAuxiliaryEffectSlotf, LPALAUXILIARYEFFECTSLOTF);
AL_IMPORT(alAuxiliaryEffectSlotfv, LPALAUXILIARYEFFECTSLOTFV);
AL_IMPORT(alGetAuxiliaryEffectSloti, LPALGETAUXILIARYEFFECTSLOTI);
AL_IMPORT(alGetAuxiliaryEffectSlotiv, LPALGETAUXILIARYEFFECTSLOTIV);
AL_IMPORT(alGetAuxiliaryEffectSlotf, LPALGETAUXILIARYEFFECTSLOTF);
AL_IMPORT(alGetAuxiliaryEffectSlotfv, LPALGETAUXILIARYEFFECTSLOTFV);