#include "qmessagebox.hpp"

Napi::FunctionReference QMessageBoxWrap::constructor;

QWIDGET_IMPL_FUNCS(QMessageBox)

Napi::Object QMessageBoxWrap::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "QMessageBox", {
        InstanceMethod("exec", &QMessageBoxWrap::exec),
        InstanceMethod("setText", &QMessageBoxWrap::setText),
        InstanceMethod("setInformativeText", &QMessageBoxWrap::setInformativeText),
        QWIDGET_JS_DEFINES(QMessageBoxWrap)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("QMessageBox", func);
    return exports;
}

QMessageBoxWrap::QMessageBoxWrap(const Napi::CallbackInfo &info) : Napi::ObjectWrap<QMessageBoxWrap>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        QWidget *parent = unwrap(info[0]);
        q_ = new QMessageBoxImpl(parent, env);
    }
    else
    {
        QMessageBoxImpl *q_parent = 0;
        q_ = new QMessageBoxImpl(q_parent, env);
    }
    
}

QMessageBoxWrap::~QMessageBoxWrap()
{
    q_ = NULL;
}

Napi::Value QMessageBoxWrap::setText(const Napi::CallbackInfo &info)
{
    q_->setText(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}
Napi::Value QMessageBoxWrap::setInformativeText(const Napi::CallbackInfo &info)
{
    q_->setInformativeText(QString::fromStdString(info[0].ToString().Utf8Value()));
    return Napi::Value();
}

Napi::Value QMessageBoxWrap::exec(const Napi::CallbackInfo &info)
{
    q_->exec();
    return Napi::Value();
}

// QWidget functions
QWIDGET_BASE_FUNCS(QMessageBoxWrap)