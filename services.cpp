//
// Copyright Metaspex - 2022
// mailto:admin@metaspex.com
//

// To test (update 8080 port number to whatever was configured in the web server):
// 
// curl http://localhost:8080/service_name -d '{..JSON payload...}'
// ...JSON response...

#include "hx2a/server.hpp"

#include "hx2a/squeaker/ontology.hpp"
#include "hx2a/squeaker/payloads.hpp"
#include "hx2a/basic_service.hpp"

using namespace hx2a;

namespace squeaker {

  // Service updating a post.
  class post_update: public basic_service<"post_update", post_update_payload>
  {
    hx2a::reply_p call(http_request&, const session_info*, const organization_p&, const hx2a::user_p&, const post_update_payload_r& q) override {
      // Logical name mapped in the configuration file to a database among the ones supported (Couchbase, MongoDB, CouchDB).
      db::connector c("hx2a");

      // Finding the post from its document identifier.
      post_p p = post::get(q->id);

      // We should take care of the hashtags one day.
      if (p != nullptr) p->set_text(q->text.get());

      // No commit, everything automatic! Detection of what was updated, and automatic save.
      return {};
    }
  } _post_update;

} // End namespace squeaker.
