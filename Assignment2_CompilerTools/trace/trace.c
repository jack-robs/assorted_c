#include <stdio.h>
#include <time.h>

static int count = 0;
static long start_t = 0;
static long end_t = 0;
static long total_time = 0;


void
__attribute__ ((constructor))
trace_begin (void)
{

start_t = clock();

}

void 
__attribute__ ((destructor))
trace_end (void)
{

end_t = clock();
total_time = (double)(end_t - start_t) / CLOCKS_PER_SEC;
printf("\n\nEnd Clocks: %ld", end_t);
printf("\n\nTotal Time: %f", total_time);
printf("\n\nFunction calls: %d\n", count);

}


__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site){

	printf("Function entered: %p from %p\n", this_fn, call_site);
	count ++;

}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site){

	printf("Function exited: %p from %p\n", this_fn, call_site);

}


