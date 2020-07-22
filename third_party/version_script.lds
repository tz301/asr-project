# Disable some symbols from tensorflow.
VERS_1.0 {
  # Export symbols in c_api.h.
  global:
    *TF_*;
    *TFE_*;
    *Py*;
    *asr*;

  # Hide everything else.
  local:
    *;
};