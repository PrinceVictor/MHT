#include <iostream>
#include <memory>

#include "log/log.h"
#include "meas/measure.h"
#include "common/random.h"
#include "track/mht.h"

using mht_common::Random;
using mht_measurement::Measurement;
using mht_track::MHT;


int main(int argc, char *argv[]){

    FLAGS_log_dir = "./log";

    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::INFO);

    LOG_INFO("---RUNNING THE TRACKING TASK---");

    std::shared_ptr<Random> random = std::make_shared<Random>();
    
    std::shared_ptr<Measurement> measurement = std::make_shared<Measurement>("./param/meas.txt");
    measurement->set_random(random);

    google::ShutdownGoogleLogging();

    return 0;
}