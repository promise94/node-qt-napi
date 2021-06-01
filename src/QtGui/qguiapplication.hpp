/*
 * @Author: lixiaowei
 * @Date: 2021-05-27 13:20:37
 * @LastEditors: lixiaowei
 * @LastEditTime: 2021-06-01 12:12:02
 * @Description: file content
 * @FilePath: /node-qt-napi/src/QtGui/qguiapplication.hpp
 */

#ifndef QGUIAPPLICATIONWRAP_H
#define QGUIAPPLICATIONWRAP_H

#include <QGuiApplication>
#include <napi.h>
#include <iostream>
#include <QDebug>
#include <QList>
#include <QScreen>
#include <QBuffer>
#include <QByteArray>
#include <QDir>
#include <QDateTime>

#include "../utils/unwrapper.hpp"

class QGuiApplicationWrap : public Napi::ObjectWrap<QGuiApplicationWrap>
{
public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  
  QGuiApplicationWrap(const Napi::CallbackInfo &info);
  ~QGuiApplicationWrap();

  QGuiApplication *q_;

private:
  static Napi::FunctionReference constructor;

  Napi::Value screenshort(const Napi::CallbackInfo &info);
};

#endif