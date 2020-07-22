# Bazel rules for building swig files.


def pywrap_library(name, srcs, swig_includes=[], deps=[], copts=[], **kwargs):
  module_name = name
  cc_library_name = "/".join(name.split("/")[:-1] + ["_" + module_name + ".so"])
  _py_wrap_cc(
      name=name + "_py_wrap", srcs=srcs, swig_includes=swig_includes,
      deps=deps, module_name=name, py_module_name=name
  )

  native.cc_binary(
      name=cc_library_name, srcs=[module_name + ".cxx"], copts=copts,
      linkstatic=1, linkshared=1, deps=deps, **kwargs
  )

  native.py_library(
      name=name, srcs=[":" + name + ".py"], srcs_version="PY2AND3",
      data=[":" + cc_library_name],
  )


def _py_wrap_cc_impl(ctx):
  srcs = ctx.files.srcs
  if len(srcs) != 1:
    fail("Exactly one SWIG source file label must be specified.", "srcs")
  src = ctx.files.srcs[0]
  inputs = depset([src])
  inputs += ctx.files.swig_includes
  for dep in ctx.attr.deps:
    inputs += dep.cc.transitive_headers
  args = [src.path, ctx.attr.module_name, ctx.outputs.cc_out.path,
          ctx.outputs.py_out.dirname]
  outputs = [ctx.outputs.cc_out, ctx.outputs.py_out]
  ctx.actions.run(
      executable=ctx.executable._swig, arguments=args, inputs=inputs,
      outputs=outputs, mnemonic="PythonSwig",
      progress_message="SWIGing " + src.path
  )
  return struct(files=depset(outputs))


_py_wrap_cc = rule(
    attrs={
        "srcs": attr.label_list(mandatory=True, allow_files=True),
        "deps": attr.label_list(allow_files=True, providers=["cc"]),
        "swig_includes": attr.label_list(allow_files=True),
        "module_name": attr.string(mandatory=True),
        "py_module_name": attr.string(mandatory=True),
        "_swig": attr.label(
            default=Label("//third_party/swig:swig"),
            executable=True, cfg="host",
        ),
    },
    outputs={"cc_out": "%{module_name}.cxx", "py_out": "%{py_module_name}.py"},
    implementation=_py_wrap_cc_impl,
)
