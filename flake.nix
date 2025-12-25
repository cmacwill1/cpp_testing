{
  description = "Reproducible C++ dev shell with Clang and CMake";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      pkgs = nixpkgs.legacyPackages."x86_64-linux";
    in 

    {
      devShells."x86_64-linux".default = pkgs.mkShell {
      # Use Clang-based stdenv so clang++ is default
      stdenv = pkgs.clangStdenv;

      # Build tools
      nativeBuildInputs = [
        pkgs.cmake        # for CMake
        pkgs.clang
        pkgs.clang-tools  # clangd, clang-format, etc.
      ];

      # Optional: environment variables to enforce clang
      shellHook = ''
        export CC=clang
        export CXX=clang++
        echo "Clang dev shell ready. Run 'cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON'"
      '';
    };
  };
}

