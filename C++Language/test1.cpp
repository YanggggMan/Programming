#include <iostream>

static int cnt = 1;

class emm
{
public:
	emm(int _xx):xx(_xx){}
	~emm() {};

	int xx;
private:

};

class em
{
public:
	em(int a) {
		aa = a;
		hh = new emm(2333);
		std::cout << "hehe" << std::endl;
		std::cout << " this:" << this << std::endl;
	}

	em(em&& a):hh(a.hh),aa(a.aa) {
		std::cout << "move    " << this << std::endl;
	}

	~em() {
		cnt++;
		std::cout << "wtf" << "cnt:  " << cnt << std::endl;

		delete hh;
		hh = nullptr;
	}

	void show() const{
		std::cout << "*****    " << hh->xx << std::endl;
	}

	emm* hh;
	int aa;

private:
	
// 	em(const em&) {
// 		std::cout << "const cooooooopy" << std::endl;
// 	}
};

int foo(em& a) {
	auto aa = &a;
	std::cout << "foooooo: " << aa << std::endl;

	aa->show();

	return 0;
	//return aa;
}

int	main() {
	
	em tmp(std::move(em(666)));
	//std::cout << tmp.aa << std::endl;
	//auto ret = foo());
	//auto ret = foo(em(std::move(em(666))));
	/*std::cout << ret->aa << std::endl;
	std::cout << "ret:" << ret << std::endl;*/
	//em(777);
	//em(888);
	//std::cout << ret->aa << std::endl;

	return 0;
}