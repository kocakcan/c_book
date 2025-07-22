#include <stdio.h>

/* the difference between nums and &nums */
int main(void) {
  int nums[] = {-1, 3, 5, -3};
  int *numsp = nums;

  printf("nums          %p (points to the first element)\n", (void *)nums);
  printf("&nums         %p (points to the entire array)\n", (void *)&nums);
  printf("&nums[0]      %p (points to the first element)\n", (void *)&nums[0]);
  printf("numsp         %p (points to the first element)\n", (void *)numsp);
  printf("&numsp        %p (points to the numsp)\n", (void *)&numsp);

  printf("\nnums + 1:     %p (second element, 4 bytes ahead)\n",
         (void *)(nums + 1));
  printf("&nums + 1:    %p (next array block, 16 bytes ahead)\n",
         (void *)(&nums + 1));
}
