#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include<string>

using std::string;

class InvalidAge {
	unsigned int age;
public:
	InvalidAge(unsigned int age) {
		this->age = age;
	};
	unsigned int getAge() const {
		return age;
	};
};

class InvalidPhoneNumber {

};


class InvalidTransportationType {
};

class InvalidAccomodationType {
	string type;
public:
	InvalidAccomodationType(string type) {
		this->type = type;
	};
	string getType() const {
		return type;
	};
};

class TripAlreadyUsed {
};

class EmptyContainer {
};

class InvalidLogin {

};

class InvalidEmail {

};

class InvalidName {

};

class InvalidZipCode {

};

class InvalidCountry {

};

class InvalidDate  {

};

class InvalidNumPeople {

};

class InvalidDay {

};

class InvalidMonth {

};

class InvalidYear {

};

class InvalidDiscount {

};

class RepeatedTrip {

};


#endif
