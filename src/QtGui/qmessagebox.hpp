#ifndef QMESSAGEBOXWRAP_H
#define QMESSAGEBOXRAP_H
#include <QMessageBox>
#include <napi.h>
#include "qwidget.hpp"
#include "qwidget_macros.hpp"
#include "qpixmap.hpp"
#include <iostream>

QWIDGET_IMPL_DEF(QMessageBox)

#include "../utils/unwrapper.hpp"
class QMessageBoxWrap : public Napi::ObjectWrap<QMessageBoxWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  QMessageBoxWrap(const Napi::CallbackInfo &info);
  ~QMessageBoxWrap();

  QMessageBoxImpl *q_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value setText(const Napi::CallbackInfo &info);
  Napi::Value setInformativeText(const Napi::CallbackInfo &info);
  Napi::Value exec(const Napi::CallbackInfo &info);
  // QWidget Funcs
  QWIDGET_DEFS
};
#endif