{
  description = "Flake with simple meson devShell";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    systems.url = "github:nix-systems/x86_64-linux";
  };

  outputs = {
    self,
    nixpkgs,
    systems,
  }: let
    pkgsFor = nixpkgs.legacyPackages;
    eachSystem = fn: nixpkgs.lib.genAttrs (import systems) (system: fn pkgsFor.${system});
  in {
    devShells = eachSystem (pkgs: {
      default = pkgs.callPackage ./nix/shell.nix {};
    });
  };
}
