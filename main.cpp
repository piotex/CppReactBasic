#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <restbed>

using namespace std;
using namespace restbed;

int Port = 8080;

void get_method_handler( const shared_ptr< Session > session )
{
    //perform awesome solutions logic...
    // const auto request = session->get_request();
    string response_body;
    std::string line;
    std::stringstream myStream;
    std::ifstream myFile("player.json");
    if (myFile.is_open())
    {
        while ( getline(myFile, line))
        {
            myStream << line << "\r\n";
        }
        myFile.close();
    }

    response_body = myStream.str();
    session->close( OK, response_body, { { "Content-Length", ::to_string(response_body.length()) }, { "Content-Type", "app"}});
}
void service_ready_handler( Service& )
{
    std::cout <<  "The service port " << Port << " /player is up and running." << std::endl;
}
int main( const int, const char** )
{
    auto resource = make_shared< Resource >( );
    resource->set_path( "/player" );
    resource->set_method_handler( "GET", get_method_handler );
    auto settings = make_shared< Settings >( );
    settings->set_port( Port );
    settings->set_default_header( "Connection", "close" );
    settings->set_default_header("Access-Control-Allow-Origin","*");   //cors errors
    // Service service;
    auto service = make_shared< Service >( );
    service->publish( resource );
    service->set_ready_handler( service_ready_handler );
    service->start( settings );
    return EXIT_SUCCESS;
}