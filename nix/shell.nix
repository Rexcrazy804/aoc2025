{
  cmake,
  meson,
  ninja,
  pkg-config,
  mkShell,
  clang-tools,
}:
mkShell {
  name = "c-dev";

  packages = [
    cmake
    meson
    ninja
    pkg-config
    clang-tools
  ];
}
