#pragma once
#include "../config.h"
// #include "../src/controller/app.h"
// #include "mainwindow.h"





// using json = nlohmann::json;

// void recv_data(std::queue<json> &queue_json);

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
