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
	printf("---int--------------------------------------------------------------------\n");

	FQueue<int> lista1;
	lista1.FQEnqueue(2);
	lista1.FQEnqueue(1);
	lista1.FQEnqueue(3);
	lista1.Print();
	cout << endl;

	printf("---double--------------------------------------------------------------------\n");

	FQueue<double> lista2;
	lista2.FQEnqueue(7.21);
	lista2.FQEnqueue(8888.2);
	lista2.FQEnqueue(420.69);
	lista2.Print();
	cout << endl;

	printf("---Tablica czarow--------------------------------------------------------------------\n");

	FQueue<const char *> lista3;
	lista3.FQEnqueue("Let");
	lista3.FQEnqueue("me");
	lista3.FQEnqueue("out");
	lista3.Print();
	cout << endl;

}
#endif

#ifdef USE_FQUEUE
void QueueTest()
{

    FQueue fifo;
    FQInfo item1(1);
    FQInfo item2(2);
    FQInfo item3(3);
    fifo.FQEnqueue( &item1);
    fifo.FQEnqueue( &item2);
    fifo.FQEnqueue( &item3);

    cout << "Queue before dequeue:" << endl;
    while (!fifo.FQEmpty())
    {
        FQInfo *pItem = fifo.FQDequeue();
        cout << *pItem << endl;
    }

    FQInfo item4(4);
    FQInfo item5(5);
    fifo.FQEnqueue( &item4);
    fifo.FQEnqueue( &item5);

    cout << "\nQueue after enqueue:" << endl;
    while (!fifo.FQEmpty())
    {
        FQInfo *pItem = fifo.FQDequeue();
        cout << *pItem << endl;
    }
}
#endif
