#include "shell.h"

/**
 * cd - Implementation of the built in 'cd' command
 *
 * @command: Pointer to the input stream
 *
 * Return: 1 (success) 0 (failure).
 */

int cd(command_t *command)
{
	char *home = "HOME", *old = "OLDPWD";
	char *prev = NULL;
	char *newpath = NULL;

	int i;

	prev = getcwd(prev, 0);
	if (!prev)
		return (1);

	/* case1: cd */
	/* change to the home directory */

	/* case2: cd - */
	/* change to OLDPWD */

	/* case3: cd .. */
	/* change up one dir */

	/* case 4: cd . */
	/* stay in cur dir */

	/* TODO */
