#include <iostream>
#include <memory>

#include "log/log.h"
#include "meas/measure.h"
#include "common/random.h"
#include "tracker/mht.h"

using mht_common::Random;
using mht_measurement::Measurement;
using mht_tracker::MHT;

int main(int argc, char *argv[]){

    FLAGS_log_dir = "./log";

    google::InitGoogleLogging(argv[0]);
    google::SetStderrLogging(google::INFO);

    LOG_INFO("---RUNNING THE TRACKING TASK---");

    std::shared_ptr<Measurement> measurement = std::make_shared<Measurement>("./param/PARAMS.txt");
    std::shared_ptr<MHT> MHT_tracker = std::make_shared<MHT>("./param/PARAMS.txt");

    auto measures = measurement->get_measurements();

    // MHT_tracker->test();

    for(auto it=measures.begin(); it!=measures.end(); it++){

        auto t_now = it->first;
        auto& meas = it->second;
        
        MHT_tracker->run(t_now, meas);
    }

    google::ShutdownGoogleLogging();

    return 0;
}