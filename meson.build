project(
  'aoc2025',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : ['warning_level=3'],
)

add_project_arguments('-Wconversion', language: 'c')

dependencies = [ ]

sources = [
  'src/main.c',
  'src/day1.c',
  'src/day2.c',
]

exe = executable (
  'aoc2025',
  sources,
  dependencies : dependencies,
  install : true,
)
