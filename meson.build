project(
  'wayland-inhibit',
  'c',
  version: '0.0.1',
  license: 'Apache',
  meson_version: '>=0.43.0',
  default_options: [
    'c_std=c11',
    'warning_level=2',
    'werror=true',
  ],
)

add_project_arguments('-Wno-unused-parameter', language: 'c')

cc = meson.get_compiler('c')

pixman = dependency('pixman-1')
wayland_client = dependency('wayland-client')
wayland_protocols = dependency('wayland-protocols', version: '>=1.15')
wlroots = dependency('wlroots')

executable(
  'wayland-inhibit',
  [
    'idle-inhibit-unstable-v1.c',
    'main.c',
  ],
  dependencies: [
    pixman,
    wayland_client,
    wayland_protocols,
    wlroots,
  ],
)
