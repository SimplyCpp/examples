#ifdef __EXAMPLE_PKG__
#define EXAMPLE_MAIN(ex_name) int run_##ex_name ()
#else
#define EXAMPLE_MAIN(ex_name) int main(int argc, char *argv[])
#endif
