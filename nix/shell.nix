{
  gcc15Stdenv,
  stdenvAdapters,
  cmake,
  meson,
  ninja,
  pkg-config,
  mkShell,
  clang-tools,
  hyperfine,
  perf,
}:
mkShell.override (old: {stdenv = stdenvAdapters.useMoldLinker gcc15Stdenv;})
{
  name = "c-meson";
  packages = [
    cmake
    meson
    ninja
    pkg-config
    clang-tools
    hyperfine
    perf
  ];
}
