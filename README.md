# minishell

![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![Grade: 100%](https://img.shields.io/badge/Grade-100%25-brightgreen?style=for-the-badge)


A shell written in C, inspired by Bash.

### Features

- Parsing, expansion, and command execution
- Pipes and redirections
- Signal handling
- Environment variables
- Builtin commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`

## Use

### Pipes and redirections

```bash
# input redirection
cat < infile

# output redirection
echo hello > outfile

# output redirection (append)
echo world >> outfile

# pipe
env | grep PATH

# heredoc
cat << EOF
line 1
line 2
EOF
```

### cd

```bash
# go home
cd

# go to path
cd /tmp
```

### echo

```bash
# print environment variable
echo $HOME

# no newline
echo -n hello
```

### export

```bash
# print exported variables (sorted)
export

# set variable
export USERNAME=jerome

# create key without value
export EMPTY_KEY

# check exported value
env | grep USERNAME
```

### env

```bash
# print set environment variables
env
```

### pwd

```bash
# print working directory
pwd
```

### unset

```bash
export TEST_VAR=42
env | grep TEST_VAR

# unset variable
unset TEST_VAR

env | grep TEST_VAR
```

### exit

```bash
# exit minishell
exit

# exit with code
exit 42
```

## Build

### Prerequisites

- OS: Linux or macOS
- make
- cc
- readline (macOS: `brew install readline`)
- valgrind (for `make valgrind`)

### Quick start

```bash
# compile
make

# launch shell
./minishell
```

### Commands

```bash
make            # compile
make clean      # remove objects
make fclean     # remove objects and executable
make re         # clean and recompile
make valgrind   # run valgrind
```

## Resources

- [Bash reference manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Introduction to Systems Programming - Chapter 5: Writing your own sell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
- [Writing a shell in C - Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/)
