#pragma once
#include "../config.h"


class DataReceiveThread : public QThread
{
    Q_OBJECT

signals:
    void cur_frame_data_signal(QJsonObject cur_frame_data);

public:
    DataReceiveThread();
    ~DataReceiveThread();
    void run();
};
