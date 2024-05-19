project('lisiblestd', 'c', default_options: ['c_std=c18', 'warning_level=3'])

lisiblestd_incdir = include_directories('src/')
lisiblestd_lib = library('lisiblestd', 
  'src/lisiblestd/log.c', 
  'src/lisiblestd/memory.c', 
  'src/lisiblestd/string.c',
  'src/lisiblestd/bytes.c',
  'src/lisiblestd/vec.c'
)
lisiblestd_dep = declare_dependency(include_directories: lisiblestd_incdir, link_with: [lisiblestd_lib])

test_string = executable('test_string', 'tests/test_runner.c', 'tests/string.c', dependencies: [lisiblestd_dep])
test('test_string', test_string)
test_bytes = executable('test_bytes', 'tests/test_runner.c', 'tests/bytes.c', dependencies: [lisiblestd_dep])
test('test_bytes', test_bytes)
test_memory = executable('test_memory', 'tests/test_runner.c', 'tests/memory.c', dependencies: [lisiblestd_dep])
test('test_memory', test_memory)
