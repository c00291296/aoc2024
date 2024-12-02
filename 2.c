#include <stdio.h>

int pair_safe(int a, int b, int sign) {
	int diff = abs(a-b);
	int newsign = a-b > 0;
	//printf("%d ", diff);
	return diff >= 1 && diff <=3 && (newsign == sign || sign == -1);
}

/* just pipe the input file into the compiled program! */
int main()
{
	int safe_reports = 0;
	int last_number = -1;
	int is_safe = 1;
	int num = -1;
	int sign = 1;
	for(;;) {
		char c;
		scanf("%d", &num);
		c = getchar();
		if(c=='\n' && c!='\r') {
			is_safe&=pair_safe(last_number, num, sign);
			if(is_safe)
				safe_reports++;
			//printf("%d", safe_reports);
			is_safe = 1;
			last_number = -1;
			sign = -1;
			//printf("\n");
		}
		else if(c==' ' && last_number != -1) {
			is_safe&=pair_safe(last_number, num, sign);
			sign = (last_number - num) > 0;
			last_number = num;
		} else if(last_number == -1) {
			last_number = num;
			is_safe = 1;
			sign = -1;
		}
		if(c==EOF)
		{
			is_safe&=pair_safe(last_number, num, sign);
			if(is_safe)
				safe_reports++;
			break;
		}

	}
	printf("Safe reports: %d\n", safe_reports);
	return 0;
}
