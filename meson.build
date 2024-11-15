project('C-Lang-Homework', 'c', version: '0.1', default_options: ['warning_level=3'])
# We need -lm for all executables built from C code that use math functions
cc = meson.get_compiler('c')

deps = [
  cc.find_library('m', required: false),
  cc.find_library('gc'),
]

subdir('src')

executable(
  'C-Lang-Homework',
  src,
  dependencies: deps,
  install: true,
)