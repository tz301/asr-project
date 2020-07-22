%module asr_py

%{
  #define SWIG_FILE_WITH_INIT
  #include "asr/pywrap/asr.h"
%}

%include "numpy.i"

%init %{
  import_array();
%}

%include "asr/pywrap/asr.h"
