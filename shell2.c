void run_command(char **args, char *prog_name, int line)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return;

	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				prog_name, line, args[0]);
			exit(127);
		}
	}
	else
	{
		wait(NULL);
	}
}
