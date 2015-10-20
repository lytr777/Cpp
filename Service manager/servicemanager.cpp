#include "servicemanager.h"

using namespace std;

service_manager::service_manager(std::shared_ptr<settings> const &settings) {

}

service_manager::~service_manager() {
    shutdown();
}

void service_manager::run_service(std::shared_ptr<service> const &) {

}

void start() {

}

void shutdown() {

}

void run_task(std::function<void()> const &task) {

}

void set_num_threads(size_t count) {

}

void save_config() {

}