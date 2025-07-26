    .globl _is_prime
    .text

// int is_prime(int n)
_is_prime:
    // x0 = n (input)
    // We'll use x1 = i, x2 = temp, x3 = remainder, x4 = i*i

    // if (n < 2) return 0;
    cmp x0, #2
    blt .not_prime

    mov x1, #2        // i = 2

.loop:
    mul x4, x1, x1    // x4 = i * i
    cmp x4, x0
    bgt .is_prime     // if i*i > n => return 1

    udiv x2, x0, x1   // x2 = n / i
    msub x3, x2, x1, x0  // x3 = n - (n / i) * i → x3 = n % i
    cbz x3, .not_prime   // if remainder == 0 → not prime

    add x1, x1, #1
    b .loop

.is_prime:
    mov x0, #1
    ret

.not_prime:
    mov x0, #0
    ret

