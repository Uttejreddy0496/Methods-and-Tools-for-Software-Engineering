#include <iostream>
#include <unistd.h>
#include <vector>
#include <signal.h>
#include <sys/wait.h>
using namespace std;

int procCin(void) {
    while (!std::cin.eof()) {
        std::string line;
        std::getline(std::cin, line);
	std::cout << line << std::endl;
    }
    return 0;
}

int main (int argc, char **argv) {

    int RtoA1[2];
    int A1toA2[2];
    pipe(RtoA1);
    pipe(A1toA2);
    pid_t k1,k2,k3,k4;

    k1  = fork();
    if(k1 == 0)
    {
      //cout<<"inside rgen child1"<<endl;
     close(RtoA1[0]);
     close(A1toA2[0]);
     close(A1toA2[1]);
     dup2(RtoA1[1], STDOUT_FILENO);
     close(RtoA1[1]);

        char *rgenarg[argc]={};
	rgenarg[0]=(char *)"./rgen";
	for(int i=1;i<argc;i++){
	  rgenarg[i]=argv[i];
	}
	rgenarg[argc]=NULL;
	execvp("./rgen",rgenarg);

    }
    else if (k1 < 0) {
      std::cerr << "Error: could not fork\n";}

    k2 = fork();
    if(k2 == 0)
    {
        //cout<<"inside a1 child1"<<endl;
        close(RtoA1[1]);
        dup2(RtoA1[0], STDIN_FILENO);
        close(RtoA1[0]);

        close(A1toA2[0]);
	dup2(A1toA2[1], STDOUT_FILENO);
        close(A1toA2[1]);

        char *argv1[3];

        argv1[0] = (char *)"python3";
        argv1[1] = (char *)"a1ece650.py";
        argv1[2] = NULL;

        execvp(argv1[0], argv1);
    }
    else if (k2 < 0) {
     std::cerr << "Error: could not fork\n";}


    k3  = fork();
    if(k3 == 0)
    {
          //  cout<<"inside a2 child1"<<endl;

	close(A1toA2[1]);
        close(RtoA1[0]);
        close(RtoA1[1]);
       dup2(A1toA2[0], STDIN_FILENO);
       close(A1toA2[0]);

               char *argv3[2];

        argv3[0] = (char *)"./a2ece650";
        argv3[1] = NULL;
	execvp(argv3[0],argv3);

    }
        else if (k3 < 0) {
     std::cerr << "Error: could not fork\n";}


    k4  = fork();
    if(k4 == 0)
    {
       close(A1toA2[0]);
        close(RtoA1[0]);
        close(RtoA1[1]);
        dup2(A1toA2[1], STDOUT_FILENO);
        close(A1toA2[1]);
        procCin();
    }
       else if (k4 < 0) {
     std::cerr << "Error: could not fork\n";}

        int status;
		wait(&status);
        kill(k1, SIGTERM);
        waitpid(k1, &status, 0);

        kill(k2, SIGTERM);
        waitpid(k2, &status, 0);

        kill(k3, SIGTERM);
        waitpid(k3, &status, 0);
        kill(k4, SIGTERM);
        waitpid(k4, &status, 0);


	return 0;

	}

