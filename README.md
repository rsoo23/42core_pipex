# pipex

This project is an introduction to topics such as: parent and child processes, pipes, redirections; a prerequisite to a later project (minishell).

## Testers:
https://github.com/vfurmane/pipex-tester

## Resources: <br />
https://www.codequoi.com/en/creating-and-killing-child-processes-in-c/ <br />
https://www.codequoi.com/en/pipe-an-inter-process-communication-method/ <br />
https://www.codequoi.com/en/handling-a-file-by-its-descriptor-in-c/

## How to use:
1. Clone the repository
```bash
git clone https://github.com/rsoo23/pipex.git pipex
```
2. Make the executable
```bash
make
```
3. Input the arguments in the format:
Single Pipe: The program handles 2 commands, getting the input from the infile and writing the output to the outfile.
```bash
./pipex infile cmd1 cmd2 outfile
```
```bash
This replicates:
./pipex < infile cmd1 | cmd2 > outfile
```
```bash
Example:
./pipex infile.txt "grep make" "wc -l" outfile.txt
```

## Bonus:
Multiple Pipes: The program handles > 2 commands using multiple pipes.
```bash
./pipex infile cmd1 cmd2 ... cmdn outfile
```
```bash
This replicates:
./pipex < infile cmd1 | cmd2 | .. | cmdn > outfile
```
```bash
Example:
./pipex infile.txt "grep make" "wc -l" "cat -e" outfile.txt
```
Here_doc: The program receives input from the standard input (STDIN) until the limiter is entered and executes the commands, writing the output to the outfile.
```bash
./pipex here_doc limiter cmd1 cmd2 outfile
```
```bash
This replicates:
./pipex cmd1 << limiter | cmd2 >> outfile
```
```bash
Example:
./pipex here_doc stop "grep hi" "wc -w" outfile.txt
```
