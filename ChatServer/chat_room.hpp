#include <boost/foreach.hpp>
#include "chat_message.hpp"

typedef std::deque<chat_message> chat_message_queue;

class chat_participant
{
public:
  virtual ~chat_participant() {};
  virtual void deliver(const chat_message& msg) {};
};


typedef boost::shared_ptr<chat_participant> chat_participant_ptr;

class chat_room
{
public:

  void join(chat_participant_ptr participant)
  {
    participants_.insert(participant);
    BOOST_FOREACH(chat_message msg, recent_msgs_)
    {
    	participant->deliver(msg);
    }
  }

  void leave(chat_participant_ptr participant)
  {
    participants_.erase(participant);
  }

  void deliver(const chat_message& msg)
  {
    recent_msgs_.push_back(msg);
    while (recent_msgs_.size() > max_recent_msgs)
      recent_msgs_.pop_front();

    BOOST_FOREACH(chat_participant_ptr participant, participants_)
    {
    	participant->deliver(msg);
    }
  }

private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs = 100 };
  chat_message_queue recent_msgs_;
};

