#ifndef RECIPEAPI_H
#define RECIPEAPI_H

#include "cpprest/asyncrt_utils.h"
#include "cpprest/http_listener.h"

class RecipeApi
{
public:
    RecipeApi() {}
    RecipeApi(utility::string_t url);

    pplx::task<void> open() { return listener_.open(); }
    pplx::task<void> close() { return listener_.close(); }

private:
    void handle_get(web::http::http_request message);
    void handle_put(web::http::http_request message);
    void handle_post(web::http::http_request message);
    void handle_delete(web::http::http_request message);

    web::http::experimental::listener::http_listener listener_;
};

#endif // RECIPEAPI_H
