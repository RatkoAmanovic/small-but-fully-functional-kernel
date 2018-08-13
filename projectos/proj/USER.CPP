#include <iostream.h>
#include "thread.h"
#include "semaphor.h"

void tick()
{

}

class BoundedBuffer
{
	int *a;
	int cap;
	int head,tail;
	Semaphore mutexHead,mutexTail,Item,Space;
public:
	BoundedBuffer(int c):mutexHead(1),mutexTail(1),Item(0),Space(c)
	{
		a=new int[cap=c];
		head=tail=0;
	}

	void put(int data)
	{
		Space.wait();
		mutexHead.wait();
		a[head]=data;
		head=(head+1)%cap;
		mutexHead.signal();
		Item.signal();
	}

	int get()
	{
		Item.wait();
		mutexTail.wait();
		int tmp=a[tail];
		tail=(tail+1)%cap;
		mutexTail.signal();
		Space.signal();
		return tmp;
	}
	~BoundedBuffer()
	{
		cout<<"BB::Destructor"<<endl;
		delete[] a;
	}
};

class Producer:public Thread
{
	BoundedBuffer *b;
	int k;
	int id;
	Semaphore *io;
public:
	Producer(BoundedBuffer *bb,int kk,Semaphore *ii,int idd):b(bb),k(kk),io(ii),id(idd){}
	void run()
	{
		for(int i=0;i<k;i++)
		{
			io->wait();
			cout<<"PROIZVODJAC "<<id<<" PROIZVODI "<<i<<endl;
			io->signal();
			b->put(i);
		}
		io->wait();
		cout<<"PROIZVODJAC "<<id<<" GOTOV"<<endl;
		io->signal();

	}
	~Producer()
	{
		waitToComplete();
	}
};

class Consumer:public Thread
{
	BoundedBuffer *b;
	Semaphore *io;
	int k;
	int id;
public:
	Consumer(BoundedBuffer *bb,int kk,Semaphore *ii,int idd):b(bb),k(kk),io(ii),id(idd){}
	void run()
	{
		for(int i=0;i<k;i++)
		{
			int tmp=b->get();
			io->wait();
			cout<<"POTROSAC "<<id<<" TROSI "<<tmp<<endl;
			io->signal();
		}
		io->wait();
		cout<<"POTROSAC "<<id<<" GOTOV"<<endl;
		io->signal();
	}
	~Consumer()
	{
		waitToComplete();
	}
};


void userMain(int argc,char *argv[])
{
	Semaphore *io=new Semaphore(1);
	BoundedBuffer *b=new BoundedBuffer(10);

	Producer **p;
	Consumer **c;
	int np=1;
	int nc=np*3;

	p=new Producer*[np];
	c=new Consumer*[nc];

	for(int i=0;i<np;i++)
	{
		p[i]=new Producer(b,30,io,i+1);
		p[i]->start();
	}
	for(int j=0;j<nc;j++)
	{
		c[j]=new Consumer(b,10,io,j+1);
		c[j]->start();
	}
	cout<<"GLAVNA SPAVA"<<endl;
	Thread::sleep(0);
	cout<<"NE SPAVA JER JE VREME NEGATIVNO"<<endl;
	Thread::sleep(5);
	cout<<"SPAVALA JE 5"<<endl<<endl<<endl<<endl<<endl;
	for(int k=0;k<np;k++) delete p[k];
	for(int l=0;l<nc;l++) delete c[l];

	delete p;
	delete c;
	delete b;

	cout<<"Obrisala bafer"<<endl<<endl<<endl;
		while(1);

	delete io;
	cout<<"GLAVNA GOTOVA"<<endl;
}
