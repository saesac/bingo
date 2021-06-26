#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int bingo_size = 0, num_temp ;
	int num[1000] = {0,};
	int rand_n, i,j, k = 0 ;
	int result_num[1000] = { 0, } ;
	char c ;
	
	srand((unsigned int)time(NULL));
	
	scanf("%d", &bingo_size) ;
	
	while(1)
	{		
		rand_n = rand()%(bingo_size*bingo_size*2) ;
		num[k] = rand_n ;
			
		for( i=0; i<=k; i++ )
		{
			if( num[k] == num[i] )
			{
				break ;
			}
		}
		if( i == k )
		{
			k++ ;
			if( k == bingo_size*bingo_size )
				break ;
		}
	}
	
	for( i=0; i<bingo_size; i++ )
	{
			for(j=0; j<bingo_size; j++)
			{
				result_num[i*bingo_size+j] = num[i*bingo_size+j] ;
				printf("%4d  ", result_num[i*bingo_size+j]) ;
			}
		printf("\n") ;
	}
	
	i = 0 ;
	while(1)
	{
			scanf("%d", &num_temp ) ;
			if (num_temp < 0 )
				break ;
			else
			{
				for( i=0; i<bingo_size*bingo_size; i++ )
				{
					if( result_num[i] == num_temp)
					{
						result_num[i] = -1 ;	
					}	
				}
				for( i=0; i<bingo_size; i++ )
				{
					for(j=0; j<bingo_size; j++)
					{
						if( result_num[i*bingo_size+j] <0)
							printf("   X", result_num[i*bingo_size+j] ) ;
						else
							printf("%4d", result_num[i*bingo_size+j]) ;
					}
					printf("\n") ;
				}
				
			}
	}
	
	for( i=0; i<bingo_size; i++ )
	{
		for(j=0; j<bingo_size; j++)
		{
			printf("%4d", num[i*bingo_size+j]) ;
		}
		printf("\n") ;
	}
	 
	 return 1 ;
}
