#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.c"

int main()
{
	List new = initList();
	printf("%d\n", isEmpty(new));

	add(new, 3);
	add(new, 4);
	add(new, 5);

	pop(new);
	return 0;
}
