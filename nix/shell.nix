{
  stdenvAdapters,
  cmake,
  meson,
  ninja,
  pkg-config,
  mkShell,
  clang-tools,
}:
mkShell.override (old: {stdenv = stdenvAdapters.useMoldLinker old.stdenv;})
{
  name = "c-meson";
  packages = [
    cmake
    meson
    ninja
    pkg-config
    clang-tools
  ];
}
