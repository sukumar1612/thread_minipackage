#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include <bits/stdc++.h>
#include <pthread.h>


using namespace std;

map<string, int> m;
char filename[100];
pthread_mutex_t lock1;
int opp=0;

struct val{
  int a;
};
void *pr(void *pos1)
{
  int pos=((struct val *)pos1)->a;

  FILE *fptr=fopen(filename,"r");
  char line1[10000];
  string s;

  fseek(fptr, pos, SEEK_SET);
  fgets(line1, sizeof(line1), fptr);

  fclose(fptr);


  for(int i=0;i<10000;i++)
  {

    if(line1[i]=='\n')
    {
    //  pthread_mutex_unlock(&lock1);
      break;
    }


    if(line1[i]==' ' || line1[i]=='.' || line1[i]=='"' || line1[i]==',' || line1[i]=='-')
    {
      pthread_mutex_lock(&lock1);
      opp++;
      transform(s.begin(), s.end(), s.begin(), ::tolower);
      m[s]++;
      s.clear();
      pthread_mutex_unlock(&lock1);
    }
    else
    {
      s+=line1[i];
    }
    //pthread_mutex_unlock(&lock1);
  }
  return NULL;
}


int main(int argc , char **argv)
{
  if (pthread_mutex_init(&lock1, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
  }

  if(argc==1)
  {
    cout<<"-------please enter appropriate file name---------\n"<<endl;
    exit(0);
  }

  FILE *f= fopen(argv[1],"r");
  strcpy(filename,argv[1]);

  if (f == NULL)
  {
      cout<<"--------Cannot open file or file doesnot exist----------\n"<<endl;
      exit(0);
  }
  char line[10000];
  int len=ftell(f);

  pthread_t t1[1000];
  int cnt=0;
  struct val *val1[1000];
  while(fgets(line, sizeof(line), f))
  {

    val1[cnt]=(struct val*)malloc(sizeof(struct val));
    val1[cnt]->a=len;

    pthread_create(&t1[cnt],NULL, pr, (void *)val1[cnt]);
    //sleep(0.3);
    cnt++;
    len=ftell(f);
  }

  for(int i=0;i<cnt;i++)
  {
    pthread_join(t1[i], NULL);
  }


  int cnt1=0;
  float avg=0;
  cout<<"-------------SIMPLE FILE ANALYSIS---------------"<<endl;
  cout<<"words and its occurances in the file--- \n\n"<<endl;

  string s1;
  for(auto i=m.begin();i!=m.end();i++)
  {
    cnt1++;

    cout<<"WORD :"<<i->first << "\t\t\tNumber of occurances:  " << i->second <<endl;
    avg=avg+i->first.size();
    if(i->second>=9)
    {
      s1+=i->first;
      s1+="\n";
    }
  }
  cout<<"\n\ntotal number of distinct words :"<<cnt1<<endl;
  cout<<"average word length :"<<avg/cnt1<<endl;
  cout<<"most frequently used words :"<<s1<<endl;

  cout<<"DEBUG COUNTER :"<<opp<<endl;
  pthread_mutex_destroy(&lock1);
}
