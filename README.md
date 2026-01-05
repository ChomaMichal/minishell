# Minishell

A custom UNIX shell implementation written in C, designed to recreate Bash functionality according to the [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html). This project is part of the 42 School curriculum. 

## Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Operators & Syntax](#operators--syntax)
- [Project Structure](#project-structure)
- [Authors](#authors)

## About

Minishell is a simplified shell that mimics the behavior of Bash.  The goal of this project is to understand how shells work under the hood, including process creation, signal handling, parsing, and command execution. 

## Features

### Shell Capabilities
- **Interactive prompt** with command history (using readline)
- **Command execution** from PATH or absolute/relative paths
- **Signal handling** (Ctrl+C, Ctrl+D, Ctrl+\)

### Operators
| Operator | Description |
|----------|-------------|
| `\|` | Pipes - connects stdout of one command to stdin of another |
| `&&` | Logical AND - executes next command only if previous succeeded |
| `\|\|` | Logical OR - executes next command only if previous failed |
| `()` | Subshell - executes commands in a child shell environment |

### Redirections
| Redirection | Description |
|-------------|-------------|
| `>` | Redirect output (overwrite) |
| `>>` | Redirect output (append) |
| `<` | Redirect input |
| `<<` | Here-document |

### Expansions
- **Variable expansion** (`$VAR`, `$? ` for exit status)
- **Quote handling** (single quotes `'.. .'` and double quotes `"..."`)
- **Wildcard/Star expansion** (`*` - filename expansion/globbing)

## Installation

### Prerequisites
- GCC compiler
- Make
- Readline library

#### Installing Readline

**Ubuntu/Debian:**
```bash
sudo apt-get install libreadline-dev
```

**macOS (with Homebrew):**
```bash
brew install readline
```

**NixOS:**
A `shell.nix` file is provided for Nix users. 

### Build

```bash
# Clone the repository
git clone https://github.com/ChomaMichal/minishell. git
cd minishell

# Compile
make

# Or compile with parallel jobs for faster build
make -j$(nproc)
```

## Usage

```bash
# Start the shell
./minishell

# You'll see a prompt where you can enter commands
minishell$ echo "Hello, World!"
Hello, World! 

minishell$ ls -la | grep . c | wc -l

minishell$ (cd /tmp && pwd) && echo "Back to original dir"

minishell$ cat file.txt || echo "File not found"

minishell$ echo $USER
```

## Built-in Commands

| Command | Description |
|---------|-------------|
| `echo` | Display text (with `-n` flag support) |
| `cd` | Change directory |
| `pwd` | Print working directory |
| `export` | Set environment variables |
| `unset` | Unset environment variables |
| `env` | Display environment variables |
| `exit` | Exit the shell |

## Operators & Syntax

### Pipes
```bash
# Chain commands together
ls -la | grep ". c" | head -5
```

### Logical Operators
```bash
# AND - run second command only if first succeeds
make && ./minishell

# OR - run second command only if first fails
cat nonexistent. txt || echo "File not found"
```

### Subshells
```bash
# Commands in parentheses run in a subshell
(cd /tmp && touch file.txt) && echo "Created file in /tmp"
```

### Quoting
```bash
# Single quotes - no expansion
echo 'Hello $USER'    # Output: Hello $USER

# Double quotes - variable expansion occurs
echo "Hello $USER"    # Output: Hello username
```

### Wildcard Expansion
```bash
# List all .c files
ls *.c

# Remove all object files
rm *.o
```

## Project Structure

```
minishell/
├── main. c                 # Entry point
├── minishell.h            # Main header file
├── Makefile               # Build configuration
├── commands/              # Built-in command implementations
│   ├── cd.c
│   ├── echo. c
│   ├── env.c
│   ├── export.c
│   ├── pwd.c
│   ├── unset.c
│   └── ft_exit.c
├── parsing/               # Tokenization and parsing
│   ├── parsing.c
│   ├── tokenize.c
│   ├── expand.c
│   ├── execution_tree.c
│   ├── redirections.c
│   ├── here_doc.c
│   └── filename_expansion.c
├── execution/             # Command execution
│   ├── entry.c
│   ├── ft_pipe.c
│   ├── ft_and.c
│   ├── ft_or. c
│   ├── ft_subshell.c
│   └── redirection.c
└── libft/                 # Custom C library functions
```

## Testing

```bash
# Build test version with -g compilation flag
make test

# Run with valgrind for memory leak detection
make runt
```

## Authors

- **mchoma** - [ChomaMichal](https://github.com/ChomaMichal)
- **jel-ghna** - [YousefElghanam](https://github.com/YousefElghanam)

---

<p align="center">
  <i>Made as part of the 42 School curriculum</i>
</p>
