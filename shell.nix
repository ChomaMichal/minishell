{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  buildInputs = [
	pkgs.gnumake
	pkgs.norminette
	pkgs.clang
	pkgs.lldb
    pkgs.readline
    pkgs.ncurses
    pkgs.pkg-config
  ];

  shellHook = ''
	export LD_LIBRARY_PATH=${pkgs.readline}/lib:${pkgs.ncurses}/lib
	alias vgt="valgrind --track-fds=all --leak-check=full --trace-children=yes  --suppressions=readline.supp ./test"
  '';
}
