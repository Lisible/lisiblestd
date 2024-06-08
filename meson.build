project('lisiblestd', 'c', version: '0.3.0', default_options: ['c_std=c18', 'warning_level=3', 'default_library=static'])

is_playdate_build = meson.get_external_property('is_playdate_build', false)

lisiblestd_c_args = []
lisiblestd_deps = []
if is_playdate_build
playdate_sdk_path = get_option('playdate_sdk_path')
playdate_sdk_incdir = playdate_sdk_path / 'C_API'
playdate_sdk_dep = declare_dependency(include_directories: playdate_sdk_incdir)
lisiblestd_c_args += '-DLSTD_PLATFORM_PLAYDATE=1'
lisiblestd_c_args += [
  '-DTARGET_PLAYDATE=1',
  '-DTARGET_EXTENSION=1',
  '-mthumb',
  '-mcpu=cortex-m7',
  '-mfloat-abi=hard',
  '-mfpu=fpv5-sp-d16',
  '-D__FPU_USED=1',
  '-falign-functions=16',
  '-fomit-frame-pointer',
  '-gdwarf-2',
  '-fverbose-asm',
  '-ffunction-sections',
  '-fdata-sections',
  '-mword-relocations',
  '-fno-common',
  '-fno-exceptions',
  '-Wno-unknown-pragmas',
  '-Wdouble-promotion',
  '-O2',
]
lisiblestd_deps += playdate_sdk_dep
endif


lisiblestd_incdir = include_directories('src/')
lisiblestd_lib = static_library('lisiblestd', 
  'src/lisiblestd/log.c', 
  'src/lisiblestd/memory.c', 
  'src/lisiblestd/string.c',
  'src/lisiblestd/bytes.c',
  'src/lisiblestd/vec.c',
  'src/lisiblestd/hash.c',
  c_args: lisiblestd_c_args,
  dependencies: lisiblestd_deps
)
lisiblestd_dep = declare_dependency(include_directories: lisiblestd_incdir, link_with: [lisiblestd_lib], dependencies: lisiblestd_deps)


if not meson.is_cross_build()
test_string = executable('test_string', 'tests/test_runner.c', 'tests/string.c', dependencies: [lisiblestd_dep])
test('test_string', test_string)
test_bytes = executable('test_bytes', 'tests/test_runner.c', 'tests/bytes.c', dependencies: [lisiblestd_dep])
test('test_bytes', test_bytes)
test_memory = executable('test_memory', 'tests/test_runner.c', 'tests/memory.c', dependencies: [lisiblestd_dep])
test('test_memory', test_memory)
test_hash_table = executable('test_hash_table', 'tests/test_runner.c', 'tests/hash_table.c', dependencies: [lisiblestd_dep])
test('test_hash_table', test_hash_table)
endif
