#include <iostream>

#include "log/log.h"
#include "track/mht.h"

using mht_mht::MHT;

int main(int argc, char *argv[]){

    FLAGS_log_dir = "./log";

    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::INFO);

    LOG_INFO("---RUNNING THE TRACKING TASK---");

    google::ShutdownGoogleLogging();

    return 0;
}