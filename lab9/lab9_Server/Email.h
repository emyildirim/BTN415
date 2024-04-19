#pragma once
#include <string>

struct EmailDetails
{
	std::string from;
	std::string to;
	std::string subject;
	std::string body;

	EmailDetails() {}
	EmailDetails(std::string from, std::string to, std::string sub, std::string body)
		: from(from), to(to), subject(sub), body(body) {}
};


class Email
{
public:
	Email();
	std::string display();
	const std::string getTo() const;

	//custom constructors
	Email(const char* username, EmailDetails Details);
private:
	std::string userName;
	struct EmailDetails details;

};