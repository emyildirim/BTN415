#include "Email.h"
#include <iostream>
#include <sstream>
#pragma warning(disable : 4996)

//
// EmailDetails
//

EmailDetails::EmailDetails() {	
	this->from = nullptr;
	this->to = nullptr;
	this->subject = nullptr;
	this->body = nullptr;
}

EmailDetails::EmailDetails(const char* from, const char* to, const char* subject, const char* body) {
	//initialize and get memory
	this->from = new char[std::strlen(from) + 1];
	this->to = new char[std::strlen(to) + 1];
	this->subject = new char[std::strlen(subject) + 1];
	this->body = new char[std::strlen(body) + 1];

	//deep copy
	std::strcpy(this->from, from);
	std::strcpy(this->to, to);
	std::strcpy(this->subject, subject);
	std::strcpy(this->body, body);
}

EmailDetails::~EmailDetails() {
	delete[] this->from;
	delete[] this->to;
	delete[] this->subject;
	delete[] this->body;
}

EmailDetails::EmailDetails(const EmailDetails& other) {
	//initialize and get memory
	this->from = new char[std::strlen(other.from) + 1];
	this->to = new char[std::strlen(other.to) + 1];
	this->subject = new char[std::strlen(other.subject) + 1];
	this->body = new char[std::strlen(other.body) + 1];

	//deep copy
	std::strcpy(this->from, other.from);
	std::strcpy(this->to, other.to);
	std::strcpy(this->subject, other.subject);
	std::strcpy(this->body, other.body);
}

EmailDetails& EmailDetails::operator=(const EmailDetails& other) {
	
	if (this != &other) {
		//deallocate
		delete[] from;
		delete[] to;
		delete[] subject;
		delete[] body;

		//initialize and get memory
		this->from = new char[std::strlen(other.from) + 1];
		this->to = new char[std::strlen(other.to) + 1];
		this->subject = new char[std::strlen(other.subject) + 1];
		this->body = new char[std::strlen(other.body) + 1];

		//deep copy
		std::strcpy(this->from, other.from);
		std::strcpy(this->to, other.to);
		std::strcpy(this->subject, other.subject);
		std::strcpy(this->body, other.body);
	}
	return *this;
}


/// 
/// Email
/// 
Email::Email() {
	this->userName = new char[std::strlen("Default") + 1];
	std::strcpy(this->userName, "Default");

	this->details = EmailDetails("Class", "Zara", "Announcement", "Welcome to BTN");
}

Email::~Email() {
	delete[] this->userName;
}

void Email::display() const {	
	std::cout << "From: " << details.from << "\n" 
		<< "To: " << details.to << "\n"
		<< "Subject: " << details.subject << "\n"
		<< "Body: " << details.body << "\n" 
		<< "****************************************************\n";
}

Email::Email(const char* userName, struct EmailDetails details) {
	this->userName = new char[std::strlen(userName) + 1];
	std::strcpy(this->userName, userName);

	this->details = EmailDetails(details.from, details.to, details.subject, details.body);
}

char* Email::getUserName() const {
	return this->userName;
}

std::string Email::emailDetailsToStr() const {
	std::stringstream ss{};
	ss << "<tr>\n"
		<< "<td>" << this->details.from << "</td>\n"
		<< "<td>" << this->details.to << "</td>\n"
		<< "<td>" << this->details.subject << "</td>\n"
		<< "<td>" << this->details.body << "</td>\n"
		<< "</tr>\n";
	return ss.str();
}

EmailDetails& Email::getEmailDetails() {
	return this->details;
}

Email::Email(const Email& other) {
	//initialize and get memory
	this->userName = new char[std::strlen(other.userName) + 1];

	//deep copying
	std::strcpy(this->userName, other.userName);
	this->details = other.details;
}

Email& Email::operator=(const Email& other) {
	
	if (this != &other) {
		//deallocate
		delete[] this->userName;

		//initialize and get memory
		this->userName = new char[std::strlen(other.getUserName()) + 1];

		//deep copy
		std::strcpy(this->userName, other.userName);
		this->details = other.details;
	}
	return *this;
}

std::string emailToHTML(std::vector<Email>& emails) {
	std::stringstream html;
	html << "<!DOCTYPE html>\n";
	html << "<html>\n<head>\n<title>Emails</title>\n";
	html << "<style>\n";
	html << "table { width: 100%; border-collapse: collapse; }\n";
	html << "th, td { border: 1px solid #dddddd; text-align: left; padding: 8px; }\n";
	html << "tr:nth-child(even) { background-color: #f2f2f2; }\n";
	html << "</style>\n";
	html << "</head>\n<body>\n";
	html << "<table>\n";
	html << "<tr><th>From</th><th>To</th><th>Subject</th><th>Body</th></tr>\n";

	for (const Email& email : emails) {
		html << email.emailDetailsToStr();
	}

	html << "</table>\n";
	html << "</body>\n</html>";

	return html.str();
}