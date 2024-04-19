#include "Email.h"
#include <iostream>


Email::Email(){
	Email::userName = "Default";
	Email::details.to = "Class";
	Email::details.from = "Zara";
	Email::details.subject = "Announcement";
	Email::details.body = "Welcome to BTN";

}

//modify it to display the email
std::string Email::display()
{	
	return ("From: " + details.from + "\n" +
		"To: " + details.to + "\n" +
		"Subject: " + details.subject + "\n" +
		"Body: " + details.body + "\n" +
		"****************************************************\n");
}

const std::string Email::getTo() const {
	return userName;
}

Email::Email(const char* username, EmailDetails Details) 
	: userName(username), details(Details) {}