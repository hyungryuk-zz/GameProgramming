/*
������ : RSA����
�а� : ��ǻ���������а�
�й� : 12101431
�̸� : ������
*/

#include <iostream>
#include <time.h>

using namespace std;

int SquareAndMultiply(int a, int pow, int mod) {					//SquareAndMultiply Algorithm.
	long long int res = 1;
	long long int s = a;
	while (pow > 0) {
		if (pow % 2 == 1)res = res*s;								//������ Ȧ���ϰ�� base�� result���� �����ش�  ���⼭ result���� ���ݱ����� ���� ����̴�
		s = s*s;																	//������ �����Ѵ�.
		pow = pow / 2;
		s %= mod;
		res %= mod;
	}
	return res;
}
bool milller(int input) {						//�Ҽ��Ǻ� ����

	int s = input - 1;
	int k = 0;
	while ((s & 1) == 0) {							//(n-1)=(2^k)*q���� k�� ���ϱ� ���� shift������ �̿��Ͽ���.
		k++;
		s = s >> 1;

	}
	int q = s;
	if (!(k > 0))return false;
	for (int i = 0; i < 6; i++) {															//���ǳ�Ʈ�� �ִ� �˰��� �״�� �����Ͽ��� ��, testȽ���� 20���� �� ��� ������ �ſ�����ɷ� 6���� �����Ͽ���.
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
int gcd(int input1, int input2) {								//Ȯ�� ��Ŭ����� �˰����� �̿��Ͽ� GCD�� ���Ѵ�.
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
int Extended_Euclid(int r1, int r2)								//AES���߶� ����ߴ� Ȯ�� ��Ŭ�����˰����� �̿��� ���� ���ϴ� �Լ��� �����Դ�
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
	srand((unsigned)time(NULL));													//random�� seed����.
	int p, q, e;
	p = rand() % 65535 + 1; q = rand() % 65535 + 1;				//p�� q�� 15bit�̹Ƿ� 2^15�� 65535���� �����ʰ� �����Ѵ�.
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