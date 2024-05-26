#include <stdint.h>
#include
<inttypes.h> volatile int counter = 0;
void *worker(void *arg)
{
    const intptr_t n_loops = (intptr_t)arg;
    for (int i = 0; i < n_loops; i++)
    {
        counter++;
    }
    return 0;
    ｝

        int
        main(int argc, char *argv[])
    {
        A if (argc != 2)
        {
            fprintf(stderr, "usage: %5 <n_loops>\n", *argv);
            return EXIT_FAILURE;
        }
const intptr_t n_loops = atoiCargv[1]);
pthread_t t1, t2;
printf("Initial value : %d\n", counter);
if (pthread_create(&t1, NULL, worker, (void *)n_loops))
{
    fprintf(stderr, "Cannot create thread-1\n");
    return EXIT_FAILURE;
}
