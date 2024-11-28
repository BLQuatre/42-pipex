#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int fd[2];
    if (pipe(fd) == -1)
        return 1;

    int pid1 = fork();
    if (pid1 < 0)
        return 2;

    if (pid1 == 0)
    {
        // child process to read from file and send to pipe
        int file_fd = open("infile", O_RDONLY);
        if (file_fd < 0)
        {
            perror("open");
            return 4;
        }
        dup2(file_fd, STDIN_FILENO);
        close(file_fd);

        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);

        execlp("cat", "cat", NULL);
        perror("execlp");
		exit(127);
		// TODO: do quit here
    }
    
	close(fd[1]);

    int pid2 = fork();
    if (pid2 < 0)
        return 3;

    if (pid2 == 0)
    {
        // child process to read from pipe and run grep
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

		int file_fd2 = open("outfile", O_RDONLY | O_WRONLY | O_CREAT, 0644);
		if (file_fd2 < 0)
        {
            perror("openee");
            return 4;
        }
        dup2(file_fd2, STDOUT_FILENO);
        close(file_fd2);

        execlp("head", "head", "-5", NULL);
        perror("execlp");
		exit(127);
		// TODO: do quit here
    }

    close(fd[0]);

    // waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
