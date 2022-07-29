# Baekjoon
This is a auto push repository for Baekjoon Online Judge created with [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub).

문제풀이 접근법:
조합문제(16565 N포커) : nCk = n-1Ck + n-1Ck-1, 포함 배제의 원리(i세트를 포함하는 하는 경우의 수를 더하게 되면 k(k>=i)세트를 포함하는 경우는 kCi번 더해지게 된다.)

오일러 피 함수(11689 GCD(n,k) = 1) : 1~n까지 n과 서로소인 수의 개수를 반환한다.
                                    phi(p^k) = p^(k-1)*(p-1){p는 소수} 과 phi(mn) = phi(m) * phi(n) {m,n은 소수} 의 성질을 이용해 풀면된다.
                                예) phi(40) = phi(2^3 * 5) = phi(2^3) * phi(5) = 4 * 4 = 16
