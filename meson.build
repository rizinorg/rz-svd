project('rz-svd', 'c',
  version: '0.1.0',
  license: 'LGPL3',
  meson_version: '>=0.56.0',
  default_options: [
    'buildtype=debugoptimized',
    'b_vscrt=from_buildtype',
  ]
)

cc = meson.get_compiler('c')

rz_svd_c_args = []

# handle dependencies
yxml_proj = subproject('yxml', default_options: ['default_library=static'])
yxml_dep = yxml_proj.get_variable('yxml_dep')

if get_option('default_library') == 'shared'
    if cc.has_argument('-fvisibility=hidden')
        rz_svd_c_args += '-fvisibility=hidden'
    endif
endif

if cc.has_argument('--std=gnu99')
    add_project_arguments('--std=gnu99', language : 'c')
elif cc.has_argument('--std=c99')
    add_project_arguments('--std=c99', language : 'c')
endif

rz_svd_src = [
  'rz_svd.c',
  'src' / 'svd_util.c',
]

# Get datadir from parent project if available
if meson.is_subproject()
  rizin_datdir = get_variable('rizin_datdir', get_option('datadir'))
  rizin_datdir_rz = get_variable('rizin_datdir_rz', rizin_datdir / 'rizin')
else
  rizin_datdir_rz = get_option('datadir') / 'rizin'
endif

svd_datadir = rizin_datdir_rz / 'svd'

# Source directory for SVD files (for development/testing)
svd_srcdir = meson.current_source_dir() / 'svd'

rz_svd_c_args += [
  '-DRZ_SVD_DATADIR="' + svd_datadir + '"',
  '-DRZ_SVD_SRCDIR="' + svd_srcdir + '"',
]

rz_svd = both_libraries('rz_svd',
  rz_svd_src,
  dependencies: [
    yxml_dep,
  ],
  c_args: rz_svd_c_args,
  implicit_include_directories: false,
  include_directories: include_directories(['.', 'include']),
  install: false,
)

# When used as a subproject (e.g., by Rizin), always prefer the static library
# since rz_svd is not installed separately — it gets embedded into the parent
# shared library (e.g., librz_bin.so). Using the shared lib here would cause
# runtime errors because librz_svd.so is built with install: false.
if meson.is_subproject()
    rz_svd_link = rz_svd.get_static_lib()
elif get_option('default_library') == 'static'
    rz_svd_link = rz_svd.get_static_lib()
elif get_option('default_library') == 'shared'
    rz_svd_link = rz_svd.get_shared_lib()
else
    # For 'both', prefer static for better compatibility
    rz_svd_link = rz_svd.get_static_lib()
endif

rz_svd_dep = declare_dependency(
  link_with: rz_svd_link,
  dependencies: [],
  include_directories: include_directories('include'),
  compile_args: rz_svd_c_args
)

meson.override_dependency('rz_svd', rz_svd_dep)

# Install SVD files
install_subdir('svd',
  install_dir: rizin_datdir_rz,
  strip_directory: false,
  exclude_files: [],
  exclude_directories: []
)
