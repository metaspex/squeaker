//
// Copyright Metaspex - 2022
// mailto:admin@metaspex.com
//

#ifndef HX2A_SQUEAKER_PAYLOADS_HPP
#define HX2A_SQUEAKER_PAYLOADS_HPP

#include "hx2a/element.hpp"
#include "hx2a/slot.hpp"

namespace squeaker {
  
  class post_update_payload;
  using post_update_payload_p = ptr<post_update_payload>;
  using post_update_payload_r = rfr<post_update_payload>;
  
  class post_update_payload: public element<>
  {
  public:
    HX2A_ELEMENT(post_update_payload, "post_update_pld", element);
  
    post_update_payload(reserved_t):
      element(reserved),
      id(*this),
      text(*this)
    {
    }

    slot<doc_id, "id"> id;
    slot<string, "source"> text;
  };

} // End namespace squeaker.

#endif
