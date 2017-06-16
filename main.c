#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "linux_list.h"

struct person {
	struct list_head list;
	int age;
	int weight;
};

int main()
{
	int i;
	int age[5] = {1,2,3,4,5};
	int weight[5] = {11,12,13,14,15};

	struct person *tmp = NULL;
	struct person head;
	struct list_head *pos, *pfree, *n;

	INIT_LIST_HEAD(&head.list);

	for (i = 0; i < sizeof(age)/sizeof(int); i++) {
		if (!(tmp = (struct person *)malloc(sizeof(struct person)))) {
			fprintf(stderr, "Malloc failed\n");
			exit(-1);
		}
		tmp->age = age[i];
		tmp->weight = weight[i];
		list_add_tail((struct list_head *)tmp, (struct list_head *)&head);
	}

	list_for_each(pos, (struct list_head *)&head) {
		printf("The age %d \t weight %d\n", ((struct person *)pos)->age, ((struct person *)pos)->weight);
	}

	list_for_each_safe(pos, n, (struct list_head *)&head) {
		if (((struct person *)pos)->age == 3) {
			list_del(pos);
			free(pos);
		}
	}

	list_for_each_safe(pos, n, (struct list_head *)&head) {
		printf("The age %d \t weight %d\n", ((struct person *)pos)->age, ((struct person *)pos)->weight);
		list_del_init(pos);
		free(pos);
	}

	return 0;
}
