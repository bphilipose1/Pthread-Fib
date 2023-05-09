#include <iostream>
#include <string>
#include <pthread.h>
using namespace std;

void* fibNum(void* maxNum)  {
  int* tempF = (int*) maxNum;    
  int* returnArr = new int[*tempF];
  for (int i = 0; i < *tempF; i++)  {
        if(i==0)    {
            returnArr[0] = 0;
        }
        else if(i==1)   {
              returnArr[1] = 1;
        }
        else    {
            returnArr[i] = returnArr[i-1]+returnArr[i-2];
        }
    }
  pthread_exit((void*)returnArr);
}

int main(int argc, char* argv[])    {
  int *F = new int;
  *F = atoi(argv[1]);
    if(*F<=0)   {
        return 0;
    }

  int* resultArrPtr;//to point to beggining of returned array
  pthread_t childThread;
  if(pthread_create(&childThread, NULL, &fibNum, (void*) F))    {
    perror("Pthread_create failed");
        delete F;
        exit(-1);

  }
  if(pthread_join(childThread, (void**)&resultArrPtr))    {
        perror("Pthread_join failed");
        delete F;
    	  exit(-2);
  }

  for(int z = 0; z < *F; z++) {
     cout << resultArrPtr[z] << " ";
  }
  cout << "" << endl;

  delete F;
  delete [] resultArrPtr;
  return 0;
}
