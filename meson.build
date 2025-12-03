project(
  'aoc2025',
  'c',
  meson_version : '>= 1.3.0',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'c_std=c23',
  ],
)

day = get_option('aoc_day')

if day == 'default'
  date_r = run_command('date', '+%d', check:true)
  day = (date_r.stdout().strip().to_int()).to_string()
endif

c_day_header = '-DDAY_INCLUDE="day' + day + '.h"'
c_day = '-DDAY="' + day + '"'
c_day_src = 'src/day' + day + '.c'

add_project_arguments(
  '-Wconversion',
  '-Wno-cpp',
  c_day_header,
  c_day,
  language: 'c',
)

dependencies = [ ]

sources = [
  'src/main.c',
  c_day_src,
]

exe = executable (
  'aoc2025',
  sources,
  dependencies : dependencies,
  install : true,
)
