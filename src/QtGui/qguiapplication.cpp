/*
 * @Author: lixiaowei
 * @Date: 2021-05-27 13:20:49
 * @LastEditors: lixiaowei
 * @LastEditTime: 2021-06-01 17:58:24
 * @Description: file content
 * @FilePath: /node-qt-napi/src/QtGui/qguiapplication.cpp
 */

#include "qguiapplication.hpp"

Napi::FunctionReference QGuiApplicationWrap::constructor;

Napi::Object QGuiApplicationWrap::Init(Napi::Env env, Napi::Object exports)
{
  Napi::HandleScope scope(env);
  // clang-format off
  Napi::Function func = DefineClass(env, "QGuiApplication", {
    InstanceMethod("screenshort", &QGuiApplicationWrap::screenshort)
  });
  // clang-format on

  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("QGuiApplication", func);
  return exports;
}

QGuiApplicationWrap::QGuiApplicationWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QGuiApplicationWrap>(info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  QGuiApplication *q_;
}

QGuiApplicationWrap::~QGuiApplicationWrap()
{
  // delete q_;
  q_ = NULL;
}

Napi::Value QGuiApplicationWrap::screenshort(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  QList<QScreen *> screenList = q_->screens();

  int size = screenList.size();

  Napi::Array list = Napi::Array::New(env, size);

  for (int i = 0; i < size; i++)
  {
    Napi::Object obj = Napi::Object::New(env);
    QScreen *screen = screenList.at(i);
    QRect rect = screen->geometry();
    obj.Set("name", screen->name().toStdString());
    obj.Set("serialNumber", screen->serialNumber().toStdString());
    obj.Set("x", rect.x());
    obj.Set("y", rect.y());
    obj.Set("width", rect.width());
    obj.Set("height", rect.height());

    // save to temp path
    QDir filePath(QDir::tempPath() + "/screenshot-temp");
    if (!filePath.exists())
    {
      filePath.mkpath(filePath.absolutePath());
    }

    QString filePathName = filePath.filePath("full-" + QDateTime::currentDateTime().toString("yyyy-MM-ddhh-mm-ss-zzz") + ".png");

    bool saveState = screen->grabWindow(0, rect.x(), rect.y(), rect.width(), rect.height()).save(filePathName, "PNG");
    if (!saveState)
    {
      obj.Set("status", Napi::Number::New(env, 0));
    }
    else
    {
      obj.Set("status", Napi::Number::New(env, 1));
    }

    obj.Set("tempPath", Napi::Value::From(env, filePathName.toStdString()));

    list.Set(uint32_t(i), obj);
  }
  return list;
}