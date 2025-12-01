{
  description = "Flake with simple meson devShell";
  inputs.nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";

  outputs = {
    self,
    nixpkgs,
  }: let
    eachSystem = fn: nixpkgs.lib.mapAttrs fn nixpkgs.legacyPackages;
  in {
    devShells = eachSystem (_: pkgs: {
      default = pkgs.callPackage ./nix/shell.nix {};
    });
  };
}
