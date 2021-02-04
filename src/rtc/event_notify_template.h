#ifndef LIB_EVENT_NOTIFY_TEMPLATE_H_
#define LIB_EVENT_NOTIFY_TEMPLATE_H_
#include <sstream>

#define NOTIFY_EVENT_HEADER                                                    \
  {                                                                            \
    Json::Value params;

#define EVENT_PARAM(name, value) params[name] = value;

#define NOTIFY_EVENT_END(name)                                                 \
  std::string json_params = params.toStyledString();                           \
  {                                                                            \
    common::AutoLock auto_lock(context_->safe());                              \
    if (context_->EventNotify()) {                                             \
      std::string event_name(name);                                            \
      context_->EventNotify()->OnEvent(                                        \
          event_name.c_str(), event_name.length(), json_params.c_str(),        \
          json_params.length());                                               \
    }                                                                          \
  }                                                                            \
  }

#define DEFINE_DISPATCH_METHOD(name, params, call_back)                        \
  {                                                                            \
    MethodHandler ptr = method_handler_map_[name];                             \
    (this->*ptr)(params, call_back);                                           \
  }

#endif // LIB_EVENT_NOTIFY_TEMPLATE_H_
