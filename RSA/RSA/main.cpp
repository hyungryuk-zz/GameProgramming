/*
과제명 : RSA구현
학과 : 컴퓨터정보공학과
학번 : 12101431
이름 : 김형륙
*/

#include <iostream>
#include <time.h>

using namespace std;

int SquareAndMultiply(int a, int pow, int mod) {					//SquareAndMultiply Algorithm.
	long long int res = 1;
	long long int s = a;
	while (pow > 0) {
		if (pow % 2 == 1)res = res*s;								//지수가 홀수일경우 base와 result값을 곱해준다  여기서 result값은 지금까지의 연산 결과이다
		s = s*s;																	//지수를 제곱한다.
		pow = pow / 2;
		s %= mod;
		res %= mod;
	}
	return res;
}
bool milller(int input) {						//소수판별 연산

	int s = input - 1;
	int k = 0;
	while ((s & 1) == 0) {							//(n-1)=(2^k)*q에서 k를 구하기 위해 shift연산을 이용하였다.
		k++;
		s = s >> 1;

	}
	int q = s;
	if (!(k > 0))return false;
	for (int i = 0; i < 6; i++) {															//강의노트에 있는 알고리즘 그대로 적용하였다 단, test횟수를 20으로 할 경우 연산이 매우오려걸려 6으로 고정하였다.
		int a = 1 + rand() % (input - 2);
		int tmp = 1;
		if (SquareAndMultiply(a, q, input) == 1)continue;
		for (int j = 0; j < k; j++) {
			if (SquareAndMultiply(a, tmp*q, input) == input - 1) {
				break;
			}
			tmp *= 2;
		}
		return false;
	}
	return true;
}
int gcd(int input1, int input2) {								//확장 유클리디안 알고리즘을 이용하여 GCD를 구한다.
	if (input2 < input1) {
		int tmp = input2;
		input2 = input1;
		input1 = tmp;
	}
	while (input1 != 0) {
		int q = input2 / input1;
		int remain = input2 % input1;
		input2 = input1;
		input1 = remain;
	}
	return input2;
}
int Extended_Euclid(int r1, int r2)								//AES개발때 사용했던 확장 유클리디언알고리즘을 이용한 역원 구하는 함수를 가져왔다
{
	int a1 = 1, a2 = 0, a3 = r1, b1 = 0, b2 = 1, b3 = r2, t1 = 0, t2 = 0, t3 = 0, q = 0;

	while (true) {
		if (b3 == 0) {
			if (a3 < 0) {
				return a3%r1;
			}
			return a3;
		}
		if (b3 == 1) {
			if (b2 < 0) {
				return r1 + b2;
			}
			return b2;
		}
		q = a3 / b3;
		t1 = a1 - (q*b1);
		t2 = a2 - (q*b2);
		t3 = a3 - (q*b3);
		a1 = b1; a2 = b2; a3 = b3;
		b1 = t1; b2 = t2; b3 = t3;
	}
}

int main() {
	srand((unsigned)time(NULL));													//random값 seed설정.
	int p, q, e;
	p = rand() % 65535 + 1; q = rand() % 65535 + 1;				//p와 q는 15bit이므로 2^15인 65535값을 넘지않게 설정한다.
	while (!milller(p)) {
		p = rand() % 65535 + 1;
	}
	cout << "p = " << p << endl;
	while (!milller(q) || p == q) {
		q = rand() % 65535 + 1;
	}

	cout << "q = " << q << endl;
	int n = p*q;
	cout << "N = " << n << endl;
	int euler = (p - 1)*(q - 1);

	cout << "phi = " << euler << endl;
	e = 257;
	cout << "e = " << e << endl;
	int d = Extended_Euclid(euler, e);
	cout << "d = " << d << endl;
	cout << "Message Input : ";
	int input;
	cin >> input;
	cout << "Message : " << input << endl;
	cout << "**Encryption" << endl;
	int  enc = SquareAndMultiply(input, e, n);
	cout << "cipher = " << enc << endl;
	cout << "**Decryption" << endl;
	int dec = SquareAndMultiply(enc, d, n);
	cout << "decrypted cipher : " << dec << endl;

	return 0;
}