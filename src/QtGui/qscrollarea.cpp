
#include "qscrollarea.hpp"

Napi::FunctionReference QScrollAreaWrap::constructor;

Napi::Object QScrollAreaWrap::Init(Napi::Env env, Napi::Object exports)
{
     Napi::HandleScope scope(env);
     // clang-format off
     Napi::Function func = DefineClass(env, "QScrollArea", {
          InstanceMethod("setWidget", &QScrollAreaWrap::setWidget),
	InstanceMethod("setWidgetResizable", &QScrollAreaWrap::setWidgetResizable),
	InstanceMethod("setGeometry", &QScrollAreaWrap::setGeometry),
	InstanceMethod("setViewport", &QScrollAreaWrap::setViewport),
	InstanceMethod("wheelEvent", &QScrollAreaWrap::wheelEvent)
     });
     // clang-format on

     constructor = Napi::Persistent(func);
     constructor.SuppressDestruct();

     exports.Set("QScrollArea", func);
     return exports;
}

QScrollAreaWrap::QScrollAreaWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QScrollAreaWrap>(info)
{
     Napi::Env env = info.Env();
     Napi::HandleScope scope(env);
     if (info.Length() > 0)
     {
          QWidget *parent = unwrap(info[0]);
          q_ = new QScrollAreaImpl(parent, env);
     } else {
          q_ = new QScrollAreaImpl(0, env);
     }
     
}

QScrollAreaWrap::~QScrollAreaWrap()
{
     q_ = NULL;
}


// Implementation

Napi::Value QScrollAreaWrap::setWidget(const Napi::CallbackInfo &info)
{
     
     QWidget* p0 = Napi::ObjectWrap<QWidgetWrap>::Unwrap(info[0].ToObject())->q_;
     
     q_->setWidget(p0);
     return Napi::Value();
}
	
Napi::Value QScrollAreaWrap::setWidgetResizable(const Napi::CallbackInfo &info)
{
     
     bool p0 = info[0].ToBoolean().Value();
     
     q_->setWidgetResizable(p0);
     return Napi::Value();
}
	
Napi::Value QScrollAreaWrap::setGeometry(const Napi::CallbackInfo &info)
{
     
     if(info.Length() != 4) {
          Napi::TypeError::New(info.Env(), "Wrong number of arguments")
               .ThrowAsJavaScriptException();
     }
     
     int p0 = (int) info[0].ToNumber().Int64Value();
	int p1 = (int) info[1].ToNumber().Int64Value();
	int p2 = (int) info[2].ToNumber().Int64Value();
	int p3 = (int) info[3].ToNumber().Int64Value();
     
     q_->setGeometry(p0, p1, p2, p3);
     return Napi::Value();
}
	
Napi::Value QScrollAreaWrap::setViewport(const Napi::CallbackInfo &info)
{
     
     QWidget* p0 = Napi::ObjectWrap<QWidgetWrap>::Unwrap(info[0].ToObject())->q_;
     
     q_->setViewport(p0);
     return Napi::Value();
}

Napi::Value QScrollAreaWrap::wheelEvent(const Napi::CallbackInfo &info)                
{                                                                                 
    Napi::Env env = info.Env();                                                   
    Napi::HandleScope scope(env);                                                 
                                                                                  
    q_->wheelEventCallback_ = Napi::Persistent(info[0].As<Napi::Function>());         
                                                                                  
    return Napi::Value();                                                         
}  

// QScrollAreaImpl

QScrollAreaImpl::QScrollAreaImpl(QWidget *parent, Napi::Env env) : QScrollArea(parent), env(env) 
{                                                                                              
}


void QScrollAreaImpl::wheelEvent(QWheelEvent *e)                                             
{                                                                                              
     if (wheelEventCallback_.IsEmpty())                                                             
          return;                                                                                
                                                                                               
     wheelEventCallback_.Call({
          Napi::Number::New(env, e->angleDelta().x()),
		Napi::Number::New(env, e->angleDelta().y()),
		Napi::Number::New(env, e->angleDelta().rx()),
		Napi::Number::New(env, e->angleDelta().ry()),
		Napi::Boolean::New(env, e->inverted())
     });                        
}



