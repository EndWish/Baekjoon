# Baekjoon
This is a auto push repository for Baekjoon Online Judge created with [BaekjoonHub](https://github.com/BaekjoonHub/BaekjoonHub).

문제풀이 접근법:
조합문제(16565 N포커) : nCk = n-1Ck + n-1Ck-1, 포함 배제의 원리(i세트를 포함하는 하는 경우의 수를 더하게 되면 k(k>=i)세트를 포함하는 경우는 kCi번 더해지게 된다.)

오일러 피 함수(11689 GCD(n,k) = 1) : 1~n까지 n과 서로소인 수의 개수를 반환한다.
                                    phi(p^k) = p^(k-1)*(p-1){p는 소수} 과 phi(mn) = phi(m) * phi(n) {m,n은 소수} 의 성질을 이용해 풀면된다.
                                예) phi(40) = phi(2^3 * 5) = phi(2^3) * phi(5) = 4 * 4 = 16

페르마의 소정리(13977 이항 계수와 쿼리) : 
      nCk = n!/((n-k!)k!) = n! * ((n-k!)k!)^-1
      n! * ((n-k!)k!)^-1 (mod p) = n! * ((n-k!)k!)^(p-2) (mod p)
        왜냐하면 a^p = a (mod p) (p는 소수, a는 p의 배수가 아닐때) : 페르마의 소정리
        위 식에서 a^2으로 양변을 나누면 a^(p-2) = a^-1 (mod p) 식을 유도할 수 있다.
      https://nicotina04.tistory.com/10 , https://seastar105.tistory.com/65 참고

조합+나머지연산 :(1086 박성원) :
      비트마스크를 이용하여 조합을 나타내고, 나머지연산의 결과 값을 index로 하여 dp로 저장하여 푸는 문제
      또한 나머지연산을 직접 구현하는 문제, 123 % 4 = (( ((10 % 4) * 10 + 2) % 4) * 10 + 3) % 4 와 같이 바꾸면 아무리큰 숫자여도 O(L)시간안에 구할수 있다.

최소 공통 조상 : DFS로 깊이를 저장하고 두 노드를 같은 깊이가 되도록 부모를 거슬러 올라온후 두 노드가 같아질 때 까지 부모로 거슬러 올라오면 된다.
