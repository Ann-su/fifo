//#define USE_FQUEUE
#define USE_TEMPLATE_FQUEUE

#ifdef USE_FQUEUE
#include "FQueue.h"
void QueueTest();
#endif

#ifdef USE_TEMPLATE_FQUEUE
#include "TemplateFQueue.h"
void TemplateTest();
#endif

int main()
{
#ifdef USE_FQUEUE
	QueueTest();
#endif

#ifdef USE_TEMPLATE_FQUEUE
	TemplateTest();
#endif

	return 0;
}

#ifdef USE_TEMPLATE_FQUEUE
void TemplateTest()
{
	printf("---INT-------------------------------------------------------------------\n");

	FQueue<int> queue_1;
	FQInfo<int> t1(5);
	FQInfo<int> t2(9);
	FQInfo<int> t3(18);
	queue_1.FQEnqueue( &t1);
	queue_1.FQEnqueue( &t2);
	queue_1.FQEnqueue( &t3);
	while (!queue_1.FQEmpty())
	{
		FQInfo<int> *pItem = queue_1.FQDequeue();
		cout << *pItem << endl;
	}
	printf("---DOUBLE-------------------------------------------------------------------\n");

	FQueue<double> queue_2;
	FQInfo<double> t4(5.13);
	cout << "t4 = " << t4 << endl;
	FQInfo<double> t5(9.2);
	FQInfo<double> t6(18.009);
	queue_2.FQEnqueue( &t4);
	queue_2.FQEnqueue( &t5);
	queue_2.FQEnqueue( &t6);
	while (!queue_2.FQEmpty())
	{
		FQInfo<double> *pItem = queue_2.FQDequeue();
		cout << *pItem << endl;
	}


	printf("---CONST CHAR*-------------------------------------------------------------------\n");

	FQueue<const char*> queue_3;
	FQInfo<const char*> t7("let");
	FQInfo<const char*> t8("me");
	FQInfo<const char*> t9("out of here");
	queue_3.FQEnqueue( &t7);
	queue_3.FQEnqueue( &t8);
	queue_3.FQEnqueue( &t9);
	while (!queue_3.FQEmpty())
	{
		FQInfo<const char*> *pItem = queue_3.FQDequeue();
		cout << *pItem << endl;
	}
}
#endif

#ifdef USE_FQUEUE
void QueueTest()
{
    // Tworzymy obiekty FQInfo i dodajemy je do kolejki
    FQueue myQueue;
    FQInfo item1(1);
    FQInfo item2(2);
    FQInfo item3(3);
    myQueue.FQEnqueue(&item1);
    myQueue.FQEnqueue(&item2);
    myQueue.FQEnqueue(&item3);

    // Wyświetlamy elementy kolejki przed dequeue
    cout << "Queue before dequeue:" << endl;
    while (!myQueue.FQEmpty())
    {
        FQInfo *pItem = myQueue.FQDequeue();
        cout << *pItem << endl;
    }

    // Dodajemy nowe elementy do kolejki
    FQInfo item4(4);
    FQInfo item5(5);
    myQueue.FQEnqueue(&item4);
    myQueue.FQEnqueue(&item5);

    // Wyświetlamy elementy kolejki po ponownym dodaniu
    cout << "\nQueue after enqueue:" << endl;
    while (!myQueue.FQEmpty())
    {
        FQInfo *pItem = myQueue.FQDequeue();
        cout << *pItem << endl;
    }
}
#endif
