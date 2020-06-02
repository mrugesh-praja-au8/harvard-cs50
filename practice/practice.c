/* Read input from STDIN. Print your output to STDOUT*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char *argv[])
{
	//Write code here

	int n;
	scanf("%i", &n);

	int q[n];
	for(int i = 0; i < n; i++)
	{
		scanf("%i", &q[i]);
	}

	int a[n];
	for(int i = 0; i < n; i++)
	{
		scanf("%i", &a[i]);
	}

	int store[n];
	for(int j = 0; j < n; j++)
	{
		store[j] = round(a[j] / q[j]);
	}

	for(int j = 0; j < n-1; )
	{
		if(store[0] > store[j + 1])
		{
			store[0] = store[j + 1];
			j++;
		}
		else
		{
			j++;
		}
	}

	printf("%i\n", store[0]);
	return 0;
}

	// if(argc < 4)
	// {
	// 	return 1;
	// }

	// int n = atoi(argv[1]);
	// int store[n];
	// for(int j = 0; j < n; j++)
	// {
	// 	store[j] = (atoi(argv[2 + n + j]) / atoi(argv[2 + j]));
	// }

	// for(int j = 0; j < n-1; )
	// {
	// 	if(store[0] > store[j + 1])
	// 	{
	// 		store[0] = store[j + 1];
	// 		j++;
	// 	}
	// 	else
	// 	{
	// 		j++;
	// 	}
	// }

