// OOSocketprogramming.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//Note the username is being sent to this server from the url
// The client is the the browser
// url : http://127.0.0.1:8080/:username

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "socketServer.h"
#include "Email.h"


std::string getUsernameFromHTTP(const std::string& httpRequest) {
    std::istringstream stream(httpRequest);
    std::string method;
    std::string url;
    stream >> method >> url;

    size_t start = url.find_last_of('/');
    return url.substr(start + 1);
}

int main() {

    // Load data
    std::vector<Email> emails;
    emails.push_back(Email("JobsS", EmailDetails("Bill", "Jobs", "Finance Presentation", "Looking forward to our meeting on finance")));
    emails.push_back(Email("BillG", EmailDetails("Warren", "Bill", "Dinner", "It was lovely meeting you over dinner meeting")));
    emails.push_back(Email("WarrenB", EmailDetails("Elon", "Warren", "SpaceX", "Hows new SpaceX project going?")));
    emails.push_back(Email("JobsS", EmailDetails("Elon", "Jobs", "Twitter", "How is it going at Twitter?")));

    Server_TCP server("127.0.0.1", 8080);
    server.create_socket();
    server.bind_socket();
    server.listen_for_connections();
    server.accept_connection();
 

    //receives the HTTP request from the client
    std::string httpRequest;
    server.receive_message(httpRequest);

    //parse username from HTTP request
    std::string recUsername = getUsernameFromHTTP(httpRequest);
    std::cout << "Username received from URL --> " << recUsername << '\n';

    //search the emails from user inbox
    std::vector<Email> results;
    for (auto& email : emails) {
        if (strcmp(email.getUserName(), recUsername.c_str()) == 0) {
            results.push_back(email);
        }
    }

    if (results.empty()) {
        std::string notFoundMessage = "<html><head><title>404 Not Found</title></head><body><h1>User Not Found</h1><p>The requested user inbox could not be found on the server. Please check the username and try again.</p></body></html>";
        std::string httpResponse = "HTTP/1.1 404 Not Found\r\n";
        httpResponse += "Content-Type: text/html; charset=UTF-8\r\n";
        httpResponse += "Content-Length: " + std::to_string(notFoundMessage.length()) + "\r\n";
        httpResponse += "\r\n";
        httpResponse += notFoundMessage;

        server.send_message(httpResponse);
        std::cout << "Sent 404 Not Found to the client!\n";
    }
    else {
        //sends the emails to the client back as HTML
        std::string res = emailToHTML(results);
        std::string response = generateResponse(res);
        server.send_message(response);
        std::cout << "Sent User Inbox to the client!\n";
    }

    return 0;
}

