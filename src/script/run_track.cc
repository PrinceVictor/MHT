#include <iostream>

#include "log/log.h"
#include "track/mht.h"
#include "meas/meas.h"

using mht_track::MHT;
using mht_measurement::Measurement;

int main(int argc, char *argv[]){

    FLAGS_log_dir = "./log";

    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::INFO);

    LOG_INFO("---RUNNING THE TRACKING TASK---");

    Measurement measurement("./param/meas.txt");

    google::ShutdownGoogleLogging();

    return 0;
}