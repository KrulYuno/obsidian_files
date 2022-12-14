#include <iostream>
#include <string>
#include <cstring>

int reverse_int(int n);
void reverse_str(char st[]);
bool sorted(int A[], int n);
int remainder(int a, int b);

int main (int argc, char *argv[])
{
  std::cout << reverse_int(42069) << std::endl;
  std::cout << reverse_int(103) << std::endl;
  std::cout << reverse_int(1496) << std::endl;
  
  char st[] = "dragrace";
  reverse_str(st);
  std::cout << std::endl;
  char st1[] = "nodevillivedon";
  reverse_str(st1);
  std::cout << std::endl;

  int s[] = {10,8,7,7,2};
  std::cout << "10,8,7,7,2: " << sorted(s, 5) << std::endl;
  int s1[] = {1, 17, 19, 43, 53, 53};
  std::cout << "1, 17, 19, 43, 53, 53: " << sorted(s1, 6) << std::endl;
  int s2[] = {3, 23, 10, 17, 15};
  std::cout << "3, 23, 10, 17, 15: " << sorted(s2, 5) << std::endl;
  int s3[] = {4, 4, 4, 4, 4};
  std::cout << "4, 4, 4, 4, 4: " << sorted(s3, 5) << std::endl;
  int s4[] = {10, 18, 71, 71, 224};
  std::cout << "10, 18, 71, 71, 224: " << sorted(s4, 5) << std::endl;
  int s5[] = {0,0,0,1};
  std::cout << "0,0,0,1: " << sorted(s5, 5) << std::endl;

  std::cout << remainder(41, 7) << std::endl;
  std::cout << remainder(11, 7) << std::endl;
  return 0;
}

int reverse_int(int n)
{
  // source: https://www.programiz.com/c-programming/examples/reverse-number
  /*
   * CONSTANTS:
   *    int reversed = 0;
   *    return reversed;
   *
   * ITERATED:
   *    n != 0
   *    n % 10
   *    10 + <>
   *    reversed * <>
   *    reversed = <>
   *    n /= 10;
   *
   * EXTRA:
   *    while (n != 0) --- last check
   *
   * T(n) = 2 + 6n + 1
   * T(n) = 6n + 3
   *
   */ 
  
  int reversed = 0;

  while( n != 0 ) 
  {
    reversed = reversed * 10 + (n % 10); 
    n /= 10; 
  }
  
  return reversed; 
}

void reverse_str(char st[])
{
    /*
     *
     * CONSTANTS:
     *    int s_len = strlen(st);
     *      strlen(st)
     *    int i=0;
     *
     * ITERATED:
     *    i < s_len;
     *    i++
     *    std::cout << st[s_len - 1 - i];
     *      s_len - 1
     *      1 - i
     *
     * EXTRA:
     *    for (i < s_len) --- FOR LOOP LAST CHECK
     *    i < s_len       --- -1
     *
     * T(n) = 3 + 5(n - 1 - 0 + 1)  + 1
     * T(n) = 5n + 4
     *
    */

      int s_len = strlen(st);
      for ( int i=0; i < s_len; i++ )
        std::cout << st[s_len - 1 - i];
} 

bool sorted(int A[], int n)
{
  /*
   *
   * CONSTANTS:
   *    if ( n == 1 )
   *    int sign = 0;
   *    int i=0;
   *    return ( sign == 0 ) ? false : true;
   *      sign == 0
   *
   * ITERATED:
   *    i<n-1;
   *      n-1
   *    i++
   *    if ( sign == 0)
   *    if ( sign < 0 && A[i] > A[i+1] )
   *      sign < 0 && A[i] > A[i+1]
   *        sign < 0
   *        A[i] > A[i+1]
   *          i+1
   *    if ( sign > 0 && A[i] < A[i+1] )
   *      sign > 0 && A[i] < A[i+1]
   *        sign > 0
   *        A[i] < A[i+1]
   *          i+1
   *
   * EXTRA:
   *    sign = A[i] - A[i+1];
   *      A[i] - A[i+1]
   *        i+1
   *    i<n-1;
   *
   * T(n) = 9 + 14(n - 1 - 0 + 1)
   * T(n) = 14n + 9
  */

  if ( n == 1 ) return true;

  int sign = 0;

  for ( int i=0; i<n-1; i++ )
  {
    if ( sign == 0)
      sign = A[i] - A[i+1];

    if ( sign < 0 && A[i] > A[i+1] ) 
      return false;
    
    if ( sign > 0 && A[i] < A[i+1] )
      return false;
  }
  
  return ( sign == 0 ) ? false : true; 
 }

int remainder(int a, int b)
{
  /*
   *
   * if ( a >= b )
   * return remainder(a-b, b);
   *   remainder(a-b, b)
   *    a-b
   *
   * T(n) = 4 + T(n - 1)
   * T(n) = 4 + 4 + T(n - 2)
   * T(n) = 4 + 4 + 4 + ... + T(1)
   * T(n) = 4(n - 1) + 2
   * T(n) = 4n - 4 + 2
   * T(n) = 4n - 2
   */
  // Assume only positive `int b`
  // No negatives please otherwise segmentation fault (core dumped). basically overflow or something

  // if ( b == 0 )
  //   exit(1);

  // b = b < 0 ? -b : b; // source: https://github.com/lattera/glibc/blob/master/stdlib/abs.c (for absolute values)
  if ( a >= b )
    return remainder(a-b, b);
  return a; 
}
