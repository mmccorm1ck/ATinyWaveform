let pkgs = import <nixpkgs> {
        crossSystem = {
                config = "avr";
        };
};
in pkgs.callPackage (
        {mkShell}:
                mkShell {
                        nativeBuildInputs = [];
                        buildInputs = [];
                }
) {}
