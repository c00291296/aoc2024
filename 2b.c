#include <stdio.h>

int pair_safe(int a, int b, int sign)
{
	int diff = abs(a-b);
	int newsign = a-b > 0;
	//printf("%d ", diff);
	return diff >= 1 && diff <=3 && (newsign == sign || sign == -1);
}

int row_safe(int* arr, int size)
{
	int is_safe = 1;
	int last;
	int sign;
	int is_1st = 1;
	int is_2nd = 0;
	for(int i = 0; i < size; i++) {
		if(arr[i] == -1) // level to be ignored
			continue;
		if(is_1st) {
			last = arr[i];
			is_1st = 0;
			is_2nd = 1;
			continue;
		}
		else if(is_2nd) {
			is_2nd = 0;
			sign = last - arr[i] > 0;
		}
		is_safe &= pair_safe(last, arr[i], sign);
		last = arr[i];
	}
	return is_safe;
}

int has_safe_permutation(int* arr, int size)
{
	int swap;
	int result = 0;
	for(int i = 0; i < size; i++) {
		swap = arr[i];
		arr[i] = -1;
		if(row_safe(arr, size))
			return 1;
		arr[i] = swap;
	}
	return 0;
}


/* just pipe the input file into the compiled program! */
int main()
{
	int safe_reports = 0;
	int last_number = -1;
	int is_safe = 1;
	int num = -1;
	int sign = 1;
	int arr[20]; //making assumptions here
	int size = 0;
	for(;;) {
		char c;
		scanf("%d", &num);
		c = getchar();
		if(c=='\n' && c!='\r') {
			is_safe&=pair_safe(last_number, num, sign);
			arr[size] = num;
			size++;
			if(is_safe)
				safe_reports++;
			else
				safe_reports+=has_safe_permutation(arr, size);
			//printf("%d", safe_reports);
			is_safe = 1;
			last_number = -1;
			size = 0;
			sign = -1;
			//printf("\n");
		}
		else if(c==' ' && last_number != -1) {
			is_safe&=pair_safe(last_number, num, sign);
			arr[size] = num;
			size++;
			sign = (last_number - num) > 0;
			last_number = num;
		} else if(last_number == -1) {
			last_number = num;
			is_safe = 1;
			sign = -1;
			arr[size] = num;
			size++;
		}
		if(c==EOF)
		{
			is_safe&=pair_safe(last_number, num, sign);
			arr[size] = num;
			size++;
			if(is_safe)
				safe_reports++;
			else
				safe_reports+=has_safe_permutation(arr, size);
			break;
		}

	}
	printf("Safe reports: %d\n", safe_reports);
	return 0;
}
