sh_binary(
    name = "swig",
    srcs = ["run_swig.sh"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "python_lib",
    hdrs = [":python_include"],
    includes = ["python_include"],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "numpy_lib",
    hdrs = [":numpy_include"],
    includes = ["numpy_include"],
    visibility = ["//visibility:public"]
)

genrule(
    name = "python_include",
    outs = [
        "python_include/abstract.h",
        "python_include/accu.h",
        "python_include/asdl.h",
        "python_include/ast.h",
        "python_include/bitset.h",
        "python_include/bltinmodule.h",
        "python_include/boolobject.h",
        "python_include/bytearrayobject.h",
        "python_include/bytes_methods.h",
        "python_include/bytesobject.h",
        "python_include/cellobject.h",
        "python_include/ceval.h",
        "python_include/classobject.h",
        "python_include/codecs.h",
        "python_include/code.h",
        "python_include/compile.h",
        "python_include/complexobject.h",
        "python_include/datetime.h",
        "python_include/descrobject.h",
        "python_include/dictobject.h",
        "python_include/dtoa.h",
        "python_include/dynamic_annotations.h",
        "python_include/enumobject.h",
        "python_include/errcode.h",
        "python_include/eval.h",
        "python_include/fileobject.h",
        "python_include/fileutils.h",
        "python_include/floatobject.h",
        "python_include/frameobject.h",
        "python_include/funcobject.h",
        "python_include/genobject.h",
        "python_include/graminit.h",
        "python_include/grammar.h",
        "python_include/import.h",
        "python_include/intrcheck.h",
        "python_include/iterobject.h",
        "python_include/listobject.h",
        "python_include/longintrepr.h",
        "python_include/longobject.h",
        "python_include/marshal.h",
        "python_include/memoryobject.h",
        "python_include/metagrammar.h",
        "python_include/methodobject.h",
        "python_include/modsupport.h",
        "python_include/moduleobject.h",
        "python_include/namespaceobject.h",
        "python_include/node.h",
        "python_include/object.h",
        "python_include/objimpl.h",
        "python_include/odictobject.h",
        "python_include/opcode.h",
        "python_include/osdefs.h",
        "python_include/osmodule.h",
        "python_include/parsetok.h",
        "python_include/patchlevel.h",
        "python_include/pgen.h",
        "python_include/pgenheaders.h",
        "python_include/pyarena.h",
        "python_include/pyatomic.h",
        "python_include/pycapsule.h",
        "python_include/pyconfig.h",
        "python_include/pyctype.h",
        "python_include/py_curses.h",
        "python_include/pydebug.h",
        "python_include/pydtrace.h",
        "python_include/pyerrors.h",
        "python_include/pyexpat.h",
        "python_include/pyfpe.h",
        "python_include/pygetopt.h",
        "python_include/pyhash.h",
        "python_include/pylifecycle.h",
        "python_include/pymacconfig.h",
        "python_include/pymacro.h",
        "python_include/pymath.h",
        "python_include/pymem.h",
        "python_include/pyport.h",
        "python_include/pystate.h",
        "python_include/pystrcmp.h",
        "python_include/pystrhex.h",
        "python_include/pystrtod.h",
        "python_include/Python-ast.h",
        "python_include/Python.h",
        "python_include/pythonrun.h",
        "python_include/pythread.h",
        "python_include/pytime.h",
        "python_include/rangeobject.h",
        "python_include/setobject.h",
        "python_include/sliceobject.h",
        "python_include/structmember.h",
        "python_include/structseq.h",
        "python_include/symtable.h",
        "python_include/sysmodule.h",
        "python_include/token.h",
        "python_include/traceback.h",
        "python_include/tupleobject.h",
        "python_include/typeslots.h",
        "python_include/ucnhash.h",
        "python_include/unicodeobject.h",
        "python_include/warnings.h",
        "python_include/weakrefobject.h",
  ],
    cmd = """
        python_path=`python3-config --includes | awk '{print substr($$1,3)}'` &&
        cp "$$python_path/abstract.h" "$(@D)/python_include/abstract.h" &&
        cp "$$python_path/accu.h" "$(@D)/python_include/accu.h" &&
        cp "$$python_path/asdl.h" "$(@D)/python_include/asdl.h" &&
        cp "$$python_path/ast.h" "$(@D)/python_include/ast.h" &&
        cp "$$python_path/bitset.h" "$(@D)/python_include/bitset.h" &&
        cp "$$python_path/bltinmodule.h" "$(@D)/python_include/bltinmodule.h" &&
        cp "$$python_path/boolobject.h" "$(@D)/python_include/boolobject.h" &&
        cp "$$python_path/bytearrayobject.h" "$(@D)/python_include/bytearrayobject.h" &&
        cp "$$python_path/bytes_methods.h" "$(@D)/python_include/bytes_methods.h" &&
        cp "$$python_path/bytesobject.h" "$(@D)/python_include/bytesobject.h" &&
        cp "$$python_path/cellobject.h" "$(@D)/python_include/cellobject.h" &&
        cp "$$python_path/ceval.h" "$(@D)/python_include/ceval.h" &&
        cp "$$python_path/classobject.h" "$(@D)/python_include/classobject.h" &&
        cp "$$python_path/codecs.h" "$(@D)/python_include/codecs.h" &&
        cp "$$python_path/code.h" "$(@D)/python_include/code.h" &&
        cp "$$python_path/compile.h" "$(@D)/python_include/compile.h" &&
        cp "$$python_path/complexobject.h" "$(@D)/python_include/complexobject.h" &&
        cp "$$python_path/datetime.h" "$(@D)/python_include/datetime.h" &&
        cp "$$python_path/descrobject.h" "$(@D)/python_include/descrobject.h" &&
        cp "$$python_path/dictobject.h" "$(@D)/python_include/dictobject.h" &&
        cp "$$python_path/dtoa.h" "$(@D)/python_include/dtoa.h" &&
        cp "$$python_path/dynamic_annotations.h" "$(@D)/python_include/dynamic_annotations.h" &&
        cp "$$python_path/enumobject.h" "$(@D)/python_include/enumobject.h" &&
        cp "$$python_path/errcode.h" "$(@D)/python_include/errcode.h" &&
        cp "$$python_path/eval.h" "$(@D)/python_include/eval.h" &&
        cp "$$python_path/fileobject.h" "$(@D)/python_include/fileobject.h" &&
        cp "$$python_path/fileutils.h" "$(@D)/python_include/fileutils.h" &&
        cp "$$python_path/floatobject.h" "$(@D)/python_include/floatobject.h" &&
        cp "$$python_path/frameobject.h" "$(@D)/python_include/frameobject.h" &&
        cp "$$python_path/funcobject.h" "$(@D)/python_include/funcobject.h" &&
        cp "$$python_path/genobject.h" "$(@D)/python_include/genobject.h" &&
        cp "$$python_path/graminit.h" "$(@D)/python_include/graminit.h" &&
        cp "$$python_path/grammar.h" "$(@D)/python_include/grammar.h" &&
        cp "$$python_path/import.h" "$(@D)/python_include/import.h" &&
        cp "$$python_path/intrcheck.h" "$(@D)/python_include/intrcheck.h" &&
        cp "$$python_path/iterobject.h" "$(@D)/python_include/iterobject.h" &&
        cp "$$python_path/listobject.h" "$(@D)/python_include/listobject.h" &&
        cp "$$python_path/longintrepr.h" "$(@D)/python_include/longintrepr.h" &&
        cp "$$python_path/longobject.h" "$(@D)/python_include/longobject.h" &&
        cp "$$python_path/marshal.h" "$(@D)/python_include/marshal.h" &&
        cp "$$python_path/memoryobject.h" "$(@D)/python_include/memoryobject.h" &&
        cp "$$python_path/metagrammar.h" "$(@D)/python_include/metagrammar.h" &&
        cp "$$python_path/methodobject.h" "$(@D)/python_include/methodobject.h" &&
        cp "$$python_path/modsupport.h" "$(@D)/python_include/modsupport.h" &&
        cp "$$python_path/moduleobject.h" "$(@D)/python_include/moduleobject.h" &&
        cp "$$python_path/namespaceobject.h" "$(@D)/python_include/namespaceobject.h" &&
        cp "$$python_path/node.h" "$(@D)/python_include/node.h" &&
        cp "$$python_path/object.h" "$(@D)/python_include/object.h" &&
        cp "$$python_path/objimpl.h" "$(@D)/python_include/objimpl.h" &&
        cp "$$python_path/odictobject.h" "$(@D)/python_include/odictobject.h" &&
        cp "$$python_path/opcode.h" "$(@D)/python_include/opcode.h" &&
        cp "$$python_path/osdefs.h" "$(@D)/python_include/osdefs.h" &&
        cp "$$python_path/osmodule.h" "$(@D)/python_include/osmodule.h" &&
        cp "$$python_path/parsetok.h" "$(@D)/python_include/parsetok.h" &&
        cp "$$python_path/patchlevel.h" "$(@D)/python_include/patchlevel.h" &&
        cp "$$python_path/pgen.h" "$(@D)/python_include/pgen.h" &&
        cp "$$python_path/pgenheaders.h" "$(@D)/python_include/pgenheaders.h" &&
        cp "$$python_path/pyarena.h" "$(@D)/python_include/pyarena.h" &&
        cp "$$python_path/pyatomic.h" "$(@D)/python_include/pyatomic.h" &&
        cp "$$python_path/pycapsule.h" "$(@D)/python_include/pycapsule.h" &&
        cp "$$python_path/pyconfig.h" "$(@D)/python_include/pyconfig.h" &&
        cp "$$python_path/pyctype.h" "$(@D)/python_include/pyctype.h" &&
        cp "$$python_path/py_curses.h" "$(@D)/python_include/py_curses.h" &&
        cp "$$python_path/pydebug.h" "$(@D)/python_include/pydebug.h" &&
        cp "$$python_path/pydtrace.h" "$(@D)/python_include/pydtrace.h" &&
        cp "$$python_path/pyerrors.h" "$(@D)/python_include/pyerrors.h" &&
        cp "$$python_path/pyexpat.h" "$(@D)/python_include/pyexpat.h" &&
        cp "$$python_path/pyfpe.h" "$(@D)/python_include/pyfpe.h" &&
        cp "$$python_path/pygetopt.h" "$(@D)/python_include/pygetopt.h" &&
        cp "$$python_path/pyhash.h" "$(@D)/python_include/pyhash.h" &&
        cp "$$python_path/pylifecycle.h" "$(@D)/python_include/pylifecycle.h" &&
        cp "$$python_path/pymacconfig.h" "$(@D)/python_include/pymacconfig.h" &&
        cp "$$python_path/pymacro.h" "$(@D)/python_include/pymacro.h" &&
        cp "$$python_path/pymath.h" "$(@D)/python_include/pymath.h" &&
        cp "$$python_path/pymem.h" "$(@D)/python_include/pymem.h" &&
        cp "$$python_path/pyport.h" "$(@D)/python_include/pyport.h" &&
        cp "$$python_path/pystate.h" "$(@D)/python_include/pystate.h" &&
        cp "$$python_path/pystrcmp.h" "$(@D)/python_include/pystrcmp.h" &&
        cp "$$python_path/pystrhex.h" "$(@D)/python_include/pystrhex.h" &&
        cp "$$python_path/pystrtod.h" "$(@D)/python_include/pystrtod.h" &&
        cp "$$python_path/Python-ast.h" "$(@D)/python_include/Python-ast.h" &&
        cp "$$python_path/Python.h" "$(@D)/python_include/Python.h" &&
        cp "$$python_path/pythonrun.h" "$(@D)/python_include/pythonrun.h" &&
        cp "$$python_path/pythread.h" "$(@D)/python_include/pythread.h" &&
        cp "$$python_path/pytime.h" "$(@D)/python_include/pytime.h" &&
        cp "$$python_path/rangeobject.h" "$(@D)/python_include/rangeobject.h" &&
        cp "$$python_path/setobject.h" "$(@D)/python_include/setobject.h" &&
        cp "$$python_path/sliceobject.h" "$(@D)/python_include/sliceobject.h" &&
        cp "$$python_path/structmember.h" "$(@D)/python_include/structmember.h" &&
        cp "$$python_path/structseq.h" "$(@D)/python_include/structseq.h" &&
        cp "$$python_path/symtable.h" "$(@D)/python_include/symtable.h" &&
        cp "$$python_path/sysmodule.h" "$(@D)/python_include/sysmodule.h" &&
        cp "$$python_path/token.h" "$(@D)/python_include/token.h" &&
        cp "$$python_path/traceback.h" "$(@D)/python_include/traceback.h" &&
        cp "$$python_path/tupleobject.h" "$(@D)/python_include/tupleobject.h" &&
        cp "$$python_path/typeslots.h" "$(@D)/python_include/typeslots.h" &&
        cp "$$python_path/ucnhash.h" "$(@D)/python_include/ucnhash.h" &&
        cp "$$python_path/unicodeobject.h" "$(@D)/python_include/unicodeobject.h" &&
        cp "$$python_path/warnings.h" "$(@D)/python_include/warnings.h" &&
        cp "$$python_path/weakrefobject.h" "$(@D)/python_include/weakrefobject.h"
    """,
)

genrule(
    name = "numpy_include",
    outs = [
        "numpy_include/numpy/__multiarray_api.h",
        "numpy_include/numpy/__ufunc_api.h",
        "numpy_include/numpy/_neighborhood_iterator_imp.h",
        "numpy_include/numpy/_numpyconfig.h",
        "numpy_include/numpy/arrayobject.h",
        "numpy_include/numpy/arrayscalars.h",
        "numpy_include/numpy/halffloat.h",
        "numpy_include/numpy/multiarray_api.txt",
        "numpy_include/numpy/ndarrayobject.h",
        "numpy_include/numpy/ndarraytypes.h",
        "numpy_include/numpy/noprefix.h",
        "numpy_include/numpy/npy_1_7_deprecated_api.h",
        "numpy_include/numpy/npy_3kcompat.h",
        "numpy_include/numpy/npy_common.h",
        "numpy_include/numpy/npy_cpu.h",
        "numpy_include/numpy/npy_endian.h",
        "numpy_include/numpy/npy_interrupt.h",
        "numpy_include/numpy/npy_math.h",
        "numpy_include/numpy/npy_no_deprecated_api.h",
        "numpy_include/numpy/npy_os.h",
        "numpy_include/numpy/numpyconfig.h",
        "numpy_include/numpy/old_defines.h",
        "numpy_include/numpy/oldnumeric.h",
        "numpy_include/numpy/ufunc_api.txt",
        "numpy_include/numpy/ufuncobject.h",
        "numpy_include/numpy/utils.h",
    ],
    cmd = """
        numpy_path=`python3 -c "import numpy as np; print(np.get_include())"` &&
        cp "$$numpy_path/numpy/__multiarray_api.h" "$(@D)/numpy_include/numpy/__multiarray_api.h" &&
        cp "$$numpy_path/numpy/__ufunc_api.h" "$(@D)/numpy_include/numpy/__ufunc_api.h" &&
        cp "$$numpy_path/numpy/_neighborhood_iterator_imp.h" "$(@D)/numpy_include/numpy/_neighborhood_iterator_imp.h" &&
        cp "$$numpy_path/numpy/_numpyconfig.h" "$(@D)/numpy_include/numpy/_numpyconfig.h" &&
        cp "$$numpy_path/numpy/arrayobject.h" "$(@D)/numpy_include/numpy/arrayobject.h" &&
        cp "$$numpy_path/numpy/arrayscalars.h" "$(@D)/numpy_include/numpy/arrayscalars.h" &&
        cp "$$numpy_path/numpy/halffloat.h" "$(@D)/numpy_include/numpy/halffloat.h" &&
        cp "$$numpy_path/numpy/multiarray_api.txt" "$(@D)/numpy_include/numpy/multiarray_api.txt" &&
        cp "$$numpy_path/numpy/ndarrayobject.h" "$(@D)/numpy_include/numpy/ndarrayobject.h" &&
        cp "$$numpy_path/numpy/ndarraytypes.h" "$(@D)/numpy_include/numpy/ndarraytypes.h" &&
        cp "$$numpy_path/numpy/noprefix.h" "$(@D)/numpy_include/numpy/noprefix.h" &&
        cp "$$numpy_path/numpy/npy_1_7_deprecated_api.h" "$(@D)/numpy_include/numpy/npy_1_7_deprecated_api.h" &&
        cp "$$numpy_path/numpy/npy_3kcompat.h" "$(@D)/numpy_include/numpy/npy_3kcompat.h" &&
        cp "$$numpy_path/numpy/npy_common.h" "$(@D)/numpy_include/numpy/npy_common.h" &&
        cp "$$numpy_path/numpy/npy_cpu.h" "$(@D)/numpy_include/numpy/npy_cpu.h" &&
        cp "$$numpy_path/numpy/npy_endian.h" "$(@D)/numpy_include/numpy/npy_endian.h" &&
        cp "$$numpy_path/numpy/npy_interrupt.h" "$(@D)/numpy_include/numpy/npy_interrupt.h" &&
        cp "$$numpy_path/numpy/npy_math.h" "$(@D)/numpy_include/numpy/npy_math.h" &&
        cp "$$numpy_path/numpy/npy_no_deprecated_api.h" "$(@D)/numpy_include/numpy/npy_no_deprecated_api.h" &&
        cp "$$numpy_path/numpy/npy_os.h" "$(@D)/numpy_include/numpy/npy_os.h" &&
        cp "$$numpy_path/numpy/numpyconfig.h" "$(@D)/numpy_include/numpy/numpyconfig.h" &&
        cp "$$numpy_path/numpy/old_defines.h" "$(@D)/numpy_include/numpy/old_defines.h" &&
        cp "$$numpy_path/numpy/oldnumeric.h" "$(@D)/numpy_include/numpy/oldnumeric.h" &&
        cp "$$numpy_path/numpy/ufunc_api.txt" "$(@D)/numpy_include/numpy/ufunc_api.txt" &&
        cp "$$numpy_path/numpy/ufuncobject.h" "$(@D)/numpy_include/numpy/ufuncobject.h" &&
        cp "$$numpy_path/numpy/utils.h" "$(@D)/numpy_include/numpy/utils.h"
    """,
)
