with import <nixpkgs> {}; {
    skidjularENV = stdenv.mkDerivation {
        name = "skidjular-env";
        buildInputs = [
            stdenv
            cmake
            gcc
            ninja
        ];
    };
}
