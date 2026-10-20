// ConstMethods : une methode const ne peut pas modifier son objet.

#include <iostream>
#include <vector>

class Truc
{
	int member_;

public:
	Truc(int value) { member_ = value; }

	void setMember(int value) { member_ = value; }
	int getMember() const { return member_; }

};

class Machin
{
	Truc truc_;

public:
	Machin(int value) : truc_(value){}

	void SetBValue(int value)
	{
		truc_.setMember(value);
	}

};


int main()
{
	std::vector<Truc> trucs;

	Machin m(10);
	m.SetBValue(10);

	//for (const auto& t : trucs)
	//{
	//	t.getMember();
	//	t.setMember(3);
	//}


}
