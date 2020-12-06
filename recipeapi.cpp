#include "recipeapi.h"

#include "cpprest/json.h"

#include <iostream>

namespace {
class TestRequest {
public:
    static TestRequest FromJSON(const web::json::object& object)
    {
        TestRequest res;

        web::json::value cs = object.at(U("test"));

        for (auto iter = cs.as_array().begin(); iter != cs.as_array().end(); ++iter)
        {
            if (!iter->is_null())
            {
                int num = iter->as_integer();
                res.numbers.push_back(num);
            }
        }

        return res;
    }

    web::json::value AsJSON() const
    {
        web::json::value res = web::json::value::object();
        web::json::value j_numbers = web::json::value::array(numbers.size());


        for (size_t i = 0; i < numbers.size(); ++i)
        {
            j_numbers[i] = numbers[i];
        }

        res[U("test")] = j_numbers;
        return res;
    }

    std::vector<int> numbers;
};

}


using web::http::methods;
using web::http::status_codes;
using web::http::uri;


RecipeApi::RecipeApi(utility::string_t url) : listener_(url)
{
    listener_.support(methods::GET, std::bind(&RecipeApi::handle_get, this, std::placeholders::_1));
    listener_.support(methods::PUT, std::bind(&RecipeApi::handle_put, this, std::placeholders::_1));
    listener_.support(methods::POST, std::bind(&RecipeApi::handle_post, this, std::placeholders::_1));
    listener_.support(methods::DEL, std::bind(&RecipeApi::handle_delete, this, std::placeholders::_1));
}

void RecipeApi::handle_get(web::http::http_request message)
{
    ucout << message.to_string() << std::endl;

       auto paths = uri::split_path(uri::decode(message.relative_uri().path()));
       if (paths.empty())
       {
           TestRequest empty;
           message.reply(status_codes::OK, empty.AsJSON());
           return;
       }

       const utility::string_t id = paths[0];

       if (id != U("0"))
       {
           message.reply(status_codes::NotFound);
       }
       else
       {
           TestRequest test;
           test.numbers.push_back(1);
           test.numbers.push_back(2);
           test.numbers.push_back(3);
           message.reply(status_codes::OK, test.AsJSON());
       }
}

void RecipeApi::handle_put(web::http::http_request message)
{

}

void RecipeApi::handle_post(web::http::http_request message)
{

}

void RecipeApi::handle_delete(web::http::http_request message)
{

}
