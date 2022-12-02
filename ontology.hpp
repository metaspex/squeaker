//
// Copyright Metaspex - 2022
// mailto:admin@metaspex.com
//

#ifndef HX2A_SQUEAKER_ONTOLOGY_HPP
#define HX2A_SQUEAKER_ONTOLOGY_HPP

#include "hx2a/element.hpp"
#include "hx2a/root.hpp"
#include "hx2a/slot.hpp"
#include "hx2a/own.hpp"
#include "hx2a/link.hpp"
#include "hx2a/link_list.hpp"

using namespace hx2a;

namespace squeaker {

  class user;
  using user_p = ptr<user>;
  using user_r = rfr<user>;
  
  class orange_check;
  using orange_check_p = ptr<orange_check>;
  using orange_check_r = rfr<orange_check>;

  class post;
  using post_p = ptr<post>;
  using post_r = rfr<post>;

  class follow;
  using follow_p = ptr<follow>;
  using follow_r = rfr<follow>;

  class hashtag;
  using hashtag_p = ptr<hashtag>;
  using hashtag_r = rfr<hashtag>;
  
  class reply;
  using reply_p = ptr<reply>;
  using reply_r = rfr<reply>;

  class repost;
  using repost_p = ptr<repost>;
  using repost_r = rfr<repost>;
  
  class post_like;
  using post_like_p = ptr<post_like>;
  using post_like_r = rfr<post_like>;
  
  class reply_like;
  using reply_like_p = ptr<reply_like>;
  using reply_like_r = rfr<reply_like>;

  class repost_like;
  using repost_like_p = ptr<repost_like>;
  using repost_like_r = rfr<repost_like>;

  class user: public root<>
  {
    HX2A_ROOT(user, "user", 1, root);
  public:

    using birth_type = unsigned int;
    
    // Reserved constructor.
    user(reserved_t, const doc_id& id):
      root(reserved, id),
      _name(*this),
      _bio(*this),
      _location(*this),
      _website(*this),
      _birth(*this),
      _orange_check(*this),
      _follow_list(*this)
    {
    }

    user(
	 std::string_view name,
	 std::string_view bio,
	 std::string_view location,
	 std::string_view website,
	 birth_type birth
    ):
      root(standard),
      _name(*this, name),
      _bio(*this, bio),
      _location(*this, location),
      _website(*this, website),
      _birth(*this, birth),
      _orange_check(*this), // Nothing yet, to be acquired subsequently.
      _follow_list(*this)
    {
    }

    string get_name() const { return _name; }
    void set_name(std::string_view name){ _name = string{name}; }

    string get_bio() const { return _bio; }
    void set_bio(std::string_view bio){ _bio = string{bio}; }

    string get_location() const { return _location; }
    void set_location(std::string_view location){ _location = string{location}; }

    string get_website() const { return _website; }
    void set_website(std::string_view website){ _website = string{website}; }

    birth_type get_birth() const { return _birth; }
    void set_birth(birth_type birth){ _birth = birth; }

    // Null means no range check.
    orange_check_p get_orange_check() const { return _orange_check; }
    void set_orange_check(const orange_check_p& bc){ _orange_check = bc; }

    using follow_list_type = own_list<follow, "f">;
    using follow_list_const_iterator = follow_list_type::const_iterator;
    using follow_list_const_reverse_iterator = follow_list_type::const_reverse_iterator;
    
    void add_follow(const follow_r& ht){ _follow_list.push_front(ht); }
    void remove_follow(const follow_r& ht){ _follow_list.remove(ht); }
    bool has_follow(const follow_r& ht){ return _follow_list.find(ht); }
      
  private:

    slot<string, "n"> _name;
    slot<string, "b"> _bio;
    slot<string, "l"> _location;
    slot<string, "w"> _website;
    slot<birth_type, "B"> _birth;
    own<orange_check, "c"> _orange_check;
    follow_list_type _follow_list;
  };
  
  class orange_check: public element<>
  {
    HX2A_ELEMENT(orange_check, "orange_check", element);
  public:

    // Reserved constructor.
    orange_check(reserved_t):
      element(reserved),
      _timestamp(*this)
    {
    }

    orange_check():
      element(standard),
      _timestamp(*this, time())
    {
    }

    time_t get_timestamp() const { return _timestamp; }
    void set_timestamp(time_t timestamp){ _timestamp = timestamp; }
    
  private:

    slot<time_t, "t"> _timestamp;
  };

  class post: public root<>
  {
    HX2A_ROOT(post, "post", 1, root);
  public:

    // Reserved constructor.
    post(reserved_t, const doc_id& id):
      root(reserved, id),
      _text(*this),
      _hashtags(*this)
    {
    }

    post(std::string_view text):
      root(standard),
      _text(*this, text),
      _hashtags(*this)
    {
    }

    string get_text() const { return _text; }
    void set_text(std::string_view text){ _text = string{text}; }
    
    using hashtags_type = link_list<hashtag, "h">;
    using hashtags_const_iterator = hashtags_type::const_iterator;
    using hashtags_const_reverse_iterator = hashtags_type::const_reverse_iterator;

    hashtags_const_iterator hashtags_cbegin() const { return _hashtags.cbegin(); }
    hashtags_const_iterator hashtags_cend() const { return _hashtags.cend(); }
    
    hashtags_const_reverse_iterator hashtags_crbegin() const { return _hashtags.crbegin(); }
    hashtags_const_reverse_iterator hashtags_crend() const { return _hashtags.crend(); }

    void add_hashtag(const hashtag_r& ht){ _hashtags.push_front(ht); }
    void remove_hashtag(const hashtag_r& ht){ _hashtags.remove(ht); }
    bool has_hashtag(const hashtag_r& ht){ return _hashtags.find(ht); }
      
  private:

    slot<string, "t"> _text;
    hashtags_type _hashtags;
  };
  
  class hashtag: public root<>
  {
    HX2A_ROOT(hashtag, "hashtag", 1, root);
  public:

    // Reserved constructor.
    hashtag(reserved_t, const doc_id& id):
      root(reserved, id),
      _text(*this)
    {
    }

    hashtag(std::string_view text):
      root(standard),
      _text(*this, text)
    {
    }

    string get_text() const { return _text; }
    void set_text(std::string_view text){ _text = string{text}; }
    
  private:

    slot<string, "t"> _text;
  };
  
  class follow: public element<>
  {
    HX2A_ELEMENT(follow, "follow", element);
  public:

    // Reserved constructor.
    follow(reserved_t):
      element(reserved),
      _followed(*this)
    {
    }

    follow(const user_r& u):
      element(standard),
      _followed(*this, &u)
    {
    }

    user_r get_followed() const { return *_followed; }
    // No change allowed.
    
  private:

    // Strong link, this will be removed in the target is removed.
    link<user, "f"> _followed;
  };
  
  class repost: public root<>
  {
    HX2A_ROOT(repost, "repost", 1, root);
  public:

    // Reserved constructor.
    repost(reserved_t, const doc_id& id):
      root(reserved, id),
      _user(*this),
      _post(*this)
    {
    }

    repost(const user_r& u, const post_r& p):
      root(standard),
      _user(*this, &u),
      _post(*this, &p)
    {
    }

    user_r get_user() const { return *_user; }
    post_r get_post() const { return *_post; }
    // No changes allowed.
    
  private:

    // Strong link, this will be removed in the target is removed.
    link<user, "u"> _user;
    link<post, "p"> _post;
  };
  
  class reply: public root<>
  {
    HX2A_ROOT(reply, "reply", 1, root);
  public:

    // Reserved constructor.
    reply(reserved_t, const doc_id& id):
      root(reserved, id),
      _user(*this),
      _post(*this),
      _reply(*this),
      _hashtags(*this)
    {
    }

    // It's either a reply on a post or a reply on a reply.
    // Either the link to the post or the link to the reply is empty.
    
    reply(const user_r& u, const post_r& p):
      root(standard),
      _user(*this, &u),
      _post(*this, &p),
      _reply(*this),
      _hashtags(*this)
    {
    }

    reply(const user_r& u, const reply_r& r):
      root(standard),
      _user(*this, &u),
      _post(*this),
      _reply(*this, &r),
      _hashtags(*this)
    {
    }

    user_r get_user() const { return *_user; }
    post_p get_post() const { return _post; }
    reply_p get_reply() const { return _reply; }
    // No changes allowed.
    
    using hashtags_type = link_list<hashtag, "h">;
    using hashtags_const_iterator = hashtags_type::const_iterator;
    using hashtags_const_reverse_iterator = hashtags_type::const_reverse_iterator;

    hashtags_const_iterator hashtags_cbegin() const { return _hashtags.cbegin(); }
    hashtags_const_iterator hashtags_cend() const { return _hashtags.cend(); }
    
    hashtags_const_reverse_iterator hashtags_crbegin() const { return _hashtags.crbegin(); }
    hashtags_const_reverse_iterator hashtags_crend() const { return _hashtags.crend(); }

    void add_hashtag(const hashtag_r& ht){ _hashtags.push_front(ht); }
    void remove_hashtag(const hashtag_r& ht){ _hashtags.remove(ht); }
    bool has_hashtag(const hashtag_r& ht){ return _hashtags.find(ht); }
      
  private:

    // Strong link, this will be removed in the target is removed.
    link<user, "u"> _user;
    link<post, "p"> _post;
    link<reply, "r"> _reply;
    hashtags_type _hashtags;
  };
  
  class post_like: public root<>
  {
    HX2A_ROOT(post_like, "post_like", 1, root);
  public:

    // Reserved constructor.
    post_like(reserved_t, const doc_id& id):
      root(reserved, id),
      _user(*this),
      _post(*this)
    {
    }

    post_like(const user_r& u, const post_r& p):
      root(standard),
      _user(*this, &u),
      _post(*this, &p)
    {
    }

    user_r get_user() const { return *_user; }
    post_r get_post() const { return *_post; }
    // No changes allowed.
    
  private:

    // Strong link, this will be removed in the target is removed.
    link<user, "u"> _user;
    link<post, "p"> _post;
  };
  
  class repost_like: public root<>
  {
    HX2A_ROOT(repost_like, "repost_like", 1, root);
  public:

    // Reserved constructor.
    repost_like(reserved_t, const doc_id& id):
      root(reserved, id),
      _user(*this),
      _repost(*this)
    {
    }

    repost_like(const user_r& u, const repost_r& p):
      root(standard),
      _user(*this, &u),
      _repost(*this, &p)
    {
    }

    user_r get_user() const { return *_user; }
    repost_r get_repost() const { return *_repost; }
    // No changes allowed.
    
  private:

    // Strong link, this will be removed in the target is removed.
    link<user, "u"> _user;
    link<repost, "p"> _repost;
  };
  
  class reply_like: public root<>
  {
    HX2A_ROOT(reply_like, "reply_like", 1, root);
  public:

    // Reserved constructor.
    reply_like(reserved_t, const doc_id& id):
      root(reserved, id),
      _user(*this),
      _reply(*this)
    {
    }

    reply_like(const user_r& u, const reply_r& p):
      root(standard),
      _user(*this, &u),
      _reply(*this, &p)
    {
    }

    user_r get_user() const { return *_user; }
    reply_r get_reply() const { return *_reply; }
    // No changes allowed.
    
  private:

    // Strong link, this will be removed in the target is removed.
    link<user, "u"> _user;
    link<reply, "p"> _reply;
  };
  
} // End namespace squeaker.

#endif
