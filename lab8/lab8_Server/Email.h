#pragma once
#include <string>
#pragma warning(disable : 4996)

struct EmailDetails
{
	char* from;
	char* to;
	char* subject;
	char* body;
	EmailDetails();
	EmailDetails(const char* from, const char* to, const char* subject, const char* body);
	~EmailDetails();
	//copy constructor and assignment operator
	EmailDetails& operator=(const EmailDetails& other);
	EmailDetails(const EmailDetails& other);
};

class Email
{
private:
	char* userName;
	struct EmailDetails details;
public:
	Email();
	Email(const char* userName, struct EmailDetails details);
	~Email();
	void display() const;
	char* getUserName() const;
	std::string emailDetailsToStr() const;
	EmailDetails& getEmailDetails();

	//copy constructor and assignment operator
	Email(const Email& other);
	Email& operator=(const Email& other);
};
