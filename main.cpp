#include "cpprest/uri.h"

#include <iostream>

#include "recipeapi.h"

using namespace web;
using namespace utility;

std::unique_ptr<RecipeApi> gRecipeApi;

void on_initialize(const string_t& address)
{
    // Build our listener's URI from the configured address and the hard-coded path "blackjack/dealer"

    uri_builder uri(address);
    uri.append_path(U("blackjack/dealer"));

    auto addr = uri.to_uri().to_string();
    gRecipeApi = std::unique_ptr<RecipeApi>(new RecipeApi(addr));
    gRecipeApi->open().wait();

    ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

    return;
}

void on_shutdown()
{
    gRecipeApi->close().wait();
    return;
}

//
// To start the server, run the below command with admin privileges:
// BlackJack_Server.exe <port>
// If port is not specified, will listen on 34568
//
#ifdef _WIN32
int wmain(int argc, wchar_t* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    utility::string_t port = U("34568");
    if (argc == 2)
    {
        port = argv[1];
    }

    utility::string_t address = U("http://localhost:");
    address.append(port);

    on_initialize(address);
    std::cout << "Press ENTER to exit." << std::endl;

    std::string line;
    std::getline(std::cin, line);

    on_shutdown();
    return 0;
}
