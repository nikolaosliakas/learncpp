# Added for merge conflicts

1. Nested functions are not supported.
2. https://datatracker.ietf.org/doc/html/rfc3092
3. Global variables are executed before `main()`


## From the [site][https://www.learncpp.com/cpp-tutorial/function-return-values-value-returning-functions/]
The C++ standard only defines the meaning of 3 status codes: 
0, EXIT_SUCCESS, and EXIT_FAILURE. 0 and EXIT_SUCCESS both mean 
the program executed successfully. EXIT_FAILURE means the program did not 
execute successfully.

EXIT_SUCCESS and EXIT_FAILURE are preprocessor macros defined in the 
`<cstdlib>` header:
```c++
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE

int main()
{
return EXIT_SUCCESS;
}
```

If you want to maximize portability, you should only use 0 or 
EXIT_SUCCESS to indicate a successful 
termination, or EXIT_FAILURE to indicate an unsuccessful termination.