## Minishell

Shell project for school 21, campus of Ecole 42.
It is a reimplementation of a shell, handling redirections, pipes, launching executables as well as some of the built-ins.

#### Usage

This version is available for Linux.  
to create an executable run: 

`git clone https://github.com/bklvsky/minishell.git`  
`cd ./minishell`  
`make`

The readline.h header is neccessary to run this programm, to install it run:

`sudo apt-get install libreadline6 libreadline6-dev`  


#### About the project

The programm displays a prompt while waiting for new command, as in bash.  
Executables can be launched with relative `./minishell`, absolute `/bin/ls`
or environment path `ls`.  

7 built-in commands had to be recoded directly:

* echo
* cd
* pwd
* export
* unset
* env
* exit

Environment variables are handled (try `echo "$USER"` and `echo '$USER'`), and the `$?` variable as well.  
Pipes `|` and redirections `> < >> <<` work the same as in bash.  
It is also possible to navigate through history of commands.  

#### Summary

Working on this project I learned a lot about interproccess communication, fork calls and file descriptors system.  
Also, it significantly boosted my understating of the shell - it is impossible to recode anything without deep immersion in the subject! - and it is an essential everyday working tool for me.  


#### Credit

The project was done in team with [Smooky](https://github.com/Smoooky).  
My part of the project was - parser, argument checking, execution,  
redirections, pipes and environment variables; and my teammate handled builtins,  
signals and termcap.  

