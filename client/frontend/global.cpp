#include "global.h"

QString gate_url_prefix = "";

std::function<void(QWidget*)> repolish =[](QWidget *w){
    w->style()->unpolish(w);
    w->style()->polish(w);
};

std::function<QString(QString)> xorString = [] (QString input) {
    QString result = input;
    int length = input.length();
    length = length % 255;
    for (int i = 0; i < length; ++i) {
        // 对每个字符进行异或处理
        result[i] = QChar(static_cast<ushort>(input[i].unicode() ^ static_cast<ushort>(length)));
    }
    return result;
};
