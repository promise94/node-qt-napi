
#ifndef QSCROLLAREAWRAP_H
#define QSCROLLAREAWRAP_H
#include <QScrollArea>
#include <napi.h>
#include <iostream>

#include <QWidget>
#include <QWheelEvent>
#include <QAbstractScrollArea>

#include "../utils/unwrapper.hpp"

#include <napi.h>
#include <iostream>
#include <QScrollArea>
#include <QWheelEvent>

class QScrollAreaImpl : public QScrollArea             
{                                                    
public:                                              
     QScrollAreaImpl(QWidget *parent, Napi::Env env);

     Napi::FunctionReference wheelEventCallback_;            
                                                       
     Napi::Env env;                                   
     bool closed = false;                             
                                                       
private:                                             
     void wheelEvent(QWheelEvent *e);                  
};


class QScrollAreaWrap : public Napi::ObjectWrap<QScrollAreaWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QScrollAreaWrap(const Napi::CallbackInfo &info);
  ~QScrollAreaWrap();

  QScrollAreaImpl *q_;

private:
  static Napi::FunctionReference constructor;
  Napi::Value setWidget(const Napi::CallbackInfo & info);
	Napi::Value setWidgetResizable(const Napi::CallbackInfo & info);
	Napi::Value setGeometry(const Napi::CallbackInfo & info);
	Napi::Value setViewport(const Napi::CallbackInfo & info);
	Napi::Value wheelEvent(const Napi::CallbackInfo & info);
  void wheelEvent(QWheelEvent *e);
};

#endif
     