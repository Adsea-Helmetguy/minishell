# minishell
Objective is to create a basic shell program in C.

We need to use redirections and pipes,
create environment variables commands such as:
cd, echo, env, exit, export, pwd and unset builtin commands.

How to use:
After you have git cloned, Type: "./minishell"
Inside the terminal to use.


Builtin commands inside:
echo (and option -n)
cd (with only a relative or absolute path)
pwd (no options)
export (no options)
unset (no options)
env (no options or arguments)
exit (with exit number but no other options)



Pipes | which redirect output from one command to input for the next



Redirections:
">" redirects output
">>" redirects output in append mode
"<" redirects input
"<<" DELIMITER displays a new prompt, and reads until reaching DELIMITER.
E.g: DELIMITER = cat.
unless u type exactly the same words "cat" You can keep typing forever.



____________________________________________________________________________________
Environment variables such as $USER or $VAR that updates and expand to their values.
____________________________________________________________________________________
The value: "$?" expands to the exit status of the most recently executed foreground pipeline.
E.g: If u exit with ctrl+C the signal should show the value 130 when you write:
"echo $?"
____________________________________________________________________________________



Use these keyboard signals:
ctrl-c displays a new prompt line.
ctrl-d exits minishell
ctrl-\ to quit during piping:
e.g:
cat | cat | cat
Instead of writing three times, u can exit with ctrl+\.
