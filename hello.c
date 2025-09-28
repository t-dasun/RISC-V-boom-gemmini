// A simple C program for RocketConfig that performs a calculation.
// It avoids printf() or other I/O, which prevents the "PutPartial" error.

int main() {
    int a = 0;
    int b = 1;
    int sum = 0;

    // Calculate the 10th Fibonacci number
    for (int i = 0; i < 10; ++i) {
        sum = a + b;
        a = b;
        b = sum;
    }

    // The program finishes here. The result 'sum' is in a register or on the stack,
    // but it's never printed to the console. The simulation will run to completion
    // and exit once the main function returns.
    return 0;
}