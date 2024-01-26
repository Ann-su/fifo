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

	FQueue<int> fifo1;
	fifo1.FQEnqueue( 2);
	fifo1.FQEnqueue( 1);
	fifo1.FQEnqueue( 3);
	fifo1.Print();
	cout << endl;

	printf("---double--------------------------------------------------------------------\n");

	FQueue<double> fifo2;
	fifo2.FQEnqueue( 7.21);
	fifo2.FQEnqueue( 8888.2);
	fifo2.FQEnqueue( 420.69);
	fifo2.Print();
	cout << endl;

	printf("---Tablica czarow--------------------------------------------------------------------\n");

	FQueue<const char *> fifo3;
	fifo3.FQEnqueue( "Let");
	fifo3.FQEnqueue( "me");
	fifo3.FQEnqueue( "out");
	fifo3.Print();
	cout << endl;

}
#endif

#ifdef USE_FQUEUE
void QueueTest()
{
	FQueue fifo;
	FQInfo* pItem = new FQInfo( 1  );
	fifo.FQEnqueue( pItem );
	cout << "Added: " << *pItem << endl;
	pItem = new FQInfo( 2);
	fifo.FQEnqueue( pItem );
	cout << "Added: " << *pItem << endl;
	pItem = new FQInfo( 3 );
	fifo.FQEnqueue( pItem );
	cout << "Added: " << *pItem << endl;

	pItem = fifo.FQDequeue();
	cout << "Removed " << *pItem << endl;
	delete pItem;
	pItem = fifo.FQDequeue();
	cout << "Removed " << *pItem << endl;
	delete pItem;
	pItem = fifo.FQDequeue();
	cout << "Removed " << *pItem << endl;
}
#endif
