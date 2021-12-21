
/*PARSER:
TOKEN RECOGNITION - READ USING SHELL GRAMMAR


TOKEN RECOGNITION:

"The token shall be from the current position in the input until a token 
is delimited according to one of the rules below; the characters forming 
the token are exactly those in the input, including any quoting characters. 
If it is indicated that a token is delimited, and no characters have been 
included in a token, processing shall continue until an actual token is delimited."

!!During token recognition no substitutions shall be actually performed!!


1. end of input - current token delimeted;
2. If the current character is backslash, single-quote, or double-quote ( '\', '", or ' )'
and it is not quoted, it shall affect quoting for subsequent characters up to 
the end of the quoted text. The rules for quoting are as described in Quoting.
3. The token shall not be delimited by the end of the quoted field.

; - isn't interpreted as a delimeter, appends to the previous command or word


PARSING AT THE TOKEN LEVEL

[command name][redirection in or out of file]

if "<" or ">" next word is a name of file 
if next sym == current - append mode in redirect output
						reading from shell in input as if it was in double quoted
open file and save in fd_in/fd_out of current token [open() flags depend on number of >>]
(if it can't be opened -> error exit with name of file as an identificator)
if "|" tokens should be placed in a linked list and pipex will be used

else ->we save all next words in char **cmd -> command name with arguments and so on
right there access/stat is performed on the first word of the token 
to check if binary file exists
or
if == builtin -> just save it as a token and move on with parsing

*/

#include "parser.h"


/*new_token() -> allocate new token and link it with a current one*/
/*manage_redirections -> new fds in current token structure*/
/*manage pipes -> if t_list *tokens->next means there is a pipe
		while tokens != NULL
			if next
				pipe()
			if (!built_in)
				fork()
			else
				built_in_management
			tokens = tokens->next*/

int		parser(char *line)
{
	int			quoted_flag;
	int			i;

	i = -1;
	quoted_flag = 0;
	while (line[++i] && line[i] != EOF)
	{
		if (line[i] == '\'' && !quoted_flag)
			quoted_flag = SINGLE_QUOTE;
		else if (line[i] == '"' && !quoted_flag)
			quoted_flag = DOUBLE_QUOTE;
		else if ((line[i] == '\'' && quoted_flag == SINGLE_QUOTE )|| \
			(line[i] == '"' || quoted_flag == DOUBLE_QUOTE))
			quoted_flag = 0;
		else if (line[i] != '|' || quoted_flag)
			write_in_token();
		else
			new_token();
	/*		
			it's from the next step
	
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i])
			break ;
		if (line[i] == '>' || line[i] == '<')
			manage_redirections();
		else if (line[i] == '|')
		*/

	}
	if (quoted_flag)
		error_exit();
}